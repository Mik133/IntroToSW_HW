#include "stack.h"

#define MAIN_STACK 0
#define TOP_INIT 0

struct stack *stack_create(int size,
		clone_t clone_func,
		destroy_t destroy_func,
		print_t print_func)
{
	if(size <= 0)
		return NULL;
	
	struct stack *stack = malloc(sizeof(struct stack)*size);
	if(stack == NULL)
		return NULL;
	
	for(int i = 0;i < size;i++)
	{
		stack[i].size = size;//Total size
		stack[i].top = TOP_INIT;//The index of the top of the stack
		stack[i].clone_func = clone_func;//Function allocatin space for item to be stored 
		stack[i].destroy_func = destroy_func;//Function releasing space allocated for item
 		stack[i].print_func = print_func;//Function printing given item
	}
	
	return stack;
}

bool stack_destroy(struct stack *stack)
{
	for(int i = 0;i < stack[MAIN_STACK].size;i++)
		if(stack[i].item != NULL) stack[i].destroy_func(stack[i].item);
	//for(int i = 0;i < stack[MAIN_STACK].size;i++)
		//if(stack[i].item != NULL) free(stack[i].item);
	free(stack);
	stack = NULL;
	if(stack == NULL)
		return SUCCESS;
	else
		return FAIL;
	
}

bool stack_push(struct stack *stack,elem_t item)
{
	if(stack[MAIN_STACK].top == stack[MAIN_STACK].size)
		return FAIL;
	else 
	{
		stack[stack[MAIN_STACK].top].item = 
				stack[stack[MAIN_STACK].top].clone_func(item);
		stack[MAIN_STACK].top++;
		return SUCCESS;
	}
}

void stack_pop(struct stack *stack)
{
	if(stack_is_empty(stack) == false)
	{
		stack[stack[MAIN_STACK].top - 1]
				  .destroy_func(stack[stack[MAIN_STACK].top - 1].item);
		stack[stack[MAIN_STACK].top - 1].item = NULL;
		stack[MAIN_STACK].top--;
	}
}

elem_t stack_peek(struct stack *stack)
{
	if(stack_is_empty(stack) == true)
		return NULL;
	else
		return stack[stack[MAIN_STACK].top - 1].item;
}

bool stack_is_empty(struct stack *stack)
{
	if(stack[MAIN_STACK].top == 0)
		return true;
	else
		return false;
}

size_t stack_size(struct stack *stack)
{
	return stack[MAIN_STACK].top;	
}

size_t stack_capacity(struct stack *stack)
{
	return stack[MAIN_STACK].size - stack[MAIN_STACK].top;
}

void stack_print(struct stack *stack)
{
	for(int i = stack[MAIN_STACK].top;i > 0;i--)
	{
		stack[i - 1].print_func(stack[i - 1].item);
	}
}


