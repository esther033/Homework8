#include<stdio.h>
#include<stdlib.h>

typedef struct Node { //listNode ����ü ����
	int key; 
	struct Node* llink;
	struct Node* rlink;
} listNode;

int initialize(listNode** h); //listNode�� �ʱ�ȭ�ϴ� �Լ�
int freeList(listNode* h); //listNode�޸𸮸� �����ϴ� �Լ�
int insertLast(listNode* h, int key); //list�� �������� ��带 �����ϴ� �Լ�
int deleteLast(listNode* h); //list�� �������� ��带 �����ϴ� �Լ�
int insertFirst(listNode* h, int key); //list�� ó���� ��带 �����ϴ� �Լ�
int deleteFirst(listNode* h); //list�� ó���� ��带 �����ϴ� �Լ�
int invertList(listNode* h); //list�� �������� ���ġ�ϴ� �Լ�

int insertNode(listNode* h, int key); //key���� ���� ��带 �����ϴ� �Լ�
int deleteNode(listNode* h, int key); //key���� ���� ��带 �����ϴ� �Լ�

void printList(listNode* h); //list�� ����ϴ� �Լ�



int main()
{
	printf("[----- [�ڿ�����]  [2022041054] -----]\n"); 
	char command; //����ڿ��� �޴��� �Է¹��� ����
	int key; //key���� �Է¹��� ����
	listNode* headnode=NULL; //listNode *headnode�� ���� �� NULL�� �ʱ�ȭ

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
		scanf(" %c", &command); //����ڿ��� �޴��� �Է¹޴´�

		switch(command) { //commad�� ���� ���� ����
		case 'z': case 'Z': //command�� z  or Z�϶�
			initialize(&headnode); //initialize�Լ��� ȣ���Ͽ� headnode �ʱ�ȭ
			break;
		case 'p': case 'P': //command�� p or P�϶�
			printList(headnode); //printList�Լ��� ȣ���Ͽ� headnode ���
			break;
		case 'i': case 'I': //command�� i or I�϶�
			printf("Your Key = ");
			scanf("%d", &key); //����ڿ��� key���� �Է¹޴´�
			insertNode(headnode, key); //insertNode�Լ��� ȣ���Ͽ� headnode�� key�� ����
			break;
		case 'd': case 'D': //command�� d or D�϶�
			printf("Your Key = ");
			scanf("%d", &key); //����ڿ��� key���� �Է¹޴´�
			deleteNode(headnode, key); //deleteNode�Լ��� ȣ���Ͽ� headnode�� key�� ����
			break;
		case 'n': case 'N': //command�� n or N�϶�
			printf("Your Key = ");
			scanf("%d", &key); //����ڿ��� key���� �Է¹޴´�
			insertLast(headnode, key); //insertLast�Լ��� ȣ���Ͽ� headnode�� key�� ����
			break;
		case 'e': case 'E': //command�� e or E�϶�
			deleteLast(headnode); //deleteLast�Լ��� ȣ���Ͽ� headnode�� key�� ����
			break; 
		case 'f': case 'F': //command�� f or F�϶�
			printf("Your Key = ");
			scanf("%d", &key); //����ڿ��� key���� �Է¹޴´�
			insertFirst(headnode, key); //insertFirst�Լ��� ȣ���Ͽ� headnode�� key�� ����
			break;
		case 't': case 'T': //command�� t or T�϶�
			deleteFirst(headnode); //deleteFirst�Լ��� ȣ���Ͽ� headnode�� key�� ����
			break;
		case 'r': case 'R': //command�� r or R�϶�
			invertList(headnode); //invertList�Լ��� ȣ���Ͽ� headnode �������� ��ġ
			break;
		case 'q': case 'Q': //command�� q or Q�϶�
			freeList(headnode); //freeList�Լ��� ȣ���Ͽ� headnode�޸� ����
			break;
		default: //command�� ���� ����� �ٸ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command�� q or Q�϶� �ݺ��� ����

	return 1;
}


int initialize(listNode** h) { //listNode�� �ʱ�ȭ �ϴ� �Լ�
	// headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �޸� ���� 
	if(*h != NULL)
		freeList(*h);

	*h = (listNode*)malloc(sizeof(listNode)); //*h�� ���� �޸� �Ҵ�
	(*h)->rlink = *h; //h�� rlink�� *h����
	(*h)->llink = *h;  //h�� llink�� *h����
	(*h)->key = -9999; //h�� Ű�� -9999����
	return 1; //�Լ�����
}

int freeList(listNode* h){ //listNode�� �޸𸮸� �����ϴ� �Լ�

	if(h->rlink == h) //h�� rlink�� h�϶�
	{
		free(h); //h�޸� ����
		return 1; //�Լ� ����
	}

	listNode* p = h->rlink; //listNode *p�� ���� �� h�� rlink����

	listNode* prev = NULL; //listNode *prev�� ���� �� NULL����
	while(p != NULL && p != h) { //p�� NULL�̰ų� h�϶����� �ݺ�
		prev = p; //prev�� p����
		p = p->rlink; //p�� p�� rlink����
		free(prev); //prev �޸� ����
	}
	free(h); //h�޸� ����
	return 0; //�Լ� ����
}



void printList(listNode* h) { //listNode�� ����ϴ� �Լ�
	int i = 0; //���� i���� �� 0���� �ʱ�ȭ
	listNode* p; //listNode *p����

	printf("\n---PRINT\n");

	if(h == NULL) { //h�� NULL�϶�
		printf("Nothing to print....\n"); //����� ���� ����
		return; // �Լ� ����
	}

	p = h->rlink;// p�� h�� rlink ����

	while(p != NULL && p != h) { //p�� NULL�̰ų� h�϶����� �ݺ�
		printf("[ [%d]=%d ] ", i, p->key); //i�� p�� key�� ���
		p = p->rlink; //p�� p�� rlink ����
		i++; //i�� ����
	}
	printf("  items = %d\n", i); //item�� ���� ���

	printf("\n---checking addresses of links\n"); //�ּҸ� ����ϴ� �κ�
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink); //head����� llink,head,rlink�� �ּ� ���

	i = 0; //i�� 0����
	p = h->rlink; //p�� h�� ������ ��ũ ����
	while(p != NULL && p != h) { //p�� NULL�̰ų� h�϶����� �ݺ�
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink); //p����� llink,node,rlink�� �ּ� ���
		p = p->rlink;//p�� ������ũ ����
		i++; //i�� ����
	}

}

int insertLast(listNode* h, int key) {//list�� ��������忡 key�� �����ϴ� �Լ�

	if (h == NULL) return -1; //h�� NULL�϶� �Լ� ����

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode *node ���� �� ���� �޸��Ҵ�
	node->key = key; //node�� key�� �Ű����� key����
	node->rlink = NULL; //node�� rlink�� NULL����
	node->llink = NULL; //node�� llink�� NULL����

	if (h->rlink == h) //h�Ǵ�����ũ�� h�϶�
	{
		h->rlink = node; //h�� rlink�� node����
		h->llink = node; //h�� llink�� node����
		node->rlink = h; //node�� rlink�� h����
		node->llink = h; //node�� rlink�� h����
	} else {
		h->llink->rlink = node; //h�� llink�� rlink�� node ����
		node->llink = h->llink; //node�� llink�� h�� llink����
		h->llink = node; //h�� link�� node ����
		node->rlink = h; //node�� rlink�� h����
	}

	return 1; //�Լ�����
}

int deleteLast(listNode* h) { //list�� ��������带 �����ϴ� �Լ�

	if (h->llink == h || h == NULL) //h�� llink�� h�̰ų� h�� NULL�϶�
	{
		printf("nothing to delete.\n"); //������ ���� ����
		return 1; //�Լ�����
	}

	listNode* nodetoremove = h->llink; //listNode *nodetoremove�� h�� llink����

	nodetoremove->llink->rlink = h; //nodetoremove�� llink�� rlink�� h ����
	h->llink = nodetoremove->llink; //h�� llink�� nodetoremove�� llink����

	free(nodetoremove); //nodetoremove�޸� ����

	return 1; // �Լ� ����
}

int insertFirst(listNode* h, int key)  {//list�� ù��°��忡 key�� �����ϴ� �Լ�

	listNode* node = (listNode*)malloc(sizeof(listNode)); ////listNode *node�� �����޸��Ҵ�
	node->key = key; //node�� key���� �Ű����� key����
	node->rlink = NULL; //node�� rlink�� NULL����
	node->llink = NULL;//node�� llink�� NULL����

	node->rlink = h->rlink; //node�� rlink�� h�� rlink����
	h->rlink->llink = node; //h�� rlink�� link�� node ����
	node->llink = h; //node�� llink�� h����
	h->rlink = node; //h�� rlink�� node ����

	return 1; //�Լ� ����
}

int deleteFirst(listNode* h) { //list�� ù��° ��带 �����ϴ� �Լ�

	if (h == NULL || h->rlink == h) //h�� llink�� h�̰ų� h�� NULL�϶�
	{
		printf("nothing to delete.\n"); //������ ���� ����
		return 0; //�Լ� ����
	}

	listNode* nodetoremove = h->rlink; //listNode *nodetoremove�� h�� llink����

	nodetoremove->rlink->llink = h; //nodetoremove�� rlink�� llink�� h ����
	h->rlink = nodetoremove->rlink; //h�� rlink�� nodetoremove�� rlink����

	free(nodetoremove); //nodetoremove�޸� ����

	return 1; //�Լ� ����

}

int invertList(listNode* h) { //list�� �������� ���ġ�ϴ� �Լ�


	if(h->rlink == h || h == NULL) { //h�� llink�� h�̰ų� h�� NULL�϶�
		printf("nothing to invert...\n"); //���ġ�� ���� ����
		return 0; //�Լ� ����
	}
	listNode *n = h->rlink; //listNode *n ���� �� h�� rlink����
	listNode *trail = h; //listNode *trail ���� �� h����
	listNode *middle = h; //listNode *middle ���� �� h����

	h->llink = h->rlink; //h�� link�� h�� rlink����

	while(n != NULL && n != h){ //n�� NULL�̰ų� h�϶����� �ݺ�
		trail = middle; //trail�� middle����
		middle = n; //middle�� n����
		n = n->rlink; //n�� n�� rlink����
		middle->rlink = trail; //middle�� rlink�� trail����
		middle->llink = n; //middle�� llink�� n����
	}

	h->rlink = middle; //h�� rlink�� middle����

	return 0; //�Լ�����
}

int insertNode(listNode* h, int key) { //�Է¹��� key�������� ��带 �����ϴ� �Լ�

	if(h == NULL) return -1; //h�� NULL�̸� �Լ�����

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode *node���� �� ���� �޸� �Ҵ�
	node->key = key; //node�� key�� �Ű����� key����
	node->llink = node->rlink = NULL; //node�� link, node�� rlink�� NULL����

	if (h->rlink == h) //h�� rlink�� h�϶�
	{
		insertFirst(h, key); //insertFirst�Լ��� ȣ���Ͽ� ù��° ��忡 ����
		return 1; //�Լ�����
	}

	listNode* n = h->rlink; //listNode *n���� �� h�� rlink�� ����

	while(n != NULL && n != h) { //n�� NULL�̰ų� h�϶����� �ݺ�
		if(n->key >= key) { //n�� key�� �Ű�����key�� ���ų� Ŭ��
			if(n == h->rlink) { //n�� h�� rlink�ΰ��
				insertFirst(h, key); //insertFirst�Լ��� ȣ���Ͽ� ù��° ��忡 ����
			} else { 
				node->rlink = n; //node�� rlink�� n����
				node->llink = n->llink; //node�� llink�� n�� llink����
				n->llink->rlink = node; //n�� llink��rlink�� node����
				n->llink = node; ////n�� llink�� node����
			}
			return 0; //�Լ�����
		}

		n = n->rlink; //n�� n�� rlink����
	}

	insertLast(h, key); //������ ������ ã�� ���Ѱ�� insertLast�Լ��� ȣ���Ͽ� list�� �������� ����߰�
	return 0; //�Լ� ����
}

int deleteNode(listNode* h, int key) { //�Է¹��� key�������� node�� �����ϴ� �Լ�

	if (h->rlink == h || h == NULL) //h�� llink�� h�̰ų� h�� NULL�϶�
	{
		printf("nothing to delete.\n"); //������ ���� ����
		return 0; //�Լ� ����
	}

	listNode* n = h->rlink; //listNode *n���� �� h�� rlink�� ����

	while(n != NULL && n != h) { //n�� NULL�̰ų� h�϶����� �ݺ�
		if(n->key == key) { //n�� key�� �Ű����� key�� �������
			if(n == h->rlink) { //n�� h�� rlink�� �������
				deleteFirst(h); //deleteFirst�Լ��� ȣ���Ͽ� h�� ù��° ��� ����
			} else if (n->rlink == h){  //n�� rlink�� h�� �������
				deleteLast(h); //deleteLast�Լ��� ȣ���Ͽ� h�� ������ ��� ����
			} else { 
				n->llink->rlink = n->rlink; //n�� llink��rlink�� n�� rlink����
				n->rlink->llink = n->llink; //n�� rlink��llink�� n�� llink����
				free(n);//n�� �޸� ����
			}
			return 0; //�Լ�����
		}

		n = n->rlink; //n�� n�� rlink����
	}

	printf("cannot find the node for key = %d\n", key); //���������� ã�� ���Ѱ�� key������ ��带 ã�� �� ����
	return 0; //�Լ� ����
}


