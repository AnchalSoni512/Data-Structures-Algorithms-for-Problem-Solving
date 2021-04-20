#include<iostream>
using namespace std;
#define N 100
#define ll long long
 
template<class dtype>
class Deque
{
   public:
      ll F=-1, R=-1;
      ll si;
      ll count;
      ll capacity;
      dtype  *dq;
   
   Deque() 
   { 
      count=0;
      capacity = N;
      dq = new dtype[N];
   }    
   
   Deque(int si, dtype d) 
   { 
      dq = new dtype[si];
      for(int i=0;i<si;i++)
      {
         dq[i]=d;
      }
      F=0;
      R=si-1;
      count=si;
      capacity = si;
   }

void display();
bool empty();
void clear();
dtype front();
dtype back();
void push_front(dtype x);
void push_back(dtype x);
void pop_front();
void pop_back();
ll size();
void resize(int , dtype);
dtype& operator[](int);

};

template<class dtype>
void Deque<dtype>::display()
{
   if(F==-1 && R==-1)
     cout<<"DQ is empty. cant display anything"<<endl;
   else
   {
      int z=F;
      while(z!=R)
      {
         cout<<dq[z]<<" ";
         z=(z+1)%capacity;
      }
      cout<<dq[R] << endl;
   }
}

template<class dtype>
bool Deque<dtype>::empty()
{
   if(F==-1 && R==-1)
     return true;
     
return false;
   
}

template<class dtype>
void Deque<dtype>::clear()
{
   F=R=-1;
   count = 0;
}

template<class dtype>
long long Deque<dtype>::size()
{ 
   return count;
}

template<class dtype>
dtype Deque<dtype>::front()
{
   if(empty())
   {  cout << "DQ is empty"<<endl;
      exit(0);
   }
   else
   {  
      return dq[F];
   }
}

template<class dtype>
dtype Deque<dtype>::back()
{
   if(empty())
   {  cout << "DQ is empty...exiting"<<endl;
     exit(0);
   }
   else
      return dq[R];
   
}

template<class dtype>
void Deque<dtype>::push_front(dtype x)
{  
      if (F==-1 && R==-1)
      {   F=R=0;
          count =1;
          dq[F]=x;
      
      }
      else if((R+1)%capacity==F)  //isfull()
      {  

      dtype* temp = new dtype[2*capacity];
      ll k=0;
      for(ll i= F; i!= R ; i=(i+1)%capacity)//loop on old array to copy elements
      {
         temp[k]= dq[i];
         k++;
      }
      temp[k]= dq[R];
      F=0;
      R=k;
      delete[] dq;
      dq=temp;
      capacity =2*capacity;
      dq[capacity-1]= x;
      F=capacity-1;
      count++;
      }

   
      else 
      {  
         if(F==0)
         { 
           F= capacity-1;
           dq[F]=x;
           count++;
         }
        else
         {  
            F=F-1;
            dq[F]=x;
            count++;
         }
      }

}

template<class dtype>
void Deque<dtype>:: push_back(dtype x)
{
   //if((F==0 && R==capacity-1) || (F==R+1))
   if((R+1)%capacity==F) //isfull()
   {
      dtype* temp = new dtype[2*capacity];
      ll k=0;
      for(ll i= F; i!=R ; i=(i+1)%capacity)//loop on old array to copy elements
      {
         temp[k]= dq[i];
         k++;
      }
      temp[k]= dq[R];
      F=0;
      R=k;
      delete[] dq;
      dq=temp;
      R++;
      dq[R]=x;
      capacity *=2;
      count++;
   }
   
   else if (F==-1 && R==-1) //when empty
   {
      F=R=0;
      dq[F]=x;
      count=1;
   }

   else 
   {
      if(R==capacity-1)
        R=0;
      else
        R++;
      
      dq[R]=x;
      count++;
   }
   
}

template<class dtype>
void Deque<dtype>:: pop_front()
{
   if(F==-1 && R==-1)
     cout<<"DQ is empty"<<endl;
   
   else 
   {  if(F==R)
       F=R=-1;

      else if(F==capacity-1)
       F=0;

      else 
       F++;

    count--;
   } 
}

template<class dtype>
void Deque<dtype>::pop_back()
{
   if(F==-1 && R==-1)
     cout<<"DQ is empty"<<endl;

   //cout<<"deleted element is: "<<deque[R]<<endl;
   else 
   {
     if(F==R)
      F=R=-1;

     else if(R==0)
      R=N-1;

     else 
      R--;

   count--;
   } 
     
}

template<class dtype>
void Deque<dtype>::resize(int newsize, dtype d)
{    dtype* temp = new dtype[newsize];
   if(empty())
   {
      // dq = new dtype[newsize];
      for(int i=0;i<newsize;i++)
      {
         temp[i]=dq;
      }

   }

   else{

   int j=0;
   for (int i = F; i!=R && j<newsize; i=(i+1)%capacity) { 
         temp[j] = dq[i]; 
         j++;
   } 
   if(count<=newsize) temp[j++] = dq[R];

   while(j<newsize)
      temp[j++] = d;
      
   }


   // else if(capacity>newsize)
   // {  cout<<"hello here\n";
   //    cout<<"capacity: "<<capacity<<endl;
   //    cout<<"newsize: "<<newsize<<endl;
   //    cout<<"front ptr: "<<F<<endl;
   //    cout<<"rear ptr: "<<R<<endl;
   //    cout<<"count: "<<count<<endl;

   //    ll k=0;
   //    for(ll i= F; i!= R && k <= newsize; i=(i+1)%capacity)
   //    {
   //       temp[k]= dq[i];
   //       k++;
   //    }
   //    temp[k]=dq[R];
   //    delete[] dq;
   //    dq=temp;

   //    if(count>newsize)
   //    count = newsize;
      
   //    cout<<"\nafter\n";
   //    cout<<"capacity: "<<capacity<<endl;
   //    cout<<"newsize: "<<newsize<<endl;
   //    cout<<"front ptr: "<<F<<endl;
   //    cout<<"rear ptr: "<<R<<endl;
   //    cout<<"count: "<<count<<endl;
   // }  

   // else//(capacity<newsize)
   // {
      
   //    ll k=0;
   //    for(ll i= F; i!= R ; i=(i+1)%capacity)
   //    {
   //       temp[k]= dq[i];
   //       k++;
   //    }
   //    temp[k]=dq[R];
   //    delete[] dq;
   //    dq=temp;
   //    for(int i=R+1;i<newsize;i++)
   //    {
   //       dq[i]=d;
   //       count++;
   //    }
      
   // }
   
      F=0;
      R=newsize-1;
      delete[] dq;
      count=newsize;
      capacity = newsize;
      dq=temp;
}

template<class dtype>
dtype& Deque<dtype>::operator[](int index)
{
   if (index >= count || index<0) { 
        cout << "Index out of bound, exiting\n"; 
        exit(0);
    }
    else{
      
    return dq[(F+index)%capacity];
    }

}


int main() 
{  
/*
Deque<string> *arr =NULL;
    int Q,c,n;
    string x;
    cin>>Q;

while (Q--)

{      
  cin>>c;

     switch (c)
     {

         case 1: cin>>x;  //push front
                 arr->push_front(x);  
                 arr->display();
                 break;
         
         case 2: arr->pop_front(); //pop front
                 arr->display();
                 break;
 
         case 3: cin>>x;           // push back
                 arr->push_back(x);  
                 arr->display();
                 break;
 
         case 4: arr->pop_back();  //pop back
                 arr->display();
                 break;
 
         case 5: if(arr !=NULL)  //initialise deq
                 delete arr;
                 arr = new Deque<string>();
                 break;

         case 6: cin>>n>>x;  //initialise deqye size n and element x
                 if(arr !=NULL)
                 delete arr;
                 arr = new Deque<string>(n,x);
                 arr->display();
                 break;

         case 7: cout<<arr->front()<<endl; // get front
                break;

         case 8: cout<<arr->back()<<endl; // get back
                break;
 
         case 9: if(arr->empty()) //empty function
                 cout<<"true\n";
                 else
                 cout<<"false\n";
                 break;

         case 10:cout<<"size: ";  // get size
                 cout<<arr->size()<<endl;
                 break;

         case 11:cin>>n>>x;  // resize
                 arr->resize(n,x);
                 arr->display();
                 break;

         case 12:arr->clear();  // clear
                 cout<<"DQ cleared\n";
                 break;
 
         case 13:cin>>n;   //find D[]
                 cout<<"fetching "<<n<<"th element\n";
                 cout<<(*arr)[n]<<endl;
                 break;

         case 14:cout<<"DQ elements: ";  // display
                 arr->display();
                 break;

         default:cout<<"invalid command! Valid command range[1-14]";
                 break;
      }

}

delete arr;
*/
Deque<int> arr;
for(int i=0; i<5;i++)
{
   arr.push_front(i);
}
arr.display();
arr.resize(3,5);
cout<<"after resize ";
arr.display();
return 0;

}