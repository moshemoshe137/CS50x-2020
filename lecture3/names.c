#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string names[] = {"Bill", "Charlie", "Fred", "George", "Ginny", "Percy", "Ron"};
    // these names are already alphabetized ! 
    
    // let's do linear search first
    for (int i = 0; i < 7; i++)
    {
        // you CANNOT use == to compare 2 strings in C
        // if (names[i] == "Ron") does NOT work
        // we have a strcmp() function from <string.h>
        
        //if Return value < 0 then it indicates str1 is less than str2.
        //if Return value > 0 then it indicates str2 is less than str1.
        //if Return value = 0 then it indicates str1 is equal to str2.
        
        if (strcmp(names[i], "Ron") == 0)
        {
            printf("Found\n");
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}