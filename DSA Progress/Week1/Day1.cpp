// Today Task List
// basic input/output 
// datatype
// keywords(const,hex,oct)
// typecasting
// operators
// loops
// function
// pointer
// array(1D)



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

// For loop
// syntex:
// for(intilization;condition;updation){}


// pattern printing

// *
// **
// ***
// ****
// *****
// ******

#include<iostream>
using namespace std;
int main(){
    int size;
    cin>>size;
    for(int i=0;i<=size;i++){
        for(int j=0;j<=i;j++){
            cout<<"*";
        }
        cout<<endl;
    }
}



// * * * * *
// * * * *
// * * *
// * *
// *

#include<iostream>
using namespace std;
int main(){
    int size;
    cin>>size;
    for(int i=size;i>=0;i--){
        for(int j=0;j<i;j++){
            cout<<"*"<<" ";
        }
        cout<<endl;
    }
}


// 1
// 1 2
// 1 2 3
// 1 2 3 4


#include<iostream>
using namespace std;
int main(){
    int size;
    cin>>size;
    for(int i=1;i<=size;i++){
        for(int j=1;j<=i;j++){
            cout<<j<<" ";
        }
        cout<<endl;
    }
}


//     *
//    * *
//   * * *
//  * * * *
// * * * * *


#include<iostream>
using namespace std;
int main(){
    int size;
    cin>>size;
    for(int i=0;i<size;i++){
        for(int j=0;j<=size-i-1;j++){
            cout<<" ";
        }
        for(int k=0;k<=i;k++){
            cout<<"*"<<" ";
        }
        cout<<endl;
    }

}



//     *
//    * *
//   * * *
//    * *
//     *


#include<iostream>
using namespace std;

int main() {
    int size;
    cin >> size;

    // Upper half
    for (int i = 0; i < size; i++) {
        if (i <= size / 2) {
            // print spaces
            for (int j = 0; j < size / 2 - i; j++) {
                cout << " ";
            }
            // print stars
            for (int k = 0; k < 2 * i + 1; k++) {
                cout << "*";
            }
        } else {
            // bottom half
            for (int j = 0; j < i - size / 2; j++) {
                cout << " ";
            }
            for (int k = 0; k < 2 * (size - i) - 1; k++) {
                cout << "*";
            }
        }
        cout << endl;
    }

    return 0;
}



// while loop
// Best is use when we don't know number of itration 
// it is best for condition itration

// syntex:
// while(condition){

// }

// do while loop
// syntex:
// do{

// }while(condtion);




// Break/continue
// Break key word use to break ingoing itration 
// When the loop hits break, it stops immediately and jumps outside the loop.

// continue 
// To skip the current iteration and continue with the next one.





// Functions

// Note 

// FORWARD DECLARATION
// function  most of time  decalre above the main function because from main method function are called 
// this is forward declaration(use karna se pehela bana liya )

//  but  if you define the function after main(), you must declare it forward, using a function prototype.
// prototype
// return type function_name();


// forward decl.
#include<iostream>
#include<string>
using namespace std;

void hello(string str){
    cout<<"hello brother "<<str;
}
int main(){
hello("mahi");
}


// prototype 
#include<iostream>
#include<string>
using namespace std;

void hello(string str);

int main(){
hello("mahi");
}

void hello(string str){
    cout<<"hello brother "<<str;
}






// we can pass parameters to functions in three main ways


// Pass by Value
// A copy of the argument is passed.
// Changes inside the function do not affect the original value.



// Pass by Reference
// A reference (alias) to the original variable is passed.
// Changes inside the function do affect the original value.


// Pass by Reference
// A reference (alias) to the original variable is passed.
// Changes inside the function do affect the original value.


#include<iostream>
using namespace std;

void byValue(int a) {
    a += 10;
}

void byReference(int &a) {
    a += 10;
}

void byPointer(int *a) {
    *a += 10;
}

int main() {
    int x = 5;

    byValue(x);
    cout << "By Value: " << x << endl;  // 5

    byReference(x);
    cout << "By Reference: " << x << endl;  // 15

    byPointer(&x);
    cout << "By Pointer: " << x << endl;  // 25

    return 0;
}



// #imp Note
// In declaration: & creates a reference (alias) to a variable, so changes affect the original.(int &ref = var;)
// When used before a variable, & gives the memory address of that variable..(int *p = &var;)


// convertion of number into binary number
#include<iostream>
#include<vector>
using namespace std;
int main(){
    int num;
    cin>>num;
vector<int>vec;
    while(num>0){
int rem=num%2;
vec.push_back(rem);
     num=num/2;
    }
    for(int i=vec.size()-1;i>=0;i--){
        cout<<vec[i];
    }
}


// convert binary to decimal

#include<iostream>
#include<math.h>
#include<vector>
using namespace std;
int main(){
    int num;
    cin>>num;
int i=0;
int dec=0;
while(num>0){
    int rem=num%10;
    dec+=rem*pow(2,i);
    i++;
    num=num/10;
}
cout<<dec;
}


// // direct function
#include<iostream>
#include<math.h>
using namespace std;
int main(){
    int num=10;
    cout<<hex<<num;
    cout<<oct<<num;

}





// dataType modifier

// long (int/double)
// it is used to increse the size of data type
// int only take the value from -32000 to +32000 but long will increase the limit


// short int(only for int)
// it decrese the memeory of int into 2 byte only 

// long long int(only for int)
// it will able to take more big size number

// unsigned
// only take non-negative number



// POINTER
// address operator &
// it give the address of varibel
// pointer is special variable that store the address of variable 

// syntex
// int * ptr=&var 


// ptr is pointer that store the address of var 
// data type of pointer indicate that which type of var address is store in this pomiter

// pointer size is fixed 8byte


// pointer of pointer

// int ** a=&ptr;
// a is pointer of pointer 



// dereference operator(*)
// it give the value of the var that is pointed by pointer

// eg int a=5
// int *ptr=&a
// cout<<*ptr   ->5
// give the val of the var whose address is store into ptr



// type of pointer
// wild pointer
// int * ptr;
// A pointer that has not been initialized. Dangerous because it points to a random location.


// NULL pointer
// A pointer that doesn’t point to any memory location.
//  int * ptr=NULL;


// Void Pointer (void*)
// A general-purpose pointer that can point to any data type, but needs to be typecast before use.

// void* ptr;
// int a = 10;
// ptr = &a;  // valid





// Array

// syntex int arr[no of element]

// for finding the size of array
// size=sizeof(array)/sizeof(array[0])

// int arr[5];
// it resereve 5*4=20byte 
// first index arr[0]=4byte 
// 20/4=5 no of element

// name of array act as reference it give the address of base element(first element)

#include<iostream>
using namespace std;
int main(){
    int arr[5]={5,5,8,7,6};
    cout<<*arr;
    for(int i=0;i<5;i++){
        cout<<*(arr+i);
    }
//     // this plus in address not increse the address by i it increase it by by (address+(i*datatypeSize))


// }

// when we pass the array into function it pass through pass by reference

// function(int arr[])
// function(int * arr)
// both are same 

// Note!!
// remeber that when you pass the array you have to pass the size of array also because in function it only pinter toward base address they don't have full array

// When you pass an array to a function in C++, what actually gets passed is a pointer to the first element (i.e., the base address), not the entire array itself.
// So the function does not know the size of the array unless you pass it separately.



// reverse the array

#include<iostream>
using namespace  std;

void reverse(int arr[],int size){
    for(int i=0;i<size/2;i++){
     int  temp=arr[i];
     arr[i]=arr[size-1-i];
     arr[size-1-i]=temp;
}

}
int main(){
    int arr[5]={5,6,7,8,9};
    reverse(arr,5);
    for(int i=0;i<5;i++){
        cout<<arr[i];
    }
}




// Binary Search

#include<iostream>
using namespace std;
int main(){
    int arr[5]={2,3,5,8,9};
    int key=9;
int st=0;
int end=5-1;
while(st<=end){
    int mid=(st+end)/2;
    if(arr[mid]==key){
        cout<<"found"<<endl;
       return 0;
    }
    else if(key>arr[mid]){
        st=mid+1;

    }
    else if(key<arr[mid]){
        end=mid-1;
    }

}
cout<<"element not present "<<endl;
return 0;

}

