#include <stdio.h>
#include <stdlib.h>

/* IMPLEMENT ME: Declare your functions here */
int add (int a, int b);
int subtract (int a, int b);
int multiply (int a, int b);
int divide (int a, int b);
int end();

/* Array of function pointers */
int (*ops[5]) (int a, int b);

int main (void) {
	int op1, op2, operation; 
	
	printf("Operand 'a': ");
	scanf("%d", &op1);
	printf("Operand 'b': ");
	scanf("%d", &op2);
	printf("Specify the operation to perform (0 : add | 1 : subtract | 2 : Multiply | 3 : divide | 4 : exit):\n");
	scanf("%d", &operation);
	
	ops[0] = add;
	ops[1] = subtract;
	ops[2] = multiply;
	ops[3] = divide;
	ops[4] = end;

	int result = (*ops[operation]) (op1, op2);
	printf("x = %d\n", result);

	return result;
}

/* IMPLEMENT ME: Define your functions here */
int add (int a, int b) { printf ("Adding 'a' and 'b'\n"); return a + b; }
int subtract (int a, int b) { printf ("Subtracting 'a' and 'b'\n"); return a - b; }
int multiply (int a, int b) { printf ("Multiplying 'a' and 'b'\n"); return a * b; }
int divide (int a, int b) { printf ("Dividing 'a' and 'b'\n"); return a / b; }
int end() { printf ("Exiting\n"); exit(0); }


