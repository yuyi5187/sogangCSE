#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ELEMENTS 1000010
#define MAX_INPUT_SIZE 100
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
  int key;
} element;

element MaxHeap[MAX_ELEMENTS];
element MinHeap[MAX_ELEMENTS];
int n = 0;
char input[MAX_INPUT_SIZE];
clock_t start_t, finish_t;
double duration;

void Insert_MaxHeap(element item, int *na);
void Insert_MinHeap(element item, int *na);
element delete_MaxHeap(int *na);
element delete_MinHeap(int *nd);

void main(int argc, char*argv[]){
    FILE *fr, *fw;
    if(argc != 2){
      printf("usage: ./hw2 input_filename\n");
      exit(1);
    }
    fr = fopen(argv[1], "r");
    if(fr == NULL){
        printf("The input file does not exit.\n");
        exit(1);
    }
    fw = fopen("hw2_result.txt", "w");

    start_t = clock();
    char *temp;
    element item;
    int na = 0;
    int nd = 0;
    while(fgets(input, MAX_INPUT_SIZE, fr) != NULL){  

      temp=strtok(input, " ");
      if (strncmp(temp, "INSERT", 6)==0){
        if(temp!=NULL) temp= strtok(NULL, " ");
        int t = atoi(temp);
        item.key = t;
        Insert_MaxHeap(item, &na);
        Insert_MinHeap(item, &nd);
      }
      else if (strncmp(temp, "DESCEND", 7)==0){
        n = na;
        for(int i=(n-1); i>=0; i--){
          item = delete_MaxHeap(&na);
          fprintf(fw, "%d ", item.key);
        }
        fprintf(fw, "\n");
      }
      else if (strncmp(temp, "ASCEND", 6) ==0){
        n = nd;
        for(int i=(n-1); i>=0; i--){
          item = delete_MinHeap(&nd);
          fprintf(fw, "%d ", item.key);
        }
        fprintf(fw, "\n");
      }
      else {
        printf("%s", temp);
        printf("Command Error!\n");
      }
    }
    fclose(fr);
    fclose(fw);
    finish_t = clock();
    duration = (double)(finish_t-start_t)/CLOCKS_PER_SEC;
    printf("output written to hw2_result.txt.\n");
    printf("running time: %f seconds\n", duration);
  return ;
}

void Insert_MaxHeap(element item, int *na){
  int i;
  if(HEAP_FULL(*na)) {
    fprintf(stderr, "The heap is full.\n");
    exit(1);
  }
  i = ++(*na);
  while((i != 1) && (item.key > MaxHeap[i/2].key)) {
    MaxHeap[i] = MaxHeap[i/2];
    i /= 2;
  }
  MaxHeap[i] = item;
}

element delete_MaxHeap(int *na) {
  int parent, child;
  element item, temp;
  if(HEAP_EMPTY(*na)) {
    fprintf(stderr, "The heap is empty");
    exit(1);
  }
  item = MaxHeap[1];
  temp = MaxHeap[(*na)--];
  parent = 1;
  child = 2;
  while(child <= *na) {
    if((child < *na) && (MaxHeap[child].key <MaxHeap[child+1].key)) child++;
    if(temp.key >= MaxHeap[child].key) break;
    MaxHeap[parent] = MaxHeap[child];
    parent = child;
    child *= 2;
  }
  MaxHeap[parent] = temp;
  return item;
}


void Insert_MinHeap(element item, int *nd){
  int i;
  if(HEAP_FULL(*nd)) {
    fprintf(stderr, "The heap is full.\n");
    exit(1);
  }
  i = ++(*nd);
  while((i != 1) && (item.key < MinHeap[i/2].key)) {
    MinHeap[i] = MinHeap[i/2];
    i /= 2;
  }
  MinHeap[i] = item;
}

element delete_MinHeap(int *nd) {
 
  int parent, child;
  element item, temp;
  if(HEAP_EMPTY(*nd)) {
    fprintf(stderr, "The heap is empty");
    exit(1);
  }

  item = MinHeap[1];
  temp = MinHeap[(*nd)--];
  parent = 1;
  child = 2;
  while(child <= *nd) {
    if((child < *nd) && (MinHeap[child].key > MinHeap[child+1].key)) child++;
    if(temp.key <= MinHeap[child].key) break;
    MinHeap[parent] = MinHeap[child];
    parent = child;
    child *= 2;
  }
  MinHeap[parent] = temp;
  return item;
}
