#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

#define STRCP 1 // use in main.c , for switching the result file

typedef struct __PHONE_BOOK_SUBENTRY {
    /* Now unuse info */
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} sub_entry;

typedef struct __PHONE_BOOK_ENTRY {
    char *lastName;
    sub_entry *detail;
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

typedef struct __HUFF_COMPRESS {
    int value;
    int ori_length;
} huff_cp;

huff_cp huffTB[26];

void InitHuffmanTB();
char *huffmanEncode(char lasName[]);
entry *findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *e);

#endif
