#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //ask the user for the height that they'd like. Make sure it is valid inpup
    int height;
    do
    {
        height = get_int("What height should the pyramids be?: ");
    }
    while (height > 8 || height < 1);
    
    
    // loop thru the rows
    for (int i = 0; i < height; i++)
    {
        //print the right number of spaces: height - rownum - 1
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        
        // print the right number of hashes: rownum + 1
        for (int j = height - i - 1; j < height; j++)
        {
            printf("#");
        }
        
        // print 2 spaces btwn the pyramids 
        printf("  ");
        
        //repeat printing hashes
        for (int j = height - i - 1; j < height; j++)
        {
            printf("#");
        }
        
        //printf("end");
        printf("\n");
    }
}