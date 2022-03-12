#define _CRT_SECURE_NO_WARNINGS
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct element element;
typedef struct element
{
	char* name;
	int value;
	element** neighbor;
	int numberofneighbor;
	element* naechsteElement; //fuer Zugriff auf die Elemente in elementlist
	element* naechsteinput; //fuer Zugriff auf die Elemente in inputlist
	_Bool sorted;

}element;

typedef struct elementlist //eine Link List von Elementen/ Knoten
{
	element* firstElement;
	element* letzteElement;
	element* aktuellElement; //ueberfluessig
	long zaehler;
} elementlist;

typedef struct mauszeiger 
{
	element* aktuellelement;
	long schritte;
}mauszeiger;
void insertnextinput(elementlist* elementliste, element* element) //neue Zielelemente (z.B a:b,c , a ist das Zielelement) in die Inputlist hinzufuegen
{
	element->naechsteinput = NULL;
	if (elementliste->firstElement == NULL)
	{
		elementliste->firstElement = element;
		elementliste->letzteElement = element;
	}
	else
	{
		elementliste->letzteElement->naechsteinput = element;
		elementliste->letzteElement = elementliste->letzteElement->naechsteinput;
	}
}

void printneighbor(element* elementzeiger)//nachbar eines Knotens ausgeben, nur zum pruefen
{
	int i = 0;
	if (elementzeiger->numberofneighbor != 0)
	{
		while (elementzeiger->neighbor[i] != NULL && i < elementzeiger->numberofneighbor)
		{
			printf("neighbors %d: %s\n", i + 1, elementzeiger->neighbor[i]->name);
			i++;
		}
	}
	else
	{
		printf("no neighbor\n");
	}
}
void printlist(elementlist* elementliste) // alle Elemente in einem Linked List ausgeben, nur zum pruefen
{
	element* elementzeiger = elementliste->firstElement;
	int index = 1;
	while (elementzeiger != NULL)
	{
		if (elementzeiger->value >= 0)
		{
			printf("name:%20s value:%d\n", elementzeiger->name, elementzeiger->value);
		}
		else
		{
			printf("name:%20s value:NULL\n", elementzeiger->name);
		}
		printneighbor(elementzeiger);
		elementzeiger = elementzeiger->naechsteElement;
		index++;
	}
}


void freelist(elementlist* elementliste) // free alle Elemente in einem Linked List
{
	element* elementzeiger = elementliste->firstElement;

	while (elementzeiger != NULL)
	{	
		element* temp = elementzeiger;
		elementzeiger = elementzeiger->naechsteElement;
		free(temp->name);
		free(temp->neighbor);
		free(temp);

	}
}

void printlistfinal(elementlist* elementliste) // Ergebnis ausgeben
{
	element* elementzeiger = elementliste->firstElement;
	int index = 1;
	while (elementzeiger != NULL)
	{
		if (elementzeiger->value >= 0)
		{
			printf("%s:%d\n", elementzeiger->name, elementzeiger->value);
		}
		else
		{
			printf("Eines des Werts ist negativ");
		}
		elementzeiger = elementzeiger->naechsteElement;
		index++;
	}
}
void insertelement(elementlist* elementliste, element* element) // elements in Elementlist einfuegen
{
	element->naechsteElement = NULL;
	if (elementliste->firstElement == NULL)
	{
		elementliste->firstElement = element;
		elementliste->letzteElement = element;
	}
	else
	{
		elementliste->letzteElement->naechsteElement = element;
		elementliste->letzteElement = elementliste->letzteElement->naechsteElement;
	}
}


element* suchenelement(elementlist* elementliste, char* name) //suche Element im Elementlist
{
	element* elementzeiger = elementliste->firstElement;
	while (elementzeiger != NULL)
	{
		/*	for (size_t i = 0; i < (elementzeiger->numberofneighbor)+1; i++)
			{
				if (strcmp(elementzeiger->neighbor[i].name, name) == 0) {
					return &elementzeiger->neighbor[i];
				}
			}*/
		if (strcmp(elementzeiger->name, name) == 0)
		{
			return elementzeiger;
		}
		else
		{
			elementzeiger = elementzeiger->naechsteElement;
		}
	}
	return NULL;

}
element* sucheninputs(elementlist* elementliste, char* name) //suche Element im Inputlist
{
	element* elementzeiger = elementliste->firstElement;
	while (elementzeiger != NULL)
	{
		if (strcmp(elementzeiger->name, name) == 0)
		{
			return elementzeiger;
		}
		else
		{
			elementzeiger = elementzeiger->naechsteinput;
		}
	}
	return NULL;

}
int determinestart(mauszeiger* mauszeiger, char* name, elementlist* elementliste) // das Anfangsknoten von dem Maus festlegen
{
	mauszeiger->aktuellelement = suchenelement(elementliste, name);
	if (mauszeiger->aktuellelement == NULL) { // Element nicht gefunden
		printf("Noch keine Elemente, Anfangsknot nicht definiert");
		return -1;
	}
	return 1;
	//printf("Startelement: %s\n", mauszeiger->aktuellelement->name);
}

int determinesteps(mauszeiger* mauszeiger, char* num) // die Anzahl der Schritte festlegen
{
	mauszeiger->schritte = atol(num);
	if (mauszeiger->schritte > (long long)(pow(2, 32)))
	{
		printf("Zu viele Schritte");
		return -1;
	}
	return 1;
	//printf("number of steps:%d\n",mauszeiger->schritte);
}

void putneighbor(element* e, element* eneighbor) //das Nachbarknoten eines Knotens in Array List von Nachbarn von Knoten e einfuegen
{
	if (eneighbor != NULL) {
		if (e->numberofneighbor == 0) // neighbor ist 0, noch kein Nachbar
		{
			e->neighbor = malloc(sizeof(e->neighbor));
			e->neighbor[0] = eneighbor;
			e->numberofneighbor++;
		}
		else// there is already neighbor/ es gibt schon nachbar
		{
			e->neighbor = realloc(e->neighbor, sizeof(element*) * ((e->numberofneighbor) + 1));
			e->neighbor[e->numberofneighbor] = eneighbor;
			if (e->neighbor == NULL)
			{
				free(e->neighbor);
				printf("realloc fail"); //nur zum pruefen
			}
			e->numberofneighbor++;
		}
	}
}
int makeneighbor(elementlist* elementliste, char* token2, element* e) // nachbar des Knotens e aktualisieren oder neu konstruieren
{
	element* eneighbor;
	if (suchenelement(elementliste, token2) != NULL)//neighbor is old/ alte Nachbar, die Dateien des Nachbars aktualisieren
	{
		eneighbor = suchenelement(elementliste, token2);
		for (int i = 0; i < eneighbor->numberofneighbor; i++)
		{
			if (strcmp(e->name, eneighbor->neighbor[i]->name) == 0)
			{
				printf("Mehrere Kante");
				return -1;

			}
		}
		eneighbor->neighbor = realloc(eneighbor->neighbor, sizeof(eneighbor->neighbor) * ((eneighbor->numberofneighbor) + 1));
		eneighbor->neighbor[eneighbor->numberofneighbor] = e; // Nachbar des Nachbars ist der Knoten e
		if (eneighbor->neighbor == NULL)
		{
			free(eneighbor->neighbor); // ueberfluessig
		}
		eneighbor->numberofneighbor++;
		

	}
	else // neighbor is new/ neue Nachbar konstruieren
	{
		eneighbor = (element*)calloc(1, sizeof(element));// calloc benutzen, um "jump using uninitialised Values" zu verhindern (valgrind)
		eneighbor->value = 0;
		eneighbor->name = malloc(strlen(token2)+1);
		strcpy(eneighbor->name, token2);
		insertelement(elementliste, eneighbor);
		elementliste->zaehler++;
		eneighbor->neighbor = (element**)malloc(sizeof(element*));
		eneighbor->neighbor[0] = e; //Nachbar des Nachbars ist der Knoten e
		eneighbor->numberofneighbor = 1;
	}

	putneighbor(e, eneighbor);
	return 1;
}

int seperatestring(char* in, char* temp, elementlist* elementliste, elementlist* inputlist, mauszeiger* mauszeiger) // die Eingabe zerlegen
{
	//initialise
	element* e;
	char* token;
	//char* temp= malloc(strlen(in)+1);
	/*strcpy(temp, in);*/


	//getname of element/ name von Element holen
	token = strtok(in, ":");
	if (sucheninputs(inputlist, token) != NULL)
	{
		printf("Element schon vorhanden");
		return -1;
	}
	if (strcmp(token, "A") == 0) // wenn A (Anfangsknoten) in der Eingabe auftaucht
	{
		token = strtok(NULL, "\0");
		int detStart= determinestart(mauszeiger, token, elementliste);
		if (detStart == -1)
		{
			printf("determine Start fehlgeschlagen");
			
			return -1;
		}
		
		return 1;
	}
	else if (strcmp(token, "I") == 0)// wenn I (Anzahl Schritte) in der Eingabe auftaucht
	{
		token = strtok(NULL, "\0");
		int detSteps=determinesteps(mauszeiger, token);
		if (detSteps == -1)
		{
			printf("determine Steps fehlgeschlagen");
			
			return -1;
		}
		
		return 1;
	}
	if (suchenelement(elementliste, token) != NULL) { // wenn das Element vorher als Nachbar eines Elements konstruiert war
		if (sucheninputs(inputlist, token) != NULL)
		{
			printf("Knoten war vorher als Eingabe definiert");
			
			return -1; // Element war vorher als Eingabe schon vorhanden
		}
			
		e = suchenelement(elementliste, token);

	}
	else
	{
		//element is new
		e = (element*)calloc(1, sizeof(element));
		e->value = 0;
		e->name = malloc( strlen(token) + 1);
		strcpy(e->name, token);

		insertelement(elementliste, e);
		elementliste->zaehler++;
		insertnextinput(inputlist, e);
		e->numberofneighbor = 0;
	}

	//	e->printneighbors = printneighbor;
	char* Knotenname = token; // Zeiger auf Knotenname beibehalten
		//get all neighbors/ Nachbars lesen
	token = strtok(NULL, "-");

	char* neighbortemp = token;
	/*char* neighbortemp = malloc(strlen(token)+1);
	strcpy(neighbortemp, token);*/

	token = strtok(temp, "-");
	token = strtok(NULL, "\0"); // Wert des Knotens lesen
	if (token != NULL)
	{
		long long wert = strtoll(token, (char**)NULL, 10);
		if (wert > (pow(2,32)-1))
		{
			printf("Wert ist groesser als 2^32-1");
			return -1;
		}
		e->value = atoi(token);
	}

	else if (token == NULL)
	{

		token = strtok(neighbortemp, ",");// getname first neighbor

		if (strcmp(token,Knotenname)==0)
		{
			printf("Knot kann nicht mit sich selbst verbunden sein\n");
			return -1;
		}

		int makeN=makeneighbor(elementliste, token, e);
		if (makeN == -1)
		{
			return -1;
		}

		while (token != NULL)
		{
			token = strtok(NULL, ",");
			if (token == NULL) break;
			if (strcmp(token, Knotenname) == 0)
			{
				printf("Knot kann nicht mit sich selbst verbunden sein\n");
				return -1;
			}
			int makeN = makeneighbor(elementliste, token, e);
			if (makeN == -1)
			{
				return -1;
			}
		}

		return 1;

	}
	if (!(strcmp(neighbortemp, token) == 0))//token is the value, meisten Fall ist die Bedingung erfuellt, so neighbortemp enthaelt das String alle Nachbars, token enthaelt das String des Werts
	{

		token = strtok(neighbortemp, ",");// getname first neighbor

		if (strcmp(token, Knotenname) == 0)
		{
			printf("Knot kann nicht mit sich selbst verbunden sein\n");
			return -1;
		}


		int makeN = makeneighbor(elementliste, token, e);
		if (makeN == -1)
		{
			return -1;
		}

		while (token != NULL)
		{
			token = strtok(NULL, ",");
			if (token == NULL) break;
			if (strcmp(token, Knotenname) == 0)
			{
				printf("Knot kann nicht mit sich selbst verbunden sein\n");
				return -1;
			}
			int makeN = makeneighbor(elementliste, token, e);
			if (makeN == -1)
			{
				return -1;
			}
		}

	}

	/*free(in);
	free(temp);
	temp=NULL;*/
	/*free(neighbortemp);*/
	return 1;
}



int checkstring(char* in, char* copy, char* copy2, mauszeiger* mauszeiger)
{
	char* token;
	/*char* copy = (char*)malloc( strlen(in) + 1);
	strcpy(copy, in);*/

	if ((mauszeiger->aktuellelement) != NULL) // Anfangsknoten schon vorhanden, dann muss naechste Eingabe I ( Anzahl Schritte) sein
	{
		if (in[0] == 'I')
		{
			if (in[1] != ':')
			{
				printf("kein Colon\n");

				return -1;
			}

			token = strtok(copy, ":");
			token = strtok(NULL, "\0");
			for (size_t i = 0; i < strlen(token); i++)
			{
				if (!(token[i] >= '0' && token[i] <= '9'))
				{
					printf("Bitte nur digit");
					return -1;
				}
			}
			//printf("Success\n");
			return 1;
		}
		else
		{
			printf("Nach A soll I kommen\n");
			return -1;
		}
	}
	if (in[0] == 'A')
	{
		if (in[1] != ':')
		{
			printf("kein Colon\n");
			return -1;
		}

		token = strtok(copy, ":");
		token = strtok(NULL, "\0");
		for (size_t i = 0; i < strlen(token); i++)
		{
			if (!((token[i] >= 'a' && token[i] <= 'z') || (token[i] >= '0' && token[i] <= '9')))
			{
				printf("Ungueltige Knotenname");
				return -1;
			}
		}
		//printf("Success\n");
		return 1;
	}
	/*free(copy);*/

	if (!(((in[0] >= 'a') && (in[0] <= 'z')) || ((in[0] >= '0') && (in[0] <= '9'))))
	{
		printf("erste zeichen fehler\n");
		return -1;
	}

	/*copy= (char*)malloc(strlen(in)+1);
	strcpy(copy, in);*/

	token = strtok(copy2, ":"); //Name des Knotens


	//printf("token:%s\n", token);
	if (strcmp(token, in) == 0)
	{
		printf("keine colon\n");
		return -1;
	}
	else
	{
		//printf("sizeoftoken:%d", strlen(token));
		int tokensize = strlen(token);
		for (int j = 0; j < (tokensize); j++)
		{
			if (!(((in[j] >= '0') && (in[j] <= '9')) || ((in[j] >= 'a') && (in[j] <= 'z'))))
			{
				printf("ungultige zeichen vor Colon\n");
				return -1;
			}
		}
	}


	char* neighbortemp;
	neighbortemp = strtok(NULL, "-"); // alle Nachbarn lesen
	token = strtok(NULL, "\0"); // den Wert lesen
	if (neighbortemp == NULL && token == NULL) // nur Knotenname steht, Weder Nachbar noch Wert
	{
		printf("Nur Knotenname steht");
		return -1;
	}
	if (neighbortemp != NULL)
	{
		int tempsize = strlen(neighbortemp);

		if (!(((neighbortemp[0] >= 'a') && (neighbortemp[0] <= 'z')) || ((neighbortemp[0] >= '0') && (neighbortemp[0] <= '9'))))
		{
			printf("after colon wrong input\n");
			return -1;
		}
		for (int i = 0; i < tempsize - 1; i++)
		{
			if (((neighbortemp[i] >= 'a') && (neighbortemp[i] <= 'z')) || ((neighbortemp[i] >= '0') && (neighbortemp[i] <= '9')))
			{
				if (!(((neighbortemp[i + 1] >= 'a') && (neighbortemp[i + 1] <= 'z')) || ((neighbortemp[i + 1] >= '0') && (neighbortemp[i + 1] <= '9')) || (neighbortemp[i + 1] == ',')))
				{
					printf("after colon digit wrong input\n");
					return -1;
				}
			}
			if (neighbortemp[i] == ',')
			{
				if (!(((neighbortemp[i + 1] >= 'a') && (neighbortemp[i + 1] <= 'z')) || ((neighbortemp[i + 1] >= '0') && (neighbortemp[i + 1] <= '9'))))
				{
					printf("after colon comma wrong input\n");
					return -1;
				}
			}
			
		}
	}
	if (token == NULL)
	{
		int inlen = strlen(in);
		if (in[inlen - 1] == '-')
		{
			printf("keinen Wert nach strich\n");
			return -1;
		}
	}

	if (token != NULL)
	{
		int valuesize = strlen(token);
		for (int i = 0; i < valuesize; i++)
		{
			if (!((token[i] >= '0') && (token[i] <= '9')))
			{
				printf("ungueltiger Wert nach strich\n");
				return -1;
			}
		}
	}
	//printf("success\n");

	/*free(copy);*/
	/*free(token);*/
	return 1;
}

int compare(char* e1Name, char* e2Name) { // Lexikographisch Vergleich fuer Quicksort
	int e1Count = strlen(e1Name);
	int e2Count = strlen(e2Name);
	int i = 0;
	while (i <= e1Count && i <= e2Count) {
		if (e1Name[i] < e2Name[i]) {
			return -1;
		}
		else if (e1Name[i] > e2Name[i]) {
			return 1;
		}
		else {
			i++;
		}
	}
	if (e1Count < e2Count) {
		return -1;
	}
	else if (e1Count > e2Count) {
		return 1;
	}
	else {
		return-1;
	}

}

void quick_sort(element** neighborsList, int links, int rechts)
{
	int pivot, i, j;
	element* t;
	if (links < rechts)
	{
		pivot = links;
		i = links + 1;
		j = rechts;
		for (;;)
		{


			while (i < rechts + 1 && (compare(neighborsList[i]->name, neighborsList[pivot]->name) == -1))
			{
				i++;
			}


			while (j > links && (compare(neighborsList[j]->name, neighborsList[pivot]->name) == 1))
			{
				j--;
			}


			if (i >= j) break;


			t = neighborsList[i];
			neighborsList[i] = neighborsList[j];
			neighborsList[j] = t;
		}




		t = neighborsList[j];
		neighborsList[j] = neighborsList[links];
		neighborsList[links] = t;

		quick_sort(neighborsList, links, j - 1); // linke Seite sortieren
		quick_sort(neighborsList, j + 1, rechts); // rechte Seite sortieren
	}
}
void move(mauszeiger* maus,elementlist* elementenliste) { // maus bewegen 
	if (elementenliste->zaehler > 1)
	{
		while (maus->schritte != 0)
		{
			if (maus->aktuellelement->sorted != 1) {
				quick_sort(maus->aktuellelement->neighbor, 0, (maus->aktuellelement->numberofneighbor) - 1);
				maus->aktuellelement->sorted = 1;
			}

			int moveNeighbor = maus->aktuellelement->value % maus->aktuellelement->numberofneighbor;
			maus->aktuellelement->value++;
			maus->aktuellelement = maus->aktuellelement->neighbor[moveNeighbor];
			maus->schritte--;

		}
	}
	else if (elementenliste->zaehler == 1)
	{
		while (maus->schritte != 0)
		{
			maus->aktuellelement->value++;
			maus->schritte--;
		}
	}
	
}

char* inputstring() // dynamisch Speicher allokieren fuer Eingabestring
{
	int strLen = 1;
	char ch;
	char* str = (char*)malloc(sizeof(char*) * strLen);
	int counter = 0;
	//printf("str_pre=:%d\n",str);//View pointer str address


	do
	{
		ch = getchar();
		if (ch == EOF && counter == 0)
		{
			printf("Eingabe Leer");
			free(str);
			return ".";
		}
		counter++;
		if (counter >= strLen)
		{
			str = (char*)realloc(str, sizeof(char*) * (++strLen));
		}
		str[counter - 1] = ch;
	} while (ch != '\n'&& ch != '\0'&& ch!= EOF);
	//printf("str_lat=:%d\n",str);//View the pointer str address after using realloc
	str[counter - 1] = '\0';
	return str;

}

int main()
{
	/*int comp=compare("a55", "b7");
	printf("%d", comp);*/
	elementlist elementliste; // Linked List fuer alle Elemente
	elementlist inputlist; // Linked List nur fuer alle Ziel Elemente
	mauszeiger mauszeiger1 = { NULL,-1 }; //mauszeiger initialisieren
	elementliste.firstElement = elementliste.letzteElement = NULL;
	inputlist.firstElement = inputlist.letzteElement = NULL;
	elementliste.zaehler = 0;

	while (mauszeiger1.schritte < 0) { // solange Anfangsknoten noch nicht initialisiert
		char* temp = inputstring();
		if (strcmp(".",temp)==0)
		{
			printf("Keine Eingabe");
			
			freelist(&elementliste);
			return -1;
		}

		if (temp[0] == '\0')
		{
			printf("leere zeile\n");
			free(temp);
			freelist(&elementliste);
			
			return -1;
		}
		char* copy = (char*)malloc(strlen(temp) + 1); //Kopie von Eingabestring
		char* copy2 = (char*)malloc(strlen(temp) + 1); //zweite Kopie von Eingabestring
		strcpy(copy, temp);
		strcpy(copy2, temp);

		if (checkstring(temp, copy, copy2, &mauszeiger1) == -1) //Eingabe pruefen
		{
			free(temp);
			free(copy);
			free(copy2);
			freelist(&elementliste);
		
			
			return -1;
		}

		free(copy);
		free(copy2);

		char* temp2 = malloc(strlen(temp) + 1);
		strcpy(temp2, temp);
		int sepString=seperatestring(temp, temp2, &elementliste, &inputlist, &mauszeiger1); //Eingabe zerlegen und auch Elemente konstruieren
		if (sepString == -1)
		{
			printf("Seperate String fehlgeschlagen");
			free(temp);
			free(temp2);
			freelist(&elementliste);
				
			return -1;
			
			
		}
		
		free(temp);
		free(temp2);
		if (elementliste.zaehler > (long long)(pow(2, 32))) {
			printf("Zu viele Elemente");
			freelist(&elementliste);
			
			return -1;
		}
	}

	
	//printlist(&elementliste);
	move(&mauszeiger1,&elementliste);
	printlistfinal(&elementliste); //Ergebnis ausgeben
	printf("E:%s", mauszeiger1.aktuellelement->name);

	// free element
	

	freelist(&elementliste);
	
	//_CrtDumpMemoryLeaks();
	
}
//Quicksort Probe
/*element* eTemp = inputlist.firstElement;
quick_sort(eTemp->neighbor,0,(eTemp->numberofneighbor)-1);
for (size_t i = 0; i < eTemp->numberofneighbor; i++)
{
	element* ithNeighbor = eTemp->neighbor[i];
	printf("Neighbor %d : %s\n", i,ithNeighbor->name);
}*/



