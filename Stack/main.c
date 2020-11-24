/*************************************************************************************
* File Name             : main.c
* Author                : Janos Szamosfalvi
* Date Created          : 11/15/2020
* Descripton            : main program to drive and test stack
*************************************************************************************/

#include <assert.h>
#include "stack.h"

extern int g_result; 

int main()
{
    int value; 
  
    // test #1 - initial init()
    init(); 
    assert(1 == isempty()); 
    assert(1 != isfull());
  
    // test #2 --  pop() on an empty stack
    value = pop(); 
    assert(STACK_EMPTY == value); 
    assert(STACK_EMPTY == g_result); 
  
    // test #3 -- push() when the stack can accept data -- all should pass
    for (int i = 0; i < MAX_SIZE; i++) 
    {
        assert(1 != isfull());          // must come before push()
        push(i); 
        assert(SUCCESS == g_result);    // check result code
    }
    
    // test #4 -- verify stack is full 
    assert(1 == isfull());
    
    // test #5 -- push() when the stack if full, and so it should fail
    push(666); 
    assert(STACK_FULL == g_result); 
    
    // test #6 - pop() when they should all pass
    for (int i = 0; i < MAX_SIZE; i++) 
    {
        assert(1 != isempty());             // emptinesscheck must come before pop()
        assert(MAX_SIZE - 1 - i == pop());  // verify we're getting the right value
        assert(SUCCESS == g_result);        // verify result code
    }
    
    // test #7 - verify stack is now empty
    assert(1 == isempty()); 
    
    // test #8 -- pop() on a freshly emptied stack, and so it should fail 
    assert(STACK_EMPTY == pop()); 
    assert(STACK_EMPTY == g_result); 
    
    // test #9 -- lastly, verify that init() will wipe a full stack clear
    for (int i = 0; i < MAX_SIZE; i++) 
    {
        push(i); 
        assert(SUCCESS == g_result);    // check result code
    }
    
    // test #9a -- verify stack is full and not empty
    assert(1 == isfull());
    assert(1 != isempty());
    
    init(); 
    
    // test #9b - verify the stack is empty after init()
    assert(1 != isfull());
    assert(1 == isempty());
  
    return 0;
}
