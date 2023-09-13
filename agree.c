#include <cs50.h>
#include <stdio.h>

int main(void)
{
    char c = get_char("Do you agree? ");
    if (c=='y' || c=='Y')
    {
        printf("Agreed\n");
    }
    else if (c=='n' || c=='N')
    {
        printf("Disagreed\n");
    }
    
    int i = 0;
    while (i<50)
    {
        printf("Hello, world\n");
        i++;
    }
    
    for (int j = 0; j < 50; j++)
    {
        printf("Hello, world\n");
    }
}