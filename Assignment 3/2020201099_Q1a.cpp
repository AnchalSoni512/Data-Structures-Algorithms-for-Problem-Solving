#include<bits/stdc++.h>
#define ll long long
using namespace std;

//comparator function
bool comp(pair<int,pair<int,int>> a, pair<int,pair<int,int>> b)
{
    if(a.second.first == b.second.first){
        if(a.second.second < b.second.second)   
        return true;
        else return false;
    }
    else{
        if(a.second.first < b.second.first) 
        return true;
        else return false;
    }
}

vector<ll> buildSuffix(string str){
    vector<pair<int,pair<int,int>>> suffix(str.size());
    vector<ll> index(str.size());
    for(ll i=0;i<str.size();i++){
        // ll rank0=str[i]-'0';
        ll rank0=str[i];
        // cout<<"rank0 : "<<rank0<<endl;
        ll rank1;
        if((i+1)<str.size())   
        // rank1=str[i+1]-'0';
        rank1=str[i+1];
        else rank1=-1;
        suffix[i]={i,{rank0,rank1}};
    }

    //sort the array according to comparator defined previously
    sort(suffix.begin(), suffix.end(), comp);

    //doing the same thing for next 2 chars than next 4 chars and so on
    for(ll p=4;p<2*str.size();p*=2){
        //assigning index and rank tothe first suffix
        ll rank=0;
        ll previous_rank=suffix[0].second.first;
        suffix[0].second.first=rank;
        index[suffix[0].first]=0;

        for(ll i=1;i<str.size();i++){

            if(suffix[i].second.first==previous_rank && suffix[i].second.second==suffix[i-1].second.second){
                previous_rank=suffix[i].second.first;
                suffix[i].second.first=rank;
            }
            else{
                rank++;
                previous_rank=suffix[i].second.first;
                suffix[i].second.first=rank;
            }
            index[suffix[i].first]=i;
        }

        for(ll i=0;i<str.size();i++){
            
            ll next=suffix[i].first + p/2;
            ll new_rank;
            if(next<str.size()){
                new_rank=suffix[index[next]].second.first;
            }
            else{
                new_rank=-1;
            }
            suffix[i].second.second=new_rank;
        }
        sort(suffix.begin(), suffix.end(), comp);
    }
    /* for(ll i=0;i<str.size();i++){
        // cout<<suffix[i].first<<endl;
        cout<<suffix[i].first<<" ";
        cout<<suffix[i].second.first<<" ";
        cout<<suffix[i].second.second<<endl;
    } */ 
    vector<ll> suffix_vector(str.size());
    for(ll i=0;i<str.size();i++){
        // cout<<suffix[i].first<<endl;
        suffix_vector[i]=suffix[i].first;
    }
    
    return suffix_vector;
}

int main(){
    ios_base::sync_with_stdio(false);
    string str;
    // cout<<"Enter String "<<endl;
    cin>>str;
    string str2=str+str;
    vector<ll> ans=buildSuffix(str2);

    ll start=0;
    
    for(ll i=0;i<str2.size();i++){
        
        if(ans[i]<str.size()){
            start=ans[i];
            break;
        }
    }
    cout<<str2.substr(start,str.size())<<endl;

    return 0;
}
