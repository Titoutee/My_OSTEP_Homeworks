#include "services.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char *argv[]) {
  if (argc > 3) {
    fprintf(stderr, "usage: reverse <input> <output>\n");
    exit(EXIT_FAILURE);
  }

  if (argc == 3) {
    if (*argv[1] == *argv[2]) {
      fprintf(stderr, "reverse: input and output file must differ\n");
      exit(EXIT_FAILURE);
    }
  }

  FILE *source = (argc >= 2) ? fopen(argv[1], "r") : stdin;
  FILE *destination = (argc >= 3) ? fopen(argv[2], "rw+") : stdout;

  if (source == NULL) {
    fprintf(stderr, "reverse: cannot open file \'%s\'\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  if (destination == NULL) {
    fprintf(stderr, "reverse: cannot open file \'%s\'\n", argv[2]);
    exit(EXIT_FAILURE);
  }

  char *buff = NULL;
  size_t nread;
  LinkedList *head = NULL;

  while((nread = getline(&buff, &nread, source)) != -1) {
    push(&head, buff, nread);
  } 
  print_normal(head, destination);

  // Cleaning up

  free(buff);
  clean_up(head);
  fclose(source);
  fclose(destination);
  exit(EXIT_SUCCESS);
}

// Pushed an element after head;
void push(LinkedList **head,
          char *data, size_t nread) { // Append an element to the linked list
  LinkedList *new;
  if((new = malloc(sizeof(LinkedList))) == NULL) {
    perror("malloc failed\n");
    exit(EXIT_FAILURE);
  }
  new->data = strdup(data);
  new->data[nread] = '\0'; // Consider a string
  new->next = *head;
  *head = new;
}

int len(LinkedList *head) {
  LinkedList *current = head;
  int count = 0;
  while (current != NULL) {
    count++;
    current = current->next;
  }
  return count;
}

void print_normal(LinkedList *head, FILE *fp) {
  LinkedList *current = head;

  while (current != NULL) {
    fprintf(fp, "%s", current->data);
    current = current->next;
  }
}

void clean_up(LinkedList *head) {
  LinkedList *current = head;

  while (current->next != NULL) {
    LinkedList *temp = current->next;
    free(current->data);
    free(current);  // Dangling here
    current = temp; // re-initialized
  }
  free(current->data);
  free(current);
}