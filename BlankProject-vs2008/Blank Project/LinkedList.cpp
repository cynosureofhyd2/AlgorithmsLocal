#include "LinkedList.h"
#include <iostream>
#include "console.h"
using namespace std;
#include "random.h"

struct node {
	int data;
	struct node* next;
};

static node* CreateNewNode(int data)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

static void push(struct node*& headRef, int data)
{
	struct node* newNode = CreateNewNode(data);
	newNode->next = headRef;
	headRef = newNode;
}

struct node* CreateRandomList(int number)
{
	int i = 0; 
	struct node* newList = NULL;
	while(i < number)
	{
		struct node* newNode = CreateNewNode(randomInteger(1, number));
		push(newList, newNode->data);
		i++;
	}
	return newList;
}

static int Length(struct node*& head)
{
	int count = 0;
	struct node* current = head;
	if(head == NULL)
		return 0;
	else
	{
		while(current != NULL)
		{
			current = current->next;
			count++;
		}
	}
	return count;
}

int GetNth(struct node* list, int N)
{
	struct node* current = list;

	int counter = 0;
	if(list == NULL)
		return -100;
	if(N < 0)
		return -100;
	else
	{
		while(current != NULL && counter < N)
		{
			current = current->next;
			counter++;
		}
	}
	return current->data;
}

void DeleteListIteratively(struct node*& list)
{
	if(list == NULL)
		return;
	else
	{
		struct node * current = list;
		struct node* next = current;
		while(current != NULL)
		{
			next = current->next;
			free(current);
			current = next;
		}
		list = NULL;
	}
}

void DeleteListRecursively(struct node*& list)
{
	if(list == NULL)
		return;
	DeleteListRecursively(list->next);
	free(list);
	list = NULL;
}

int main()
{	
	struct node* newList  = CreateRandomList(10);
	cout << Length(newList) << endl;
	int nthNode = GetNth(newList, 5);
	cout << nthNode << endl;
	DeleteListRecursively(newList);
	return 0;
}

