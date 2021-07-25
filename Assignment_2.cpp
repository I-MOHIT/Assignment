#include<bits/stdc++.h>
using namespace std;

class Graph{
    public:
    vector<vector<int>> adjList;

    Graph(vector<vector<int>> &roads,int n){
        adjList.resize(n);

        for(int i=0;i<roads.size();i++){
            adjList[roads[i][0]-1].push_back(roads[i][1]-1);
            adjList[roads[i][1]-1].push_back(roads[i][0]-1);
        }
    }
};

bool isReachable(int n,int u,int v,Graph g,int x){
    if(u==v){
        return true;
    }

    queue<int> q;

    vector<bool> visited;
    visited.resize(n,false);

    visited[u]=true;
    q.push(u);

    vector<int> dist;
    dist.resize(n,INT_MAX);
    dist[u]=0;

    while(!q.empty()){
        u=q.front();
        q.pop();

        for(int w:g.adjList[u]){
            if(visited[w]==false){
                visited[w]=true;
                q.push(w);
                dist[w]=dist[u]+1;

                if(w==v){
                    if(dist[v]<=x){
                        return true;
                    }else{
                        return false;
                    }
                }
            }
        }
    }
    return false;
}

int possibleHotspots(int n,int h,int x,vector<int> &hotspots,vector<vector<int>> &roads){
    Graph g(roads,n);

    int count=0;

    for(int i=0;i<n;i++){
        bool isHotspot=true;
        for(int j=0;j<h;j++){
            if(isReachable(n,i,hotspots[j]-1,g,x)==false){
                isHotspot=false;
                break;
            }
        }
        if(isHotspot){
            count++;
        }
    }

    return count;
}

int main(){
    int n,h,x;

    cout<<"Enter the number of cities, number of hotspot cities and the maximum distance the virus can travel."<<endl;
    cin>>n>>h>>x;

    vector<int> hotspots;
    hotspots.resize(h,0);

    cout<<"Enter the hotspot cities."<<endl;

    for(int i=0;i<h;i++){
        cin>>hotspots[i];
    }

    vector<vector<int>> roads;
    roads.resize(n-1,vector<int> (2,0));

    cout<<"Enter the cities in pairs which are connected."<<endl;

    for(int i=0;i<n-1;i++){
        cin>>roads[i][0]>>roads[i][1];
    }

    cout<<possibleHotspots(n,h,x,hotspots,roads);

    return 0;
}
