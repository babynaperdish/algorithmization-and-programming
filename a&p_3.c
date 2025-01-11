#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quick_sort(int arr[], int left, int right) {
	if (left >= right) return;
	int i = left; 
	int j = right;
	int value = arr[(left + right) / 2];
	while (i <= j) {
		while (arr[i] < value) i++;
		while (arr[j] > value) j--;
		if (i <= j) {
			int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
			i++; j--;
		}
	}
	
	quick_sort(arr, left, j);
	quick_sort(arr, i, right);
}

int main() {
	srand(time(NULL));
	int a[100];
	int m;
	double m_v = 0;
	for (int i = 0; i < 100; i++) {
		a[i] = rand()%100;
		m_v += (double)a[i]/100;
	}
	for (int i = 0; i < 100; i++) {
		printf("%d ", a[i]);
	}
	quick_sort(a, 0, 99);
	printf("\n \n");
	for (int i = 0; i < 100; i++) {
		printf("%d ", a[i]);
	}
	printf("\n\n");
	m = (a[49] + a[50]) / 2;
	printf("Median: %d\n", m);
	printf("Mean: %f\n ", m_v);
}

//ЗАДАНИЕ:
//1. Сгенерировать случайные числа в массив размером 100
//2. Сортировка массива НЕ пузырьком
//3. Найти медиану