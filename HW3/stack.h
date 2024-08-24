#ifndef STACK_H
#define STACK_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "common.h"

typedef void *elem_t;
typedef elem_t (*clone_t)(elem_t e);
typedef void (*destroy_t)(elem_t e);
typedef void (*print_t)(elem_t e);

struct stack{
	elem_t item;
	int size;
	int top;
	clone_t clone_func;
	destroy_t destroy_func;
	print_t print_func;
};

struct stack *stack_create(int size,clone_t clone_func,destroy_t destroy_func,print_t print_func);
bool stack_destroy(struct stack *stack);
bool stack_push(struct stack *stack,elem_t item);
void stack_pop(struct stack *stack);
elem_t stack_peek(struct stack *stack);
bool stack_is_empty(struct stack *stack);
size_t stack_size(struct stack *stack);
size_t stack_capacity(struct stack *stack);
void stack_print(struct stack *stack);

#endif