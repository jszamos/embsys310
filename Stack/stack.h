/*************************************************************************************
* File Name             : stack.h
* Author                : Janos Szamosfalvi
* Date Created          : 11/15/2020
* Descripton            : header for stack
*************************************************************************************/
#ifndef _STACK_H_
#define _STACK_H_

// some global defines, have to be visible for testing
#define MAX_SIZE    512
#define SUCCESS      0
#define STACK_FULL  -1
#define STACK_EMPTY -2

// function prototypes
void init(void);            // initialize the stack internals
void push(int data);        // push an element onto the stack
int pop(void);              // pop an element off the stack
int isempty(void);          // returns 1 if stack is empty
int isfull(void);           // returns 1 if stack is full

#endif

