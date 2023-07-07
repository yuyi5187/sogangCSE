#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cmath>
#include<time.h>
#include<fstream>

using namespace std;

const int size_threshold=16;
const char *filename;
int algo;
long long n=-1;
int space = -16;
clock_t start, ending;
string infile, algorithm, outfile;

void swap(long long int* a, long long int* b) { 
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return; 
}

void insertion_sort(long long int arr[], int st, int ed){
    int i,j, key;
    for(i=st+1;i<=ed;i++){
        key=arr[i];
        j=i-1;
        while(j>=st && (arr[j]>key)){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
    return;
}

int partition(long long int arr[],int left, int right){
    int x=arr[right];
    int low=left-1;
    for(int j=left; j<right;j++){
        if(arr[j]<=x){
            low++;
            swap(&arr[low], &arr[j]);
        }
    }
    low++;
    swap(&arr[low], &arr[right]);
    return low;
}

int random_partition(long long int arr[],int left, int right){
    int random=rand()%(right+1)+left;
    swap(&arr[random], &arr[right]);
    int x=arr[right];
    int low=left-1;
    for(int j=left; j<right;j++){
        if(arr[j]<=x){
            low++;
            swap(&arr[low], &arr[j]);
        }
    }
    low++;
    swap(&arr[low], &arr[right]);
    return low;
}

void quick_sort(long long int arr[], int left, int right){
    if (left<right) {
        int pivot=partition(arr, left, right);
        quick_sort(arr, left, pivot-1);
        quick_sort(arr, pivot+1, right);
    }
    
    return; 
}

void random_quick_sort(long long int arr[], int left, int right){
    if (left<right) {
        int pivot=random_partition(arr, left, right);
        quick_sort(arr, left, pivot-1);
        quick_sort(arr, pivot+1, right);
    }
    
    return; 
}

void merge(long long int arr[], int left, int mid, int right){
    int nL=mid-left+1;
    int nR=right-mid;

    int *arrL=(int*)malloc(sizeof(int)*(nL+1));
    int *arrR=(int *)malloc(sizeof(int)*(nR+1));
    for(int i=1; i<=nL;i++){
        arrL[i]=arr[left+i-1];
    }
    for(int j=1;j<=nR; j++){
        arrR[j]=arr[mid+j];
    }
    int l=1, r=1, k=left;
    while(l<=nL && r<=nR){
        if(arrL[l]<=arrR[r]){
            arr[k++]=arrL[l++];
        }
        else{
            arr[k++]=arrR[r++];
        }
    }

    while(l<=nL){
        arr[k++]=arrL[l++];
    }
    while(r<=nR){
        arr[k++]=arrR[r++];
    }

    return;   
}
void merge_sort(long long int arr[], int left, int right){
    if(left>=right) return;
    int mid=(int)(((double)left+(double)right)/2);
    //printf("mid: %d\n", mid);
    merge_sort(arr, left, mid);
    merge_sort(arr, mid+1, right);
    merge(arr, left, mid, right);
    return; 
}


void heapify(long long int arr3[],  int size, int cur) {
    int largest=cur, left = cur * 2 + 1, right = cur * 2 + 2;

    if (left<size&&arr3[left]>arr3[largest])
        largest = left;
    if (right < size&&arr3[right]>arr3[largest])
        largest = right;
 
    if (largest != cur) {
        swap(&arr3[largest], &arr3[cur]);
        heapify(arr3,  size, largest);
    }
}

void heap_sort(long long int arr3[], int size) {
    
    for (int j = size / 2 - 1; j >= 0; j--) {
        heapify(arr3,size, j);
    }
    for (int k= size - 1; k >= 0; k--) {
        swap(&arr3[0], &arr3[k]);
        heapify(arr3, k, 0);
    }
}

int MedianOfThree(long long int arr[], int x, int y, int z){
    int a=arr[x], b=arr[y], c=arr[z];
    if (a<=b && b<=c) return (y);
    else if (c<=b && b<=a) return (y);
    else if (a<=c && c<=b) return (z);
    else if (b<=c && c<=a) return (z);
    else if (b<=a && a<=c) return (x);
    else if (c<=a && a<=b) return (x);
}



void intros_sort(long long int arr[], int left, int right, int depth_limit){
    int size=right-left+1;
    if(size<32){
        insertion_sort(arr, left, right);
        return;
    }
    if(depth_limit==0){
        long long size=right-left+1;
        long long *arr2=new long long int[size];
        for(int i=0; i<size;i++){
            arr2[i]=arr[left+i];
        }
        heap_sort(arr2, size);
        for(int i=0;i<size; i++){
            arr[left+i]=arr2[i];
        }
        return;
    }
    else{
        depth_limit--;
        //assign median as pivot
        int pivot=MedianOfThree(arr, left, (left+size)/2 , right);
        swap(&arr[pivot], &arr[right]);
        //partition
        int pivot2=partition(arr, left, right);
        //recursive call 
        intros_sort(arr, left, pivot2-1, depth_limit);
        intros_sort(arr, pivot2+1, right, depth_limit);
        
    }
    return;
}


void random_intros_sort(long long int arr[], int left, int right, int depth_limit){
    int size=right-left+1;
    if(size<32){
        insertion_sort(arr, left, right);
        return;
    }
    if(depth_limit==0){
        long long size=right-left+1;
        long long *arr2=new long long int[size];
        for(int i=0; i<size;i++){
            arr2[i]=arr[left+i];
        }
        heap_sort(arr2, size);
        for(int i=0;i<size; i++){
            arr[left+i]=arr2[i];
        }
        return;
    }
    else{
        depth_limit--;
        //assign random pivot
        //partition
        int pivot2=random_partition(arr, left, right);
        //recursive call 
        intros_sort(arr, left, pivot2-1, depth_limit);
        intros_sort(arr, pivot2+1, right, depth_limit);
    }
    return;
}



int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

    if(argc != 3){
        printf("Argument Error!\n");
        return 0;
    }

    ifstream input;
    ofstream output;

    input.open(argv[1]);
	if (input.fail()) {
		cout << "File not Found\n";
		exit(1);
	}
    infile=argv[1];
    algorithm=argv[2];
    algo=atoi(argv[2]);
    if(algo<=0 || algo>4){
        cout<< "Invalid algorithm\n";
        exit(1);
    }
    outfile="result_"+algorithm+"_"+infile;

    start = clock();
    long long *arr;
    string str;
    int i;
    long long j=1, t=0;
    string s="";

    while (!input.eof()) {
            getline(input, str);
            int size=str.size();
            if(str[str.size()-1]-'0'==space){
                size--;
            }
            for (i = 0;i <size;i++) {
                if (str[i] - '0' != space) {
                    s += str[i];
                }
                else {
                    if(n==-1){
                        n = stoi(s);
                        arr = new long long [n+1];
                    }
                    else{
                        t=stoi(s);
                        arr[j++]=t;
                    }
                    s = "";
                }
            }
            t=stoi(s);
            arr[j++]=t;
            s="";        
    }
    input.close();


    double depthL;
    switch(algo){
        case 1:
            insertion_sort(arr, 1, n);
            break;
        case 2:
            merge_sort(arr, 1,n);
            break;
        case 3:
            quick_sort(arr, 1, n);
            break;
        // case 4:
        //     depthL=floor((log((double)n)));
        //     depthL*=2;
        //     intros_sort(arr, 1, n, (int)depthL);
        //     //intros_sort(arr, 1, n, 0);
        //     //heap_sort(arr, n);
        //     break;
        // case 5:
        //     random_quick_sort(arr, 1,n);
        //     break;
        case 4:
            depthL=floor((log((double)n)));
            depthL*=2;
            random_intros_sort(arr, 1, n, (int)depthL);
            break;
        default:
            break;
    }
    ending = clock();

    output.open(outfile);
    /*output*/
    output<<argv[1]<<"\n";//input file name
    output<<algo<<"\n";//algorithm index
    output<<n<<"\n";
    /*running time*/
    output<<1000* (double)(ending-start)/CLOCKS_PER_SEC<<"\n";
    /*sorted array*/
    
    for(i=1;i<=n;i++){
        output<<arr[i]<<" ";
    }
    output.close();

    

    return 0;
}