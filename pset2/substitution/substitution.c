#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


bool is_valid(string key);


int main(int argc, string argv[])
{
    string key = argv[1];
    if (argc != 2 || !is_valid(key))
    {
        //if the number of arguements is wrong or the string is invalid, print the error message below and return 1. 
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    string plaintext = get_string("plaintext: ");
    int n_pt = strlen(plaintext);

    printf("ciphertext: ");

    
    for (int i = 0; i < n_pt; i++)
    {
        // loop thru each letter of the plaintext
        
        // seperate, simple cases for uppercase and lowercase letters
        // to map A -> 0; B -> 1, etc., using some "ascii-arithmatic". 
        // also converting the key toupper()/tolower() to match the plaintext
        if isupper(plaintext[i])
        {
            int index = plaintext[i] - 'A';
            printf("%c", toupper(key[index]));
        }
        else if islower(plaintext[i])
        {
            int index = plaintext[i] - 'a';
            printf("%c", tolower(key[index]));
        }
        else
        {
            // if it is not an upercase or lowercase letters, it's some sort of punctiation/numbers. Just keep it as-is.
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
   
}


bool is_valid(string key)
{
    int n = strlen(key);
    
    if (n != 26)
    {
        // detects keys that are not exactly 26 chars long
        return false;
    }
    
    // for each letter of the key
    for (int i = 0; i < n; i++)
    {
        char letter = toupper(key[i]);
        if (letter < 'A' || letter > 'Z')
        {
            // make sure it is btwn A and Z
            return false;
        }
        
        for (int j = 0; j < i; j++)
        {
            //check all the letters BEFORE me
            // if one of them is the same, key is invalid
            char other_letter = toupper(key[j]);
            if (letter == other_letter)
            {
                return false;
            }
        }
    }
    
    return true;
}