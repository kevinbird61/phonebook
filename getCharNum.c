#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct alpha {
    int count;
    char alphabet;
} ALPHA;

int cmp(const void *s1, const void *s2)
{
    return *(int *)s1 - *(int *)s2;
}

int main(void)
{
    FILE *fp;
    int i;
    fp = fopen("./dictionary/words.txt","r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }
    char line[32];
    ALPHA charCount[26];
    int temp[26];
    // Set 0
    for(i=0; i<26; i++) {
        temp[i] = 0;
        charCount[i].count =0;
        charCount[i].alphabet = (char)(i+65);
    }
    // Assume has no blank
    while (fgets(line, sizeof(line), fp)) {
        int i = 0;
        while (line[i] != '\n') {
            if(line[i]>=65 && line[i] <=90) {
                // Upper case
                temp[line[i]-65]++;
                charCount[line[i]-65].count++;
            } else if(line[i]>=97 && line[i] <=122) {
                // Lower case
                temp[line[i]-97]++;
                charCount[line[i]-97].count++;
            }
            i++;
        }
    }

    qsort(temp,26,sizeof(int),cmp);

    for(i=0; i<26; i++) {
        int j;
        for(j=0; j<26; j++) {
            if(temp[i] == charCount[j].count) {
                printf("%c : %d\n",charCount[j].alphabet,charCount[j].count);
                break;
            }
        }
    }
}
