// Check that a password has at least one lowercase letter, uppercase letter, number and symbol

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

/* int main(void) */
int main(int argc, string argv[])
{
    /* string password = get_string("Enter your password: "); */
    if (argc == 2)
        string password = argv[1];
    else
        return 1;

    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    int passlength = strlen(password);
    bool number = false, upper = false, lower = false, symbol = false;
    for (int i = 0; i < passlength; i++) 
    {
        if (isupper(password[i])) 
        {
            upper = true;
        }
        else if (islower(password[i]))
        {
            lower = true;
        }
        else if (isdigit(password[i])) 
        {
            number = true;
        }
        else if (ispunct(password[i])) 
        {
            symbol = true;
        }
    }

    if (number & upper & lower & symbol)
        return true;
    return false;
}
