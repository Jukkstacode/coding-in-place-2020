//https://www.youtube.com/watch?v=2Ti5yvumFTU
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct person
{
    char name[MAX_NAME];
    int age;
    struct person *next;
    //TODO add other attributes
}
person;

person *hash_table[TABLE_SIZE];

unsigned int hash(char *name)
{
    int length = strlen(name);
    int checksum = 0;
    for (int i = 0; i < length; i++)
    {
        checksum += name[i];
        checksum = (checksum * name[i]) % TABLE_SIZE;
    }
    return checksum;
}

void init_hash_table()
{
    // set the hash table pointers equal to NULL
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
}

void print_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        printf("Table Index[%i]", i);
        while(hash_table[i] != NULL)
        {
            printf(" => %s", hash_table[i]->name);
            hash_table[i] = hash_table[i]->next;
        }
        printf("\n");
    }
}

bool hash_table_insert (person *p)
{
    if (p == NULL)
    {
        return 1;
    }
    int index = hash(p->name);
    p->next = hash_table[index];
    hash_table[index] = p;
    return true;
    
}

//find person in table
person *hash_table_lookup (char *name)
{
    int index = hash(name);
    person *tmp = hash_table[index];
    
    while (tmp != NULL && strcmp(tmp->name, name) == 0)
    {
        tmp=tmp->next;
    }
    return tmp;
}

int main ()
{
    init_hash_table();

    person jacob = {.name = "Jacob", .age = 256};
    person stella = {.name = "Stella", .age = 100};
    person bimm = {.name = "Bimm", .age = 13};
    person lily = {.name = "Lily", .age = 26};
    person frank = {.name = "Frank", .age = 26};
    person ang = {.name = "Ang", .age = 5};
    
    hash_table_insert(&jacob);
    hash_table_insert(&stella);
    hash_table_insert(&bimm);
    hash_table_insert(&lily);
    hash_table_insert(&frank);
    hash_table_insert(&ang);
    
    print_table();

    person *tmp = hash_table_lookup("Ang");
    
    if (tmp == NULL)
    {
        printf("Not found\n");
    }
    else
    {
        printf("Found %s\n", tmp->name);
    }
    // printf("Jacob => %u\n", hash("Jacob"));
    // printf("Stella => %u\n", hash("Stella"));
    // printf("Bimm => %u\n", hash("Bimm"));    
    // printf("Lily => %u\n", hash("Lily"));
    // printf("Frank => %u\n", hash("Frank"));
    // printf("Billy => %u\n", hash("Billy"));    
    // printf("Beauregard => %u\n", hash("Beauregard"));
    // printf("Sokka => %u\n", hash("Sokka"));
    // printf("Kelly => %u\n", hash("Kelly"));
    // printf("Ang => %u\n", hash("Ang"));
    // printf("Toph => %u\n", hash("Toph"));
}