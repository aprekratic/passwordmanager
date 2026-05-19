#include "library.h"

int authSetup(void)
{
    char pass[MAX_PASS_LEN];

    printf("\n=== Postavljanje master lozinke ===\n");
    safeInput(pass, MAX_PASS_LEN, "Nova lozinka: ");

    FILE *fp = fopen(MASTER_FILE, "w");
    if (fp == NULL) {
        perror("authSetup: fopen");
        return 0;
    }
    fprintf(fp, "%s\n", pass);
    fclose(fp);

    printf("Master lozinka postavljena.\n");
    return 1;
}

int authLogin(void)
{

}