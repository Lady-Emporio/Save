#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
const int ROW_TABLE=40;
const int COL_TABLE=40;
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
    void setRow(int x){row_=x;}
    void setCol(int x){col_=x;}
    int Row()const{return row_;}
    int Col()const{return col_;}
private:
    int row_;
    int col_;
    char value_;
    __status__ status_;
    __position__ pos_;
};
ostream & operator<<(ostream &x,Cell const &cell){
    x<<cell.Value();
    return x;
}
void printValue(Cell table[ROW_TABLE][COL_TABLE], int x=0){
    if(x==0){
        for(int row=0;row!=ROW_TABLE;++row){
            for(int col=0;col!=COL_TABLE;++col){
                cout<<table[row][col]<<" ";
            };
            cout<<endl;
        };
    }
    else{
        for(int row=0;row!=ROW_TABLE;++row){
            for(int col=0;col!=COL_TABLE;++col){
                char i=table[row][col].Value();
                if(i=='0'){
                    i=' ';
                }
                cout<<i<<" ";
            };
            cout<<endl;
        };
    }    
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

bool testIndexTable(int index){
    if(index>=COL_TABLE){
        return true;
    }
    else if(index<0){return true;}
    else{
        return false;
    }

}

bool tryFreeSizeVertical(Cell table[ROW_TABLE][COL_TABLE],__position__ pos,string word,int row,int col,int id){
bool really=true;
if(pos==vertical){//then need set in horizontal
for(int i=id-1, r=row-1;i>=0;--i,--r){   //[:совпадение][совпадение:] и еще блок перед этим
    if(testIndexTable(r)){return false;}
    Cell *next=&table[r][col];
    if(next->Status()==wordHere || next->Status()==block){
        really=false;
    }
}
for(int i=id+1, r=row+1;i!=word.size();++i,++r){ //блок за словом.
    if(testIndexTable(r)){return false;}
    Cell *next=&table[r][col];
    if(next->Status()==wordHere || next->Status()==block){
        really=false;
    }
}   
if(!really){
    return false;
}else{
    for(int i=id-1, r=row-1;i>=-1;--i,--r){ //до совпадения
        if(i==-1){
        if(testIndexTable(r)){return true;}
        Cell *next=&table[r][col];
        next->setValue('#');
        next->setPos(zero);
        next->setStatus(block);
        break;
        }
        Cell *next=&table[r][col];
        next->setValue(word[i]);
        next->setPos(horizontal);
        next->setStatus(wordHere);
        
    }
    for(int i=id+1, r=row+1;i!=word.size()+1;++i,++r){ //после совпадения
        if(i==word.size()){
            if(testIndexTable(r)){return true;}
            Cell *next=&table[r][col];
            next->setValue('#');
            next->setPos(zero);
            next->setStatus(block);
            break;
        }
        Cell *next=&table[r][col];
        next->setValue(word[i]);
        next->setPos(horizontal);
        next->setStatus(wordHere);
    }
}
return true;
}
}

bool tryFreeSizeHorizontal(Cell table[ROW_TABLE][COL_TABLE],__position__ pos,string word,int row,int col,int id){
bool really=true;
if(pos==horizontal){//then need set in vertical
for(int i=id-1, c=col-1;i>=0;--i,--c){   //[:совпадение][совпадение:] и еще блок перед этим
    if(testIndexTable(c)){return false;}
    Cell *next=&table[row][c];
    if(next->Status()==wordHere || next->Status()==block){
        really=false;
    }
}
for(int i=id+1, c=col+1;i!=word.size();++i,++c){ //блок за словом.
    if(testIndexTable(c)){return false;}
    Cell *next=&table[row][c];
    if(next->Status()==wordHere || next->Status()==block){
        really=false;
    }
}   
if(!really){
    return false;
}
else{
    for(int i=id-1, c=col-1;i>=-1;--i,--c){   //[:совпадение][совпадение:] и еще блок перед этим
        if(i==-1){
        if(testIndexTable(c)){return true;}
        Cell *next=&table[row][c];
        next->setValue('#');
        next->setPos(zero);
        next->setStatus(block);
        break;
        }
        Cell *next=&table[row][c];
        next->setValue(word[i]);
        next->setPos(vertical);
        next->setStatus(wordHere);
    }
    for(int i=id+1, c=col+1;i!=word.size()+1;++i,++c){ //блок за словом.
        if(i==word.size()){
            if(testIndexTable(c)){return false;}
            Cell *next=&table[row][c];
            next->setValue('#');
            next->setPos(zero);
            next->setStatus(block);
        break;
        }
        Cell *next=&table[row][c];
        next->setValue(word[i]);
        next->setPos(vertical);
        next->setStatus(wordHere);
    }
    
    
}
}
}

void CanSetWord(Cell table[ROW_TABLE][COL_TABLE],string word){
    for(int row=0;row!=ROW_TABLE;++row){
        for(int col=0;col!=COL_TABLE;++col){
            for(int i=0;i!=word.size();++i){
                if(table[row][col].Value()==word[i]){
                    if(table[row][col].Pos()==vertical){
                        if(tryFreeSizeVertical(table,table[row][col].Pos(),word,row,col,i)){
                            return;
                        }
                    }else if(table[row][col].Pos()==horizontal){
                        if(tryFreeSizeHorizontal(table,table[row][col].Pos(),word,row,col,i)){
                            return;
                        }
                    }
//                     if(tryFreeSizeVertical(table,table[row][col].Pos(),word,row,col,i)){
//                         return;
//                     }if(tryFreeSizeHorizontal(table,table[row][col].Pos(),word,row,col,i)){
//                         return;
//                     }
                }
            }
        }
    }
}
int main() {
    Cell table[ROW_TABLE][COL_TABLE];
    string w1="force";
    string w2="hope";
    string w3="place";
    int xy[3]={-1,-1,-1};
    for(int i=-1;i!=w1.size()+1;++i){
        if(i==-1 || i==w1.size()){
            Cell *next=&table[ROW_TABLE/2][i+(COL_TABLE/2)-(w1.size()/2)];
            next->setValue('#');
            next->setPos(zero);
            next->setStatus(block);
            continue;
        }
        Cell *next=&table[ROW_TABLE/2][i+(COL_TABLE/2)-(w1.size()/2)];
        next->setValue(w1.c_str()[i]);
        next->setPos(vertical);
        next->setStatus(wordHere);
    };
  
//     CanSetWord(table,w2);
//     TryIfCellBlock(table,1);
//     CanSetWord(table,"leo");
//     TryIfCellBlock(table,1);
    
//     vector<string>w={"install","Framework","using","an","online","offline","building","source","packages","yourself"};
    vector<string>w={"computers","are","some","of","the","most","versatile","tools","that","we","have","available","they","are","capable","of","performing","stunning","feats","of","computation","they","allow","information","to","be","exchanged","easily","regardless","of","their","physical","location","they","simplify","many","everyday","tasks","and","they","allow","us","to","automate","many","processes","that","would","be","tedious","or","boring","to","perform","otherwise"};
    for(int i=0;i!=w.size();++i){
        CanSetWord(table,w[i]);
        TryIfCellBlock(table,1);
    };
    
    
//     TryIfCellBlock(table,1);
//     printStatus(table);
    //printValue(table);
    printValue(table,1);
    return 0;
}
