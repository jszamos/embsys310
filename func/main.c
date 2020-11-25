// tasting 5 parameters with function 

int func1(int p0, int p1, int p2, int p3, int p4)
//void func1(int p0, int p1, int p2, int p3, int p4)
{
    int sum = p0 + p1 + p2 + p3 + p4;
    return sum;
}

void func2()
{
    int retval = func1(1, 2, 3, 4, 5); 
    //func1(1, 2, 3, 4, 5);
}    

int main()
{
    func2(); 
    return 0;
}
