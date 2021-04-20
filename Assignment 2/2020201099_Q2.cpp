// Anchal Soni roll no.-2020201099
//hashing- Q2 (implement generic unordered map)
//insert(key, value)- 
// erase(key) - delete node if present else do nothing
// find (key) - return true or false
// umap[key] - returns value mapped to key

#include <bits/stdc++.h>
using namespace std;
#define si 100
#define ll long long

template <class T, class U>
class umap
{
    public:
    class node
    {   public:
        T key;
        U value;
        node *next;
    };
node* arr[si];
ll p = 31;
    umap() //constructor initialises the object of the class
    {
        //cout<<"hereeee\n";
        ll i =0;
        while(i < si)
        {
            arr[i]=NULL;
            i++;
        }

    }
    node* createNewNode(T keyelement, U val) 
    {
        node *a = new node; 
        a->key = keyelement; 
        a->value = val;
        a->next = NULL;
        return a; 
    }
    
    ll mapping(T keyelement)
    {
        ostringstream strobj;
        strobj << keyelement;
        string s = strobj.str();
        // cout<<"inside mapping:printing string s :"<<s<<endl;
        ll output = 0;
        ll multiply = 1;
        ll i=0;
        while(i<s.size())
        {
            output = output+(s[i]*multiply);
            output = output%si;
            multiply=multiply*p;
            i++;
        }
        return output;

    }
    void insert(T keyelement, U val)
    {
        // cout<<"here";
       ll indexval = mapping(keyelement);
       node *head = arr[indexval];
       if(head==NULL)
       {
           node* n= createNewNode(keyelement, val);
           arr[indexval] = n;

           return;
       }
       else if(head->next==NULL && head->key == keyelement)
       {
           return;
       }
       else if(head->next==NULL && head->key != keyelement)
       {
            node* n= createNewNode(keyelement, val);
            head->next=n;
            return;
       }
       else
       {
           node* temp=head;
           while(temp->next != NULL)
           {
               if(temp->key == keyelement)
               return;
               else
               {
                   temp = temp->next;
               }
               
           }
           if(temp->key==keyelement)
           return;

           node* n = createNewNode(keyelement, val);
           temp->next=n;
           return;
       }
       return;
    }
    pair<bool,U> find(T keyelement)
    {
        ll indexval= mapping(keyelement);
        node *head = arr[indexval];
        pair<bool, U>res;
        if(head==NULL)
        {
            res.first=false;
            return res;
        }
        else
        {
            node* temp=head;
            while(temp!=NULL)
            {
                if(temp->key==keyelement)
                {
                    res={true, temp->value};
                    return res;
                }
                else
                {
                    temp=temp->next;
                }
            }
            res.first=false;
            return res;
        }
        
    }
    void erase(T keyelement)
    {
        ll indexval=mapping(keyelement);
        node* head = arr[indexval];
        node* temp=head;
        node* leftnode=NULL;
        if(head==NULL)
        {
            cout<<"no value corresponding to this key found!"<<endl;
            return;
        }
        else
        {
            while(temp->key != keyelement && temp->next != NULL)
            {
                leftnode=temp;
                temp=temp->next;
            }
            if(head->key==keyelement)//simple ptr manipulation like we do in ll node deletion
            {
                temp=head;
                head=head->next;
                arr[indexval]=head;
                free(temp);
                return;
            }
            else if(temp->next==NULL && temp->key!=keyelement)
            {
                cout<<"no value corresponding to this key"<<endl;
                return;
            }
            else//key to be deleted found
            {
                leftnode->next=temp->next;
                free(temp);
            }
        }
        return;
    }
    //prints the whole table
    void printbuckets()
    {
        ll i=0;
        while(i<si)
        {
            cout<<endl<<i<<" : ";
            node* arb=arr[i];
            while(arb != NULL)
            {
                cout << "--->(" << arb->key << "=" << arb->value << ")";
                arb = arb->next;
            }
            cout<<endl;
            i++;
        }
    }
    U& operator[](T keyelement)
    {
        // U var=(U)0;
        // pair<bool, string> res = find(keyelement);
        // if(res.first == false)
        // {
        //     return var;
        // }
        
        ll indexval=mapping(keyelement);
        node* head = arr[indexval];
        node* temp=head;
        /*
        if(head == NULL)
        {
            cout<<"value not found!\n";
            return ;
        }
        else{
        while(temp->key != keyelement)
        {
            temp = temp->next;
        }
        if(temp == NULL)
        {
            cout<<"value not found!\n";
            return;
        }
        else
        return temp->value;
        }*/

        while(temp->key != keyelement)
        {
            temp = temp->next;
        }
        if(temp == NULL)
        {
            cout<<"value not found!\n";
            
        }
        return temp->value;
    }
};

int main()
{
    string keyinput;
    string keydata;
    umap<string, string> m;
    int choice;
    cout<<"\nEnter choice:\n\n1.insert(key,value)\n2.earse(key)\n3.find(key)\n4.umap[key]\n5.Print all LinkedList\n6.exit\n";
    while(1){
    cout<<"\nchoice: ";
    cin>>choice;
    if(choice==1)
    {
        cin>>keyinput;
        cin>>keydata;
        m.insert(keyinput,keydata);
        cout<<"\ninserted successfully!\n";
    }
    else if(choice == 2)
    {
        cin>>keyinput;
        m.erase(keyinput);
    }
    else if(choice == 3)
    {
        cin>>keyinput;
        pair<bool, string> res = m.find(keyinput);
        if (res.first == true)
            cout << res.second << endl;
        else
            cout << "False" << endl;
    }
    else if(choice == 4)
    {
        cin>>keyinput;
        cout<<m[keyinput]<<endl;

    }
    else if(choice == 5)
    {
        m.printbuckets();
    }
    else if(choice == 6)
    {
        exit(0);
    }
    else
    {
        cout<<"invalid command!"<<endl;
        break;
    }
    
    }

}

// Anchal Soni roll no.-2020201099
//hashing- Q2 (implement generic unordered map)

//insert(key, value)----done
// erase(key) ----------done
// find (key) ----------done   0 or 1
// umap[key] -----------done but need exception handling













