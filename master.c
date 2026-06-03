#define _CRT_SECURE_NO_WARNINGS
#include "library.h"

int authSetup(void)
{
	char pass[MAX_PASS_LEN];

	printf("\n=== Postavljanje master lozinke ===\n");
	printf("Nova lozinka: ");
	scanf("%63s", pass);
	clearBuff();

	FILE* fp = fopen(MASTER_FILE, "w");
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
	static int pokusaji = 0;

	if (pokusaji >= MAX_LOGIN_TRIES) {
		printf("Previse pogresnih pokusaja. Izlaz.\n");
		return -1;
	}

	FILE* fp = fopen(MASTER_FILE, "r");
	if (fp == NULL) {
		printf("Nije postavljena master lozinka. Postavljanje.\n");
		return authSetup();
	}

	char spremljeno[MAX_PASS_LEN];
	fscanf(fp, "%63s", spremljeno);
	fclose(fp);

	char input[MAX_PASS_LEN];
	printf("Master lozinka: ");
	scanf("%63s", input);
	clearBuff();

	if (strcmp(input, spremljeno) != 0) {
		pokusaji++;
		printf("Pogresna lozinka. Pokusaj %d/%d.\n", pokusaji, MAX_LOGIN_TRIES);
		return 0;
	}

	return 1;
}
