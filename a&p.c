#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int a, b, c, d, e, f;
int *pa = &a, *pb = &b, *pc = &c, *pd = &d, *pe = &e, *pf = &f;


void swap(int **pt1, int **pt2) {
	*pt1 = (int*)((uintptr_t)*pt1 + (uintptr_t)*pt2); 
	*pt2 = (int*)((uintptr_t)*pt1 - (uintptr_t)*pt2);
	*pt1 = (int*)((uintptr_t)*pt1 - (uintptr_t)*pt2);
}

int main(void) {
	srand(time(NULL));
	a = rand(); b = rand(); c = rand(); d = rand(); e = rand(); f = rand();
	printf("Variables: %d %d %d %d %d %d", a, b, c, d, e, f);
	printf("\nAddresses: %p %p %p %p %p %p", pa, pb, pc, pd, pe, pf);
	printf("\nOriginal: %d %d %d %d %d %d", *pa, *pb, *pc, *pd, *pe, *pf);

	for (int i = 0; i < 6; i++) {
		if (*pa > *pb) {
			swap(&pa, &pb);
		}
		if (*pb > *pc) {
			swap(&pb, &pc);
		}
		if (*pc > *pd) {
			swap(&pc, &pd);
		}
		if (*pd > *pe) {
			swap(&pd, &pe);
		}
		if (*pe > *pf) {
			swap(&pe, &pf);
		}
	}
	printf("\n\nVariables: %d %d %d %d %d %d", a, b, c, d, e, f);
	printf("\nAddresses: %p %p %p %p %p %p", pa, pb, pc, pd, pe, pf);
	printf("\nSorted: %d %d %d %d %d %d\n", *pa, *pb, *pc, *pd, *pe, *pf);
}

//ЗАДАНИЕ:
//Отсортировать 6 целых чисел, меняя местами адреса их указателей