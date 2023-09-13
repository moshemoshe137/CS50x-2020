#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n = 50;
    printf("%i\n", n);
    
    // print where something is in memory
    // & means "address of"
    // * means look inside a particular memory address. "Dereference" opperator. 
    
    printf("%p\n", &n); // prints the mem address
    // %p stands for pointer 
    
    
    printf("%i\n", *&n); // just prints n
    
    int *p = &n;  // must ALWAYS have the * to declare a pointer. Int is the type of the thing we're pointing at. 
    // p has a type of "int star".
    
    
    printf("%p\n", p);
    printf("%i\n", *p);
    
    
    
    
    
    
    string s = "HI!";
    printf("%s\n", s);
    printf("%p\n", &s);
    printf("%p\n", &s[0]);
    printf("%p\n", &s[1]);
    printf("%p\n", &s[2]);
    
    
    // strings are just addresses
    // they are the address of the 1st character
    // string is another word for char *s = "Hi!"
    
    printf("%c\n", s[0]);
    printf("%c\n", s[1]);
    printf("%c\n", s[2]);
    
    char *t = "HI!";
    printf("%c\n", t[0]);
    printf("%c\n", t[1]);
    printf("%c\n", t[2]);
    
    printf("%c\n", *s);  // prints H
    printf("%c\n", *(s + 1));  // prints I
    printf("%c\n", *(s + 2));  // prints !
    printf("%i\n", *(s + 3));  // prints 0, since we're looking at the null character
    printf("%i\n", *(s + 100000));  // Segmentation fault! 
}