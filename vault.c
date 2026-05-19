#define _CRT_SECURE_NO_WARNINGS
#include "library.h"

Vault* vaultCreate(void)
{
    Vault* v = (Vault*)malloc(sizeof(Vault));
    if (v == NULL)
    {
        perror("Greska pri alokaciji memorije");
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
}

static void showMenu(void)
{
    toolsClearScreen();
    printf("\n----------------------------------");
    printf("     UPRAVITELJ LOZINKAMA\n");
    printf("------------------------------------\n");
    printf("  1. Prikazi sve unose\n");
    printf("  2. Prikazi konkretnu lozinku\n");
    printf("  3. Dodaj novi unos\n");
    printf("  4. Obrisi unos\n");
    printf("  5. Generiraj lozinku\n");
    printf("  0. Izlaz\n");
    printf("------------------------------------\n");
    printf("Odabir: ");
}

void menuMain(Vault *v)
{
    int choice;
    do {
        showMenu();
        scanf("%d", &choice);
        toolsFlushInput();

        switch (choice) {
            case MENU_VIEW_ALL:
                vaultPrintAll(v);
                break;
            case MENU_VIEW_ONE:
                /* */
                break;
            case MENU_ADD:
                doAdd(v);
                break;
            case MENU_DELETE:
                doDelete(v);
                break;
            case MENU_GENERATE:
                doGenerate();
                break;
            case MENU_EXIT:
                printf("Izlaz iz programa.\n");
                break;
            default:
                printf("Nepoznata opcija.\n");
                toolsPressEnter();
                break;
        }
    } while (choice != MENU_EXIT);
}


static void doAdd(Vault *v)
{
    char site[MAX_SITE_LEN];
    char user[MAX_USER_LEN];
    char pass[MAX_PASS_LEN];
    char choice[4];

    toolsClearScreen();
    printf("\n=== Dodavanje unosa ===\n");
    toolsSafeInput(site, MAX_SITE_LEN, "Naziv stranice:  ");
    toolsSafeInput(user, MAX_USER_LEN, "Korisnicko ime:  ");
    toolsSafeInput(pass, MAX_PASS_LEN, "Lozinka: ");

    if (vaultAdd(v, site, user, pass)) {
        if (storageSave(v)) 
        {
            printf("Unos dodan i spremljen.\n");
            } else {
            printf("Unos dodan ali NIJE spremljen!\n");
        }
    toolsPressEnter();

    /*dodati autogeneriranje lozinke*/
    }
}