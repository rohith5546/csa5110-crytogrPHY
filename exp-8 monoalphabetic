#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char plain[] = "abcdefghijklmnopqrstuvwxyz";
    char cipher[] = "CIPHERABDFGJKLMNOQSTUVWXYZ";
    char text[100];
    int i;

    printf("Enter Plain Text: ");
    scanf("%s", text);

    printf("Cipher Text: ");

    for(i = 0; text[i] != '\0'; i++)
    {
        if(isalpha(text[i]))
        {
            char ch = tolower(text[i]);
            printf("%c", cipher[ch - 'a']);
        }
        else
        {
            printf("%c", text[i]);
        }
    }

    return 0;
}

OUTPUT

Enter Plain Text: hello
Cipher Text: BEJJM
