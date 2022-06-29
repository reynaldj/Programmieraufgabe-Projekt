/* needs to stay the first line */
asm(".code16gcc\njmp $0, $main");

/* space for additional code */

char scan(){
	char ch;
	asm volatile(
		// "call .scan;"
		
		
		// ".scan:"
		"mov $0, %%eax; int $0x16;"
		"mov %%al, %0;"
		//  "ret;"

		// ".done:"
		// "ret"
		".done:"
		 :"=r"(ch)
		 :
		 :"eax"
	);
	return ch;
}

// char scannow2(){
// 	char ch;
// 	asm(
// 		// "call .scan;"
		
		
// 		// ".scan:"
// 		"mov $0, %%eax; int $0x16;"
// 		"mov %%al, %0;"
// 		 "ret;"

// 		// ".done:"
// 		// "ret"
// 		".done:"
// 		 :"=r"(ch)
// 		 :
// 		 :"eax"
// 	);
// 	return ch;
// }




void print(char ch){
	asm volatile(
		
		


		// ".print:"
		"mov %0, %%al; "
		"mov $0xE, %%ah; int $0x10;"
		// "ret;"
		// "jmp .scan;"
		
		
		:
		:"r"(ch)
		:"eax"
		
	);
}

void print_string(char * str, int counter){
	for (int i = 0; i < counter; i++)
	{
		print(str[i]);
	}
	
}

void reboot(){
	print_string("Reboot!\n\r",9);
	asm volatile(
		"int $0x19;"
		
	);
}


void wait_keystroke(){
	
	char str [8] ;
	int counter = 0;
	
		
	
	
	for (int i = 0; i < 8; i++)
	{
		/* code */
		char ch;
		
		ch = scan();
		if (ch == 0x0D ) {
			
			goto print_out;
			
		}
		
		char stern = '*';
		print(stern);
	
		
		str[i] = ch;
		counter++;
		
	}
	
print_out:	
	print('\n');
	print('\r');

	if (counter == 0){
		reboot();
	}	
		
		
	 print_string(str, counter);
	 print('\n');
	print('\r');
	
	
}






void main(void) {
	asm(
		".main:"
		"mov $0x007, %%ebx;"
		"mov $0xE48, %%eax; int $0x10;"
		"mov $0xE65, %%eax; int $0x10;"
		"mov $0xE6C, %%eax; int $0x10;"
		"mov $0xE6C, %%eax; int $0x10;"
		"mov $0xE6F, %%eax; int $0x10;"
		"mov $0xE21, %%eax; int $0x10;"
		"mov $0xE0A, %%eax; int $0x10;"
		"mov $0xE0D, %%eax; int $0x10;"
		// "mov $0, %%ecx;"// Register c ein Counter
		// "mov $300, %%edx;" // Register d ein Pointer
		// "jmp .wait_keystroke;"

		// ".wait_keystroke:"
		// "cmp $8, %%ecx;"
		// "je .print;"
		// "mov $0, %%eax; int $0x16;"
		// "cmp $0x0D, %%al;"
		// "je .print;"
		// "mov %%al, (%%edx);" //store keystroke in adress
		// "add $1, %%edx;"
		// "add $1, %%ecx;"
		// "mov $0xE2E, %%eax; int $0x10;"
		// "jmp .wait_keystroke;"
		
		// ".print:"
		// "mov $0xE0A, %%eax; int $0x10;"
		// "mov $0xE0D, %%eax; int $0x10;"
		// "cmp $0, %%ecx;" //leere String
		// "je .reboot;"
		// "sub %%ecx, %%edx;"
		// "call _printstring;"
		// "mov $0xE0A, %%eax; int $0x10;"
		// "mov $0xE0D, %%eax; int $0x10;"
		// "mov $0, %%ecx;"// Register c ein Counter
		// "mov $100, %%edx;" // Register d ein Pointer
		// "jmp .wait_keystroke;"

		// "_printstring:"
		// "cmp $0, %%ecx;"
		// "je .done;"
		// "mov (%%edx), %%al;"
		// "movb $0, (%%edx);"
		// "mov $0xE, %%ah; int $0x10;"
		// "add $1, %%edx;"
		// "sub $1, %%ecx;"
		// "jmp _printstring;"


		// ".reboot:"
		// "mov $0xE52, %%eax; int $0x10;"
		// "mov $0xE65, %%eax; int $0x10;"
		// "mov $0xE62, %%eax; int $0x10;"
		// "mov $0xE6F, %%eax; int $0x10;"
		// "mov $0xE6F, %%eax; int $0x10;"
		// "mov $0xE74, %%eax; int $0x10;"
		// "mov $0xE21, %%eax; int $0x10;"
		// "mov $0xE0A, %%eax; int $0x10;"
		// "mov $0xE0D, %%eax; int $0x10;"
		// "int $0x19;"
		

		// ".done:"
		// "ret"



		
		::: "eax", "ebx", "ecx", "edx"
	);
	for(;;)
	wait_keystroke();
	
	// char ch = scan();
	
	// print(ch);
	
	// char cd = scan();
	
	// print(cd);
	
}
