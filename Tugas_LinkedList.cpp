#include<stdio.h>
#include<stdlib.h>

struct tnode
{
	int x;
	tnode *next;
	tnode *prev;//4
} *head, *tail, *curr;

void push_front(int value)
{
	struct tnode *node = (tnode*)malloc(sizeof(tnode));
	node->x = value;
	
	if(head == NULL)
	{
		head = tail = node;
		node->next = NULL;
		node->prev = NULL;//3
	}
	else
	{
		node->next = head;
		head->prev = node;//1
		head = node;
		head->prev = NULL; //2
	}
}

void push_back(int value)
{
	struct tnode *node = (tnode*)malloc(sizeof(tnode));
	node->x = value;
	
	if(head == NULL)
	{
		head = tail = node;
		tail->next = NULL;
		tail->prev = NULL;
	}
	else
	{
		tail->next = node;
		node->prev = tail;
		tail = node;
		tail->next = NULL;
	}
}

void push_mid(int value, int searchKey)
{
	//create node
	struct tnode *node = (tnode*)malloc(sizeof(tnode));
	node->x = value;
	
	//checking first node
	if(head == NULL)
	{
		head = tail = node;
		tail->next = NULL;
	}
	else
	{
		struct tnode *curr = head;
		while(curr!=NULL)
		{
			if(curr->x==searchKey)
			{
				if(curr==tail)
				{
					push_back(value);
				}
				else
				{
					node->next = curr->next;
					curr->next = node;
				}
				break;
			}
			//pindahin posisi curr jika tdk ketemu
			curr = curr->next;
		}
		if(curr==NULL)
		{
			printf("Data %d is not found\n",searchKey);
		}
	}
}

void printList()
{
	if(head==NULL)
	{
		printf("There is no data\n");
		return;
	}
	
	//struct tnode *curr = head;
	curr=head;
	while(curr!=NULL)
	{
		printf("%d ",curr->x);
		curr = curr->next;
	}
}

void del_back()
{
	if(head==NULL)
	{
		printf("There is no data\n");
		//return;
	}
	else
	{
		if(head==tail)
		{
			free(head);
			head=tail=NULL;
		}
		else
		{
			struct tnode *del = head;
			while(del->next!=tail)
			{
				del = del->next;
			}
			free(tail);
			tail=del;
			tail->next=NULL;
		}
	}
}

void del_front()
{
	if(head==NULL)
	{
		printf("There is no data\n");
		//return;
	}
	else
	{
		if(head==tail)
		{
			free(head);
			head=tail=NULL;
		}
		else
		{
			struct tnode *del = head;
			head = head->next;
			free(del);
		}
	}
}

void del_mid(int value)
{
    if(head == NULL)
    {
        printf("There is no data\n");
        return;
    }
    struct tnode *curr = head;
    while(curr != NULL)
    {
        if(curr->x == value)
        {
            if(curr == head)
            {
                del_front();
            }
            else if(curr == tail)
            {
                del_back();
            }
            else
            {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                free(curr);
            }
            return;
        }
        curr = curr->next;
    }
    printf("Data %d is not found\n", value);
}

int main()
{
	printf("Linked List\n");
	
	push_front(76);
	push_front(90);
	push_front(45);
	push_mid(33,90);
	//45 90 76
	//76 90 33 45
	del_back();
	//76 90 33
	del_front();
	//90 33
	push_front(21);
	del_mid(90);
	
	printList();getchar();
	
	return 0;
}
