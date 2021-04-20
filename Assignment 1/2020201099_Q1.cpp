#include <iostream>
#include<iomanip>
using namespace std;
#define nl cout<<endl;
const int SIZE = 20;
 
template <class StackType> 
class stack {
  StackType stck[SIZE];
  int tos;
 
public:
  stack() {
     tos = -1;
  }
    void push(StackType ob)
    {
      if(tos==SIZE) {
        cout << "Stack is full.\n";
    
      }
      else 
      tos++;
      stck[tos] = ob;
      
    }
 
    StackType pop()
    {
      if(tos==-1) {
        cout << "Stack is empty.\n";
        return -1; // return null on empty stack
      }
      tos--;
      return stck[tos];
    }

    StackType top()
    {
        if(tos==-1) {
        cout << "Stack is empty. ";
        return -1; // return null on empty stack
        }
      return stck[tos];
    }
 
    bool empty()
    {
        if(tos==-1) {
        return true;
        }
        return false;
    }

    void display()
    {   int count=tos;
        while(count>=0)
        {
          cout<<"stack element "<<stck[count]; nl
         count--;
        }
    }

};
//-----------------------------------------------------------------------//
////----------expression evaluation by using two generic stack---------////
//-----------------------------------------------------------------------//

    stack <double> datastack; 
    stack <char> operatorstack; 

double performopr(double a, double b, char op){ 
    // cout<<"hello 6";nl
    switch(op){ 
        case '+': return a + b; 
        case '-': return a - b; 
        case '*': return a * b; 
        case '/': return a / b; 
        case '%': return int(a) % int(b);
    } 
 cout<<"something went wrong...returning ";
 return 0;
} 


void pnp() // perform and push function
{
   double val2 = datastack.top(); 
   datastack.pop(); 
                  
   double val1 = datastack.top(); 
   datastack.pop(); 
                  
   char op = operatorstack.top(); 
   operatorstack.pop(); 
                  
   datastack.push(performopr(val1, val2, op)); 
}


int precedence(char op){ 
    if(op == '+'||op == '-') 
    return 1; 
    if(op == '*'||op == '/'||op == '%') 
    return 2; 
    return 0; 
} 
   
double calculate(string exp){ 

    for(int i = 0; i < exp.length(); i++)
    {            
        if(exp[i] == '(')
            // cout<<"Hello 1"<<endl;
            operatorstack.push(exp[i]); 
          
        
        else if(isdigit(exp[i])){ 
            double val = 0; 
            //    cout<<"Hello 2"<<endl;
            string num="";
            while(i < exp.length() && (isdigit(exp[i]) || exp[i]=='.')) 
            {  
                num += exp[i];
                i++; 
                
            } 
            val = stod(num);
            num="";
            datastack.push(val);
            i--;
            
        } 
          
        else if(exp[i] == ')') 
        { 
            //  cout<<"Hello 3"<<endl;
            while(!operatorstack.empty() && operatorstack.top() != '(') 
                pnp();
              
            // pop opening brace. 
            if(!operatorstack.empty()) 
               operatorstack.pop(); 
        } 
          
        else
        { 
        //   cout<<"Hello 4"<<endl;
            while(!operatorstack.empty() && precedence(operatorstack.top()) >= precedence(exp[i]))
                pnp();
              
            // Push current character to 'operatorstack'. 
            operatorstack.push(exp[i]); 
        } 
    } 
    
    while(!operatorstack.empty())
        pnp(); //perform and push

    return datastack.top(); 
} 
  
int main() { 

    string ex;
    cin >> ex;
    cout << fixed << setprecision(9)<< calculate(ex) << "\n";
    // string exp1="75*854/7953/6490*1641-100";
    // string exp2="87*16+(87/50)*28-60-(41-73)/69+30";
    // string exp3="20/76-(65*46)+80*94*(55*68)-73*16";
    // string exp4="86/41/(73/2)/25*4042/7696+43";
    // string exp5="84-27*(26+29)*55-65-(3*2)*5/80";
    // string exp6="66-7333/5082-4999-2127/87";
    // string exp7="86/6686-4479+24*(43/1)/45+71";
    // string exp8="100+72+(87*1)**(32-66)/47-3764/5";
    // string exp9="45-50*(83*78)*82/48-(1-66)*39*63";
    // string exp10="75*854/7953/6490*1641-100";
    // cout << fixed << setprecision(5)<< calculate(exp1) << "\n";
    // cout << fixed << setprecision(5)<< calculate(exp2) << "\n";
    // cout << fixed << setprecision(5)<< calculate(exp3) << "\n";
    // cout << fixed << setprecision(5)<< calculate(exp4) << "\n";
    // cout << fixed << setprecision(5)<< calculate(exp5) << "\n";
    // cout << fixed << setprecision(5)<< calculate(exp6) << "\n";
    // cout << fixed << setprecision(5)<< calculate(exp7) << "\n";
    // cout << fixed << setprecision(5)<< calculate(exp8) << "\n";
    // cout << fixed << setprecision(5)<< calculate(exp9) << "\n";
    // cout << fixed << setprecision(5)<< calculate(exp10) << "\n";

     
    return 0; 
}
