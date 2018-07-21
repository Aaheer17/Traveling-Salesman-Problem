#include <bits/stdc++.h>

using namespace std;
typedef pair<int,double> pp;
typedef pair<pair<int, int>, double> pPair;

list<pp >* createGraph(double cord[][2],int cities){

    list<pp>* adj=new list<pp>[cities];
    double x1,x2,y1,y2;

    for(int i=0;i<cities;i++){
        x1=cord[i][0];
        y1=cord[i][1];

        for(int j=0;j<cities;j++){
            if(i!=j){
                x2=cord[j][0];
                y2=cord[j][1];

                double weight=(x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);

                weight=sqrt(weight);
                adj[i].push_back(make_pair(j,weight));
            }
        }


    }
    return adj;


}



vector<int> nearestnbr(double** graph, int cities){
    int u=rand()%cities;
    int initial=u;
    bool visited[cities];
    vector<int> path;
    double cost=0;
    path.push_back(u);
    visited[u]=true;
    int cnt=cities-1;
    double min;
    int v=u;

    while(cnt!=0){
        u=v;
        visited[u]=true;
        min=99999;

        for(int i=0;i<cities;i++){

            if(visited[i]==false && min>graph[u][i]){
                min=graph[u][i];
                v=i;
            }
        }
        cost+=graph[u][v];

        path.push_back(v);
        cnt--;

    }
    path.push_back(initial);
    cost+=graph[v][initial];
    cout<<"Path of Nearest Neighbor: \n";
    for(int i=0;i<path.size()-1;i++){
        cout<<path[i]<<"--";
    }
    cout<<path[path.size()-1];
    cout<<endl;

    cout<<"Cost of Nearest Neighbor: "<<cost<<endl;

    return  path;
}


vector<int> dfs(list<pp>* path,int cities, list<pp>* adj){
    int root=rand()%cities;
    vector<int> p;
    bool visit[cities];

    stack <int> stk;
    stk.push(root);

    while(!stk.empty()){
        int r=stk.top();
        stk.pop();

        if(!visit[r]){
            // cout<<r<<" ";
            visit[r]=true;
            p.push_back(r);

        }
        for (auto i = path[r].begin(); i != path[r].end(); ++i) {
            if (!visit[(*i).first])
                stk.push((*i).first);
        }
    }

    p.push_back(root);
    double cost=0;
    cout<<"Path of MST Heuristic: \n";

    for(int i=0;i<p.size();i++){

        if(i==p.size()-1){
            cout<<p[i]<<endl;
            for(auto a=adj[p[i]].begin(); a!=adj[p[i]].end();a++){
                if((*a).first==p[0]){
                    cost+=(*a).second;

                    break;
                }
            }
            break;

        }
        cout<<p[i]<<"--";
        for(auto a=adj[p[i]].begin(); a!=adj[p[i]].end();a++){
            if((*a).first==p[i+1]){

                cost+=(*a).second;
                break;
            }
        }

    }


    cout<<"MST Heuristic Cost: ";

    cout<<cost<<endl;

    return p;
}


class myComparator
{
public:
    int operator() (const pp& b1, const pp& b2)
    {
        return b1.second > b2.second;
    }
};




vector<int> three_opt_exchange(vector<int> vector, int i, int k, int i1, int j);

list<pp>* MST(list<pp >* adj, int cities){

    if(cities>0){
        //list<pp>* path=new list<pp>[cities];

        list<pp>* path=new list<pair<int, double> >[cities];
        int src=0;
        vector<double> cost(cities,99999);
        vector<int> parent(cities,-1);
        vector<bool> visited(cities,false);
        priority_queue< pp, vector<pp> ,myComparator > pQueue;

        pQueue.push(make_pair(src,0));
        cost[src]=0;
       // parent[src]=0;

        while(!pQueue.empty()){

            int vertex=pQueue.top().first;
            pQueue.pop();

            visited[vertex]=true;

            list< pp >::iterator itr;
            for (itr = adj[vertex].begin(); itr != adj[vertex].end(); itr++)
            {

                int v = (*itr).first;
                double weight = (*itr).second;


                if (visited[v] == false && cost[v] > weight)
                {

                    cost[v] = weight;
                    pQueue.push(make_pair( v,cost[v]));
                    parent[v] = vertex;
                }
            }




        }


        for(int i=0;i<cities;i++){
          //  cout<<"parent: "<<parent[i]<<" cost "<<cost[i]<<endl;
            int u=parent[i];
           if(u!=-1) {
               path[u].push_back(make_pair(i, cost[i]));
               path[i].push_back(make_pair(u, cost[i]));
           }
        }

        return  path;

    }
}


vector<int> two_opt_swap(vector<int> route,int i,int k){

    vector<int> new_route;
    int tmp=k;
    for(int m=0;m<i;m++){
        new_route.push_back(route[m]);
    }

    for(int m=k;m>=i;m--){
        new_route.push_back(route[m]);
    }

    for(int m=k+1;m<route.size();m++){
        new_route.push_back(route[m]);
    }

    return new_route;


}


double get_path_cost(vector<int> path,double** graph )
{

    double cost=0;
    for(int i=0;i<path.size()-1;i++){
        cost+=graph[path[i]][path[i+1]];

    }
    return cost;


}



void two_opt(double** graph, vector<int> route){
    double best_cost=get_path_cost(route,graph);
    vector<int> tmproute=route;
    int isImproved=0;
    vector<int> new_route;

    while(true){

        isImproved=0;
        route=tmproute;
        for(int i=1;i<route.size()-2;i++){

            for(int k=i+1;k<route.size()-1;k++){

                new_route=two_opt_swap(route,i,k);
               /* for(int i=0;i<new_route.size();i++){
                    cout<<new_route[i]<<" ";
                }*/

                double newCost=get_path_cost(new_route,graph);

               // cout<<"\nnew_cost"<<newCost<<endl;


                if(newCost<best_cost){
                    best_cost=newCost;
                    tmproute=new_route;
                    isImproved=1;

                }

            }
        }

        if(isImproved==0) break;

    }

    cout<<"Path of 2-opt"<<endl;
    for(int i=0;i<route.size()-1;i++){
        cout<<route[i]<<"--";
    }
    cout<<route[0]<<endl;
    cout<<"Cost of 2-opt: "<<best_cost<<endl;


}

vector<int> three_opt_swap(vector<int> path,int first,int second, int third,int fourth){
    vector<int> tmp;

    for(int i=0;i<first;i++){
        tmp.push_back(path[i]);
    }
    for(int i=second;i>=first;i--){
        tmp.push_back(path[i]);
    }
    for(int i=fourth;i>=third;i--){
        tmp.push_back(path[i]);
    }
    for(int i=fourth+1;i<path.size();i++){
        tmp.push_back(path[i]);
    }

    return  path;
}

vector<int> tour_3_opt(double** graph,int cities, vector<int> tour){

    ///x-y-z-p(initial path)   x=0-i, y=i+1-j, z=j+1-k, p=k+1-len
    double bestCost=get_path_cost(tour,graph);
    int len=tour.size();
    vector<int> newpath,tmp;
    double newCost;

    for(int i=0;i<len-3;i++){
        for(int j=i+1;j<len-2;j++){
            for(int k=j+1;k<len-1;k++){



                //case-1:  x-y-z'-p
                newpath=two_opt_swap(tour,j+1,k);
                newCost=get_path_cost(newpath,graph);
                if(newCost<bestCost){

                    return tour_3_opt(graph,cities,newpath);
                }

                //case-2:  x-y'-z-p
                newpath=two_opt_swap(tour,i+1,j);
                newCost=get_path_cost(newpath,graph);
                if(newCost<bestCost){

                    return tour_3_opt(graph,cities,newpath);
                }


                //case-3:  x-y'-z'-p
                newpath=three_opt_swap(tour,i+1,j,j+1,k);
                newCost=get_path_cost(newpath,graph);
                if(newCost<bestCost){

                    return  tour_3_opt(graph,cities,newpath);
                }

                //case-4: x-z-y-p
                newpath=three_opt_exchange(tour,j+1,k,i+1,j);
                newCost=get_path_cost(newpath,graph);
                if(newCost<bestCost){

                    return  tour_3_opt(graph,cities,newpath);
                }

                //case-5: x-z'-y-p

                for(int m=0;m<=i;m++){
                    newpath.push_back(tour[m]);
                }
                for(int m=k;m>=j+1;m--){
                    newpath.push_back(tour[m]);
                }
                for(int m=i+1;m<=j;m++){
                    newpath.push_back(tour[m]);
                }

                for(int m=k+1;m<tour.size();m++){
                    newpath.push_back(tour[m]);
                }

                newCost=get_path_cost(newpath,graph);
                if(newCost<bestCost){

                    return  tour_3_opt(graph,cities,newpath);
                }

                //case-6: x-z-y'-p
                for(int m=0;m<=i;m++){
                    newpath.push_back(tour[m]);
                }
                for(int m=j+1;m<=k;m++){
                    newpath.push_back(tour[m]);
                }
                for(int m=j;m>=i+1;m--){
                    newpath.push_back(tour[m]);
                }
                for(int m=k+1;m<tour.size();m++){
                    newpath.push_back(tour[m]);
                }
                newCost=get_path_cost(newpath,graph);
                if(newCost<bestCost){

                    return  tour_3_opt(graph,cities,newpath);
                }

                //case-7: x-z'-y'-p

                for(int m=0;m<=i;m++){
                    newpath.push_back(tour[m]);
                }
                for(int m=k;m>=j+1;m--){
                    newpath.push_back(tour[m]);
                }
                for(int m=j;m>=i+1;m--)
                {
                    newpath.push_back(tour[m]);
                }
                for(int m=k+1;m<tour.size();m++){
                    newpath.push_back(tour[m]);
                }


                newCost=get_path_cost(newpath,graph);
                if(newCost<bestCost){
                    //cout<<"case 7: new_cost: "<<newCost<<" bestCost: "<<bestCost<<endl;
                    return  tour_3_opt(graph,cities,newpath);
                }




            }
        }
    }

    return tour;

}

vector<int> three_opt_exchange(vector<int> path, int j1, int k, int i1, int j) {
    vector<int>tmp;

    for(int i=0;i<i1;i++){
        tmp.push_back(path[i]);

    }
    for(int i=j1;i<=k;i++){
        tmp.push_back(path[i]);

    }
    for(int i=i1;i<=j;i++){
        tmp.push_back(path[i]);

    }
    for(int i=k+1;i<path.size();i++){
        tmp.push_back(path[i]);
    }

    return tmp;


}


int find_k(double** graph, vector<int> path,int cities,bool visited[]){
    int k;
    double min=9999;
    for(int i=0;i<path.size();i++){

        for(int j=0;j<cities;j++){
            if(visited[j]==false && min>graph[path[i]][j]){
                k=j;
                min=graph[path[i]][j];
            }
        }
    }

    return k;

}

vector<int> pathInsertion(vector<int> path,int i , int j, int k){
    vector<int> p;
    for(int m=0;m<=i;m++){
        p.push_back(path[m]);
    }
    p.push_back(k);
    p.push_back(path[j]);
    for(int m=j+1;m<path.size();m++){
        p.push_back(path[m]);
    }

    return  p;

}

double costInsertion(double** graph, vector<int> p,int i, int j, int r){
    double cost=graph[p[i]][r]+graph[p[j]][r]-graph[p[i]][p[j]];

    return cost;


}


vector<int> nearestInsertion(double** graph,int cities){
    int r=rand()% cities;
    int cnt=cities;

    //int help;

    vector<int> path;
    double min=99999;
    int m,n;
    path.push_back(r);
    for(int i=0;i<cities;i++){

        if(min>graph[r][i]){
            min=graph[r][i];
            m=i;
        }

    }
    path.push_back(m);
    path.push_back(r);
    cnt=cnt-2;

   // cout<<r<<" "<<m;

    bool visited[cities];
    visited[r]=true;
    visited[m]=true;
    vector<int> tmpPath=path;

   // cout<<"count : "<<cnt;

    while(cnt>0){
        min=99999;
        path=tmpPath;

        n=find_k(graph,path,cities,visited);
        //cout<<"n: "<<n;
        visited[n]=true;
        cnt--;
       // cout<<"count: "<<cnt<<endl;
        //if(cnt==0) help=path[path.size()-1];
        for(int i=0;i<path.size()-1;i++){
            vector<int> new_Path=pathInsertion(path,i,i+1,n);
            double cost=costInsertion(graph,path,i,i+1,n);
            if(min>cost){
                tmpPath=new_Path;
                min=cost;
            }
        }

    }

    path=tmpPath;
    double cst=0;

   // path.push_back()
    cout<<endl<<"Path of Nearest Insertion: "<<endl;
    for(int i=0;i<path.size()-1;i++){
       cst+=graph[path[i]][path[i+1]];
        cout<<path[i]<<"--";
    }
    cout<<path[path.size()-1]<<endl<<endl;
  //  cst+=graph[path.size()-1][path[0]];
    //cout<<path[0]<<endl;

    cout<<"Cost of path :"<<endl;
    cout<<cst;
    //path.push_back(path[0]);

    return path;


}





void cheapInsertion(double** graph, int cities){

    int r=rand()% cities;
    int cnt=cities;

    vector<int> path;
    double min=99999;
    int m,n;
    path.push_back(r);
    for(int i=0;i<cities;i++){

        if(min>graph[r][i]){
            min=graph[r][i];
            m=i;
        }

    }
    path.push_back(m);
    path.push_back(r);
    cnt=cnt-2;

    bool visited[cities];
    visited[r]=true;
    visited[m]=true;
    int k;
    vector<int> tmpPath=path;

    while(cnt>0){
        min = 99999;
        path=tmpPath;

        for(int i=0;i<cities;i++){

            if(visited[i]==false){

                for(int j=0;j<path.size()-1;j++){
                    vector<int> new_Path=pathInsertion(path,j,j+1,i);
                    double cost=costInsertion(graph,path,j,j+1,i);

                    if(min>cost){
                        tmpPath=new_Path;
                        min=cost;
                        k=i;

                    }
                }
            }
        }


        cnt--;
        visited[k]=true;
    }

    path=tmpPath;


    cout<<endl<<"Path of cheapst Insertion: "<<endl;
    for(int i=0;i<path.size()-1;i++){
        //cst+=graph[path[i]][path[i+1]];
        cout<<path[i]<<"--";
    }
    cout<<path[path.size()-1]<<endl<<endl;

    double cst=get_path_cost(path,graph);
    cout<<"Cost of cheapest insertion: "<<cst<<endl<<endl;

    two_opt(graph,path);
    vector<int> tmp=tour_3_opt(graph,cities,path);

    cout<<endl<<"3-opt on cheapst Insertion: "<<endl;
    for(int i=0;i<tmp.size()-1;i++){
        //cst+=graph[path[i]][path[i+1]];
        cout<<tmp[i]<<"--";
    }
    cout<<path[path.size()-1]<<endl<<endl;

     cst=get_path_cost(tmp,graph);
    cout<<"Cost of 3-opt on cheapest insertion: "<<cst<<endl<<endl;





    //return path;


}




int main() {
    int cities;
    cout<<"Enter the number of cities\n";
    cin>>cities;

    double cord[cities][2];
   // double graph[cities][cities];
    double** graph;
    graph=new double*[cities];

    for(int i=0;i<cities;i++){
        graph[i]=new double[cities];
    }

    cout<<"Enter the co-ordinates of cities:\n";
    for(int i=0;i<cities;i++){
        cout<<"For city "<<i<<" : "<<endl;
        cin>>cord[i][0]>>cord[i][1];
    }

    list< pp > *adj;

    adj=createGraph(cord,cities);

    //printing tha graph.

    cout<<" GRAPH: \n";
    for(int i=0;i<cities;i++){
        list<pair<int, double > >::iterator itr;
        graph[i][i]=99999;
        for(itr=adj[i].begin();itr != adj[i].end(); itr++){
            int v=(*itr).first;
            double weight=(*itr).second;

            graph[i][v]=weight;
            //cout<<graph[i][v]<<"  ";

           // cout<<i<<"--"<<v<< "  weight: "<<weight<<endl;
        }


    }


    for(int i=0;i<cities;i++){
        for(int j=0;j<cities;j++){
            cout<<graph[i][j]<<"  ";
        }
        cout<<endl;
    }

    cout<<endl<<endl;

     vector <int> nbr=nearestnbr(graph,cities);
     cout<<"\n\n2-opt on Nearest Neighbor: \n";
     two_opt(graph,nbr);

    cout<<"\n\n3-opt on Nearest Neighbor: \n";

    vector<int> threopt3=tour_3_opt(graph,cities,nbr);

    for(int i=0;i<threopt3.size()-1;i++){
        cout<<threopt3[i]<<"--";
    }
    cout<<threopt3[threopt3.size()-1]<<endl;

    cout<<"Cost: "<<get_path_cost(threopt3,graph)<<endl<<endl<<endl;


    list<pp>* mstPath=MST(adj,cities);
    vector<int> mst=dfs(mstPath,cities,adj);

    cout<<"\n\n2-opt on MST: "<<endl;

    two_opt(graph,mst);


    cout<<"\n\n3-opt on MST: "<<endl;

    vector<int> threopt2=tour_3_opt(graph,cities,mst);

    for(int i=0;i<threopt2.size()-1;i++){
        cout<<threopt2[i]<<"--";
    }
    cout<<threopt2[threopt2.size()-1]<<endl;

    cout<<"Cost: "<<get_path_cost(threopt2,graph)<<endl;





    vector<int> ni=nearestInsertion(graph,cities);

    cout<<"\n\n2-opt on Nearest Insertion: "<<endl;

    two_opt(graph,ni);

    cout<<"\n\n3-opt on Nearest insertion: "<<endl;

    vector<int> threopt1=tour_3_opt(graph,cities,ni);

    for(int i=0;i<threopt1.size()-1;i++){
        cout<<threopt1[i]<<"--";
    }
    cout<<threopt1[threopt1.size()-1]<<endl;

    cout<<"Cost: "<<get_path_cost(threopt1,graph)<<endl;


    cheapInsertion(graph,cities);

}