#include<bits/stdc++.h>

using namespace std;

struct htnode{
    unsigned freq;
    char* nc;
    struct htnode* left;
    struct htnode* right;
    
};

struct comparefreq{
    bool operator()(htnode*& n1,htnode*& n2){
        return n1->freq>=n2->freq;
    }
};

vector<char> unichar(string s){
    int n = s.size();
    vector<char> c;
    vector<int> b(96,0);
    for(int i=0;i<n;i++){
        b[s[i]-' ']=1;
    }
    for(int i=0;i<96;i++){    
        if(b[i]==1){
            char j = ' '+i;
            c.push_back(j);
        }
    }
    return c;
}

vector<int> getfreq(vector<char> &c, string s){
    int n = c.size();
    int m = s.size();
    vector<int> freq(n,0);
    vector<int> f(96,0);
    for(int i=0;i<m;i++){
        f[s[i]-' ']++;
    }
    for(int i=0,j=0;i<96;i++){
        char k = ' '+i;
        if(k==c[j]){
            freq[j]=f[i];
            j++;
        }
    }
    return freq;
}

htnode* huffmancoding(vector<char> c,vector<int> freq){
    int n = c.size();
    priority_queue<htnode*,vector<htnode*>,comparefreq> que;
    for(int i=0;i<n;i++){
        char* cc;
        cc = (char*)malloc(sizeof(char));
        cc[0] = c[i];
        htnode* temp = new htnode;
        temp->freq = freq[i];
        temp->nc = cc;
        temp->left = NULL;
        temp->right = NULL;
        que.push(temp);
    }
    htnode* root;
    while(!que.empty()){
        htnode* n1 = que.top();
        que.pop();
        if(!que.empty()){
            htnode* n2 = que.top();
            que.pop();
            char* cc = NULL;
            htnode* n3 =  new htnode;
            n3->freq = n1->freq + n2->freq;
            n3->nc = cc;
            // cout<<n1->freq<<" "<<n2->freq<<endl;
            // cout<<n3->freq<<endl;
            n3->left = n1;
            n3->right = n2;
            que.push(n3);
        }
        else{
            root = n1;
            // cout<<"rara"<<root->freq<<endl;
            break;
        }
    }
    return root;
}

void tra(htnode* root,string s,vector<string>& key){
    // cout<<s<<" "<<root->freq<<endl;
    if(root->nc!=NULL){
        cout<<root->nc[0]<<": "<<root->freq<<": "<<s<<endl;
        key[root->nc[0]-' ']=s;
    }
    int n = s.size();
    s+="1";
    if(root->left!=NULL)tra(root->left,s,key);
    s[n]='0';
    if(root->right!=NULL)tra(root->right,s,key);
}

string printencodedtext(vector<string> key,string s){
    string ans;
    int n = s.size();
    for(int i=0;i<n;i++){
        cout<<key[s[i]-' '];
        ans+=key[s[i]-' '];
    }
    cout<<endl;
    return ans;
}

void cnfrm(htnode* node, string s){
    htnode* root = node;
    int n = s.size();
    for(int i=0;i<=n;i++){
        
        if(s[i]=='1')node=node->left;
        else node=node->right;

        if(node->nc!=NULL){
            cout<<node->nc[0];
            node=root;
        }
    }
}

int main(){
    string s;
    getline (cin, s);
    vector<char> c = unichar(s);
    vector<int> freq = getfreq(c,s);

    int n = c.size();
    
    htnode* root = huffmancoding(c,freq);
    // cout<<root->freq<<endl;
    vector<string> key(96);
    string g="";
    tra(root,g,key);
 
    string ans = printencodedtext(key,s);

    cnfrm(root,ans);    
    return 0;
}