#include<bits/stdc++.h>
using  namespace std;
#define nl cout<<endl;
#define ll long long
#define MAX 3000

ll gcd(ll num1,ll num2)
{
    while(num1!=num2)
    {
        if(num1>num2)
        {
            num1=num1-num2;
        }

        else
        {
            num2=num2-num1;
        }
        
    }
   return num1;
}

int multiply(int n, int result[], int resultsize) 
{ 
	int c = 0;
	for (int i=0; i<resultsize; i++) 
	{ 
		int mult = result[i] * n + c; 
		result[i] = mult % 10; 
		c = mult/10;	 
	} 

	while (c) 
	{ 
		result[resultsize] = c%10; 
		c /= 10; 
		resultsize++; 
	}

	return resultsize;

} 


void exponent(int x, int n)  
{ 
  if (n == 0)
   {  
    cout<<"1"; nl
    return; 
   }

   if (x == 0)
   {  
    cout<<"0"; nl
    return; 
   }

    int resp[MAX]; 
    int resizepower = 0; 
    int temp = x; 
  
    while (temp != 0) 
    { 
    resp[resizepower++] = temp % 10; 
    temp = temp / 10; 
    } 
 
    for (int i = 2; i <= n; i++) 
       resizepower = multiply(x, resp, resizepower); 
  

    for (int i = resizepower - 1; i >= 0; i--) 
       cout << resp[i]; 
       nl
} 

void factorial(int fact) 
{   
    /*if (fact== 0 || fact ==1)
   {
    cout<<"1"; nl
    return; 
   }*/

	int result[MAX]; 
	result[0] = 1; 
	int resultsize = 1; 

	for (int i=2; i<=fact; i++)
    {//   cout <<"hello "<<i;
       resultsize = multiply(i, result, resultsize);
    }
		 

	//"Factorial of given number is "; 
	for (int i=resultsize-1; i>=0; i--) 
		cout << result[i]; 

        nl
} 

int main()
{   
    int ch,q;
    ll fact;
    ll base, exp;
    ll num1,num2;
     
    //cout<< "enter 1 for exponential 2 for gcd and 3 for factorial "; nl
    cin>>q;
    while(q--)
    {
        cin>> ch;

    switch(ch)
    {
    case 1:
       
        cin>> base>> exp;
        exponent(base, exp);
        break;
          
    case 2:
        cin >> num1 >> num2;
        cout<<gcd(num1,num2)<<endl;
        break;
       
    
    case 3:
        
        cin >> fact; 
        factorial(fact);
        break;
    
    default:cout<<"invalid option"<<endl;
    break;

    }
    }
   return 0; 
}
