#include<bits/stdc++.h>
#define pii pair<int,int>
#define pii2 pair<pii,int>
using namespace std;
typedef struct Process
{
    int arrivaltime;
    int remainingtime;
    int timequantum;
    int pushbacktime;
} Process;
main()
{
    int n;
    cout<<"Number of processes: ";
    cin>>n;
    Process a[n+1];
    priority_queue<pii2,vector<pii2>,greater<pii2> >pq;
    queue<int>q1,q2;
    int executing=0,t=0;
    for(int i=1;i<=n;i++)
    {
        cout<<"Process "<<i<<": "<<'\n';
        cout<<"Arrival time: ";
        cin>>a[i].arrivaltime;
        cout<<"Burst time: ";
        cin>>a[i].remainingtime;
        pq.push({{a[i].arrivaltime,0},i});
    }
    while(pq.size()||q1.size()||q2.size()||executing)
    {
        while(pq.size()&&pq.top().first.first==t)
        {
            if(pq.top().first.second==1)
            {
                if(a[pq.top().second].remainingtime==0||t!=a[pq.top().second].pushbacktime+15)
                {
                    pq.pop();
                    continue;
                }
            }
            q1.push(pq.top().second);
            a[pq.top().second].timequantum=8;
            if(pq.top().first.second==1)
            {
                cout<<"Time "<<t<<": Push process "<<pq.top().second<<" from queue 2 to queue 1"<<'\n';
                q2.pop();
            }
            else
            {
                cout<<"Time "<<t<<": Process "<<pq.top().second<<" arrives and is pushed to queue 1"<<'\n';
            }
            pq.pop();
        }
        if(executing)
        {
            if(a[executing].timequantum==0&&q1.size())
            {
                q2.push(executing);
                pq.push({{t+15,1},executing});
                cout<<"Time "<<t<<": Process "<<executing<<" is preempted and pushed back to queue 2"<<'\n';
                a[executing].pushbacktime=t;
                executing=q1.front();
                q1.pop();
                a[executing].remainingtime--;
                a[executing].timequantum--;
                if(a[executing].remainingtime==0)
                {
                    cout<<"Time "<<t<<": Execute process "<<executing<<" in queue 1. Remaining time: 0"<<'\n';
                    executing=0;
                    t++;
                    continue;
                }
                if(a[executing].timequantum==0)
                {
                    q2.push(executing);
                    pq.push({{t+16,1},executing});
                    cout<<"Time "<<t<<": Execute process "<<executing<<" in queue 1. Remaining time: "<<a[executing].remainingtime<<'\n';
                    cout<<"Time "<<t<<": Push process "<<executing<<" from queue 1 to queue 2"<<'\n';
                    a[executing].pushbacktime=t+1;
                    executing=0;
                    t++;
                }
                else
                {
                    cout<<"Time "<<t<<": Execute process "<<executing<<" in queue 1. Remaining time: "<<a[executing].remainingtime<<'\n';
                    t++;
                }
            }
            else if(a[executing].timequantum==0)
            {
                a[executing].remainingtime--;
                a[executing].pushbacktime=t+1;
                if(a[executing].remainingtime==0)
                {
                    cout<<"Time "<<t<<": Execute process "<<executing<<" in queue 2. Remaining time: 0"<<'\n';
                    executing=0;
                    t++;
                }
                else
                {
                    cout<<"Time "<<t<<": Execute process "<<executing<<" in queue 2. Remaining time: "<<a[executing].remainingtime<<'\n';
                    t++;
                }
            }
            else
            {
                a[executing].remainingtime--;
                a[executing].timequantum--;
                if(a[executing].remainingtime==0)
                {
                    cout<<"Time "<<t<<": Execute process "<<executing<<" in queue 1. Remaining time: 0"<<'\n';
                    executing=0;
                    t++;
                    continue;
                }
                if(a[executing].timequantum==0)
                {
                    q2.push(executing);
                    pq.push({{t+16,1},executing});
                    cout<<"Time "<<t<<": Execute process "<<executing<<" in queue 1. Remaining time: "<<a[executing].remainingtime<<'\n';
                    cout<<"Time "<<t<<": Push process "<<executing<<" from queue 1 to queue 2"<<'\n';
                    executing=0;
                    a[executing].pushbacktime=t+1;
                    t++;
                }
                else
                {
                    cout<<"Time "<<t<<": Execute process "<<executing<<" in queue 1. Remaining time: "<<a[executing].remainingtime<<'\n';
                    t++;
                }
            }
        }
        else if(q1.size())
        {
            executing=q1.front();
            q1.pop();
            a[executing].remainingtime--;
            a[executing].timequantum--;
            if(a[executing].remainingtime==0)
            {
                cout<<"Time "<<t<<": Execute process "<<executing<<" in queue 1. Remaining time: 0"<<'\n';
                executing=0;
                t++;
                continue;
            }
            if(a[executing].timequantum==0)
            {
                q2.push(executing);
                pq.push({{t+16,1},executing});
                cout<<"Time "<<t<<": Execute process "<<executing<<" in queue 1. Remaining time: "<<a[executing].remainingtime<<'\n';
                cout<<"Time "<<t<<": Push process "<<executing<<" from queue 1 to queue 2"<<'\n';
                a[executing].pushbacktime=t+1;
                executing=0;
                t++;
            }
            else
            {
                cout<<"Time "<<t<<": Execute process "<<executing<<" in queue 1. Remaining time: "<<a[executing].remainingtime<<'\n';
                t++;
            }
        }
        else if(q2.size())
        {
            executing=q2.front();
            q2.pop();
            a[executing].pushbacktime=t+1;
            a[executing].remainingtime--;
            if(a[executing].remainingtime==0)
            {
                cout<<"Time "<<t<<": Execute process "<<executing<<" in queue 2. Remaining time: 0"<<'\n';
                executing=0;
                t++;
            }
            else
            {
                cout<<"Time "<<t<<": Execute process "<<executing<<" in queue 2. Remaining time: "<<a[executing].remainingtime<<'\n';
                t++;
            }
        }
        else 
        {
            cout<<"Time "<<t<<": No process execution"<<'\n';
            t++;
        }
        //cout<<executing<<" "<<pq.size()<<" "<<q1.size()<<" "<<q2.size()<<'\n';
    }
    cin>>n;
}