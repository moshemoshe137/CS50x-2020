#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //ask the user for a (valid) start date.
    int start_size;
    do
    {
        start_size = get_int("What is the starting population size?: ");
    }
    while (start_size < 9);

    //ask the user for a (valid) end date.
    int end_size;
    do
    {
        end_size = get_int("What is the ending population size?: ");
    }
    while (end_size < start_size);

    //simulate each year until the population is the proper size
    int years = 0;
    while (start_size < end_size)
    {
        start_size = start_size + (start_size / 3) - (start_size / 4);
        years++;
    }

    //Return how many years the simulation took
    printf("Years: %i\n", years);
}