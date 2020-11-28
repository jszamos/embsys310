#define LIL 1
#define BIG 2

int main()
{
    int endian; 
    unsigned int i = 0xFF000000;
  
    // tyuecast int i with a char pointer, so depending on the endianness, 
    // the char it's pointing to can be either 0 or '\255'
    char* ch = (char *)&i;
  
    if (*ch)
        endian  = BIG;
    else 
        endian = LIL;

    return endian; 
}
