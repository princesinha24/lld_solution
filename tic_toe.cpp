#include <bits/stdc++.h>
using namespace std;
enum cell_val{
    available=0,
    player1=1,
    player2=-1  
};
class Player{
    public:
        int no;
        string name;
        Player(int k,string name){
            no=k;
            this->name=name;
        }
};

class cell{
    cell_val val;
    public:
        cell(){
            val=available;
        }
        cell_val fill_cell(Player* pl){
            if(pl->no==1){
                val=player1;
            }
            else{
                val=player2;
            }
            return val;
        }
        cell_val get_cell(){
            return val;
        }
};

class Board{
    int n;
    int cells_free;
    vector<vector<cell*>>cells;
    vector<int>row;
    vector<int>col;
    int dig1,dig2;
    void init_board(int n){
        this->n=n;
        for(int i=0;i<n;i++){
            vector<cell*>temp;
            for(int j=0;j<n;j++){
                temp.push_back(new cell());
            }
            cells.push_back(temp);
        }
        row=vector<int>(n,0);
        col=vector<int>(n,0);
        dig1=0;
        dig2=0;
        cells_free=n*n;
        winner=false;
    }
    bool check_winner(int x,int y){
        row[x-1]+=cells[x-1][y-1]->get_cell();
        col[y-1]+=cells[x-1][y-1]->get_cell();
        if(row[x-1]*cells[x-1][y-1]->get_cell()==n || col[y-1]*cells[x-1][y-1]->get_cell()==n){
            return true;
        }
        if(x==y){
            dig1+=cells[x-1][y-1]->get_cell();
            if(dig1*cells[x-1][y-1]->get_cell()==n){
                return true;
            }
        }
        if(x-1==n-y){
            dig2+=cells[x-1][y-1]->get_cell();
            if(dig2*cells[x-1][y-1]->get_cell()==n){
                return true;
            }
        }
       return false; 
    }
    bool valid_move(int x,int y){
        if(x>n || x<=0 || y>n || y<=0){
            return false;
        }
        if(cells[x-1][y-1]->get_cell()!=available){
            return false;
        }
        return true;
    }
    public:
        bool winner;
        Board(int n){
            init_board(n);
        }
        bool move(Player* pl,int x, int y){
            if( valid_move(x,y)){
                cells[x-1][y-1]->fill_cell(pl);
                cells_free--;
                if (check_winner(x,y)){
                    cout<<pl->name<<" is winner"<<endl;
                    winner=true;
                }
                else if(cells_free==0){
                    cout<<"Match Draw no one wins \n";
                    winner=true;
                }
                return true;
            }
            cout<<"Invalid move \n";
            return false;
        }
        ~Board(){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    delete cells[i][j];
                }
            }
        }
};
int main(){
    int n;
    cout<<"Enter size of Board \n";
    cin>>n;
    Board* board= new Board(n);
    Player* p1=new Player(1,"Prince");
    Player* p2=new Player(2,"Roshan");
    int x,y;
    for(int i=0;i<n*n;){
        if(board->winner){
            break;
        }
        else{
            if(i%2==0){
                cout<<p1->name<<" make move \n";
                cin>>x>>y;
                if(board->move(p1,x,y)){
                    i++;
                }
            }
            else{
                cout<<p2->name<<" make move \n";
                cin>>x>>y;
                if(board->move(p2,x,y)){
                    i++;
                }
            }
        }
    }
    delete board;
    delete p1;
    delete p2;
    cout<<"Game end"<<endl;
}
