#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string);
int count_words(string);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    // printf("%s\n", text);
    // printf("%i letter(s)\n", count_letters(text)); 
    // printf("%i word(s)\n", count_words(text)); 
    // printf("%i sentence(s)\n", count_sentences(text));
    
    
    //using functions below, count the letters, words, and sentences. 
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    
    //compute L and S in the relevant formula
    float L = letters / (words / 100.0);
    float S = sentences / (words / 100.0);
    
    // apply formula. Simply casting to int did not round correctly.
    // to round correctly, I am using the round() function from the <math.h> library
    // found on https://manual.cs50.io/. 
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    
    
    // if statements to catch the weird <1 and >=16 print conditions.
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
    

}

// my functions
int count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char letter = toupper(text[i]);
        if (letter >= 'A' && letter <= 'Z')  // if the ascii code is >='A' (65) and <='Z' (90), count it. 
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
{
    // count is weird here.
    // it starts at 1, since, for example, the 1st space signalizes 2 sentences. 
    int count = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char letter = toupper(text[i]);
        if (letter == ' ')
        {
            count++;
        }
    }
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char letter = toupper(text[i]);
        if (letter == '.' || letter == '!' || letter == '?')
        {
            count++;
        }
    }
    return count;
}