/*************************************************************************************
* File Name             : stack.c
* Author                : Janos Szamosfalvi
* Date Created          : 11/28/2020
* Descripton            : Re-implementation of the stack with only pointers 
*                       : this is a stack that grows from smaller index to higher 
*                       : top points to stack[0], bottom to the last elements
*                       : curr is where push/pop takes place 
*************************************************************************************/

#include "stack.h"

int g_result;           // global result, similar to LastError
int stack[MAX_SIZE];    // use an array for the stack to keep it real simple 

const int*  top; 
const int*  bottom;   
int*        curr;


void init(void)
{
    top =   &stack[0];
    curr =  &stack[0] - 1;
    bottom= &stack[MAX_SIZE - 1];
}    
    
void push(int data)
{
    if (!isfull()) 
    {
        *(++curr) = data;
        g_result = SUCCESS;
    }
    else 
        g_result = STACK_FULL; 
}

int pop(void)
{
    int data;
    if (!isempty())
    {
        data = *curr--;
        g_result = SUCCESS;
        return data;
    }
    else
    {
        g_result = STACK_EMPTY;
        return STACK_EMPTY;
    }
}

int isempty(void)
{
    return (curr + 1 == top); 
}
 
int isfull(void)
{
    return (curr == bottom); 
}
