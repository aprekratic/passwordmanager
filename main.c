#define _CRT_SECURE_NO_WARNINGS
#include "library.h"

int main(void)
{
    printf("=============================\n");
    printf("Upravitelj lozinkama\n");
    printf("=============================\n");


    /*prijava*/
    while (authLogin() == 0) {
    }

    printf("Prijava uspjesna.\n");

    /*kreiranje trezora*/
    Vault* vault = vaultCreate();
    if (vault == NULL) {
        fprintf(stderr, "vault create\n");
        return EXIT_FAILURE;
    }


    /*glavni izbornik*/
    menuMain(vault);
    
    /*ciscenje memorije*/


    return 0;
}
