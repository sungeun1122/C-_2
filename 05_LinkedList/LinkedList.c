#include <stdio.h>
#include <stdlib.h> // malloc, rand, atoi .. 동적메모리, 난수, 문자열 변환
#include <string.h> // strcpy .. 문자열 함수.  memcpy.. 메모리블럭 함수
#include <conio.h>  // _getch, putch .. MS 기반 C비표준 함수
#include <time.h>   // clock .. 시간 날짜 함수
#pragma warning(disable:4996)  // scanf() 등 전통 C함수중 버퍼문제.
#pragma warning(disable:4477)  // unsigned <--> signed 관련 warning
#include "LinkedList.h"

// 리스트 초기화
void list_init(List *pList)
{
	// head 용 dummy node 방식
	pList->pHead = (Node*)malloc(sizeof(Node));
	pList->pHead->pNext = NULL;
	pList->pTail = pList->pHead; // 최초에는 tail 과 head 동일

	pList->numData = 0;

	printf("리스트 초기화\n");
}

// 리스트 제거
void list_destroy(List *pList)
{
	list_init_iter(pList);
	Node *pPrev = NULL;  // 이전 노드를 가리킬 포인터
	while (list_hasNext(pList))
	{
		pPrev = pList->pCurrent;  // pCurrent 를 이동하기 전에  pCurrent 값을 '이전 노드'로 기억
		list_next(pList);  // pCurrent 이동
		free(pPrev); 
	}

	memset(pList, 0, sizeof(Node));
	printf("리스트 소멸\n");
}

// 데이터 추가
int list_add(List *pList, Data data)
{
	// 새로운 node 생성
	Node *pNewNode = (Node*)malloc(sizeof(Node));
	memset(pNewNode, 0, sizeof(Node));
	pNewNode->data = data;

	// tail이 가리키던 node 의 next 를 새로운 node 에 연결
	pList->pTail->pNext = pNewNode;

	// tail 을 새로운 node 로 이동
	pList->pTail = pNewNode;
	
	// 데이터 개수 증가
	(pList->numData)++;

	return TRUE;
}

// n번째 데이터 삭제
int list_remove(List *pList, int n)
{
	if (n >= pList->numData) return FALSE;

	// n번째 노드 삭제하려면
	// n번째 뿐 아니라 n-1 번째 노드 정보도 알아야 한다
	// 즉. 이전 노드(previous node) 또한 알아야 한다.
	list_init_iter(pList);
	int i = 0;
	Node *pPrev = NULL;  // 이전 노드를 가리킬 포인터
	while (list_hasNext(pList))
	{
		pPrev = pList->pCurrent;  // pCurrent 를 이동하기 전에  pCurrent 값을 '이전 노드'로 기억
		list_next(pList);  // pCurrent 이동
		if (i >= n) break;
		i++;
	}

	// 위 while 문이 끝나면 
	// pCurrent 는 n번째 노드를, 
	// pPrev 는 n-1번째 노드를 가리키고 있다

	// 순서 잘 생각해야 한다.  순서 바뀌면 엉망된다.

	// 삭제진행: 매우 단순 (배열에 비해)
	pPrev->pNext = pList->pCurrent->pNext;

	// 만약 tail 이 삭제할 노드였다면 tail 값도 수정해야 한다.
	if (pList->pCurrent == pList->pTail)
		pList->pTail = pPrev;  // tail 을 이전 노드로 이동.

	// n번째 노드 삭제. 동적 메모리 할당 해제! 꼭!
	free(pList->pCurrent);

	pList->numData--;  // 데이터 개수 -1 감소

	return TRUE;
}

// n번째 데이터 수정
int list_set(List *pList, int n, Data data)
{
	if (n >= pList->numData) return FALSE;

	// head부터 시작해서 n번째 노드 찾기, iteration 사용
	list_init_iter(pList);  // iteration 시작
	int i = 0;   // 현재 몇번째 노드?
	while (list_hasNext(pList))
	{
		list_next(pList);
		if (i >= n) break;  // n번째 노드 찾음!
		i++;
	}
	// 위 while 문이 끝나면 pCurrent 는 n번째 노드를 가리키고 있슴.

	printf("%d 번째 데이터 수정 %d --> %d\n", n, pList->pCurrent->data, data);

	pList->pCurrent->data = data;  // 데이터 수정
	return TRUE;
}

// 데이터 개수
int list_length(List *pList)
{
	return pList->numData;
}

// 데이터 조회, iteration 초기화
void list_init_iter(List *pList)
{
	pList->pCurrent = pList->pHead;
}

// 데이터 조회, iteration 다음 데이터 추출?
Data list_next(List *pList)
{
	pList->pCurrent = pList->pCurrent->pNext;  // 우선 current 한발 앞으로 이동
	Data result = pList->pCurrent->data; // 데이터 추출
	return result;
}

// 데이터 조회, iteration 다음 데이터 있나?
int list_hasNext(List *pList)
{
	if (pList->pCurrent->pNext == NULL)  // '다음 노드' 존재 여부 체크
		return FALSE;

	return TRUE;
}

// 데이터 조회 : n번째 데이터 값 읽기
int list_get(List *pList, int n, Data *pData)
{
	if (n >= pList->numData) return FALSE;

	// head부터 시작해서 n번째 노드 찾기, iteration 사용
	list_init_iter(pList);  // iteration 시작
	int i = 0;   // 현재 몇번째 노드?
	while (list_hasNext(pList))
	{
		list_next(pList);
		if (i >= n) break;  // n번째 노드 찾음!
		i++;
	}

	// 매개변수에 n번째 노드 데이터 담아줌
	*pData = pList->pCurrent->data;

	return TRUE;
}

// 데이터 삽입 : n번째 위치에 데이터 삽입
int list_insert(List *pList, int n, Data data)
{
	// n값 유효범위 검증,  >= 이 아니라  > 닷!
	if (n > pList->numData) return FALSE;

	// 새로운 node 생성
	Node *pNewNode = (Node*)malloc(sizeof(Node));
	memset(pNewNode, 0, sizeof(Node));
	pNewNode->data = data;


	// 1. 첫번째 데이터 이거나 맨 끝에 추가하는 경우.  (add() 와 동일)
	if (pList->numData == 0 || pList->numData == n)
	{
		// add() 와 동일
		pList->pTail->pNext = pNewNode;
		pList->pTail = pNewNode;
	}
	else
	{  // 2. n번째 노드에 삽입하는 경우
		list_init_iter(pList);
		int i = 0;
		Node *pPrev = NULL;  // 이전 노드를 가리킬 포인터
		while (list_hasNext(pList))
		{
			pPrev = pList->pCurrent;  // pCurrent 를 이동하기 전에  pCurrent 값을 '이전 노드'로 기억
			list_next(pList);  // pCurrent 이동
			if (i >= n) break;
			i++;
		}

		// n번째 => pCurrent
		// n-1번째 => pPrev 
		pPrev->pNext = pNewNode;  // 이전 노드는 새로운 노드를 가리키고
		pNewNode->pNext = pList->pCurrent; // 새로운 노드는 기존의 n번째 노드를 가리키면 된다.
	}
	
	//printf("[%d] 번째 데이터 %d 삽입\n", n, data);

	// 데이터 개수 증가.
	pList->numData++;  // 데이터
	
	return TRUE;
}