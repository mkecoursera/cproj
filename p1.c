#include<stdio.h>
#include<unistd.h>
void swap(int *a, int *b);
void printArr(int a[]);
int main(){
int *pi, a[10];
a[0] = 5;
pi = a;
*(pi + 1) = 25;
printArr(a);
swap(pi, pi+1);
printArr(a);
//printf("value = %d\n", a[1]);
exit(0);
}
void swap(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void printArr(int a[]){
	printf("0 = %d 1 == %d\n", a[0],a[1]);
}