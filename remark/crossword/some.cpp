#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
const int ROW_TABLE=10;
const int COL_TABLE=10;
enum __status__{freely,alone,block,wordHere};
enum __position__{vertical,horizontal,zero};
class Cell{
public:
    explicit Cell(char value,__status__ status=freely,__position__ pos=zero):
            status_(status),
            value_(value),
            pos_(pos){}
    Cell():
            status_(freely),
            value_('0'),
            pos_(zero){}
    __status__ Status()const{return status_;}
    void setStatus(__status__ x){status_=x;}
    char Value() const{return value_;};
    void setValue(char x){value_=x;}
    __position__ Pos()const{return pos_;}
    void setPos(__position__ x){pos_=x;}
    friend ostream &operator<<(ostream&, const Cell&);
private:
    char value_;
    __status__ status_;
    __position__ pos_;
};
ostream & operator<<(ostream &x,Cell const &cell){
    x<<cell.Value();
    return x;
}
void printValue(Cell table[ROW_TABLE][COL_TABLE]){
    for(int row=0;row!=ROW_TABLE;++row){
        for(int col=0;col!=COL_TABLE;++col){
            cout<<table[row][col]<<" ";
        };
        cout<<endl;
    };
}
void printStatus(Cell table[ROW_TABLE][COL_TABLE]){
    for(int row=0;row!=ROW_TABLE;++row){
        for(int col=0;col!=COL_TABLE;++col){
            cout<<table[row][col].Status()<<" ";
        };
        cout<<endl;
    };
}

void TryIfCellBlock(Cell table[ROW_TABLE][COL_TABLE],int flag=0){
    for(int row=0;row!=ROW_TABLE;++row){
        for(int col=0;col!=COL_TABLE;++col){
            Cell *next=&table[row][col];
            if(next->Status()!=block && next->Status()!=wordHere){
                int sum=0;
                if(table[row][col+1].Status()==wordHere){sum+=1;}
                if(table[row][col-1].Status()==wordHere){sum+=1;}
                if(table[row+1][col].Status()==wordHere){sum+=1;}
                if(table[row-1][col].Status()==wordHere){sum+=1;}
                if(sum!=0){
                    if(sum==1){
                        next->setStatus(alone);
                    }
                    else{
                        if(flag!=0){
                            next->setValue('#');
                        }
                        next->setStatus(block); 
                    }
                }
            }
        };
    };
}

bool TryStringInTable(Cell table[ROW_TABLE][COL_TABLE],string word,__position__ flag,int xy[3]){
    for(int row=0;row!=ROW_TABLE;++row){
        for(int col=0;col!=COL_TABLE;++col){
            for(int i=0;i!=word.size();++i){
                if(table[row][col].Status()==wordHere){
                    if(table[row][col].Value()==word[i]){
                        xy[0]=row;
                        xy[1]=col;
                        xy[2]=i;
                        return true;
                    }
                }  
            };
        };
    };
    return false;
}

bool SetStringToTable(Cell table[ROW_TABLE][COL_TABLE],string word,int xy[3],__position__ pos){
    int sum=0;
    if(pos==horizontal){
    for(int i=xy[2]-1,row=xy[0]-1;i>=0;--i,--row){
        Cell *next=&table[row][xy[1]];
        if(next->Status()==block && next->Status()==wordHere){
            ++sum;
        }
        if(next->Pos()==pos){
            sum+=2;
            break;
        }
    };        
    for(int i=xy[2],row=xy[0];i!=word.size();++i,++row){
        Cell *next=&table[row][xy[1]];
        if(next->Status()==block && next->Status()==wordHere){
            ++sum;
        }
        if(next->Pos()==pos){
            sum+=2;
            break;
        }
    };
    if(sum<=1){
    for(int i=xy[2]-1,row=xy[0]-1;i>=0;--i,--row){
        Cell *next=&table[row][xy[1]];
        next->setValue(word[i]);
        next->setPos(pos);
        next->setStatus(wordHere);
    };
    for(int i=xy[2],row=xy[0];i!=word.size();++i,++row){
        Cell *next=&table[row][xy[1]];
        next->setValue(word[i]);
        next->setPos(pos);
        next->setStatus(wordHere);
    };
        return true;
    }else{
        return false;
    }
    }
    else if(pos==vertical){
//     for(int i=xy[2]-1,row=xy[0]-1;i>=0;--i,--row){
    for(int i=xy[2]-1,col=xy[1]-1;i>=0;--i,--col){
//         Cell *next=&table[row][xy[1]];
        Cell *next=&table[xy[0]][col];
        if(next->Status()==block && next->Status()==wordHere){
            ++sum;
        }
        if(next->Pos()==pos){
            sum+=2;
            break;
        }
    };        
    for(int i=xy[2],col=xy[1];i!=word.size();++i,++col){
        Cell *next=&table[xy[0]][col];
        if(next->Status()==block && next->Status()==wordHere){
            ++sum;
        }
        if(next->Pos()==pos){
            sum+=2;
            break;
        }
    };
    if(sum<=1){
    for(int i=xy[2]-1,col=xy[1]-1;i>=0;--i,--col){
        Cell *next=&table[xy[0]][col];
        next->setValue(word[i]);
        next->setPos(pos);
        next->setStatus(wordHere);
    };
    for(int i=xy[2],col=xy[1];i!=word.size();++i,++col){
        Cell *next=&table[xy[0]][col];
        next->setValue(word[i]);
        next->setPos(pos);
        next->setStatus(wordHere);
    };
        return true;
    }else{
        return false;
    }
    }
}
int main() {
    Cell table[ROW_TABLE][COL_TABLE];
    string w1="force";
    string w2="hope";
    string w3="place";
    int xy[3]={-1,-1,-1};
    for(int i=0;i!=w1.size();++i){
        Cell *next=&table[ROW_TABLE/2][i+(w1.size()/2)];
        next->setValue(w1.c_str()[i]);
        next->setPos(vertical);
        next->setStatus(wordHere);
    };
    
    if(TryStringInTable(table,w2,vertical,xy)){
        if(SetStringToTable(table,w2,xy,horizontal)){
            TryIfCellBlock(table,1);
        }
    }
    if(TryStringInTable(table,w3,vertical,xy)){
        if(SetStringToTable(table,w3,xy,horizontal)){
            TryIfCellBlock(table,1);
        }
    }
    string w4="fear";
    if(TryStringInTable(table,w4,vertical,xy)){
        if(SetStringToTable(table,w4,xy,horizontal)){
            TryIfCellBlock(table,1);
        }
        else{
            cout<<w4+" is not in"<<endl;
        }
    }
    w4="leo";
    if(TryStringInTable(table,w4,horizontal,xy)){
        if(SetStringToTable(table,w4,xy,vertical)){
            TryIfCellBlock(table,1);
        }
        else{
            cout<<w4+" is not in"<<endl;
        }
    }
    w4="en";
    if(TryStringInTable(table,w4,horizontal,xy)){
        if(SetStringToTable(table,w4,xy,vertical)){
            TryIfCellBlock(table,1);
        }
        else{
            cout<<w4+" is not in"<<endl;
        }
    }
//     TryStringInTable(table,,vertical,xy);
//     SetStringToTable(table,"fear",xy);
//     TryIfCellBlock(table,1);
//     printStatus(table);
    printValue(table);
    return 0;
}
/*
Running first/f.cpp...
fear is not in
en is not in
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 p # 0 0 0
0 0 0 0 0 l e o 0 0
0 0 # h # a # 0 0 0
0 0 f o r c e 0 0 0
0 0 # p # e # 0 0 0
0 0 0 e 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
*/
