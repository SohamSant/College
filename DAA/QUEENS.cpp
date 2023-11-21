#include<bits/stdc++.h>
using namespace std;

void print(int n,int col[])     // Function to print current states of Queens
{
        for(int i=0;i<n;i++)
        {
               for(int j=0;j<n;j++)
               {
                        /* Print current queen number ie row number if 
                        column matches with j else print 0 */
                        if(col[i]==j) cout<<i+1<<" ";
                        else cout<<"0 ";
               }
               cout<<"\n";
        }
        cout<<"\n";      
}


bool place(int queen,int c,int col[])      // Function to check can Queen placed at current position
{
        int j=0;
        // Iterate throgh the column array
        while(j<queen)
        {
                // Check if there is queen in same column or diagonal
                if(col[j]==c || abs(col[j]-c)==abs(j-queen))    
                        return false;
                j++;
        }
        // Return true if current position is safe
        return true;
}

bool nqueen(int queen,int n,int col[])  
{
        // Flag to check can current queen be placed in any column
        int fl=0;
        
        // Loop through all the columns
        for(int i=0;i<n;i++)
        {
                // Check can queen be placed in current column
                if(place(queen,i,col))
                {
                        // If queen can be placed then assign its column in col array 
                        col[queen]=i;   
                        
                        //Print current state
                        cout<<"Placing Queen "<<queen+1<<"\n";
                        print(n,col);
                        
                        //If all queens placed end the execution
                        if(queen==n-1) return true;
                        
                        //After placing current queen check if next queen can be placed in next row
                        if(nqueen(queen+1,n,col))
                                return true;
                        
                        //Backtrack if placing queen doesn't lead to solution
                        col[queen]=-1;
                        
                        //Print backtrack state
                        cout<<"Backtracking Queen "<<queen+1<<"\n";
                        print(n,col);
                                              
                        fl=1;
                }
                        
        }       
        
        //If current Queen doesnt get ant position as safe 
        if(!fl)
        cout<<"Unable to place Queen "<<queen+1<<"\n\n";
        
        return false;
}



int main()
{
        int n;
        // Input for size of chessboard
        cout<<"Enter Size of chessboard : ";
        cin>>n;
        
        // N queens can not be placed if size is less than 3
        if(n<=3)
        {
                cout<<"\nSize should be more than 3\n";
                return 0;
        }
        
        /* Initialise col array to store column number 
         of queen number same as row number */
        int col[n];
        for(int i=0;i<n;i++) col[i]=-1;
        
        // Call nqueen function to place queens 
        nqueen(0,n,col);
          
        return 0;
}