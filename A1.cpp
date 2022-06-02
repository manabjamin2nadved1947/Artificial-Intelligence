#include<bits/stdc++.h>

using namespace std;
float ttime;
//vector< vector<int> > vii;
int v;
vector<char> vs;
int k;
vector<string>ks;
int CC;
vector<vector<int>> MC;
string str1, str2;
int total_MC=0;
int total_CC=0;

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

int min(int a, int b, int c){
    int temp;
    if(a<b)
        temp= a;
    else
        temp = b;
    if(temp<c){
        //total_CC +=CC; 
        return temp;
    }
    else {
        
        return c;
    }
}

int get_idx(char x){
    auto it = find(vs.begin(), vs.end(), x);
    if (it != vs.end()){
      
        int index = it - vs.begin();
        return index;
    }
    return -1;
}

int diff(int i, int j){
    if(str2.at(i-1)!=str1.at(j-1))
        return MC[get_idx(str2.at(i-1))][get_idx(str1.at(j-1))];
    else return 0;
}

void edit_distance(){
    int r,c;
    int t=0,t1=0;
    int dash_count=0;
    for(int i =0;i<k-1;i++){
        str1 = ks[i];
        for(int j=i+1;j<k;j++){
            str2 = ks[j];
            
            r = str2.size()+1; c = str1.size()+1;
            
            int *E[r];
            for (int i = 0; i < r; i++)
                E[i] = (int*)malloc(c * sizeof(int));  
            
                //init
            for (int i=0; i<r; i++)
                E[i][0]=i*MC[v][0]; //MC(x,-)
            for (int j=0; j<c; j++)
                E[0][j]=j*MC[v][0]; //   MC(x,-)
                
                //dp
                for(int i =1;i<r;i++){
                    for(int j=1;j<c;j++){
                        //get the i-1 and j-1
                        char x = str2.at(i-1);
                        char y = str1.at(j-1);
                        int idx= get_idx(x);
                        int idy= get_idx(y);
                        //E[i][j]=min(E[i-1][j]+MC[idx][idy],E[i][j-1]+MC[idx][idy],E[i-1][j-1]+diff(i,j));
                        E[i][j]= min(E[i-1][j]+MC[v][0],E[i][j-1]+MC[v][0],diff(i,j)+E[i-1][j-1]);
                       // cout<<"total_CC--- "<<total_CC<<endl;
        }
        }
        t = E[r-1][c-1];
        //cout<<"tempu--"<<t<<endl;
        t1 += t;


        //reconstructing the string
        int k = r-1, l = c-1;
        
        while(k>0 && l>0){
            if(str2.at(k-1) == str1.at(l-1)){
                k--;l--;
                //cout<<"same found\n";

            }
            //when strings alphabets are not same
            else{ 
                //cout<<"not same found\n";
                //check minimum for left , up or diagonal
                int minn = min(E[k-1][l],E[k][l-1],E[k-1][l-1]);
                if(E[k-1][l] == minn){
                    dash_count++;
                    //cout<<"dash  here--"<<dash_count<<endl;
                    //how the i and j changes
                    k--;
                    continue;
                } 
                if(E[k][l-1]==minn){
                    dash_count++;
                    //how i and j changes
                    l--;
                    //cout<<"dash  there--"<<dash_count<<endl;
                    continue;
                }
                if(E[k-1][l-1]==minn){
                    dash_count++;
                    dash_count++;
                    k--;l--;
                    //cout<<"dash  where--"<<dash_count<<endl;
                    continue;
                }
            }
        }//end of while
    }
   
   //cout<<"cumsum--"<<t1<<endl;
    }
    total_MC = t1;
    total_CC = dash_count*CC;
    //cout<<dash_count<<endl;
}



int main(){
    cout<<"Please use space as separator for variables not comma\n";
    cin>>ttime;
    cin>>v;
    for(int i=0;i<v;i++){
        char ch;
        cin>>ch;
        vs.push_back(ch);
    }
    cin>>k;
    
    for(int i=0; i<k;i++){
        string str;
        cin>>str;
        ks.push_back(str);
    }
    cin>>CC;
    MC.resize((v+1), vector<int>(v+1));
    
    for(int i=0;i<(v+1);i++){
        for(int j=0;j<(v+1);j++){
            cin>>MC[i][j];
        }
    }
    

    

    edit_distance();
    cout<<"ONLY MC is found CC is under process\n";
    cout<<endl<<"optimal total MC="<<total_MC<<endl;
    //cout<<" "<<total_CC<<endl;
}
/*

Please use space as separator for variables not comma
4
4
A C T G
3
ACTGTGA
TACTGC
ACTGA
3
0 2 2 2 1
2 0 2 2 1
2 2 0 2 1
2 2 2 0 1
1 1 1 1 0
8
ONLY MC is found CC is under process

optimal total MC=10
*/