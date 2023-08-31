#include "services.h"
#include "stdio.h"
#include "stdlib.h"
#include "vector.h"

#define REST_SIZE 512

int main(int argc, char *argv[]) {
  if (argc > 3) {
    fprintf(stderr, "usage: reverse <input> <output>\n");
    exit(EXIT_FAILURE);
  }

  if (argc == 3) {
    if (argv[1] == argv[2]) {
      fprintf(stderr, "Input and output file must differ\n");
      exit(EXIT_FAILURE);
    }
  }

  FILE *source = (argc == 2) ? fopen(argv[1], "r") : stdin;
  FILE *destination = (argc == 3) ? fopen(argv[2], "r") : stdout;

  if (source == NULL) {
    fprintf(stderr, "error: cannot open file \'%s\'\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  if (destination == NULL) {
    fprintf(stderr, "error: cannot open file \'%s\'\n", argv[2]);
    exit(EXIT_FAILURE);
  }

  char *buff = NULL;
  size_t buff_len = 0;
  long n_read = getline(&buff, &buff_len, source);
  if (n_read == -1) {
    fprintf(stderr, "Cannot read line for some reason...");
    exit(EXIT_FAILURE);
  }
  LinkedList *head = malloc(sizeof(LinkedList));
  head->data = buff; // First node is first line, so we have our header
  head->next = NULL;

  // Reinit
  buff = NULL;
  buff_len = 0;

  // Getline
  while (getline(&buff, &buff_len, source) != -1) {
    push(head, buff);
    buff = NULL; // For automatic allocation
  }
  free(buff);

  // Last line
  Vec *rest = malloc(sizeof(Vec));
  init_vec(rest);
  char c;
  while ((c = fgetc(source)) != EOF) {
    vec_push(rest, c);
  }
  push(head, inner(rest));
  free(rest);

  reverse(&head);
  print(head);
  printf("\n");

  // Cleaning up
  clean_up(head);
  //fclose(source);
  fclose(destination);
  return 0;
}

void push(LinkedList *head,
          char *data) { // Append an element to the linked list
  LinkedList *current = head;

  while (current->next != NULL) { // We go to end of our linked list
    current = current->next;
  }

  current->next = (LinkedList *)malloc(sizeof(LinkedList));
  if (current->next == NULL) {
    fprintf(stderr, "malloc failed\n");
    exit(EXIT_FAILURE);
  }
  current = current->next;
  current->data = data;
  current->next = NULL;
}

void print(LinkedList *head) {
  LinkedList *current = head;
  // printf("HEAD->");
  while (current->next != NULL) {
    printf("%s", current->data);
    current = current->next;
  }
  // printf("NULL");
}

void clean_up(LinkedList *head) {
  LinkedList *current = head;

  while (current->next != NULL) {
    LinkedList *temp = current->next;
    free(current->data);
    free(current);  // Dangling here
    current = temp; // re-initialized
  }
  free(current);
}

void reverse(LinkedList **head) {
  LinkedList *current = *head;
  LinkedList *prev = NULL;
  LinkedList *next = NULL;

  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  *head = prev; // Last node here, so prev is new head
}