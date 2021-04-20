#include<bits/stdc++.h>
using namespace std;
#define ll long long
class trie
{
   public:
   trie* left;
   trie* right;
   bool is_end;
};

void insert(ll n, trie* root)
{   
    trie* current = root;
    for(ll i=40; i>=0;i--)
    {
        ll b = (n>>i)&1;
        if(b)
        {
           if(!current->right)
            {
                current->right = new trie();
            }
            current=current->right;
        }
        else
        {
            if(!current->left)
            {
                current->left = new trie();
            }
            current=current->left;
        }
    }
    current->is_end=true;
}

ll findmaxor(ll n, trie* root)
{
    // ll maxx=0;
    trie* current = root;
    ll curmaxx = 0;
    for(ll i=40; i>=0; i--)
    {
       ll b = (n>>i)&1;
       if(b)
        {
            if(current->left)
            { 
                curmaxx += pow(2,i);
                current = current->left;
            }
            else
            {
               current=current->right;   
            }
        }
        else
        {
            if(current->right)
            {   
                curmaxx += pow(2,i);
                current = current->right;
            }
            else
            {
                current=current->left;
            }
        }
    }
   return curmaxx;
}

int main()
{

    trie* head = new trie();
    /* ll arr[6] = {8,1,2,15,10,5};
    for(ll i=0; i<6; i++)
    {
        insert(arr[i],head);
    }
    cout<<findmaxor(5,head)<<endl; */

    ll n,q; // n = number of array elements and q = number of queries
    cin>>n;
    cin>>q;
    while(n--)
    {   
        ll x;
        cin>>x;
        insert(x,head);
    }
    // cin>>q;
    while(q--)
    {
        ll f;
        cin>>f;
        cout<<findmaxor(f,head)<<endl;
    }
    return 0;
}
