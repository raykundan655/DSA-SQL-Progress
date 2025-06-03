//  Enumartion

// enum (short for enumeration) is a user-defined type in C++
//  used to assign names to integral constants to make code more readable and maintainable.

#include<iostream>
using namespace std;
enum color{RED,GREEN,BLUE};
int main(){
    color c=BLUE;
    cout<<c; 
}



// Inline function

#include<iostream>
#include<cstring>
using namespace std;
class student{
    public:
    float cgpa;
    string name;
  
inline void getter(string name,float cgpa){
   this->name=name;
   this->cgpa=cgpa;
    }

};
int main(){
 student s1;
 s1.getter("mahi",8.9);
//  inline function replace the function call with defination at compile time but not necessary it will do surely
 cout<<s1.name;

}



// non inline function
// we can define memeber function outside of the class

#include<iostream>
#include<cstring>
using namespace std;
class cal{
   
    int a,b;
    public:
    void set(){
        cin>>a>>b;
    }
    void add();
};
void cal::add(){
    cout<<a+b;
}
int main(){
cal c1;
c1.set();
c1.add();

}



// if the function conatain loop,not return statement,stataic var then request of inline function will 
// be cancel 



// Static var & Stataic function

// cannot directly initialize a static data member inside the class definition


#include<iostream>
using namespace std;
class rox{
    public:
    static int reserve;
 
    float height;
    string name;

};
int rox::reserve=50000;
// we have initialize like this
int main(){
    rox x;
    cout<<x.reserve;
}


// Static function

// static function only can access the static data memeber
// and it is function of class so it will always call by using class name ,eg:class_name::function()

#include<iostream>
using namespace std;
class enroll{
    static int enrollNo;
    public:
    enroll(){
        enroll::enter();
        // static method always call by class name
    }

    static void enter(){
        enrollNo++;
    }
    void show(){
        cout<<enrollNo;
    }

};
int enroll::enrollNo=0;
int main(){
    enroll e1;
    e1.show();
}



// Friend function

// it is not a function of class but it's friend of the class so it can be access the all private public memeber
// how to declare
// friend  returnType function(object) 
// we need object to access the property

#include<iostream>
using namespace std;
class test{
    int a,b;
    public:
    void set(){
        cin>>a>>b;
    }
    friend void add(test &t);
    // we can use pass by value but for avoid copy so best practice is pass by refrence
};
void add(test &t){
    t.set();
  cout<<  t.a+t.b;
}
int main(){
test t1;
add(t1);
}



// friend class 
// class a{
//     friend class b;
// }
// b is friend of a so b can access private and public memeber of a but a can't access the memeber of b it's only one way friendship


#include<iostream>
using namespace std;
class a{
   
    int val;
    void move(){
        cout<<"move";
    }
    friend class b;
};
class b{
    public:
    void display(a & obj){
        obj.move();
    }
};

int main(){
a obj;
b obj1;
obj1.display(obj);
}
// friend class can access public and private memeber of friend class




// initializer_lists


#include<iostream>
using namespace std;
class dt{
    int val1,val2;
    public:
    dt(int a,int b):val1(a),val2(b){

    }
    void get(){
        cout<<val1<<val2;
    }

};
int main(){
dt d1(5,6);
d1.get();


}


// operator overloading 
// define +,*,/,% will work for  user define datatype

// Unary
// prefix
#include<iostream>
using namespace std;
class add{
    public:
    int num;
    
    void set(){
        cin>>num;
    }
   void operator ++(){
    num=++num;
   }
};

int main(){
add ad;
ad.set();
++ad;
cout<<ad.num;

}




#include<iostream>
using namespace std;
class add{
    public:
    int num;
    
    void set(){
        cin>>num;
    }
   int operator ++(){
    num=++num;
    return num;
   }
};

int main(){
add ad;
ad.set();
int n=++ad;
cout<<n;

}



// postfix
// for diff from prefix and postfix in postfix compiler pass int garbage value so for that we have to create int var


#include<iostream>
using namespace std;
class add{
    public:
int num;
add(){
    cin>>num;
}
void operator ++(int var){
    num=num+1;
}
void display(){
    cout<<num;
}
};
int main(){
    add ad;
    ad++;
    ad.display();

}


// Binary operator overloading


#include<iostream>
using namespace std;
class add{
    public:
int num;
add(){
    cin>>num;
}
void operator +(add & obj){
    num+=obj.num;
}
void display(){
    cout<<num;
}
};
int main(){
    add ad;
    add ad2;
    ad+ad2;
    // ad.operator(ad2) compiler will be treat like this 
    ad.display();

}




