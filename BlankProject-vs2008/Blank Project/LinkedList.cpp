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

int Pop(struct node*& head)
{
	int headdata ;
	if(head == NULL)
		return -100;
	else
	{
		struct node* current = head;
		headdata = head->data;
		head = head->next;
		free(current);
	}
	return headdata;
}	

void InsertNth(struct node*& head, int position, int data)
{
	struct node* newNode = CreateNewNode(data);
	if(head == NULL)
		return;
	if(position < 0)
		return;
	if(position == 0)
		push(head, data);
	else
	{
		struct node* current = head;
		int i = 0; 
		while(i < position && current != NULL)
		{
			current = current->next;
			i++;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
}

void PrintListIteratively(struct node* list)
{
	if(list == NULL)
		return;
	else
	{
		struct node * current = list;
		cout << "Printing List Iteratively " << endl;
		while(current != NULL)
		{
			cout << current->data << endl;
			current = current->next;
		}
	}
}

void PrintListRecursively(struct node* list)
{
	cout << "Printing List Recursively " << endl;
	if(list == NULL)
		return;
	else
	{
		PrintListRecursively(list->next);
		cout << list->data << endl;
	}
}

// Given a list that is sorted in increasing order, insert a new node which is in its correct place in the sorted list
void SortedInsert(struct node*& headRef, struct node* newNode)
{
		struct node* current = headRef;
		if(headRef == NULL)
		{
			newNode->next = headRef;
			headRef = newNode;
		}
		if(current != NULL)
		{
			while(current->next != NULL && newNode->data > current->next->data)
			{
				current = current->next;
			}
			newNode->next = current->next;
			current->next = newNode;
		}
}

// Make use of the Sorted Insert to create a Sorted List
void InsertSort(struct node*& headRef)
{
	struct node* result = NULL;
	struct node* current = headRef;
	struct node* next; 
		while(current != NULL)
		{
			next = current->next;
			SortedInsert(result, current);
			current = next;
		}
		headRef = result;	
}

/*Takes 2 Lists a nd b and appends b onto end of a and then sets b to NULL */
void Append(struct node*& aref, struct node*& bref)
{
	if(aref == NULL || bref == NULL)
		return;
	else
	{
		struct node* current = aref;
		while(current->next != NULL)
		{
			current = current->next;
		}
		current->next = bref;
		bref = NULL;
	}
}


void FrontBackSplit(struct node* source, struct node*& front, struct node*& back)
{
	if(source == NULL)
		return;
	else
	{
		struct node* slow = source;
		struct node* fast = source;
		//front = CreateNewNode(slow->data);
		while(fast!= NULL && fast->next != NULL)
		{
			push(front, slow->data);
			slow = slow->next;
			fast = fast->next->next;
		}
		if(fast->next == NULL)
		{
			push(front, slow->data);
			slow = slow->next;
		}
		
		while(slow != NULL)
		{
			push(back, slow->data);
			slow = slow->next;
		}
	}
}

/*Takes a Sorted List and removes Duplicates from it */
void RemoveDuplicates(struct node*& head)
{
	struct node* current = head;
	struct node* temp = NULL;
	while(current != NULL)
	{
		if(current->next != NULL && current->data == current->next->data)
		{
			temp = current;
			if(temp->next != NULL)
			{
				while(temp->data == temp->next->data)
				{
					temp = temp->next;
				}
			}
			current->next = temp->next;
		}
		current = current->next;
	}
}
/*This Function will take the first node from the second list and append it to beginning of first list*/
void MoveNode(struct node*& dest, struct node*& source)
{
	if(dest == NULL)
		return;
	struct node* nextsource = NULL;
	if(source != NULL)
	{
		push(dest, source->data);
		nextsource = source->next;
		free(source);
		source = nextsource;
	}
}

void AlternatingSplit(struct node* source, struct node*& aref, struct node*& bref)
{
	
}

int main()
{	
	struct node* newList  = CreateRandomList(10);
	cout << Length(newList) << endl;
	int nthNode = GetNth(newList, 5);
	cout << nthNode << endl;
	// DeleteListRecursively(newList);
	//cout << Pop(newList) << endl;
	PrintListIteratively(newList);
	InsertSort(newList);
	PrintListIteratively(newList);
	RemoveDuplicates(newList);
	/*InsertNth(newList, 2, 10);
	
	cout << Length(newList) << endl;
	cout << GetNth(newList,3) << endl;*/
	struct node* anotherList = CreateRandomList(3);
	MoveNode(newList, anotherList);
	//Append(newList, anotherList);
	cout << "Final Length " << endl;
	cout << Length(newList) << endl;
	struct node* aRef = NULL, *bRef = NULL;
	FrontBackSplit(newList, aRef, bRef);
	int left = Length(aRef);
	int right = Length(bRef);
	return 0;
}

