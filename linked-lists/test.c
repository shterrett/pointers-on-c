#include "minunit.h"
#include <assert.h>

typedef struct NODE {
  struct NODE *prev;
  struct NODE *next;
  int value;
} node;

node *new_node(int value) {
  node *n = malloc(sizeof(node));
  n->next = NULL;
  n->prev = NULL;
  n->value = value;
  return n;
}

node *new_queue(void) {
  node *q = malloc(sizeof(node));
  q->prev = NULL;
  q->next = NULL;
  return q;
}

int queue_empty(node *queue) {
  if (queue->next == NULL) {
    assert(queue->prev == NULL);
    return 1;
  } else {
    assert(queue->prev != NULL);
    return 0;
  }
}

void queue_push(node *queue, int value) {
  node *tail = queue->prev;
  node *new = new_node(value);
  if (tail != NULL) {
    tail->next = new;
  }
  queue->prev = new;
  if (queue->next == NULL) {
    queue->next = new;
  }
}

int queue_pop(node *queue) {
  assert(!queue_empty(queue));
  node *head = queue->next;
  int value = head->value;
  queue->next = head->next;
  if (head->next == NULL) {
    queue->prev = NULL;
  } else {
    head->next->prev = NULL;
  }
  free(head);
  return value;
}

node *new_stack(void) {
  return new_queue();
}

int stack_empty(node *stack) {
  return stack->next == NULL;
}

void stack_push(node *stack, int value) {
  node *new = new_node(value);
  new->next = stack->next;
  stack->next = new;
}

int stack_pop(node *stack) {
  assert(!stack_empty(stack));
  node *head = stack->next;
  int value = head->value;
  stack->next = head->next;
  free(head);
  return value;
}


char *test_queue(void) {
  node *queue = new_queue();
  queue_push(queue, 1);
  queue_push(queue, 3);
  queue_push(queue, 2);

  mu_assert(queue_pop(queue) == 1, "Expected first element of queue to be 1");
  mu_assert(queue_pop(queue) == 3, "Expected second element of queue to be 3");
  mu_assert(queue_pop(queue) == 2, "Expected third element of queue to be 2");

  return NULL;
}

char *test_queue_empty(void) {
  node *queue = new_queue();
  mu_assert(queue_empty(queue) == 1, "New queue should be empty");

  queue_push(queue, 1);
  mu_assert(queue_empty(queue) == 0, "Queue not empty after push");

  queue_pop(queue);
  mu_assert(queue_empty(queue) == 1, "Queue should be empty after last value popped");

  return NULL;
}

char *test_stack(void) {
  node *stack = new_stack();
  stack_push(stack, 1);
  stack_push(stack, 3);
  stack_push(stack, 2);

  mu_assert(stack_pop(stack) == 2, "Expected first element of stack to be 2");
  mu_assert(stack_pop(stack) == 3, "Expected second element of stack to be 3");
  mu_assert(stack_pop(stack) == 1, "Expected third element of stack to be 1");

  return NULL;
}

char *test_stack_empty(void) {
  node *stack = new_stack();
  mu_assert(stack_empty(stack) == 1, "New stack should be empty");

  stack_push(stack, 1);
  mu_assert(stack_empty(stack) == 0, "Stack not empty after push");

  stack_pop(stack);
  mu_assert(stack_empty(stack) == 1, "Stack should be empty after last value popped");

  return NULL;
}

char *all_tests(void) {
  mu_suite_start();
  mu_run_test(test_queue);
  mu_run_test(test_queue_empty);
  mu_run_test(test_stack);
  mu_run_test(test_stack_empty);

  return NULL;
}

RUN_TESTS(all_tests);
