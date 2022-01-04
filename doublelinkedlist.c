#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	struct node* pre; // ���� ��带 ����Ű�� ������
	int data; // ������ ���� ����
	struct node* next; // ���� ��带 ����Ű�� ������
}Node;
typedef struct list
{
	Node* head; // ����Ʈ�� �Ӹ�
	Node* tail; // ����Ʈ�� ����
	int count; // ����� ����
}List;
void listinit(List* plist)
{
	plist->head=NULL;
	plist->tail=NULL;
	plist->count=0;
}// ����Ʈ �ʱ�ȭ �Լ�
void append(List* plist,int data)
{
	Node* newnode= (Node*)malloc(sizeof(Node));
	newnode->data=data;
	newnode->pre=NULL;
	newnode->next=NULL;

	if(plist->head==NULL) // ó�� ��� �߰���
	{
		plist->head=newnode;
	}
	else{
		plist->tail->next=newnode; // ����� ���� �۾�
		newnode->pre=plist->tail;
	}
	plist->tail=newnode; // ����Ʈ�� ���� ��ġ ����
	plist->count++;
}// ��� �߰� �Լ�
Node* fsearch(List* plist,int location)// ���� Ž��
{
	Node* cur=plist->head; // Ž���� ���� ���
	if(plist->head==NULL)
		return NULL; // ����ִ� ����Ʈ������ Ž�� �Ұ�

	while(cur!=NULL)
	{
		if(cur->data==location)
			return cur; // ���ϴ� ��带 ã���� �ش� ��带 ��ȯ
	
		cur=cur->next;
	}
	return NULL; // �ش� ����Ʈ�� ���ϴ� �����Ͱ� ���� ���
}
Node* lsearch(List* plist,int location)// �Ĺ� Ž��
{
	Node* cur=plist->tail;
	if(plist->tail==NULL)
		return NULL; // ����ִ� ����Ʈ������ Ž�� �Ұ�

	while(cur!=NULL)
	{
		if(cur->data==location)
			return cur;
		cur=cur->pre;
	}
	return NULL;
}
int deleteNode(List* plist,int location)
{
	Node* cur= fsearch(plist,location); // Ž���� ���� �����ϰ��� �ϴ� ��带 ã�´�

	if(cur==NULL) // ���ϴ� ��尡 ���� ���
		return -1; // ���� ���� ó��
	if(cur==plist->head){
		plist->head=cur->next;
		cur->next->pre=cur->pre;
	} // head ��带 �����ϴ� ���
	else if(cur==plist->tail){
		plist->tail=cur->pre; // tail ��带 �����ϴ� ���
		cur->pre->next=cur->next;
	}
	else{
		cur->pre->next=cur->next;
		cur->next->pre=cur->pre;
	}
	plist->count--;
	return 1;
}
void print(List* plist)
{
	Node* cur=plist->head;

	printf("list: ");
	while(cur!=NULL)
	{
		printf("%d ",cur->data);
		cur=cur->next;
	}printf("\n");
}
int insert(List* plist,int data,int location)
{
	Node* cur= fsearch(plist,location); // Ž���� ���� �����ϰ��� �ϴ� ��带 ã�´�
	Node* newnode= (Node*)malloc(sizeof(Node));
	newnode->data=data;
	newnode->pre=NULL;
	newnode->next=NULL;

	if(cur==NULL) // ���ϴ� ��尡 ���� ���
		return -1;
	else{
		newnode->next=cur->next;
		newnode->pre=cur;
		cur->next->pre=newnode;
		cur->next=newnode;
	}
	plist->count++;
	return 1;
}
int main(void)
{
	Node* re;
	List list;
	listinit(&list);
	append(&list,1);
	append(&list,2);
	append(&list,3);
	print(&list);
	
	re=lsearch(&list,3);
	printf("lsearch : %d\n",re->data);

	deleteNode(&list,2);
	print(&list);

	insert(&list,2,1);
	print(&list);

	deleteNode(&list,1);
	print(&list);

	
	return 0;
}