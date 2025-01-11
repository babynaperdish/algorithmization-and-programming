#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int a, b, num, remainder, i = 1;

ENTER:
    printf("\nEnter a and b: ");
    scanf("%d %d", &a, &b);
    if (a < 0 || a > 10000 || b < 2 || b > 32) {
        goto ENTER;
    }


FIND_DEGREE:
    if (i <= a) {
        i *= b;
        goto FIND_DEGREE;
    }

i /= b;

CONVERTION:
    if (i > 0){
        num = a / i;
        a = a % i;
        i /= b;

        printf("%d ", num);
        goto CONVERTION;
    }
}

/*
* ЗАДАНИЕ 1:
* нельзя использовать циклы, только IF и GOTO, без массивов и указателей
* УСЛОВИЕ:
* вводится 2 числа: первое число (a) - десятичное от 0 до 10к, второе (b) - десятичное от 0 до 32
* нужно вывести число a в системе счиления b, при выводе разряды разделять пробелом, буквы выводить как двузначные числа
*/
