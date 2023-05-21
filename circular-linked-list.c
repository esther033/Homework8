#include<stdio.h>
#include<stdlib.h>

typedef struct Node { //listNode 구조체 선언
	int key; 
	struct Node* llink;
	struct Node* rlink;
} listNode;

int initialize(listNode** h); //listNode를 초기화하는 함수
int freeList(listNode* h); //listNode메모리를 해제하는 함수
int insertLast(listNode* h, int key); //list의 마지막에 노드를 삽입하는 함수
int deleteLast(listNode* h); //list의 마지막에 노드를 삭제하는 함수
int insertFirst(listNode* h, int key); //list의 처음에 노드를 삽입하는 함수
int deleteFirst(listNode* h); //list의 처음에 노드를 삭제하는 함수
int invertList(listNode* h); //list를 역순으로 재배치하는 함수

int insertNode(listNode* h, int key); //key값에 따라 노드를 삽입하는 함수
int deleteNode(listNode* h, int key); //key값에 따라 노드를 삭제하는 함수

void printList(listNode* h); //list를 출력하는 함수



int main()
{
	printf("[----- [박에스더]  [2022041054] -----]\n"); 
	char command; //사용자에게 메뉴를 입력받을 변수
	int key; //key값을 입력받을 변수
	listNode* headnode=NULL; //listNode *headnode를 선언 후 NULL로 초기화

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //사용자에게 메뉴를 입력받는다

		switch(command) { //commad의 값에 따라 실행
		case 'z': case 'Z': //command가 z  or Z일때
			initialize(&headnode); //initialize함수를 호출하여 headnode 초기화
			break;
		case 'p': case 'P': //command가 p or P일때
			printList(headnode); //printList함수를 호출하여 headnode 출력
			break;
		case 'i': case 'I': //command가 i or I일때
			printf("Your Key = ");
			scanf("%d", &key); //사용자에게 key값을 입력받는다
			insertNode(headnode, key); //insertNode함수를 호출하여 headnode에 key값 삽입
			break;
		case 'd': case 'D': //command가 d or D일때
			printf("Your Key = ");
			scanf("%d", &key); //사용자에게 key값을 입력받는다
			deleteNode(headnode, key); //deleteNode함수를 호출하여 headnode에 key값 삭제
			break;
		case 'n': case 'N': //command가 n or N일때
			printf("Your Key = ");
			scanf("%d", &key); //사용자에게 key값을 입력받는다
			insertLast(headnode, key); //insertLast함수를 호출하여 headnode에 key값 삽입
			break;
		case 'e': case 'E': //command가 e or E일때
			deleteLast(headnode); //deleteLast함수를 호출하여 headnode에 key값 삭제
			break; 
		case 'f': case 'F': //command가 f or F일때
			printf("Your Key = ");
			scanf("%d", &key); //사용자에게 key값을 입력받는다
			insertFirst(headnode, key); //insertFirst함수를 호출하여 headnode에 key값 삽입
			break;
		case 't': case 'T': //command가 t or T일때
			deleteFirst(headnode); //deleteFirst함수를 호출하여 headnode에 key값 삭제
			break;
		case 'r': case 'R': //command가 r or R일때
			invertList(headnode); //invertList함수를 호출하여 headnode 역순으로 배치
			break;
		case 'q': case 'Q': //command가 q or Q일때
			freeList(headnode); //freeList함수를 호출하여 headnode메모리 해제
			break;
		default: //command가 위의 값들과 다를때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command가 q or Q일때 반복문 종료

	return 1;
}


int initialize(listNode** h) { //listNode를 초기화 하는 함수
	// headNode가 NULL이 아니면, freeNode를 호출하여 메모리 해제 
	if(*h != NULL)
		freeList(*h);

	*h = (listNode*)malloc(sizeof(listNode)); //*h를 동적 메모리 할당
	(*h)->rlink = *h; //h의 rlink에 *h저장
	(*h)->llink = *h;  //h의 llink에 *h저장
	(*h)->key = -9999; //h의 키에 -9999저장
	return 1; //함수종료
}

int freeList(listNode* h){ //listNode의 메모리를 해제하는 함수

	if(h->rlink == h) //h의 rlink가 h일때
	{
		free(h); //h메모리 해제
		return 1; //함수 종료
	}

	listNode* p = h->rlink; //listNode *p를 선언 후 h의 rlink저장

	listNode* prev = NULL; //listNode *prev를 선언 후 NULL저장
	while(p != NULL && p != h) { //p가 NULL이거나 h일때까지 반복
		prev = p; //prev에 p저장
		p = p->rlink; //p에 p의 rlink저장
		free(prev); //prev 메모리 해제
	}
	free(h); //h메모리 해제
	return 0; //함수 종료
}



void printList(listNode* h) { //listNode를 출력하는 함수
	int i = 0; //변수 i선언 후 0으로 초기화
	listNode* p; //listNode *p선언

	printf("\n---PRINT\n");

	if(h == NULL) { //h가 NULL일때
		printf("Nothing to print....\n"); //출력할 것이 없음
		return; // 함수 종료
	}

	p = h->rlink;// p에 h의 rlink 저장

	while(p != NULL && p != h) { //p가 NULL이거나 h일때까지 반복
		printf("[ [%d]=%d ] ", i, p->key); //i와 p의 key값 출력
		p = p->rlink; //p에 p의 rlink 저장
		i++; //i값 증가
	}
	printf("  items = %d\n", i); //item의 개수 출력

	printf("\n---checking addresses of links\n"); //주소를 출력하는 부분
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink); //head노드의 llink,head,rlink의 주소 출력

	i = 0; //i에 0저장
	p = h->rlink; //p에 h의 오른쪽 링크 저장
	while(p != NULL && p != h) { //p가 NULL이거나 h일때까지 반복
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink); //p노드의 llink,node,rlink의 주소 출력
		p = p->rlink;//p에 다음링크 저장
		i++; //i값 증가
	}

}

int insertLast(listNode* h, int key) {//list의 마지막노드에 key를 삽입하는 함수

	if (h == NULL) return -1; //h가 NULL일때 함수 종료

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode *node 선언 후 동적 메모리할당
	node->key = key; //node의 key에 매개변수 key저장
	node->rlink = NULL; //node의 rlink에 NULL저장
	node->llink = NULL; //node의 llink에 NULL저장

	if (h->rlink == h) //h의다음링크가 h일때
	{
		h->rlink = node; //h의 rlink에 node저장
		h->llink = node; //h의 llink에 node저장
		node->rlink = h; //node의 rlink에 h저장
		node->llink = h; //node의 rlink에 h저장
	} else {
		h->llink->rlink = node; //h의 llink의 rlink에 node 저장
		node->llink = h->llink; //node의 llink에 h의 llink저장
		h->llink = node; //h의 link에 node 저장
		node->rlink = h; //node의 rlink에 h저장
	}

	return 1; //함수종료
}

int deleteLast(listNode* h) { //list의 마지막노드를 삭제하는 함수

	if (h->llink == h || h == NULL) //h의 llink가 h이거나 h가 NULL일때
	{
		printf("nothing to delete.\n"); //삭제할 것이 없다
		return 1; //함수종료
	}

	listNode* nodetoremove = h->llink; //listNode *nodetoremove의 h의 llink저장

	nodetoremove->llink->rlink = h; //nodetoremove의 llink의 rlink에 h 저장
	h->llink = nodetoremove->llink; //h의 llink에 nodetoremove의 llink저장

	free(nodetoremove); //nodetoremove메모리 해제

	return 1; // 함수 종료
}

int insertFirst(listNode* h, int key)  {//list의 첫번째노드에 key를 삽입하는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode)); ////listNode *node를 동적메모리할당
	node->key = key; //node의 key값에 매개변수 key저장
	node->rlink = NULL; //node의 rlink에 NULL저장
	node->llink = NULL;//node의 llink에 NULL저장

	node->rlink = h->rlink; //node의 rlink에 h의 rlink저장
	h->rlink->llink = node; //h의 rlink의 link에 node 저장
	node->llink = h; //node의 llink에 h저장
	h->rlink = node; //h의 rlink에 node 저장

	return 1; //함수 종료
}

int deleteFirst(listNode* h) { //list의 첫번째 노드를 삭제하는 함수

	if (h == NULL || h->rlink == h) //h의 llink가 h이거나 h가 NULL일때
	{
		printf("nothing to delete.\n"); //삭제할 것이 없음
		return 0; //함수 종료
	}

	listNode* nodetoremove = h->rlink; //listNode *nodetoremove의 h의 llink저장

	nodetoremove->rlink->llink = h; //nodetoremove의 rlink의 llink에 h 저장
	h->rlink = nodetoremove->rlink; //h의 rlink에 nodetoremove의 rlink저장

	free(nodetoremove); //nodetoremove메모리 해제

	return 1; //함수 종료

}

int invertList(listNode* h) { //list를 역순으로 재배치하는 함수


	if(h->rlink == h || h == NULL) { //h의 llink가 h이거나 h가 NULL일때
		printf("nothing to invert...\n"); //재배치할 것이 없다
		return 0; //함수 종료
	}
	listNode *n = h->rlink; //listNode *n 선언 후 h의 rlink저장
	listNode *trail = h; //listNode *trail 선언 후 h저장
	listNode *middle = h; //listNode *middle 선언 후 h저장

	h->llink = h->rlink; //h의 link에 h의 rlink저장

	while(n != NULL && n != h){ //n이 NULL이거나 h일때까지 반복
		trail = middle; //trail에 middle저장
		middle = n; //middle에 n저장
		n = n->rlink; //n에 n의 rlink저장
		middle->rlink = trail; //middle의 rlink에 trail저장
		middle->llink = n; //middle의 llink에 n저장
	}

	h->rlink = middle; //h의 rlink에 middle저장

	return 0; //함수종료
}

int insertNode(listNode* h, int key) { //입력받은 key값에따라 노드를 삽입하는 함수

	if(h == NULL) return -1; //h가 NULL이면 함수종료

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode *node선언 후 동적 메모리 할당
	node->key = key; //node의 key에 매개변수 key저장
	node->llink = node->rlink = NULL; //node의 link, node의 rlink에 NULL저장

	if (h->rlink == h) //h의 rlink가 h일때
	{
		insertFirst(h, key); //insertFirst함수를 호출하여 첫번째 노드에 삽입
		return 1; //함수종료
	}

	listNode* n = h->rlink; //listNode *n선언 후 h의 rlink에 저장

	while(n != NULL && n != h) { //n이 NULL이거나 h일때까지 반복
		if(n->key >= key) { //n의 key가 매개변수key와 같거나 클때
			if(n == h->rlink) { //n이 h의 rlink인경우
				insertFirst(h, key); //insertFirst함수를 호출하여 첫번째 노드에 삽입
			} else { 
				node->rlink = n; //node의 rlink에 n저장
				node->llink = n->llink; //node의 llink에 n의 llink저장
				n->llink->rlink = node; //n의 llink의rlink에 node저장
				n->llink = node; ////n의 llink에 node저장
			}
			return 0; //함수종료
		}

		n = n->rlink; //n에 n의 rlink저장
	}

	insertLast(h, key); //마지막 노드까지 찾지 못한경우 insertLast함수를 호출하여 list의 마지막에 노드추가
	return 0; //함수 종료
}

int deleteNode(listNode* h, int key) { //입력받은 key값에따라 node를 삭제하는 함수

	if (h->rlink == h || h == NULL) //h의 llink가 h이거나 h가 NULL일때
	{
		printf("nothing to delete.\n"); //삭제할 것이 없다
		return 0; //함수 종료
	}

	listNode* n = h->rlink; //listNode *n선언 후 h의 rlink에 저장

	while(n != NULL && n != h) { //n이 NULL이거나 h일때까지 반복
		if(n->key == key) { //n의 key가 매개변수 key와 같을경우
			if(n == h->rlink) { //n이 h의 rlink와 같을경우
				deleteFirst(h); //deleteFirst함수를 호출하여 h의 첫번째 노드 삭제
			} else if (n->rlink == h){  //n의 rlink와 h가 같을경우
				deleteLast(h); //deleteLast함수를 호출하여 h의 마지막 노드 삭제
			} else { 
				n->llink->rlink = n->rlink; //n의 llink의rlink에 n의 rlink저장
				n->rlink->llink = n->llink; //n의 rlink의llink에 n의 llink저장
				free(n);//n의 메모리 해제
			}
			return 0; //함수종료
		}

		n = n->rlink; //n에 n이 rlink저장
	}

	printf("cannot find the node for key = %d\n", key); //마지막까지 찾지 못한경우 key에대한 노드를 찾을 수 없음
	return 0; //함수 종료
}


