#define _CRT_SECURE_NO_WARNINGS
#include "library.h"

int broj_unosa = 0;
static int kapacitet = 8;

void clearBuff(void)
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int storageSave(const Vault* v)
{
	if (v == NULL) return 0;

	FILE* fp = fopen("vault_temp.dat", "w");
	if (fp == NULL) {
		perror("storageSave: fopen");
		return 0;
	}

	for (int i = 0; i < v->count; i++) {
		if (fprintf(fp, "%s|%s|%s\n", v->entries[i].site, v->entries[i].username, v->entries[i].password) < 0) {
			perror("storageSave: fprintf");
			fclose(fp);
			return 0;
		}
	}

	fclose(fp);
	remove(VAULT_FILE);
	rename("vault_temp.dat", VAULT_FILE);
	return 1;
}

static int compareEntries(const void* a, const void* b)
{
	return strcmp(((const Entry*)a)->site, ((const Entry*)b)->site);
}

int storageLoad(Vault* v)
{
	if (v == NULL) return -1;

	FILE* fp = fopen(VAULT_FILE, "r");
	if (fp == NULL) {
		return 0;
	}

	fseek(fp, 0, SEEK_END);
	long velicina = ftell(fp);
	rewind(fp);

	if (velicina == 0) {
		fclose(fp);
		return 0;
	}

	char site[MAX_SITE_LEN];
	char user[MAX_USER_LEN];
	char pass[MAX_PASS_LEN];
	int ucitano = 0;

	while (fscanf(fp, "%63[^|]|%63[^|]|%63[^\n]\n",
		site, user, pass) == 3) {
		vaultAdd(v, site, user, pass);
		ucitano++;
	}

	fclose(fp);
	qsort(v->entries, (size_t)v->count, sizeof(Entry), compareEntries);
	return ucitano;
}

Vault* vaultCreate(void)
{
	Vault* v = (Vault*)malloc(sizeof(Vault));
	if (v == NULL)
	{
		perror("malloc vault");
		return NULL;
	}

	v->entries = (Entry*)calloc(kapacitet, sizeof(Entry));
	if (v->entries == NULL)
	{
		perror("calloc entries");
		free(v);
		return NULL;
	}
	v->count = 0;
	v->capacity = kapacitet;
	return v;
}

void vaultPrintRecursive(const Vault* v, int index)
{
	if (v == NULL || index >= v->count) return;
	printf("%-4d  %-20s  %-20s\n", index + 1, v->entries[index].site, v->entries[index].username);
	vaultPrintRecursive(v, index + 1);
}

void vaultPrintAll(const Vault* v)
{
	if (v == NULL || v->count == 0)
	{
		printf("Nema spremljenih unosa.\n");
		return;
	}
	printf("\n%-4s  %-20s  %-20s\n", "Br.", "Stranica", "Korisnicko ime");
	printf("%-4s  %-20s  %-20s\n", "---", "--------", "--------------");
	vaultPrintRecursive(v, 0);
}

void vaultPrintOne(const Vault* v, const char* site)
{
	if (v == NULL || site == NULL || v->count == 0) return;

	Entry key;
	memset(&key, 0, sizeof(key));
	strncpy(key.site, site, MAX_SITE_LEN - 1);

	Entry* pronadjen = (Entry*)bsearch(&key, v->entries,
		(size_t)v->count, sizeof(Entry),
		compareEntries);
	if (pronadjen == NULL) {
		printf("Unos '%s' nije pronadjen.\n", site);
		return;
	}

	printf("\n----------------------------\n");
	printf("  Stranica:       %s\n", pronadjen->site);
	printf("  Korisnicko ime: %s\n", pronadjen->username);
	printf("  Lozinka:        %s\n", pronadjen->password);
	printf("----------------------------\n");
}

int vaultAdd(Vault* v, const char* site, const char* user, const char* pass)
{
	if (v == NULL || site == NULL || user == NULL || pass == NULL) return 0;
	if (site[0] == '\0' || user[0] == '\0' || pass[0] == '\0') {
		printf("Greska: sva polja moraju biti popunjena.\n");
		return 0;
	}

	for (int i = 0; i < v->count; i++) {
		if (strcmp(v->entries[i].site, site) == 0) {
			char potvrda[4];
			printf("Unos za '%s' vec postoji. Azurirati (d/n)?: \n", site);
			scanf("%3s", potvrda);
			clearBuff();
			if (potvrda[0] == 'd' || potvrda[0] == 'D') {
				printf("Novi username: ");
				scanf("%63s", v->entries[i].username);
				printf("Nova lozinka: ");
				scanf("%63s", v->entries[i].password);
				clearBuff();
				return 1;
			}
			return 0;
		}
	}

	if (v->count >= v->capacity) {
		int new_cap = v->capacity * 2;
		Entry* temp = (Entry*)realloc(v->entries, (size_t)new_cap * sizeof(Entry));
		if (temp == NULL) {
			perror("realloc entries");
			return 0;
		}
		v->entries = temp;
		v->capacity = new_cap;
	}

	strncpy(v->entries[v->count].site, site, MAX_SITE_LEN - 1);
	strncpy(v->entries[v->count].username, user, MAX_USER_LEN - 1);
	strncpy(v->entries[v->count].password, pass, MAX_PASS_LEN - 1);
	v->entries[v->count].site[MAX_SITE_LEN - 1] = '\0';
	v->entries[v->count].username[MAX_USER_LEN - 1] = '\0';
	v->entries[v->count].password[MAX_PASS_LEN - 1] = '\0';
	v->count++;
	broj_unosa++;

	qsort(v->entries, (size_t)v->count, sizeof(Entry), compareEntries);
	return 1;
}

void vaultDestroy(Vault* v)
{
	if (v == NULL) return;
	if (v->entries != NULL) {
		memset(v->entries, 0, (size_t)v->capacity * sizeof(Entry));
		free(v->entries);
		v->entries = NULL;
	}
	free(v);
}

static void addEntry(Vault* v)
{
	char site[MAX_SITE_LEN];
	char user[MAX_USER_LEN];
	char pass[MAX_PASS_LEN];
	printf("\n---- Dodavanje unosa -----\n");
	printf("Naziv stranice: ");
	scanf("%63s", site);
	clearBuff();

	printf("Korisnicko ime: ");
	scanf("%63s", user);
	clearBuff();

	printf("Lozinka: ");
	scanf("%63s", pass);
	clearBuff();

	if (vaultAdd(v, site, user, pass)) {
		if (storageSave(v)) {
			printf("Unos dodan i spremljen.\n");
		}
		else {
			printf("Unos nije spremljen.\n");
		}
	}
	pressEnter();
}

static void deleteEntry(Vault* v)
{
	char site[MAX_SITE_LEN];
	char potvrda[4];

	printf("\n---- Brisanje unosa -----\n");
	vaultPrintAll(v);
	printf("Naziv stranice za brisanje: ");
	scanf("%63s", site);
	clearBuff();

	printf("Sigurno obrisati unos? (d/n): ");
	scanf("%3s", potvrda);
	clearBuff();

	if (potvrda[0] != 'd' && potvrda[0] != 'D') {
		printf("Otkazano.\n");
		pressEnter();
		return;
	}

	int pronadjen = 0;
	for (int i = 0; i < v->count; i++) {
		if (strcmp(v->entries[i].site, site) == 0) {
			for (int j = i; j < v->count - 1; j++)
				v->entries[j] = v->entries[j + 1];
			memset(&v->entries[v->count - 1], 0, sizeof(Entry));
			v->count--;
			pronadjen = 1;
			broj_unosa--;
			break;
		}
	}

	if (pronadjen) {
		if (storageSave(v)) {
			printf("Unos obrisan i spremljen.\n");
		}
		else {
			printf("Unos obrisan ali nije spremljen.\n");
		}
	}
	else {
		printf("Unos '%s' nije pronadjen.\n", site);
	}
	pressEnter();
}

static void generatePassword(void)
{
	char pass[33];
	int duljina, i;

	printf("\n---- Generator lozinki -----\n");
	printf("Duljina (8-32): ");
	scanf("%d", &duljina);
	clearBuff();

	if (duljina < 8)  duljina = 8;
	if (duljina > 32) duljina = 32;

	srand((unsigned int)time(NULL));

	for (i = 0; i < duljina; i++) {
		int tip = rand() % 3;
		if (tip == 0)
			pass[i] = 'a' + rand() % 26;
		else if (tip == 1)
			pass[i] = 'A' + rand() % 26;
		else
			pass[i] = '0' + rand() % 10;
	}
	pass[duljina] = '\0';

	printf("Generirana lozinka: %s\n", pass);
	pressEnter();
}

static void showMenu(void)
{
	printf("\n---- ");
	printf("UPRAVITELJ LOZINKAMA ");
	printf("-----\n");
	printf("  1. Prikazi sve unose\n");
	printf("  2. Prikazi konkretnu lozinku\n");
	printf("  3. Dodaj novi unos\n");
	printf("  4. Obrisi unos\n");
	printf("  5. Generiraj lozinku\n");
	printf("  6. Izlaz\n");
	printf("----------------------------\n");
	printf("Odabir: ");
}

void menuMain(Vault* v)
{
	int odabir;
	do {
		showMenu();
		scanf("%d", &odabir);
		clearBuff();

		switch (odabir) {
		case MENU_VIEW_ALL:
			vaultPrintAll(v);
			pressEnter();
			break;
		case MENU_VIEW_ONE:
		{
			char site[MAX_SITE_LEN];
			printf("Naziv stranice: ");
			scanf("%63s", site);
			clearBuff();
			vaultPrintOne(v, site);
			pressEnter();
			break;
		}
		case MENU_ADD:
			addEntry(v);
			break;
		case MENU_DELETE:
			deleteEntry(v);
			break;
		case MENU_GENERATE:
			generatePassword();
			break;
		case MENU_EXIT:
			printf("Izlaz iz programa.\n");
			break;
		default:
			printf("Nepoznata opcija.\n");
			pressEnter();
			break;
		}
	} while (odabir != MENU_EXIT);
}
