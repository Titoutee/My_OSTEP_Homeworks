#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"

typedef struct LinkedList{
    char *data;
    struct LinkedList *next;
} LinkedList;

void init(LinkedList list);
void push(LinkedList *head, char *data);
void print(LinkedList *head);
void clean_up(LinkedList *head);
int len(LinkedList *head);
void reverse(LinkedList **head);