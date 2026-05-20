#define _CRT_SECURE_NO_WARNINGS
#include "library.h"

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

int storageSave(const Vault* v)
{
    if (v == NULL)
        return 0;
    FILE* fp = fopen(VAULT_FILE, "w");
    if (fp == NULL) {
        perror("storageSave: fopen");
        return 0;
    }
       
    for (int i = 0; i < v->count; i++) {
        if (fprintf(fp, "%s[%s]%s\n", v->entries[i].site, v->entries[i].username, v->entries[i].password < 0)) {
            perror("storageSave: fprintf");
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}


/*dodati generate password*/
