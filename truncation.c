#include <cs50.h>
#include <stdio.h>

int main(void)
{

    // get 2 numbers from the user
    int x = get_int("x: ");
    int y = get_int("y: ");

    // divide x by y
    float z = (float) x / (float) y;

    printf("x / y = %f\n", z);
}