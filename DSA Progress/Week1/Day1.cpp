// Today Task List














#include<iostream>
using namespace std;
// // namespace std is folder that contain all the build in class and function 
// // when we are writing using  namespace std  it's mean we are inside the namespace std and we don't tell std:: again again we can directly pick any thing
// // without mentioning you're taking from std lib

int main(){
int a;
cin>>a;
cout<<a<<endl;
cout<<"a value"<<a;

}


// execution always start from main function



#include<iostream>
using namespace std;
#include<math.h>
#include<iomanip>
#define M_PI  3.14159265358979323846
// /*input output manipulation is use to manipulate the input and output data like set the precision etc*/
int main(){
cout<<M_PI;
cout<<fixed<<setprecision(2)<<M_PI;
// I have set the precision as 2
int a=123;
cout<<setw(10)<<a<<endl;
cout<<setw(10)<<setfill('*')<<a;
}




// constant keyword
// const is keyword use to fixed the value 
// once we declared we can't modify that 
#include<iostream>
using namespace std ;
int main(){
    const int a=20;
    // a=15;
    // this will give error because this is fixed value 
    cout<<a;
}


// typecasting
// implicite typecasting

// compiler convert it automatically 
// smaller datatype converted into bigger data type or equal size datatype automatically

#include<iostream>
using namespace std;
int main(){
    int a=5;
    float b=a;
    cout<<b;
    // implicite conversion
}


// explicite typecasting
// we convert forcefully 
// bigger datatpe into smaller one 
// syntex: (datatype)var 

#include<iostream>
using namespace std;
int main(){
    float a=5;
    int b=(int)a;
    cout<<b<<endl;
    char ch='A';
    cout<<(int)ch;
    
}



// Boolean value

// non zero number treated as True
// Zero treated as False


#include<iostream>
using namespace std;
int main(){
    cout<<(bool)(-5);
}




// operator

// arithmetic operator
// Binary
// +,-,*,/,%
// unary

// Postfix increment
// first assign then increment
// prefix increment
// first increase then assign


#include<iostream>
using namespace std;
int main(){
    int a=10;
    int b=a++;
    cout<<b<<" "<<a<<endl;
    // first assign then increment

    int c=++a;
    cout<<c<<" "<<a;
    // first increase then assign

}


// assignment
// 1. =
// a=5;
// 2. +=
// a+=6
// a=a+6
// a*=7
// a=a*7
// =/

// Relational
// ==
// >=
// <=
// !=
// >
// <
// return type bool 
// it used to find the relation b/w var


// Logical
// &&  -> and  if both condion are true then true
// ||  -> or if one of the condition are true then true
// !   ->convert the type
// return type bool



// Note
// precedence of operator
// bracket
//2 arithmetic
//3 relation
//4 logical
//5 condtion
//6 assignment



// condition statement

// income tex calculator
// constraint
// if income<5L
// 0% tex
// else if  5-10L
// 20% tax
// else
// 30% tax


#include<iostream>
#include<math.h>
using namespace std;
int main(){
    int income;
    cout<<"enter your income yearly income :";
    cin>>income;
    if(income<500000){
        int amount=income;
        cout<<"the have to pay zero percent tex"<<" amount"<<amount;
    }
    else if((income>500000) && (income<=1000000)){
        cout<<"they have to pay 20 percent tax<<endl";
        int tax=0.20*income;
        int amount=income-tax;
        cout<<"the final amount after paying tax is "<<amount;

    }
    else{
        cout<<"they have to pay 30 percent tax<<endl";
        int tax=0.30*income;
        int amount=income-tax;
        cout<<"the final amount after paying tax is "<<amount;
    }
}



// Ternary operator
// Syntex 
// (condition)?True value:false value

#include<iostream>
using namespace std;
int main(){
    (500>600)? cout<<"No": (500>300)? cout<<"Yes":cout<<"No";
    // it is singal line if and else
    // we can also produce some value and store into var 
    // so we can use it letter 
    int age=14;
    bool val=(age>18)? true:false;
    cout<<endl<<val;

}





// LOOP


