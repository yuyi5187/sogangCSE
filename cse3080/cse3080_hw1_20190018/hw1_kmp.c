#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STRING_SIZE 100000000
#define MAX_PATTERN_SIZE 30000

int kmp(char* string, char* pat);
void fail(char* pat);

int failure[MAX_PATTERN_SIZE];
char str[MAX_STRING_SIZE];
char pat[MAX_PATTERN_SIZE];
int ans[MAX_STRING_SIZE];

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
    
    fail(pat);
    rv=kmp(str, pat);
    
    fw=fopen("result_kmp.txt", "w");
    fprintf(fw, "%d\n", rv);
    for(i=0; i<rv; i++){
        fprintf(fw, "%d ", ans[i]);
        // fputc(ans[i]+'0', fw);
        // fputc(' ', fw);
    }
    fclose(fw);

    printf("Program complete. Result saved to result_kmp.txt\n");
    return ;
}

void fail(char *pat){
    int i,j;
    int n = strlen(pat);
    failure[0]=-1;

    for(j=1;j<n;j++){
        i=failure[j-1];
        while((pat[j]!= pat[i+1]) && (i>=0)) {
            i=failure[i];
        }
        if(pat[j]==pat[i+1]) {
            failure[j]=i+1;
        }
        else {
            failure[j]=-1;
        }
        
    }
    return;
}


int kmp(char *string, char *pat) {
  /* Knuth-Morris-Pratt string matching algorithm */
  int i=0, j=0;
  int r=0; // index 총 개수
  int lens = strlen(string);
  int lenp = strlen(pat);
  
  while(i < lens && j < lenp) {
    if(string[i] == pat[j]) { 
        i++; j++;
        
    }
    else if(j == 0){
        i++;
    }
    else{
        j = failure[j-1] + 1;
    }

    //pattern 끝까지 탐색색
    if(j==lenp){
        ans[r++]=i-lenp;
        //printf("%d ",ans[r] );
        //j=0;
        j=failure[j-1] +1;
    }
    
  }
  
  return r;
}