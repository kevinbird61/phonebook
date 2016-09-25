#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_strcp.h"

void InitHuffmanTB()
{
    // FIXME : Make it generate by itself
    huffTB[0].value = 6;
    huffTB[0].ori_length = 3; // A
    huffTB[1].value = 1;
    huffTB[1].ori_length = 6; // B
    huffTB[2].value = 1;
    huffTB[2].ori_length = 5; // C
    huffTB[3].value = 15;
    huffTB[3].ori_length = 5; // D
    huffTB[4].value = 4;
    huffTB[4].ori_length = 3; // E
    huffTB[5].value = 62;
    huffTB[5].ori_length = 6; // F
    huffTB[6].value = 30;
    huffTB[6].ori_length = 5; // G
    huffTB[7].value = 21;
    huffTB[7].ori_length = 5; // H
    huffTB[8].value = 1;
    huffTB[8].ori_length = 4; // I
    huffTB[9].value = 254;
    huffTB[9].ori_length = 8;
    huffTB[10].value = 14;
    huffTB[10].ori_length = 6;
    huffTB[11].value = 14;
    huffTB[11].ori_length = 4;
    huffTB[12].value = 14;
    huffTB[12].ori_length = 5; // M
    huffTB[13].value = 5;
    huffTB[13].ori_length = 4; // N
    huffTB[14].value = 4;
    huffTB[14].ori_length = 4;
    huffTB[15].value = 20;
    huffTB[15].ori_length = 5; // P
    huffTB[16].value = 255;
    huffTB[16].ori_length = 8;
    huffTB[17].value = 2;
    huffTB[17].ori_length = 4; // R
    huffTB[18].value = 6;
    huffTB[18].ori_length = 4;
    huffTB[19].value = 11;
    huffTB[19].ori_length = 4; // T
    huffTB[20].value = 6;
    huffTB[20].ori_length = 5;
    huffTB[21].value = 0;
    huffTB[21].ori_length = 7; // V
    huffTB[22].value = 1;
    huffTB[22].ori_length = 7;
    huffTB[23].value = 253;
    huffTB[23].ori_length = 8;
    huffTB[24].value = 15;
    huffTB[24].ori_length = 6;
    huffTB[25].value = 252;
    huffTB[25].ori_length = 8;
}

char *huffmanEncode(char origName[])
{
    int i,totalSize=0,codeSize=0,codeValue=0;
    unsigned long long high=0,low=0; // 8 bytes
    char *result;
    for(i = 0; i < strlen(origName); i++) {
        /* Calculate length */
        if(origName[i] >= 65 && origName[i] <= 90) {
            codeSize = huffTB[origName[i]-65].ori_length;
            codeValue = huffTB[origName[i]-65].value;
        } else if(origName[i] >= 97 && origName[i] <= 122) {
            codeSize = huffTB[origName[i]-97].ori_length;
            codeValue = huffTB[origName[i]-97].value;
        }
        /* Record FIXME - Need to chech if bigger than 64*/
        if((totalSize+codeSize) <= 64) {
            // Record in low bytes
            low <<= codeSize;
            low |= codeValue;
        }
        /*
        else if((totalSize+codeSize) > 64 && totalSize < 64){
          // Using upper bytes for storage

        }
        else if(totalSize > 64){
          // All store into upper
        }*/
        totalSize += codeSize;
    }
    // Calculate for total require memory
    int size = ((totalSize/8)+( (totalSize%8 != 0) ? 1 : 0));
    result = (char *)malloc( size * sizeof(char) );

    for(i = 0; i < size ; i++) {
        // Each is denoted as 8 bits
        int count=0,temp=0;
        for(count=0; count < 8; count++) {
            temp |= (low & (0x01 << (8*i + count)));
        }
        result[i] = (char)temp;
    }
    return result;
}

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
{
    /* TODO: implement */
    char *strfind = huffmanEncode(lastname);
    while (pHead != NULL) {
        if (strlen(strfind)==strlen(pHead->lastName) && (strcasecmp(strfind, pHead->lastName) == 0))
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    // Huffman compression
    char *result = huffmanEncode(lastName);
    e->pNext = (entry *) malloc(sizeof(entry));
    e->lastName = result;
    e->detail = NULL;
    e = e->pNext;
    e->pNext = NULL;
    return e;
}
