#include "library.h"

void clearScreen(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void clearBuff(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pressEnter(void)
{
    printf("\nPritisni enter za nastavak...");
    clearBuff();
}

int safeInput(char *buff, int maxlen, const char *prompt)
{
    if (buff == NULL || maxlen <= 0) {
        return -1;
    }
    if (prompt != NULL && prompt[0] != '\0') {
        printf("%s", prompt);
    }
    if (fget(buff, maxlen, stdin) == NULL) {
        buff[0] = '\0';
        return -1;
    }

    int len = (int)strlen(buff);
    if (len > 0 && buff[len - 1] == '\n') {
        buff[--len] = '\0';
    } else {
        clearBuff();
    }

   return len;
}


/*dodati generate password*/