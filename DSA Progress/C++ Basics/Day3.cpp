// removing duplicate
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
    vector<int>vec;
    int val;
    while(true){
        cin>>val;
        if(val==-1){
            break;
        }
        vec.push_back(val);
    }
    sort(vec.begin(),vec.end());
    for(int i=0;i<vec.size();){
        if(vec[i]==vec[i+1]){
            vec.erase(vec.begin()+i);
        }
        else{
            i++;
        }
    }
    for(int va:vec){
        cout<<va<<" ";
    }
}



// #explore library cmath

// Function	Return Type     	        Description	                           Example
// abs(int x)	int	                    Absolute value (int)	                 abs(-10) → 10
// fabs(double x)	double	         Absolute value (float/double)	          fabs(-4.2) → 4.2
// sqrt(double x)	double	               Square root                  	    sqrt(16) → 4.0
// cbrt(double x)	double	                Cube root	                         cbrt(27) → 3.0
// pow(double base, double exp)double	      Power 
// ceil(double x)	double	                Round up	                         ceil(3.2) → 4.0
// floor(double x)	double	                Round down	                         floor(3.9) → 3.0
// round(double x)	double	              Round to nearest int	                   round(3.5) → 4.0



#include<iostream>
#include<cmath>
using namespace std;
int main(){
int x=-5;
float y=3.5;
cout<<abs(x)<<endl;
int z=abs(x);
cout<<fabs(y)<<endl;
cout<<pow(z,2)<<endl;
cout<<sqrt(4)<<endl;
cout<<ceil(y)<<endl;
cout<<floor(y);

}



// explore algorithm(sorting,serching,itration,finding)use for stl (array,vector,list etc)
// Function	           Return Type	                Description	                           Example
// sort(start, end)	     void	            Sorts in ascending order	             sort(v.begin(), v.end())
// reverse(start, end)	 void	              Reverses the range	                 reverse(v.begin(), v.end())
// find(start, end, value)	iterator	    Finds first occurrence of value	              find(v.begin(), v.end(), 5)
// binary_search(start, end, value)	bool	Checks if value exists (sorted data only)	binary_search(v.begin(), v.end(), 10)
// min(a, b)	same type as a/b	            Returns the smaller	                           min(3, 5) → 3
// max(a, b)	same type as a/b	             Returns the larger	                           max(3, 5) → 5
// count(start, end, value)	int	           Counts how many times value appears	        count(v.begin(), v.end(), 5)


#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int main(){
char arr[50]="mahi";
sort(arr,arr+strlen(arr)-1);
cout<<arr<<endl;
reverse(arr,arr+strlen(arr)-1);
cout<<arr<<endl;
int arrr[5];
for(int i=0;i<5;i++){
cin>>arrr[i];
}
int *ptr=find(arrr,arrr+4,5);
cout<<*ptr;

}





// include<cctype>
// Function	Purpose	                                                    Example (char)
// isalnum(c)	Checks if c is alphanumeric (a-z, A-Z, 0-9)	               isalnum('A') → true
// isalpha(c)	Checks if c is alphabetic	                                isalpha('g') → true
// isdigit(c)	Checks if c is a digit	                                    isdigit('5') → true
// islower(c)	Checks if c is lowercase	                                islower('m') → true
// isupper(c)	Checks if c is uppercase	                               isupper('X') → true
// isspace(c)	Checks for space, tab, newline, etc.	                   isspace(' ') → true
// ispunct(c)	Checks for punctuation (., !, etc.)	                         ispunct('.') → true
// isxdigit(c)	Checks if hex digit (0-9, A-F, a-f)	                       isxdigit('B') → true
// tolower(c)	Converts uppercase to lowercase	                           tolower('G') → 'g'
// toupper(c)	Converts lowercase to uppercase	                            toupper('n') → 'N'



#include<iostream>
#include<cstring>
#include<cctype>
using namespace std;
int main(){
string str;
getline(cin,str);
int count=0;
for(char val:str){
    char ch=tolower(val);
    if(ch=='a' || ch=='i' || ch=='e' || ch=='o' || ch=='u'){
        count++;
    }
}
cout<<count;
}




// 2D vector

// A 2D vector  is essentially a vector of vectors. It allows you to create a matrix-like structure using STL

#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<vector<int>>vec(3,vector<int>(4,-1));
    for(int i=0;i<vec.size();i++){
        for(int j=0;j<vec[i].size();j++){
            cin>>vec[i][j];
        }
    }

     for(int i=0;i<vec.size();i++){
        for(int j=0;j<vec[i].size();j++){
            cout<<vec[i][j]<<" ";
        }
        cout<<endl;
    }
}





// OOPS
// (object orianted programming)


#include<iostream>
#include<cstring>
using namespace std;
class Student{
    float cgpa;
    public:
    string name;
    void getcgpa(){
       cout<<"Bhai pehela cgpa daal to de";
    }
};

int main(){
Student s1;
s1.name="mahi";
cout<<s1.name;
s1.getcgpa();
}



// some propert are too much private and we don't want to give direct access of it so for that we will make getter and setter
// getter will help the get the private data and setter will hwlp you to set the data 


#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
class student{
    string name;
    float cgpa;
    public:
    void findpercent(){
        cout<<cgpa*10<<"%"<<endl;
    }
    void setter(string arr,float cg){
        name=arr;
        cgpa=cg;
    }
    float cgpaGetter(){
        return cgpa;
    }
    string namegetter(){
        return name;
    }
};
int main(){
    student s1;
    s1.setter("mahi",8.9);
    s1.findpercent();
  cout<<s1.cgpaGetter()<<" ";
   cout<<s1.namegetter();

}









// // // Note 
// // // Stack me: "Object ka naam hai, directly kaam kar sakte ho"
// // // Heap me: "Naam nahi, sirf address hai — pointer se kaam hota hai"




// constructor
// basically used for initilisation 
// type:
// default constructor
// parameterised constructor
// copy constructor;

#include<iostream>
#include<cstring>
using namespace std;
class car{
    string name;
    string model;
    public:
    car(string name,string model){
        this->name=name;
        this->model=model;
    }
    car(car & obj){
        name=obj.name;
        model=obj.model;
    }
    void detail(){
        cout<<name<<endl<<model;
    }
};
int main(){
    car c1("tata","m4");
    // c1.detail();
    car c2(c1);
    c2.detail();
}


// Note!!
// If both parent and child classes have parameterized constructors, then:
// You must explicitly tell the child class constructor to pass values
// to the parent class constructor using an initializer list.


class Parent {
public:
    Parent(int x) {
        
    }
};

class Child : public Parent {
public:
    Child(int a, int b) : Parent(a) {
       
    }
};




// inheritance

// singal inheritance

// only one parent and onr child
// class parent{

// };
// class child:public parent{

// };

// multilevel inheritance

// class grandfather{

// };
// class parent:public grandfather{

// };
// class son:public parent{

// };

// multiple inheritance

// class father{

// };
// class mother{

// };
// class son:public father,public mother{

// };

// hierarchial 
// one base class  multiple derive class 






