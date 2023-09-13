#include <stdio.h>
#include <stdlib.h>  // for malloc

int main(void)
{
    // int list[3];
    
    // list[0] = 1;
    // list[1] = 2;
    // list[2] = 3;
    
    // for (int i = 0; i < 3; i++)
    // {
    //     printf("%i\n", list[i]);
    // }
    
    int *list = malloc(3 * sizeof(int));
    
    if (list == NULL)
    {
        return 1;
    }
    
    list[0] = 1;  // *list = 1;
    list[1] = 2;  // *(list + 1) = 2;
    list[2] = 3;  // *(list + 2) = 3;  ... but these are pretty bad
    
    // how to add a fourth integer?
    
    // int *temp = malloc(4 * sizeof(int));
    int *temp = realloc(list, 4 * sizeof(int));
    if (temp == NULL)
    {
        free(list);
        return 1;
    }
    
    // for (int i = 0; i < 3; i++)
    // {
    //     temp[i] = list[i];
    // }
    // realloc() actually copies the old into the new for you, automatically !
    // So, no need for this for loop! 
    // However, it just does the same thing in the background. It's ineffecient. 
    
    temp[3] = 4;
    
    free(list);
    list = temp;  // make the list point at the new list
    
    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }
    
    free(list);
}