#define _CRT_SECURE_NO_WARNINGS
#include "library.h"

int brojUnosa = 0;

void clearBuff(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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
        if (fprintf(fp, "%s|%s|%s\n", v->entries[i].site, v->entries[i].username, v->entries[i].password) < 0) {
            perror("storageSave: fprintf");
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}

Vault* vaultCreate(void)
{
    Vault* v = (Vault*)malloc(sizeof(Vault));
    if (v == NULL)
    {
        perror("malloc vault");
        return NULL;
    }

    v->entries = (Entry *)calloc(8, sizeof(Entry));
    if (v->entries == NULL)
    {
        perror("calloc entries");
        free(v);
        return NULL;
    }
    v->count = 0;
    v->capacity = 8;
    return v;
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
    for (int i = 0; i < v->count; i++) {
        printf("%-4d  %-20s  %-20s\n", i + 1, v->entries[i].site, v->entries[i].username);
    }
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
            printf("Unos za '%s' vec postoji.\n", site);
            return 0;
        }
    }

    if (v->count >= v->capacity) {
        int new_cap = v->capacity * 2;
        Entry* tmp = (Entry*)realloc(v->entries, (size_t)new_cap * sizeof(Entry));
        if (tmp == NULL) {
            perror("realloc entries");
            return 0;
        }
        v->entries = tmp;
        v->capacity = new_cap;
    }

    strncpy(v->entries[v->count].site,     site, MAX_SITE_LEN - 1);
    strncpy(v->entries[v->count].username, user, MAX_USER_LEN - 1);
    strncpy(v->entries[v->count].password, pass, MAX_PASS_LEN - 1);
    v->entries[v->count].site[MAX_SITE_LEN - 1]     = '\0';
    v->entries[v->count].username[MAX_USER_LEN - 1] = '\0';
    v->entries[v->count].password[MAX_PASS_LEN - 1] = '\0';
    v->count++;
    brojUnosa++;

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
        } else {
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
            brojUnosa--;
            break;
        }
    }

    if (pronadjen) {
        if (storageSave(v)) {
            printf("Unos obrisan i spremljen.\n");
        } else {
            printf("Unos obrisan ali NIJE spremljen!\n");
        }
    } else {
        printf("Unos '%s' nije pronadjen.\n", site);
    }
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

void menuMain(Vault *v)
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
                /*dodati*/
                break;
            case MENU_ADD:
                addEntry(v);
                break;
            case MENU_DELETE:
                deleteEntry(v);
                break;
            case MENU_GENERATE:
                /* generatePassword(); */
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