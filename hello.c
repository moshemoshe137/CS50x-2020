#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // ask the user for their name
    string answer = get_string("What's your name? ");
    printf("hello, %s\n", answer);
}
