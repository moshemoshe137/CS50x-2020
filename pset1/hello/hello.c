#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // ask the user for their name
    string name = get_string("What is your name?: ");
    
    //then greet the user
    printf("hello, %s\n", name);
}