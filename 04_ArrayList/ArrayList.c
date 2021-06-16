#include <stdio.h>
#include <stdlib.h> // malloc, rand, atoi .. �����޸�, ����, ���ڿ� ��ȯ
#include <string.h> // strcpy .. ���ڿ� �Լ�.  memcpy.. �޸𸮺��� �Լ�
#include <conio.h>  // _getch, putch .. MS ��� C��ǥ�� �Լ�
#include <time.h>   // clock .. �ð� ��¥ �Լ�
#pragma warning(disable:4996)  // scanf() �� ���� C�Լ��� ���۹���.
#pragma warning(disable:4477)  // unsigned <--> signed ���� warning

#include "ArrayList.h"

// ����Ʈ �ʱ�ȭ
void list_init(List *pList)
{
	pList->numData = 0;
	pList->curPosition = -1;  // for iteration
	memset(pList->arr, 0, sizeof(pList->arr));  // �迭�� ���� 0���� �ʱ�ȭ
	printf("����Ʈ �ʱ�ȭ\n");
}

// ����Ʈ ����
void list_destroy(List *pList)
{
	pList->numData = 0;
	printf("����Ʈ ����\n");
}

// ������ �߰�
int list_add(List *pList, Data data)
{
	if (pList->numData >= LIST_LEN)
	{
		printf("������ �߰� �Ұ�\n");
		return FAIL;
	}

	pList->arr[pList->numData] = data;   // ������ �߰�

	printf("[%d] ��° ������ %d �߰�\n", pList->numData, data);
	(pList->numData)++;  // ������ ���� ����
	return SUCCESS;
}

// n��° ������ ����
int list_remove(List *pList, int n);

// n��° ������ ����
int list_set(List *pList, int n, Data data);

// ������ ����
int list_length(List *pList);

// ������ ��ȸ, iteration �ʱ�ȭ
void list_init_iter(List *pList);

// ������ ��ȸ, iteration ���� ������ ����?
Data list_next(List *pList);

// ������ ��ȸ, iteration ���� ������ �ֳ�?
int list_hasNext(List *pList);

// ������ ��ȸ : n��° ������ �� �б�
int list_get(List *pList, int n, Data *pData);





