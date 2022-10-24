#include<bits/stdc++.h>
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll          long long int
#define nl          "\n"
#define pb          push_back
#define mk          make_pair
#define fe          first
#define se          second
#define all(v)      v.begin(),v.end()
#define testcases   ll t;cin>>t;while(t--)
#define var(n)      ll n;cin>>n;
#define input(v,n)  vector<ll> v(n);for(ll i=0;i<n;i++)cin>>v[i];
using namespace std;

// SJF non preemptive to calculate avg waiting time and avg turn around time
struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;


};
 

int main()
{
    //FASTIO
    int n;
    struct process p[100];// array of the process
    float avg_turnaround_time;
    float avg_waiting_time;
    
    int total_turnaround_time;
    int total_waiting_time;
    
    //int burst_remaining[100];// we have have restriction to change the array because of the formula
    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed));// copies 0 at each index in is_completed array
    

    cout<<"Enter the number of processes :";

    cin>>n;

    for(int i=0;i<n;i++)
    {
        cout<<"Enter arrival time of process "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Enter the burst time of the process "<<i+1<<": ";
        cin>>p[i].burst_time;
        p[i].pid=i+1;
        //burst_remaining[i]=p[i].burst_time;
        cout<<endl;
    }
    int current_time=0;
    int completed=0;
    int prev=0;// to get idle time 
    while(completed!=n)
    {
        int idx=-1;
        int mn=INT_MAX;
        // first we have to calculate which process are in ready queue
        for(int i=0;i<n;i++)
        {
            if(p[i].arrival_time<=current_time &&is_completed[i]==0)//if process have arrival time<=current_time and process is not completed that means this process are in ready queue
            {
                    if(p[i].burst_time<mn)//take process with minimum burst time
                    {
                        mn=p[i].burst_time;
                        idx=i;
                    }
                    if(p[i].burst_time==mn)// if two process have same burst time then check for its arrival time
                    {
                        if(p[i].arrival_time<p[idx].arrival_time)
                        {
                            mn=p[i].arrival_time;
                            idx=i;
                        }
                    }
            }
        }
        if(idx!=-1)// means process is found in ready queue which fullfill the crieteria
        {
            p[idx].start_time=current_time;

            p[idx].completion_time=p[idx].start_time+p[idx].burst_time;

            p[idx].turnaround_time=p[idx].completion_time-p[idx].arrival_time;//

            p[idx].waiting_time=p[idx].turnaround_time-p[idx].burst_time;//

            total_turnaround_time+=p[idx].turnaround_time;

            total_waiting_time+=p[idx].waiting_time;

            is_completed[idx]=1;

            completed++;

            current_time=p[idx].completion_time;

            prev=current_time;





        }
        else
        {
            current_time++;
        }

    }

    avg_turnaround_time=(float)total_turnaround_time/n;

    avg_waiting_time=(float)total_waiting_time/n;

    cout<<nl<<nl;

    cout<<"#P\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<nl<<endl;

    for(int i=0;i<n;i++)
    {
        cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].start_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<endl;
    }

    cout<<"Avarage waiting time is :"<<avg_waiting_time<<endl;

    cout<<"Avarage turn around time is :"<<avg_turnaround_time<<endl;

    cout<<endl;
    



    return 0;
}
