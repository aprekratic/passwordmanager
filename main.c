#define _CRT_SECURE_NO_WARNINGS
#include "library.h"

int main(void)
{
    printf("=============================\n");
    printf("Upravitelj lozinkama\n");
    printf("=============================\n");

    while (authLogin() == 0) {
    }

    printf("Prijava uspjesna.\n");

    Vault* vault = vaultCreate();
    if (vault == NULL) {
        fprintf(stderr, "vault create\n");
        return EXIT_FAILURE;
    }

    menuMain(vault);

    vaultDestroy(vault);
    vault = NULL;

    return 0;
}
