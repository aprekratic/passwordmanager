#define _CRT_SECURE_NO_WARNINGS
#include "library.h"

int main(void)
{
    printf("=============================\n");
    printf("Upravitelj lozinkama\n");
    printf("=============================\n");

    int rezultat;
    while ((rezultat = authLogin()) == 0) {
    }

    if (rezultat == -1) {
        return EXIT_FAILURE;
    }

    printf("Prijava uspjesna.\n");

    Vault* vault = vaultCreate();
    if (vault == NULL) {
        fprintf(stderr, "vault create\n");
        return EXIT_FAILURE;
    }

    int ucitano = storageLoad(vault);
    if (ucitano > 0) {
        printf("Ucitano %d unosa.\n", ucitano);
    }

    menuMain(vault);

    vaultDestroy(vault);
    vault = NULL;

    return 0;
}