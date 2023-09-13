#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>  // for to upper
#include <stdlib.h> // for malloc() function

int main(void)
{
    char *s = get_string("s: ");
    
    // //wanna copy s to t
    // char *t = s;
    
    // t[0] = toupper(t[0]);
    
    // printf("%s\n", s);
    
    // printf("%s\n", t);
    
    // // so how can we actually copy s to t?
    
    // malloc function. Memory allocate
    char *u = malloc(strlen(s) + 1);
    if (u == NULL)
    {
        return 1;
    }
    
    for (int i = 0, n = strlen(s); i <= n; i++)  // notice the less than or EQUAL to, in order to include the null char
    {
        u[i] = s[i];
    }
    
    if (strlen(s) > 0)
    {
        u[0] = toupper(u[0]);

    }
    printf("%s\n", s);
    
    printf("%s\n", u);
    
    
    // there is a much simplier way to copy strings:
    char *v = malloc(strlen(s) + 1);
    strcpy(v, s);
    printf("%s\n", v);
    
    // when you use malloc, you must free it after
    
    free(u);
    free(v);
}