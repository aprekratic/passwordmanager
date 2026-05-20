#define _CRT_SECURE_NO_WARNINGS
#include "library.h"

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
    int choice;
    do {
        showMenu();
        scanf("%d", &choice);
        clearBuff();

        switch (choice) {
            case MENU_VIEW_ALL:
                vaultPrintAll(v);
                break;
            case MENU_VIEW_ONE:
                /* */
                break;
            case MENU_ADD:
                addEntry(v);
                break;
            case MENU_DELETE:
               /*deleteEntry(v);*/
                break;
            case MENU_GENERATE:
                /*generatePassword();*/
                break;
            case MENU_EXIT:
                printf("Izlaz iz programa.\n");
                break;
            default:
                printf("Nepoznata opcija.\n");
                pressEnter();
                break;
        }
    } while (choice != MENU_EXIT);
}
void vaultPrintAll(const Vault* v)
{
    if (v == NULL || v->count == 0)
    {
        printf("Nema spremljenih unosa.\n");
        return;
    }
}

static void addEntry(Vault* v)
{
    char site[MAX_SITE_LEN];
    char user[MAX_USER_LEN];
    char pass[MAX_PASS_LEN];
    printf("\n---- Dodavanje unosa -----\n");
    printf("Naziv stranice: ");
    scanf("%s", site);
    clearBuff();

    printf("Korisnicko ime: ");
    scanf("%s", user);
    clearBuff();

    printf("Lozinka: ");
    scanf("%s", pass);
    clearBuff();

    /*
    if (vaultAdd(v, site, user, pass)) {
        if (storageSave(v)) {
            printf("Unos dodan i spremljen.\n");
        } else {
            printf("Unos nije spremljen.");
        }
    }
    */
}
