#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int TAT;
    int waiting_time;

};

void SJF(vector<process> p){
    int c=0;
    int time=0;
    string gantt="|";
    while (c<p.size())
    {
        int shortest=-1;
        for(int i =0 ; i<p.size();i++){
            if(p[i].arrival_time<=time&&p[i].remaining_time>0){
                if(shortest==-1||p[i].remaining_time<p[shortest].remaining_time)
                    shortest=i;
            }
        }

        if(shortest==-1){
            time++;
            gantt+="-";
        }
        else{
            p[shortest].remaining_time--;
            time++;
            gantt+=to_string(p[shortest].pid);

            if(p[shortest].remaining_time==0){
                c++;
                p[shortest].TAT=time-p[shortest].arrival_time;
                p[shortest].waiting_time=p[shortest].TAT-p[shortest].burst_time;
            }
        }

    }

    cout<<"Gantt Chart: "<<gantt<<"|"<<endl;

    double avg_turnaround_time = 0.0, avg_waiting_time = 0.0;
    for (int i =0; i<p.size();i++) {
        avg_turnaround_time += p[i].TAT;
        avg_waiting_time += p[i].waiting_time;
    }
    avg_turnaround_time /= p.size();
    avg_waiting_time /= p.size();
    cout << "Average Turnaround Time: " << avg_turnaround_time << "\n";
    cout << "Average Waiting Time: " << avg_waiting_time << "\n";
}
    


void RR(vector<process> p, int q){
    int completed =0;
    int time = 0;
    string gantt ="|";

    while(completed<p.size()){
        for(int i =0; i< p.size();i++){
            if(p[i].arrival_time<=time&&p[i].remaining_time>0){
                int execution_time=min(q,p[i].remaining_time);
                p[i].remaining_time-=execution_time;
                time+=execution_time;

                for(int j =0 ; j<execution_time;j++){
                    gantt+=to_string(p[i].pid);
                }

                if(p[i].remaining_time==0){
                    completed++;
                     p[i].TAT=time-p[i].arrival_time;
                     p[i].waiting_time=p[i].TAT-p[i].burst_time;
                }
            }
        }
    }

    cout<<"Gantt Chart: "<<gantt<<"|"<<endl;

    double avg_turnaround_time = 0.0, avg_waiting_time = 0.0;
    for (int i =0; i<p.size();i++) {
        avg_turnaround_time += p[i].TAT;
        avg_waiting_time += p[i].waiting_time;
    }
    avg_turnaround_time /= p.size();
    avg_waiting_time /= p.size();
    cout << "Average Turnaround Time: " << avg_turnaround_time << "\n";
    cout << "Average Waiting Time: " << avg_waiting_time << "\n";
    
}

int main(){
        int n ;
        int choice;
        int q;
        cout<<"Enter the number of processed:";
        cin>>n;

        vector<process> pro(n);

        cout<<"Enter Arival time and Burst time:"<<endl;

        for(int i =0; i<n;i++){
            pro[i].pid=i+1;
            cout<<"Process "<<i+1<<" :";
            cin>>pro[i].arrival_time>>pro[i].burst_time;
            pro[i].remaining_time=pro[i].burst_time;
        }

        while(true){
            cout<<"Choode scheduling algorithm:"<<endl;
            cout<<"1. SJF"<<endl;
            cout<<"2. Round Robin\n";
            cout<<"3. Exit\n";

            cin>>choice;

            switch(choice){
                case 1:
                    SJF(pro);
                    break;
                case 2:
                    cout<<"Enter time quantum for Round Robin:";
                    cin>>q;
                    RR(pro,q);
                    break;
                case 3:
                    cout<<"Thank you..."<<endl;
                    return 0;
                default:
                    cout<<"Invalid choice"<<endl;
            }
        }

        return 0;
}