#include <stdio.h>
#include <cs50.h>

int get_digit(long, int);

int main(void)
{
    long number = get_long("Number: ");
    
    long sum = 0;
    
    // loop thru all possible digits
    for (int i = 0; i < 16; i++)
    {
        int digit = get_digit(number, i);
        // printf("%i\n", digit);
       
        
        
        // for digits in odd slots, get the 1st and 2nd digits after multiplying by 2
        if (i % 2 == 1)
        {
            sum += (get_digit(2 * digit, 0) + get_digit(2 * digit, 1));
        }
        
        // for digits in even slots, just add the digits to the sum
        else
        {
            sum += digit;
        }
    }
    
    // if the sum is not 0 mod 10, then the card is invalid
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    
    // otherwise, check if it's Visa
    // It's Visa if the 16th number is a 4.
    // If the card is <15 digits long, check if the 13th number is a 4.
    else if (get_digit(number, 15) == 4 ||
             (get_digit(number, 15) == 0 && get_digit(number, 14) == 0 && get_digit(number, 12) == 4))
    {
        printf("VISA\n");
    }
            
    // otherwise, check if it's MasterCard
    else if (get_digit(number, 15) == 5 && get_digit(number, 14) > 0 && get_digit(number, 14) < 6)
    {
        printf("MASTERCARD\n");
    }
    
    // otherwise, check if it's Amex

    else if (get_digit(number, 14) == 3 &&
             (get_digit(number, 13) == 4 || get_digit(number, 13) == 7))

    {
        printf("AMEX\n");
    }
    
    else
    {
        printf("INVALID\n");
    }
    

}


// a short function to get the digit^{th} digit of number
int get_digit(long number, int digit)
{
    // using a for loop since I don't yet know exponentiation. 
    for (int i = 0; i < digit; i++)
    {
        // do integral division by 10 to get the desired digit moved to the ones place
        number /= 10;
    }
    
    // return mod 10, to get the desired digit, which is now sitting in number's ones place. 
    return number % 10;
}