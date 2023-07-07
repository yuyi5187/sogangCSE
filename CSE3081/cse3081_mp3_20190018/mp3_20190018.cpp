#include<iostream>
#include<cstdlib>
#include<fstream>
#include<queue>
#include<functional>
#include<algorithm>
#include<map>
#include<string>
#include<bitset>
#include<sstream>
#define internal "INTERNAL"

using namespace std;

/*공통*/
ifstream input;
ofstream output;
string option, infile, outfile;
int total_char=0; //metadata에 포함된 char의 갯수
int padding_num=0;

/*encoding*/
int origin_size=0;
int codeword_size=0;
map<string, string>ans; //각 char마다 codeword 저장
map<string, int>frequency; //각 char 마다 frequency 저장
string metadata=""; //huffman tree
int meta_size=0; //metadata size
//encoding 후 저장시에 다음 순서로 저장
//total_char(8bit)padding_bit개수(8bit)metadata+codeword

/*decoding*/
string encoded_data;
string read_meta;
int idx=0;


struct Node{
    string data;
    int freq;
    struct Node *left, *right;
    Node(string data, int freq){
        left=right=NULL;
        this->data=data;
        this->freq=freq;
    }
};

struct cmp{
    bool operator()(Node *left, Node *right){
        return (left->freq> right->freq);
    }
};

bool isLeaf(struct Node *node){
    if(node->left==NULL && node->right==NULL){
        return true;
    }
    return false;
}

void writeNode(struct Node* root){
    if(isLeaf(root)){
        //cout<<"1";
        total_char+=1;
        metadata+="1";
        string s=root->data;
        int ascii=s[0];
        //cout<<ascii<<" ";
        string tmp=bitset<8>(ascii).to_string();
        metadata+=tmp;
        //cout<<tmp<<"\n";

    }
    else{
        metadata+="0";
        //cout<<"0";
        writeNode(root->left);
        writeNode(root->right);
    }

    return;
}


void HuffmanCode(struct Node *root, string code){
    if(root==NULL){
        return;
    }
    //string->bitset으로 바꿔야 함
    if (root->data!=internal){
        ans.insert({root->data, code});
    }
    HuffmanCode(root->left, code+"0");
    HuffmanCode(root->right, code+"1");
}

void HUFFMAN(){
    priority_queue<Node*, vector<Node*>, cmp> MinHeap;
    struct Node *l, *r, *top;
    int i;
    for(auto iter=frequency.begin(); iter!=frequency.end(); iter++){
        struct Node *node=new Node(iter->first, iter->second);
        MinHeap.push(node);
    }

    int newfreq;
    while(MinHeap.size()>1){
        l=MinHeap.top();
        MinHeap.pop();
        r=MinHeap.top();
        MinHeap.pop();

        newfreq=l->freq+r->freq;
        top=new Node(internal, newfreq);
        top->left=l;
        top->right=r;
        MinHeap.push(top);
    }
    //전체 암호문 암호화하기
    HuffmanCode(MinHeap.top(), "");
    // for(auto iter: ans){
    //     cout<<iter.first<<": "<<iter.second<<"\n";
    // }
    /* tree 저장하기
       leaf: 1bit+8-bit char
       non-leaf: 0bit-> recursive call
    */
    writeNode(MinHeap.top());
    meta_size=metadata.size();

    return;
}

vector<string> string_to_codeword(string dataword){
    vector<string>codeword;
    string binary;
    string tmp;    
    //string dataword를 binary string codeword 
    int i;
    for( i=0;i<dataword.size(); i++){
        tmp=dataword[i];
        auto item=ans.find(tmp);
        if(item!= ans.end()){
            //cout<<item->first<<" "<<item->second<<"\n";
            auto tmp2=item->second;
            binary+=tmp2;
            codeword_size+=tmp2.size();
        }
        else{
            cout<<"HUFFMAN ERROR!\n";
        }
       
    }
    // for(auto k: ans){
    //     cout<<k.first<<" "<<k.second<<"\n";
    // }
    //cout<<binary<<"\n";
    int total_size=meta_size+codeword_size;
    //padding bit 추가하기
    padding_num=8-(total_size%8);
    //cout<<padding_num<<"\n";
    //padding+metadata+binary
    //cout<<codeword_size<<"\n";
    if(padding_num==8){
        padding_num=0;
    } 
    binary=metadata+binary;
    for(i=0;i<padding_num; i++){
        binary="0"+binary;
    }
    
    //전체 암호문(binary)를 8bit, byte단위로 나눠서 codeword에 저장하기
    for(i=0;i<total_size; i+=8){
        codeword.push_back(binary.substr(i, 8));
    }
    return codeword;
}

string binary_to_char(string binary){
    string c;
    bitset<8>bit(binary);
    c=char(bit.to_ulong());
    return c;
}

void encoder(){
    input.open(infile);
    output.open(outfile);
    if(input.fail()){
        cout<<"Input File Open Error!\n";
        exit(1);
    }
    if(output.fail()){
        cout<<"Output File Open Error!\n";
        exit(1);
    }

    //cout<<"START\n";

    string dataword; //원본 데이터 저장
    //읽으면서 각 알파벳마다 frequency 세기
    string str;
    int i;
    string tmp="";
    char c;
    while(true){
        c=input.get();
        if(input.fail()) break;
        tmp+=c;
        if(frequency.find(tmp)!=frequency.end()){
            frequency[tmp]++;
        }
        else{
            frequency[tmp]=1;
        }
        origin_size++;
        tmp="";
        dataword+=c; //원본 문자열 저장
    }

    input.close();
    
    //HUFFMAN Code 만들기
    HUFFMAN();
    
    /*출력*/
    //dataword to codeword
    vector<string>codeword=string_to_codeword(dataword);

    //total_char 개수 출력
    // string char_bin=bitset<8>(total_char).to_string();
    // output<<binary_to_char(char_bin);

    //padding bit 개수 출력
    string padnum_bin=bitset<8>(padding_num).to_string();
    output<<binary_to_char(padnum_bin);
    //cout<<padnum_bin<<"\n";
    //string -> bitset -> char 출력
    for(i=0;i<codeword.size();i++){
        //cout<<codeword[i]<<" ";
        output<<binary_to_char(codeword[i]);        
    }
    output.close();

}


void inorder(struct Node* t){
    if(t!=NULL){
        inorder(t->left);
        cout<<t->data<<" ";
        inorder(t->right);
    }
    return;
}



struct Node* readNode(){
    if(encoded_data[idx]=='1'){
        idx++;
        string tmp="";
        //tmp+=encoded_data[idx++];
        tmp=encoded_data.substr(idx, 8).c_str();
        //cout<<"a: "<<tmp<<" ";
        bitset<8>bit(tmp);
        char val=char(bit.to_ulong());
        tmp="";
        tmp+=val;
        //cout<<val<<"\n";
        idx+=8;
        struct Node *res=new Node(tmp, 0);
        return res;
    }
    else {
        idx++;
        struct Node *res=new Node(internal, 0);
        struct Node *leftchild=readNode();
        struct Node *rightchild=readNode();
        res->left=leftchild;
        res->right=rightchild;
        return res;
    }
    
}

string huffmanDecode(struct Node *root, string codeword){
    string ans="";
    struct Node *cur=root;
    for(int i=0;i<codeword.size();i++){
        if(codeword[i]=='0'){
            cur=cur->left;
        }
        else{
            cur=cur->right;
        }
        if(isLeaf(cur)){
            ans+=cur->data;
            cur=root;
        }
    }
    return ans;
}


string rebuild_HUFFMAN(){

    struct Node *root;
    root=readNode();
    //cout<<idx;
    encoded_data=encoded_data.substr(idx);
    //cout<<encoded_data<<"\n";
    
    //inorder(root);
    //cout<<"\n";

    string dataword=huffmanDecode(root, encoded_data);
    return dataword;
}


void decoder(){
    input.open(infile);
    output.open(outfile);
    if(input.fail()){
        cout<<"Input File Open Error!\n";
        exit(1);
    }
    if(output.fail()){
        cout<<"Output File Open Error!\n";
        exit(1);
    }

    string str, tmp;
    int i, ascii;
    char c;
    while(true){
        c=input.get();
        if(input.fail()) break;
        
        ascii=c;
        tmp=bitset<8>(ascii).to_string();
        
        encoded_data+=tmp;
        
    }
    input.close();
    //첫 8bit는 total_char, 두 번째 8bit는 padding_num
    //total_char=strtol(encoded_data.substr(0, 8).c_str(), 0, 2);
    padding_num=strtol(encoded_data.substr(0, 8).c_str(), 0, 2);
    //cout<<encoded_data<<"\n";
    encoded_data=encoded_data.substr(8+padding_num);
    //cout<<encoded_data<<"\n";
    string dataword=rebuild_HUFFMAN();
    output<<dataword;
    output.close();
    return;
}


int main(int argc, char *argv[]){
    ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
    if(argc!=3){
        cout<<"Arguments Error\n";
        exit(1);
    }
    option=argv[1];
    if(option!="-c" && option!="-d"){
        cout<<"Option Type Error\n";
        exit(1);
    }
    infile=argv[2];
    if(option=="-c"){
        outfile=infile+".zz";
        encoder();
    }
    else{
        outfile=infile+".yy";
        decoder();
    }

    

    return(0);

}