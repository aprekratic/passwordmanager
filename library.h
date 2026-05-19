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


typedef enum {
MENU_EXIT = 0,
MENU_VIEW_ALL = 1,
MENU_VIEW_ONE = 2,
MENU_ADD = 3,
MENU_DELETE = 4,
MENU_GENERATE = 5,
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

Vault* vaultCreate(void);
void vaultPrintAll(const Vault* v);
int authSetup(void);
int authLogin(void);
void clearScreen(void);
void clearBuff(void);
void pressEnter(void);
int toolsSafeInput(char *buff, int maxlen, const char *prompt);
void menuMain(Vault *v);

#endif