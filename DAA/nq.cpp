#include<bits/stdc++.h>
using namespace std;

bool issafe(vector<vector<int>> board,int row,int colm,int n){
        for(int i =0;i<n;i++){
            if(board[i][colm]==1){
                return false;
            }
        }
        for(int i =row,j=colm;i>=0&&j>=0;i--,j--){
            if(board[i][j]==1){
                return false;
            }
        }
        for(int i =row,j=colm;i>=0&&j<n;i--,j++){
            if(board[i][j]==1){
                return false;
            }
        }
        return true;
}

bool solve(vector<vector<int>> board,int row,int n){
    if(row==n){
        for(int i =0;i<n;i++){
            for(int j =0;j<n;j++){
                cout<<(board[i][j]==1? 'Q':'.')<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        return true;
    }


    for(int colm =0 ;colm<n;colm++){
        if(issafe(board,row,colm,n)){
            board[row][colm]=1;

            if(solve(board,row+1,n)){
                return true;
            }

            board[row][colm]=0;

        }
    }

    return false;
}
int main(){
    int n ;
    cout<<"Enter the No. of queens :";
    cin>>n;

    vector<vector<int>> board (n,vector<int>(n,0));

    if(!solve(board,0,n)){
        cout<<"No SOL";
    }

    return 0;
}