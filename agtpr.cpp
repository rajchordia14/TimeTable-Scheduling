#include<bits/stdc++.h>
#include<algorithm>
#include<chrono>
using namespace std;
#define pb push_back
int counter = 0;
bool p = false;
vector<int> colors;

void fun(vector<int>& vertex_color,vector<bool>& vertex_colored,vector<int>& vertex_degree,vector<vector<int>>& adj,int x)
{
    counter++;
    int biggest = 0; // node with highest degree
    int tp = 0; //temp highest degree

    if(counter == 1)
    {
        for(int i=0;i<x;i++)
        {
            for(int j=0;j<x;j++)
            {
                if(adj[i][j]==1)
                    vertex_degree[i]++;
            }
        }
    }

    for(int w=0;w<x;w++)
    {
        if(!vertex_colored[w])
        {

            if(tp<vertex_degree[w])
            {
                tp = vertex_degree[w];
                biggest = w;
            }
        }
    }

    vertex_color[biggest] = colors[counter];
    
    for(int e=0;e<x;e++)
    {
        if(!adj[biggest][e] && biggest!=e && !vertex_colored[e])  // checking the node that are not neighbor that are not colored yet
        {
            for(int t=0;t<x;t++)
            {
                if(adj[e][t] && vertex_color[t]==vertex_color[biggest])
                    p=true ; // conditon arises when 2 nodes are not connected to main/biggest node but connnected apas mai.
                if(t==x-1 && !p)
                {
                    vertex_color[e] = colors[counter];
                  //  cout<<vertex_id[e]<<" "<<vertex_color[e]<<"\n";
                    vertex_colored[e]=true;
                    p = false;
                }
                else if(t==x-1)
                    p = false;



            }
        }
        vertex_colored[biggest] = true;
    }
    int c = 0;
    for(int v=0;v<x;v++)
    {
        if(vertex_colored[v]==true)
            c++;
    }

    if(c==x)
        return;
    else
    {
        fun(vertex_color,vertex_colored,vertex_degree,adj,x);

    }

}

int main()
{
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
        string x;
        while(getline(mainfile,x))
        {
            string tp =x;
            tp = x.substr(0,x.length()-4);
            cout<<tp<<"\n";
            subjects[nodecnt] = tp;
            files.push_back(x);
            nodecnt++;
        }
    }
    mainfile.close();
    int n = files.size();
    vector<vector<int>> adj1(nodecnt,vector<int>(nodecnt,0));
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            fstream f1;
            f1.open(files[i],ios::in);
            f1.is_open();

            set<string> st;
            string x;

            while(getline(f1,x))
            {
                st.insert(x);
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
                    adj1[i][j]=1;
                    adj1[j][i]=1;
                    break;
                }
                
            }
            f2.close();
        }
    }
    
    vector<int> vertex_degree(nodecnt);
    vector<int> vertex_color(nodecnt);
    vector<bool> vertex_colored(nodecnt);
    int x = nodecnt;
    
    for(int i=0;i<=200;i++)
    {
        colors.push_back(i);
    }

    for(int i=0;i<x;i++)
    {
        vertex_color[i]=99;
        vertex_colored[i]=false;
        vertex_degree[i]=0;
    }
    map<int,vector<int>> m1,m2;

    fun(vertex_color,vertex_colored,vertex_degree,adj1,x);
    
    for(int i=0;i<x;i++)
    {
        m1[vertex_color[i]].pb(i);
    }

    // end of mwf

    // start of tt

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

        string x;

        while(getline(mainfile2,x))
        {
            string tp=x;
            tp = x.substr(0,x.length()-4);
            subjects2[nodecnt2] = tp;
            files2.push_back(x);

            nodecnt2++;
        }
    }
    mainfile2.close();
    n = files2.size();

    vector<vector<int>> adj2(nodecnt2,vector<int>(nodecnt2,0));

    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            fstream f1;
            f1.open(files2[i],ios::in);
            f1.is_open();

            set<string> st;
            string x;

            while(getline(f1,x))
            {
                st.insert(x);
            }

            f1.close();
            fstream f2;
            f2.open(files2[j],ios::in);
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
    vertex_color.clear();
    vertex_colored.clear();
    vertex_degree.clear();

    counter=0;
    p=false;

    vertex_color.resize(nodecnt2);
    vertex_colored.resize(nodecnt2);
    vertex_degree.resize(nodecnt2);

    x = nodecnt2;
    
    for(int i=0;i<=200;i++)
    {
        colors.push_back(i);
    }

    for(int i=0;i<x;i++)
    {
        vertex_color[i]=99;
        vertex_colored[i]=false;
        vertex_degree[i]=0;
    }

    fun(vertex_color,vertex_colored,vertex_degree,adj2,x);

    for(int i=0;i<x;i++)
    {
        m2[vertex_color[i]].pb(i);
    }
    
    
    //end of tts
    cout<<"MWF\n";
    for(auto i:m1)
    {
        cout<<"Time Slot "<<i.first<<" : ";
        for(int j=0;j<m1[i.first].size();j++)
            cout<<subjects[m1[i.first][j]]<<" ";
        cout<<"\n";
    }

    cout<<endl<<"TT\n";
    for(auto i:m2)
    {
        cout<<"Time Slot "<<i.first<<" : ";
        for(int j=0;j<m2[i.first].size();j++)
            cout<<subjects2[m2[i.first][j]]<<" ";
        cout<<"\n";

    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    
  //  printf("Result: %.20f\n", sum);
    
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    return 0;
}
