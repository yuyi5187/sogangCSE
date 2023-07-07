#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_VERTICES 10001
#define MAX_EDGES 50000001
#define MAX_INPUT_SIZE 100
#define HEAP_FULL(n) (n == MAX_EDGES-1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
  int u,v,w;
} element;

int n, m;
int heap_size, mst_size, min_weight;
bool is_connect = true;
element MinHeap[MAX_EDGES];
element MST[MAX_VERTICES];
int parent[MAX_VERTICES];
int visit[MAX_VERTICES];

clock_t start_t, finish_t;
double duration;

void Insert_MinHeap(element item, int *heap_size);
element delete_MinHeap(int *nd);
int find(int parent[], int x);
void merge(int parent[], int x, int y);
bool check(int parent[], int x, int y);

void main(int argc, char*argv[]){
    if (argc !=2 ){
        printf("usage: ./hw3 input_filename\n");
        exit(0);
    }

    FILE *fr, *fw;
    int i;
    fr = fopen(argv[1], "r");
    if(fr == NULL){
        printf("The input file does not exit.\n");
        exit(1);
    }
    
    fw = fopen("hw3_result.txt", "w");
    start_t = clock();

    /*input 입력받기*/
    fscanf(fr, "%d", &n);
    fscanf(fr, "%d", &m);

    int vertex1, vertex2, cost;
    element item;

    while(fscanf(fr, "%d %d %d", &vertex1, &vertex2, &cost)!=EOF){
        //printf("%d %d %d\n", vertex1, vertex2, cost);
        item.u = vertex1;
        item.v = vertex2;
        item.w = cost;
        /* min_heap만들기 */
        Insert_MinHeap(item, &heap_size);
    }
    fclose(fr);

    /* parent 초기화 */
    for(i = 0; i<=n; i++){
      parent[i]=i;
    }

    /* MST 만들기 */
    while( mst_size<n && heap_size > 0){
      item = delete_MinHeap(&heap_size);
      int a = item.u;
      int b = item.v;
      
      if (!check(parent, a, b)){
        MST[mst_size++] = item;
        merge(parent, a , b);
      }
    }

    //printf("%d\n", mst_size);
    int u1, v1, w1;
    for(i=0; i<mst_size; i++){
      item = MST[i];
      u1 = item.u;
      v1 = item.v;
      w1 = item.w; 
      min_weight += w1;
      /*connect, disconnet 여부 확인하기*/
      visit[u1] = 1;
      visit[v1] = 1;
      fprintf(fw, "%d %d %d\n", item.u, item.v, item.w);
    }
    fprintf(fw, "%d\n", min_weight);
    
    for(i=0; i<n; i++){
      if(visit[i] == 0){
        is_connect = false;
        break;
      }
    }

    if (is_connect){
      fprintf(fw, "CONNECTED\n");
    }
    else{
      fprintf(fw, "DISCONNECTED\n");
    }

    fclose(fw);

    finish_t = clock();
    duration = (double)(finish_t-start_t)/CLOCKS_PER_SEC;

    printf("output written to hw3_result.txt.\n");
    printf("running time: %f seconds\n", duration);
    return; 
}


void Insert_MinHeap(element item, int *heap_size){
  int i;
  if(HEAP_FULL(*heap_size)) {
    fprintf(stderr, "The heap is full.\n");
    exit(1);
  }
  i = ++(*heap_size);
  while((i != 1) && (item.w < MinHeap[i/2].w)) {
    MinHeap[i] = MinHeap[i/2];
    i /= 2;
  }
  MinHeap[i] = item;
}


element delete_MinHeap(int *heap_size) {
 
  int parent, child;
  element item, temp;
  if(HEAP_EMPTY(*heap_size)) {
    fprintf(stderr, "The heap is empty");
    exit(1);
  }

  item = MinHeap[1];
  temp = MinHeap[(*heap_size)--];
  parent = 1;
  child = 2;
  while(child <= *heap_size) {
    if((child < *heap_size) && (MinHeap[child].w > MinHeap[child+1].w)) child++;
    if(temp.w <= MinHeap[child].w) break;
    MinHeap[parent] = MinHeap[child];
    parent = child;
    child *= 2;
  }
  MinHeap[parent] = temp;
  return item;
}


int find(int parent[], int x){

  if (parent[x] == x) return x;
  return parent[x] = find(parent, parent[x]);
}

void merge(int parent[], int x, int y){
  x = find(parent, x);
  y = find(parent, y);

  if (x < y) parent[y] = x;
  else parent[x] = y;
  
  return; 
}

bool check(int parent[], int x, int y){
  x = find(parent, x);
  y = find(parent, y);

  if(x == y) return true;
  else return false;
}