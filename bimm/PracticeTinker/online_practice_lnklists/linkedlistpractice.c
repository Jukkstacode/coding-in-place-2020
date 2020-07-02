// https://www.youtube.com/watch?v=VOpjAHCee7c

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

typedef struct node
{
    int value;
    struct node* next;
}
node;

//prints the linked list given the first pointer
void printList (node *head)
{
    node *tmp = head;
    printf("%i", tmp->value);
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
        printf(" -> %i",tmp->value);
    }
    printf("\n");
}

node *createNode (int value)
{
    node *result = malloc(sizeof(node));
    result->value = value;
    result->next = NULL;
    return result;
}

//create a function for inserting a node at the front of the list
node *insertAtHead (node *old_head, int value)
{
    node *new_head = createNode(value);
    new_head->next = old_head;
    return new_head;
}


node *insertAtTail (node *head, int value)
{
    //crawl the list until you find the last node
    while (head->next != NULL)
    {
        head = head->next;
    }
    //create a new node and point to it from the previous last node
    head->next = createNode(value);
    return head->next;
}

node *findNode(node *head, int tgtValue)
{
    //start count at 1 to keep track of number of nodes
    int count = 1;
    //iterate through list if 
    while(head->next != NULL)
    {
        //if target value is found, return the pointer to that value
        if (head->value == tgtValue)
        {
            printf("node at %p is %i item in list\n", head->next, count);
            return head;
        }
        //update pointer to next node
        head = head->next;
        //update counter
        count++;
    }
    //make one final check on the last value to determine if it's the target value
    if (head->value == tgtValue)
    {
        printf("node at %p is %i item in list\n", head->next, count);
        return head;
    }
    printf("value not found in list of %i items\n", count);
    return NULL;
}

node *insertNodeAfter (node *head, int createValue, int tgtValue)
{
    node *tmp = createNode(createValue);
    while(head->value != tgtValue)
    {
        head = head->next;
    }
    tmp->next = head->next;
    head->next = tmp;
    return head->next;
}

int main (void)
{
    node *head = createNode(5);
    head = insertAtHead(head, 1);
    head = insertAtHead(head, 0);
    
    node *tail = insertAtTail(head, 7);
    tail = insertAtTail(head, 9);
    tail = insertAtTail(head, 899);
    
    int searchValue = get_int("What value are you looking for: ");
    findNode(head, searchValue);
    
    int insertValue = get_int("What value do you want to insert in the middle: ");
    insertNodeAfter(head, insertValue, 0);
    
    printf("head is pointing to %p\n", &head);
    printf("value at the point is %i\n", head->value);

    printList(head);



    //This is better as it just iterates the nodes through a loop, but we can do better
    /*
    node *head = NULL;
    node *tmp;

    for (int i=0; i < 25; i++)
    {
        tmp = createNode(i);
        tmp->next = head;
        head = tmp;
    }
    printList(head);
    */

    //this uses functions and pointers to make the list, but can still do better
    /*

    node *head;
    node *tmp;

    tmp = createNode(32);
    head = tmp;
    tmp = createNode(8);
    tmp->next = head;
    head = tmp;
    tmp = createNode(45);
    tmp->next = head;
    head = tmp;
    printList(head);
    */

    //declaring a bunch of nodes and linking them via addressing. Not the typical route.
    /*
    node n1, n2, n3;
    node *head;
    n1.value = 45;
    n2.value = 8;
    n3.value = 32;

    head = &n3;

    n3.next = &n1;
    n2.next = NULL;
    n1.next = &n2;

    node n4;
    n4.value = 23;
    n4.next = &n2;
    n1.next = &n4;

    printList(head);

    */
    return 0;
}