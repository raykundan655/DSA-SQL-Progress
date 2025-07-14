// / virtual function
// the function we have to overriden  ino the base class 
// for declare write virtual keyword with function

// #include <iostream>
// using namespace std;

// class Grandfather {
// public:
//     virtual void show() {
//         cout << "Grandfather" << endl;
//     }
// };

// class parent : public Grandfather {
// public:
//     void show() override {
//         cout << "Parent" << endl;
//     }
// };


// int main() {
//     parent * ptr = new parent();
//     ptr->show();  // Output: Parent
// }


// abstruct class
// An abstract class is a class that cannot be instantiated — it only serves as a base class for other classes
//  It contains at least one pure virtual function.
// pure virtual function is function that declare prototype and define in the derive class
// virtual void function()=0;


// To achieve Abstraction in C++ 

// #include <iostream>
// using namespace std;

// class Animal {
// public:
//     virtual void sound() = 0;  // Pure virtual function
// };

// class Dog : public Animal {
// public:
//     void sound() override {
//         cout << "Dog barks" << endl;
//     }
// };

// int main() {
    
//     Dog d;                
//     d.sound();           

//     Animal* ptr = new Dog();
//     ptr->sound();         // Output: Dog barks
//     delete ptr;
// }



// imp NOTE
// base class pointer pointing to derive class so when it call it will call property of parent class 
// vut if the property is overridden then derive class propety will be call beacuse of runtime poly
// for call derive class propety we have to type cast the pointer into derive class

// Even though:
// human* ptr = new dog();
// you’re assigning a derived object (dog) to a base pointer (human*), 
// C++ will not use runtime polymorphism unless the base class function is virtual.

// Because C++ uses the vtable (virtual table) mechanism. If a function is marked virtual,
//  C++ generates a vtable pointer to dynamically bind the function at runtime.



// In C++, the virtual keyword is used to support runtime polymorphism, which means:
// The function to be executed is decided at runtime,
//  not at compile-time — based on the actual object type, not the pointer type.


// After declaring a function as virtual in C++:
// ✅ The function call depends on the object type,
// ❌ Not on the pointer type.





// practice question from leetcode

// Maximum Subarray (Easy, #53)

// brute force
// class Solution {
// public:
//     int maxSubArray(vector<int>& nums) {
//         int sum=INT_MIN;
//         for(int i=0;i<nums.size();i++){
//             for(int j=i;j<nums.size();j++){
//                 int val=0;
//                 for(int k=i;k<=j;k++){
//                     val+=nums[k];
//                 }
//                 sum=max(sum,val);

//             }
//         }
//         return sum;
//     }
// };


// optimised
// Optimized Solution — Kadane’s Algorithm (O(n) Time)
// Idea:
// Keep a running sum.
// If the current sum becomes negative, reset it to zero or current value(because starting a new subarray may yield a better result).
// Track the maximum sum seen so far.

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
       int maxsum=nums[0];
       int current=nums[0];
       for(int i=1;i<nums.size();i++){
        if(current<0){
            current=nums[i];
        }
        else{
            current+=nums[i];
            // If you reset current to zero, you are effectively saying, “My new subarray sum starts at zero, ignoring the current element.” 
        }
        if(current>maxsum){
            maxsum=current;
        }
       

       }
       return maxsum;
    }

// The sum of the subarray you were tracking so far is dragging down the total.
// Keeping that negative sum and adding future elements to it will only make things worse (or at least not better) for finding a maximum sum subarray.
// So, there’s no point in continuing with that negative sum because any subarray starting after that negative sum will be better if you start fresh.
};


// Remove Duplicates from Sorted Array (Easy, #26)
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
   int j=0;
   for(int i=1;i<nums.size();i++){
    if(nums[i]!=nums[j]){
        j++;
        nums[j]=nums[i];
    }
   }
   return j+1;

    
       
}
};


// Move Zeroes (Easy, #283)

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n=nums.size();
        for(int i=0;i<n-1;i++){
            if(nums[i]==0){
                for(int j=i;j<n-1;j++){
                    int temp=nums[j];
                    nums[j]=nums[j+1];
                    nums[j+1]=temp;
                }
                i--;
                n--;
            }
        }
        for(int i=0;i<nums.size();i++){
            cout<<nums[i]<<" ";
        }

    }
};

