#include "library.h"

int main(void)
{
    printf("=============================\n");
    printf("Upravitelj lozinkama\n");
    printf("=============================\n");


    /*prijava*/
    int tries = 0;
    while (tries < MAX_LOGIN_TRIES) {
        if (authLogin()) break;
        tries++;
        if (tries < MAX_LOGIN_TRIES)
        printf("Pokusaj %d/%d. Pokusati ponovno.\n\n", tries, MAX_LOGIN_TRIES);
    }
    if (tries >= MAX_LOGIN_TRIES) {
        fprintf(stderr, "Previse pogresnih pokusaja. Izlaz.\n");
        return EXIT_FAILURE;
    }

    printf("Prijava uspjesna.\n");

    /*kreiranje trezora*/
    Vault* vault = vaultCreate();
    if (vault == NULL) {
        fprintf(stderr, "Greska: Trezor nije moguce alocirati.\n");
        return EXIT_FAILURE;
    }


    /*glavni izbornik*/
    menuMain(vault);
    
    /*ciscenje memorije*/


    return 0;
}