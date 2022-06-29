#include "threadpool.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> // Für Threads

#include "array.h"

#define true 1
#define false 0

typedef struct node node;
typedef struct stackNode stackNode;

static inline void error (const char *msg){
	perror(msg);
	exit(-1);
}

typedef struct stack{
	stackNode* top;
}stack;

typedef struct ThreadPool {
	/* TODO: benötigte Attribute hinzufügen */
	ThreadTask_f fn;
	pthread_t* threads_arr; //speichert ganz normale pthreads, keine pthreads ptr
	int result;
	stack* t_stack;
	int t_size;
	int running;

} ThreadPool;

typedef struct node {
	Future* fn;
	node *next;
}node;

typedef struct que {
	node* first;
	node* last;
}que;

typedef struct stackNode{
	Future* fnStack;
	stackNode * prev;
}stackNode;



ThreadPool t_pool;
//könnte auch in threadpool struct verschoben werden
que work_que;
//TODO: Müssen die mutexe nochmal initialisiert werden? Dann in tpInit
pthread_mutex_t que_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t que_notify;
Future** function_call_stack; //nimmt future*
pthread_mutex_t function_call_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t function_call_notify;

struct que* init_que (){
	que* q = (que *)malloc(sizeof(que));
	q->first = NULL;
	q->last = NULL;

	return q;
}

void enque(struct que* q, Future* fn){
	node* Task = malloc(sizeof(node));

	Task->fn = fn;
	Task->next = NULL;
	if (q->first == NULL && q->last == NULL){
		q->first = Task;
		q->last = Task;
	}else{
		q->last->next = Task;
		q->last = Task;
	}
}

int is_que_empty (struct que* q){
	if(q->first == NULL && q->last == NULL){
		return true;
	}else{
		return false;
	}
}

 Future* deque(struct que* q){
	if(is_que_empty(&work_que)){
		printf("Nothing to dequeue");
		return NULL;
	}
	node* Task = q->first;
	if(q->first==q->last){
	q->first=NULL;
	q->last=NULL;	
	}else{
	q->first = Task->next;
	}


	//can do something with task
	return Task->fn;
}

struct stack* init_stack(){
	stack* newStack = (stack*)malloc(sizeof(stack));
	newStack->top = NULL;
	return newStack;
}

void stackPush(struct stack* s, Future* fn){
	stackNode* sNode = (stackNode*)malloc(sizeof(stackNode));
	sNode->fnStack=fn;
	if(s->top == NULL){
		sNode->prev=NULL;
		s->top = sNode;
		
	}else{
		sNode->prev = s->top;
		s->top = sNode;
	}
}

struct stackNode* stackTop(struct stack* s){
	return s->top;
}

struct stackNode* stackPop(struct stack* s){
	if(s->top == NULL){
		return NULL;
	}else{
		stackNode* tmp = s->top;
		s->top = s->top->prev;
		return tmp;
	}
}


int same_future(Future* fut1, Future* fut2){
	if(fut1==fut2){
		return true;
	}else{
		return false;
	}
}

int get_index_pthread(pthread_t thread){
	
	for(int i=0; i<t_pool.t_size;i++){
		if(pthread_equal(thread,t_pool.threads_arr[i])){
			return i;
		}
	}
	//thread == parent_thread, was müssen wir machen
	return t_pool.t_size;

}
/* TODO: interne, globale Variablen hinzufügen */





/* TODO: interne Hilfsfunktionen hinzufügen */
static void* start_thread(void* arg){
	//TODO: implement start routine


	//Implement "shutdown"
	while(t_pool.running == true){
		here:
		//kritischer bereich
		pthread_mutex_lock(&que_mutex);

		while (is_que_empty(&work_que))
		{
			pthread_cond_wait(&que_notify ,&que_mutex);
		}
		//printf("Thread %d is out\n",(int)pthread_self());
		Future* future;
		if(!is_que_empty(&work_que)){
		
			/* code */
			future = deque(&work_que);
			if(future == NULL||future->fn==NULL){
				//sched_yield();
				goto here;
			}
		} 
		
		
		//printf("have deque\n");
		pthread_mutex_unlock(&que_mutex);
		//printf("mutex released\n");
		//ende kritischer bereich
		pthread_cond_signal(&que_notify);
		//Do the dirty work
		//((*future).fn)((*future).arg);	
		(future->fn)(future);
		future->done = true;
		//printf("fib %d done with value %d\n",future->arg,future->res);
		pthread_mutex_lock(&que_mutex);
		pthread_cond_signal(&que_notify);
		pthread_mutex_unlock(&que_mutex);
		//sched_yield();
		pthread_cond_signal(&que_notify);
	}

	//Was machen bei mehr task als threads -> threads muss sich die nächste task nehmen um weiterzukommen, 
	//das soll durch einne gemeinsamem Stack gelöst werden
	//sched_yield() vllt. interessant

	//es muss immer weiter gerechnet werden mit neuen tasks
	// -> wenn man auf await in task trifft nimmt man sich der thread neue task aus der que
}


int tpInit(size_t size) {
	t_pool.threads_arr= (pthread_t *)malloc(sizeof(pthread_t)*size);
	t_pool.t_size=size;
	//pthread_t threads[size];
	int ret_pthread;
	for(int i = 0; i<(int)size; i++){
		ret_pthread = pthread_create(&(t_pool.threads_arr[i]), NULL, &start_thread, NULL);
		if (ret_pthread!=0){
			error("Fehler bei Erstellung von Thread");
		}
	}

	//pthread_t* threads_arr;
	//t_pool.threads_arr = threads_arr;
	//arrayInit(t_pool.threads_arr);
	// // for(int i = 0; i<(int)size; i++){
	// // 	//threads oder &threads?
	// // 	arrayPush(t_pool.threads_arr) = threads[i];
	// // }

	work_que = *(init_que());
	//arrayInit(function_call_stack);
	pthread_cond_init(&que_notify, NULL);
	//TODO: Wie viele Sterne?
	//Future **stacks[size+1];
	stack stacks[size+1];
	t_pool.t_stack=stacks;
	t_pool.running=true;
	for(int i=0; i<(int)size+1; i++){
		t_pool.t_stack = init_stack();
	}
	

	return 0;
}

void tpRelease(void) {
	t_pool.running=false;
	for(int i = 0; i<t_pool.t_size; i++){
		pthread_cancel(t_pool.threads_arr[i]);
		pthread_join(t_pool.threads_arr[i],NULL);
		
	}
	printf("JOin hat funktioniert\n");
	pthread_mutex_destroy(&que_mutex);
	printf("DEstroy hat funktioniert\n");
	exit(-1);
}

void tpAsync(Future *future) {
	pthread_t work_thread;
	/*if (!arrayIsEmpty(t_pool.threads_arr)){
		work_thread = arrayPop(t_pool.threads_arr);
	}*/
	if(future->fn == NULL){
		printf("Future has No Task\n");
		exit(-1);
	}
	pthread_mutex_lock(&que_mutex);
	enque(&work_que, future);
	pthread_mutex_unlock(&que_mutex);

	//hier muss ein signal an die wartenden threads geschickt werden, das ein neuer task verfügbar ist ->
	//pthread_mutex_lock(&que_mutex);
	pthread_cond_signal(&que_notify);
	//pthread_mutex_unlock(&que_mutex);

}

void tpAwait(Future *future) {
	if(future->done != 0){
		return NULL;
	}
	pthread_t tmp_thread = pthread_self();
	int index_thread = get_index_pthread(tmp_thread);
	//pthread_mutex_lock(&function_call_mutex);
	stackPush(&(t_pool.t_stack[index_thread]),future);
	//printf("fib(%d) stacked in Stack %d\n",future->arg,index_thread);
	//pthread_cond_signal(&function_call_notify);
	// pthread_mutex_unlock(&function_call_mutex);
	//wenn thread auf await stößt und noch keine ergebnisse von seinen async rufen hat ->
	//muss er sich einen neuen task aus der que holen!
	Future* LocalFuture = future; // wann die fertig ist
	pthread_cond_signal(&que_notify);

	
	//pthread_mutex_lock(&function_call_mutex);
	if(stackTop(&(t_pool.t_stack[index_thread]))!= NULL){
		pthread_mutex_lock(&que_mutex);
		if(is_que_empty(&work_que) && stackTop(&(t_pool.t_stack[index_thread]))->fnStack->done == false){
			pthread_cond_wait(&que_notify,&que_mutex);//überprüfe ob Signal richtig ist
		}
	}else{ //es gibt noch nichts in dem Stack
		pthread_mutex_lock(&que_mutex);
		if(is_que_empty(&work_que)){
			pthread_cond_wait(&que_notify,&que_mutex);
		}
	}
	pthread_mutex_unlock(&que_mutex);
	//pthread_mutex_unlock(&function_call_mutex);
	//pthread_mutex_lock(&function_call_mutex);
	Future* fut_temp = stackTop(&(t_pool.t_stack[index_thread]))->fnStack;
	
	if(fut_temp != NULL&& fut_temp->done != NULL){
	if(!same_future(LocalFuture,fut_temp)&& fut_temp->done==true){
		
		//pthread_mutex_unlock(&function_call_mutex);
		//sched_yield();

	}else if(fut_temp->done==true && same_future(LocalFuture,fut_temp)){
		stackNode* temp = stackPop(&(t_pool.t_stack[index_thread]));
		//printf("fib(%d) von Stack %d done mit Result=%d",temp->fnStack->arg,index_thread,temp->fnStack->res);
		pthread_cond_signal(&que_notify);
		//sched_yield();
		return;
		}
	}
	
	pthread_mutex_lock(&que_mutex);
	if(!is_que_empty(&work_que)){
		do
		{
			/* code */
			Future* future = deque(&work_que);
		} while (future == NULL||future->fn == NULL);
		
		
		
		pthread_mutex_unlock(&que_mutex);
		//ende kritischer bereich

		//Do the dirty work
		//((*future).fn)((*future).arg);	
		(future->fn)(future);
		future->done = true;
		//printf("fib %d done with value %d\n",future->arg,future->res);
		//pthread_mutex_lock(&que_mutex);
		pthread_cond_signal(&que_notify);
		//pthread_mutex_unlock(&que_mutex);
		// if(fut_temp->done==true && same_future(LocalFuture,fut_temp)){
		// stackNode* temp = stackPop(&(t_pool.t_stack[index_thread]));
		// printf("fib(%d) von Stack %d done mit Result=%d",temp->fnStack->arg,index_thread,temp->fnStack->res);
		// sched_yield();
		// return;
		// }
		//sched_yield();

	}

}