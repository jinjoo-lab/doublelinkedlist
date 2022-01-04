#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	struct node* pre; // 이전 노드를 가리키는 포인터
	int data; // 데이터 저장 공간
	struct node* next; // 다음 노드를 가리키는 포인터
}Node;
typedef struct list
{
	Node* head; // 리스트의 머리
	Node* tail; // 리스트의 꼬리
	int count; // 노드의 개수
}List;
void listinit(List* plist)
{
	plist->head=NULL;
	plist->tail=NULL;
	plist->count=0;
}// 리스트 초기화 함수
void append(List* plist,int data)
{
	Node* newnode= (Node*)malloc(sizeof(Node));
	newnode->data=data;
	newnode->pre=NULL;
	newnode->next=NULL;

	if(plist->head==NULL) // 처음 노드 추가시
	{
		plist->head=newnode;
	}
	else{
		plist->tail->next=newnode; // 양방향 연결 작업
		newnode->pre=plist->tail;
	}
	plist->tail=newnode; // 리스트의 꼬리 위치 조정
	plist->count++;
}// 노드 추가 함수
Node* fsearch(List* plist,int location)// 전방 탐색
{
	Node* cur=plist->head; // 탐색을 위한 노드
	if(plist->head==NULL)
		return NULL; // 비어있는 리스트에서는 탐색 불가

	while(cur!=NULL)
	{
		if(cur->data==location)
			return cur; // 원하는 노드를 찾을시 해당 노드를 반환
	
		cur=cur->next;
	}
	return NULL; // 해당 리스트에 원하는 데이터가 없는 경우
}
Node* lsearch(List* plist,int location)// 후방 탐색
{
	Node* cur=plist->tail;
	if(plist->tail==NULL)
		return NULL; // 비어있는 리스트에서는 탐색 불가

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
	Node* cur= fsearch(plist,location); // 탐색을 통해 삭제하고자 하는 노드를 찾는다

	if(cur==NULL) // 원하는 노드가 없는 경우
		return -1; // 삭제 실패 처리
	if(cur==plist->head){
		plist->head=cur->next;
		cur->next->pre=cur->pre;
	} // head 노드를 삭제하는 경우
	else if(cur==plist->tail){
		plist->tail=cur->pre; // tail 노드를 삭제하는 경우
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
	Node* cur= fsearch(plist,location); // 탐색을 통해 삽입하고자 하는 노드를 찾는다
	Node* newnode= (Node*)malloc(sizeof(Node));
	newnode->data=data;
	newnode->pre=NULL;
	newnode->next=NULL;

	if(cur==NULL) // 원하는 노드가 없는 경우
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