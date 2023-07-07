#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STRING_SIZE 100000000
#define MAX_PATTERN_SIZE 30000

char str[MAX_STRING_SIZE];
char pat[MAX_PATTERN_SIZE];
int ans[MAX_STRING_SIZE];

int nfind(char* string, char* pat);

void main(){
    int rv, i;

    FILE *fs, *fp, *fw;
    fs=fopen("string.txt", "r");
    if(fs==NULL){
        printf("The string file does not exit.\n");
        exit(1);
    }
    fgets(str, MAX_STRING_SIZE, fs);
    fclose(fs);

    fp=fopen("pattern.txt", "r");
    if(fp==NULL){
        printf("The pattern file does not exit.\n");
        exit(1);
    }
    fgets(pat, MAX_PATTERN_SIZE, fp);
    fclose(fp);
    
    rv = nfind(str, pat);
    fw=fopen("result_naive.txt", "w");
    fprintf(fw, "%d\n", rv);
    for(i=0; i<rv; i++){
        fprintf(fw, "%d ", ans[i]);
    }
    fclose(fw);

    printf("Program complete. Result saved to result_kmp.txt\n");
    return ;
}

int nfind(char* string, char*pat){
    int i=0,j=0, start=0;
    int r=0;
    int lasts = strlen(string)-1;
    int lastp = strlen(pat)-1;
    int endmatch=lastp;
    for(i=0; endmatch<=lasts; endmatch++, start++){
        if(string[endmatch]==pat[lastp]){
            //printf("%d %d\n", endmatch, start);
            for(j=0, i=start; j<lastp && string[i]==pat[j]; i++,j++);
            if(j==lastp){
                ans[r++]=start;
                //printf("%d ", start);
            }
        }
        
    }
    return r;
}