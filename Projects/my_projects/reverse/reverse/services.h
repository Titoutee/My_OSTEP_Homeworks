#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

typedef struct LinkedList {
  char *data;
  struct LinkedList *next;
} LinkedList;

void init(LinkedList list);
void push(LinkedList **head, char *data, size_t nread);
void clean_up(LinkedList *head);
int len(LinkedList *head);
void print_normal(LinkedList *head, FILE *fp);
// void reverse(LinkedList **head);
void push_front(LinkedList **head, char *data);
