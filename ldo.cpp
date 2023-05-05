#include<bits/stdc++.h>
#include <algorithm>
#include<chrono>

using namespace std;
#define pb push_back
void fun(int x,vector<int> &vertex_degree,vector<int> &colors,vector<int> &colored,vector<vector<int>>& adj){

    for(int i=0;i<x;i++)
    {
        for(int j=0;j<x;j++)
        {
            if(adj[i][j]==1)
                vertex_degree[i]++;
        }
    }
    

    set<pair<int , int> > temp;
    vector<int>order(x);
    
    for (int i = 0 ; i < x ; i++)order[i] = i;
    // cout << vertex_degree.size() << endl;
    sort(order.begin() , order.end() , [&](int a , int b) -> bool{
        return vertex_degree[b] < vertex_degree[a];
    });

    colored[order[0]] = 1;

    for (int i = 1 ; i < x ; i++){
    
        vector<int>colorsTaken(x+2);
        
        for (int j = 0 ; j < x ; j++){
            if (adj[order[i]][j]){
                colorsTaken[colored[j]] = 1;
            }
        }
        int k = 1;
        while (colorsTaken[k] == 1)k++;
        colored[order[i]] = k;
    }
}

int main(){


    auto begin = std::chrono::high_resolution_clock::now();

    fstream mainfile;
    vector<string> files;
    map<int,string> subjects;
    mainfile.open("mwf.txt",ios::in);
    int nodecnt = 0;
    if(!mainfile)
    {
        cout<<"File doesn't exist.\n";
        return 0;
    }
    else{
        string xx;
        while(getline(mainfile,xx))
        {
            string tp =xx;
            tp = xx.substr(0,xx.length()-4);
            subjects[nodecnt] = tp;
            files.push_back(xx);

            nodecnt++;
        }
    }
    int x = nodecnt;
    mainfile.close();
    int n = files.size();

    vector<vector<int>> adj (x , vector<int>(x,0));
    vector<int> colored(x+2),colors(x+2),vertex_degree(x+2);

    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            fstream f1;
            f1.open(files[i],ios::in);
            f1.is_open();

            set<string> st;
            string xx;

            while(getline(f1,xx))
            {
                st.insert(xx);
            }
            f1.close();
            fstream f2;
            f2.open(files[j],ios::in);
            f2.is_open();
            string y;
            while(getline(f2,y))
            {
                if(st.find(y)!=st.end())
                {
                    //cout<<"FOUND\n";
                    adj[i][j]=1;
                    adj[j][i]=1;
                    break;
                }
                
            }
            f2.close();
        }
    }
    for(int i=0;i<x;i++){
        vertex_degree[i]=0;
    }
    
    fun(x,vertex_degree,colors,colored,adj);


    map<int,vector<int>> m;

    for(int i=0;i<x;i++){
        m[colored[i]].pb(i);
    }
    cout<<"MWF\n";
    for(auto i:m){
        cout<<"Color "<<i.first<<"--> ";
        for(int j=0;j<m[i.first].size();j++)
            cout<<subjects[m[i.first][j]]<<" ";

        cout<<"\n";
    }





    cout<<"\n";

    fstream mainfile2;
    vector<string> files2;
    map<int,string> subjects2;
    mainfile2.open("tt.txt",ios::in);
    int nodecnt2 = 0;
    if(!mainfile2)
    {
        cout<<"File doesn't exist.\n";
        return 0;
    }
    else{
        string xx;
        while(getline(mainfile2,xx))
        {
            string tp =xx;
            tp = xx.substr(0,xx.length()-4);
            subjects2[nodecnt2] = tp;
            files2.push_back(xx);
            nodecnt2++;
        }
    }
    int x2 = nodecnt2;
    mainfile2.close();
    int n2 = files2.size();

    vector<vector<int>> adj2 (x2 , vector<int>(x2,0));
    vector<int> colored2(x2+2),colors2(x2+2),vertex_degree2(x2+2);

    for(int i=0;i<n2;i++)
    {
        for(int j=i+1;j<n2;j++)
        {
            fstream f1;
            f1.open(files[i],ios::in);
            f1.is_open();

            set<string> st;
            string xx;

            while(getline(f1,xx))
            {
                st.insert(xx);
            }
            f1.close();
            fstream f2;
            f2.open(files[j],ios::in);
            f2.is_open();
            string y;
            while(getline(f2,y))
            {
                if(st.find(y)!=st.end())
                {
                    //cout<<"FOUND\n";
                    adj2[i][j]=1;
                    adj2[j][i]=1;
                    break;
                }
                
            }
            f2.close();
        }
    }
    for(int i=0;i<x2;i++){
        vertex_degree2[i]=0;
    }
    
    fun(x2,vertex_degree2,colors2,colored2,adj2);


    map<int,vector<int>> m2;

    for(int i=0;i<x2;i++){
        m2[colored[i]].pb(i);
    }

    cout<<"TT\n";
    for(auto i:m2){
        cout<<"Color "<<i.first<<"--> ";
        for(int j=0;j<m2[i.first].size();j++)
            cout<<subjects2[m2[i.first][j]]<<" ";

        cout<<"\n";
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    
    //printf("Result: %.20f\n", sum);
    
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    return 0;
    
}
