#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC //malloc->_malloc_dbg and free->_free_dbg
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct town {
	struct town* pNext;
	struct town* pPrev;
	char Name[]; //размер не указан
};
typedef struct town Town;
Town* pFirst = 0, * pLast = 0;
Town* Create(const char* name) {
	size_t len = strlen(name); //приведение типов перед malloc ОБЯЗАТЕЛЬНО
	Town* po = (Town*)malloc(sizeof(Town) + len + 1);
	if (po == 0) return 0;
	strncpy_s(po->Name, len + 1, name, len + 1);
	return po;
}
void Destroy(Town* po) {
	if (po) free(po);
}
void Add2List(Town* po) {
	if (pLast) pLast->pNext = po;
	po->pPrev = pLast;
	pLast = po;
	po->pNext = 0;
	if (pFirst == 0) pFirst = po;
}
void DelFromList(Town* po) {
	if (po == 0) return;
	Town* pop = po->pPrev, * pon = po->pNext;
	if (pop) { pop->pNext = po->pNext; }
	else { pFirst = po->pNext; }
	if (pon) { pon->pPrev = po->pPrev; }
	else { pLast = po->pPrev; }
}
Town* Search4(const char* name) {
	Town* po = pFirst;
	while (po) {
		if (strcmp(po->Name, name) == 0) {
			return po;
		}/*strcmp сравнивает строчки по алфавиту*/
		po = po->pNext;
	}
	return 0;
}

void SortTowns() {
	if (pFirst == NULL) return; // Если список пуст, ничего не делать
	bool swapped;
	do {
		swapped = false;
		Town* current = pFirst;
		while (current->pNext) {
			if (strcmp(current->Name, current->pNext->Name) > 0) {
				
				Town* next = current->pNext; 

				// обмен внешними элементами
				current->pNext = next->pNext; 
				next->pPrev = current->pPrev; 

				if (current->pPrev) {
					current->pPrev->pNext = next; 
				}
				else {
					pFirst = next; 
				}

				// обмен внутренними элементами
				next->pNext = current; 
				current->pPrev = next; 

				if (current->pNext) {
					current->pNext->pPrev = current; 
				}
				else {
					pLast = current;
				}

				swapped = true; 
			}
			else {
				current = current->pNext;
			}
		}
	} while (swapped); 
}

void PrintAllTowns(void) {
	printf("All Town List:");
	Town* po = pFirst;
	while (po) {
		printf("\n %s", po->Name);
		po = po->pNext;
	}
}
int main(void) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF); //_CRTDBG_LEAK_CHECK_DF ИЛИ _CRTDBG_CHECK_ALWAYS_DF
	Town* po;
	po = Create("Saint Peterburg"); if (po == 0) return -1; Add2List(po);
	po = Create("Moscow"); if (po == 0) return -1; Add2List(po);
	po = Create("Paris"); if (po == 0) return -1; Add2List(po);
	po = Create("Tokyo"); if (po == 0) return -1; Add2List(po);
	po = Create("Beijng"); if (po == 0) return -1; Add2List(po);
	po = Create("Saratov"); if (po == 0) return -1; Add2List(po);
	PrintAllTowns();
	printf("\n");
	SortTowns();
	PrintAllTowns();
	if (Search4("Saint Peterburg")) Destroy(po);
	if (Search4("Moscow")) Destroy(po);
	if (Search4("Paris")) Destroy(po);
	if (Search4("Tokyo")) Destroy(po);
	if (Search4("Beijng")) Destroy(po);
	if (Search4("Saratov")) Destroy(po);
	return 0;
}
/*ЗАДАНИЕ:
добавить функцию сортировки двунаправленного списка через использование pNext, pPrev, pFirst, pLast
*/