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
    for(int row=0;row!=ROW_TABLE;++row){
        for(int col=0;col!=COL_TABLE;++col){
            for(int i=0;i!=w2.size();++i){
                if(table[row][col].Status()==wordHere){
                    if(table[row][col].Value()==w2[i]){
                        xy[0]=row;
                        xy[1]=col;
                        xy[2]=i;
                        goto MyBreak;
                    }
                }  
            };
        };
    };
    MyBreak:
//     cout<<xy[0]<<" "<<xy[1]<<" "<<xy[2]<<endl;
    for(int i=xy[2]-1,row=xy[0]-1;i>=0;--i,--row){
        Cell *next=&table[row][xy[1]];
        next->setValue(w2[i]);
        next->setPos(horizontal);
        next->setStatus(wordHere);
    };
    for(int i=xy[2],row=xy[0];i!=w2.size();++i,++row){
        Cell *next=&table[row][xy[1]];
        next->setValue(w2[i]);
        next->setPos(horizontal);
        next->setStatus(wordHere);
    };
    xy[0]=-1,xy[1]=-1,xy[2]=-1;
     for(int row=0;row!=ROW_TABLE;++row){
        for(int col=0;col!=COL_TABLE;++col){
            for(int i=0;i!=w3.size();++i){
                if(table[row][col].Status()==wordHere){
                    if(table[row][col].Value()==w3[i]){
                        xy[0]=row;
                        xy[1]=col;
                        xy[2]=i;
                        goto MyBreak2;
                    }
                }  
            };
        };
    };
    MyBreak2:
    for(int i=xy[2]-1,row=xy[0]-1;i>=0;--i,--row){
        Cell *next=&table[row][xy[1]];
        next->setValue(w3[i]);
        next->setPos(horizontal);
        next->setStatus(wordHere);
    };
    for(int i=xy[2],row=xy[0];i!=w3.size();++i,++row){
        Cell *next=&table[row][xy[1]];
        next->setValue(w3[i]);
        next->setPos(horizontal);
        next->setStatus(wordHere);
    };
    TryIfCellBlock(table,1);
//     printStatus(table);
    printValue(table);
    return 0;
}
