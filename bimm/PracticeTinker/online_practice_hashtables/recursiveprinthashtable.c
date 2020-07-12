#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

#define HASH_TABLE 5

typedef struct person
{
    char *name;
    int age;
    struct person *next;
}
person;

person *hash_table[HASH_TABLE];

void init_hash_table ()
{
    for (int i = 0; i < HASH_TABLE; i++)
    {
         hash_table[i] = NULL;
    }
}

int hash(person *name)
{
    int index = name->name[0];
    index = (index * 9) % 5;
    return index;
}

void assign(person *person)
{
    //check if the entry is used and if so, set the pointer to the person next
    if (hash_table[hash(person)] == NULL)
    {
        hash_table[hash(person)] = person;
        return;
    }
    else
    {
        person->next = hash_table[hash(person)];
        hash_table[hash(person)] = person;
    }
    hash_table[hash(person)] = person;
    return;
}

void printlistentry(person *entry)
{
    //called because the entry in the hashtable isn't null so print the name
    printf(" -> %s", entry->name);
    //if the next entry is null, you've reached the end of the list, return the previous name
    if (entry->next == NULL)
    {
        return;
    }
    //if the next isn't null call the print function on the next value
    else
    {
        printlistentry(entry->next);
    }
    return;
}

void printlist()
{
    printf("List is currently:\n");

    for (int i = 0; i < HASH_TABLE; i++)
    {
    //you need the conditional because if you try to print the string from a NULL pointer, you'll segfault since there's nothing there
        if (hash_table[i] == NULL)
        {
            printf("Entry %i empty\n", i+1);
        }
        //if the entry isn't empty
        else
        {
            //print the list
            printf("Entry %i",i+1);
            printlistentry(hash_table[i]);
            printf("\n");
        }
    }
}

void create()
{
    person *newguy = malloc(sizeof(person));
    newguy->name = get_string("What is this person's name? ");
    assign(newguy);
    printlist();
}

int main (void)
{
    init_hash_table();
    create();
    create();
    create();
    create();
    create();
    create();
}

/*
    old list of creating people to put in the list
    if this pointer is initialized as NULL, you'll segfault when you try to assign values
    person *jith = malloc(sizeof(person));
    jith->name = "Jith";
    jith->age = 33;
    printf("Index of Jith's name is %i\n", hash(jith));
    assign(jith);

    person *joe = malloc(sizeof(person));
    joe->name = "Joe";
    joe->age = 33;
    printf("Index of Joe's name is %i\n", hash(joe));
    jith->next = joe;

    person *bimm = malloc(sizeof(person));
    bimm->name = "Bimm";
    bimm->age = 33;
    printf("Index of bimm's name is %i\n", hash(bimm));
    assign(bimm);

    person *bob = malloc(sizeof(person));
    bob->name = "Bob";
    bob->age = 33;
    printf("Index of Bob's name is %i\n", hash(bob));
    assign(bob);

    person *billy = malloc(sizeof(person));
    billy->name = "Billy";
    billy->age = 33;
    printf("Index of Billy's name is %i\n", hash(billy));
    assign(billy);
*/