#include <bits/stdc++.h>
using namespace std;

void sos(int index, int size , int set[],int targetsum,vector<int> subset){
    if(targetsum==0){
        cout<<endl;
        cout<<"[";
        for(int i =0 ; i<subset.size();i++){
            cout<<subset[i]<<" ";
        }
        cout<<"]"<<endl;
        cout<<endl;

        return;
    }
    if(index==size||targetsum<0){
        return;
    }

    sos(index+1,size,set,targetsum,subset);

    subset.push_back(set[index]);
    sos(index+1,size,set,targetsum-set[index],subset);
    subset.pop_back();
};

int main(){
    int n;
    cout<<"Enter the size of the set :";
    cin>>n;
    int set[n];

    cout<<"Enter the values of the state: ";
    for(int i =0;i<n;i++){
        cin>>set[i];
    }

    int sum;
    cout<<"enter the target sum: ";
    cin>>sum;

    vector<int> subset;


    sos(0,n,set,sum,subset);

}