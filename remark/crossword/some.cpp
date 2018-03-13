#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
void print(char table[10][10]){
    for(int row=0;row!=10;++row){
        for(int col=0;col!=10;++col){
            cout<<table[row][col]<<" ";
        };
        cout<<endl;
    };
}

void fillTable(char table[10][10]){
    for(int row=0;row!=10;++row){
        for(int col=0;col!=10;++col){
            table[row][col]='0';
        };
    };
}



int main() {
    string w1="qwerty";
    string w2="frvbn";
    char table[10][10];
    int xy[3]={-1,-1,-1};
    fillTable(table);
    //string w1="force";
    for(int i=0;i!=w1.size();++i){
        table[10/2][i+1]=w1.c_str()[i];
    };
    //string w2="hope";
    for(int row=0;row!=10;++row){
        for(int col=0;col!=10;++col){
            for(int i=0;i!=w2.size();++i){
                if(table[row][col]==w2[i]){
                    xy[0]=row;
                    xy[1]=col;
                    xy[2]=i;
                    goto MyBreak;
                }  
            };
        };
    };
    print(table);
    MyBreak:
    
    for(int i=xy[2]-1,row=xy[0]-1;i>=0;--i,--row){
        table[row][xy[1]]=w2[i];
    };
    for(int i=xy[2],row=xy[0];i!=w2.size();++i,++row){
        table[row][xy[1]]=w2[i];
    };
    print(table);
    return 0;
}
