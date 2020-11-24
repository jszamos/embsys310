/*************************************************************************************
* File Name             : stack.c
* Author                : Janos Szamosfalvi
* Date Created          : 11/15/2020
* Descripton            : Implementation of the stack -- to keep everything as 
*                       : simple as possible, it uses an array as an underlying 
*                       : data structure and a stack pointer (index in reality)
*                       : into that array that can get incremented/decremented
*                       : as data is added/removed from the stack.
*************************************************************************************/

#include "stack.h"

int top;                // stack pointer (index)
int g_result;           // global result, similar to LastError
int stack[MAX_SIZE];    // use an array for the stack to keep it real simple 

void init(void)
{
    top = -1;
    g_result = SUCCESS;
}

void push(int data)
{
    if (!isfull()) 
    {
        top++;
        stack[top] = data; 
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
        data = stack[top]; 
        top--;
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
    return (top <= -1); 
}
 
int isfull(void)
{
    return (top >= MAX_SIZE - 1); 
}

