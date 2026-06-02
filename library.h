#pragma once
#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define MAX_LOGIN_TRIES 3
#define MAX_SITE_LEN 64
#define MAX_USER_LEN 64
#define MAX_PASS_LEN 64

#define MASTER_FILE "master.dat"
#define VAULT_FILE "vault.dat"

extern int brojUnosa;

typedef enum {
	MENU_VIEW_ALL = 1,
	MENU_VIEW_ONE = 2,
	MENU_ADD = 3,
	MENU_DELETE = 4,
	MENU_GENERATE = 5,
	MENU_EXIT = 6,
} MenuOption;

typedef struct {
	char site[MAX_SITE_LEN];
	char username[MAX_USER_LEN];
	char password[MAX_PASS_LEN];
} Entry;

typedef struct {
	Entry* entries;
	int count;
	int capacity;
} Vault;

void clearBuff(void);

static inline void pressEnter(void)
{
	printf("\nPritisni enter za nastavak...");
	clearBuff();
}

Vault* vaultCreate(void);
void vaultPrintAll(const Vault* v);
void vaultPrintOne(const Vault* v, const char* site);
void vaultPrintRecursive(const Vault* v, int index);
int authSetup(void);
int authLogin(void);
int storageSave(const Vault* v);
int storageLoad(Vault* v);
void menuMain(Vault* v);
void vaultDestroy(Vault* v);
int vaultAdd(Vault* v, const char* site, const char* user, const char* pass);

#endif