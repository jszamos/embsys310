
// code for assignment02

int counter = 0; 

int main()
{
    // int counter = 0; 
    // unsigned counter = 0; 
    int *p_int = (int *)0x20000000;
    ++(*p_int);
    ++(*p_int);
    ++(*p_int);
    counter++; 
#if 0
    counter++;
    counter++; 
    counter++;
    counter++; 
    counter++; 
    counter++;
#endif  
    return 0;
}
