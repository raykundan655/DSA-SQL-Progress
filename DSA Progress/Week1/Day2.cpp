// Topic cover
// Practice question based on 1D Array
// Sorting Algo.
// String
// Vector







// Practice question

// Printing SubArray
// #include<iostream>
// using namespace std;
// int main(){
//     int *arr=new int[5];
//     for(int i=0;i<5;i++){
//         cin>>arr[i];
//         // *(arr + i)

//     }
//     for(int i=0;i<5;i++){
//         for(int j=i;j<5;j++){
//             for(int k=i;k<=j;k++){
//                 // cout<<arr[k];
//                 cout<<*(arr+k);
//             }
//             cout<<" ";

//         }
//         cout<<endl;
//     }

// }



// Max subarray sum

// #include<iostream>
// #include<climits>
// using namespace std;
// int main(){
//     int * arr=new int[6];
//     for(int i=0;i<6;i++){
//         cin>>arr[i];
//     }

//     int maxi=INT_MIN;

//     for(int i=0;i<6;i++){
//         for(int j=i;j<6;j++){
//             int sum=0;
//             for(int k=i;k<=j;k++){
//                 sum+=arr[k];
//             }
//             maxi=max(sum,maxi);
//         }
//     }
//     cout<<"max sum"<<maxi;
// }



// SORTING ALGO

// bubble sort
// #include<iostream>
// using namespace std;
// int main(){
//     int arr[5];
//     for(int i=0;i<5;i++){
//         cin>>arr[i];
//     }
//   for(int i=0;i<5-1;i++){
//     for(int j=0;j<5-i-1;j++){
//         if(arr[j]>arr[j+1]){
//             swap(arr[j],arr[j+1]);
//         }
//     }
//   }
//     for(int i=0;i<5;i++){
//        cout<<arr[i]<<" ";
//     }
// }


// Selection sort

// #include<iostream>
// using namespace std;
// int main(){
//       int arr[5];
//     for(int i=0;i<5;i++){
//         cin>>arr[i];
//     }

//     for(int i=0;i<5-1;i++){
//         int ind=i;
//         for(int j=i+1;j<5;j++){
//             if(arr[ind]>arr[j]){
//                 ind=j;
//             }
//         }
//         swap(arr[ind],arr[i]);

//     }

//      for(int i=0;i<5;i++){
//        cout<<arr[i]<<" ";
//     }
// }



// INBUILD SORTING ALGO

// #include<algorithm>
//  #include<iostream>
// using namespace std;
// int main(){
//       int arr[5];
//     for(int i=0;i<5;i++){
//         cin>>arr[i];
//     }

   
//     sort(arr,arr+4);

//      for(int i=0;i<5;i++){
//        cout<<arr[i]<<" ";
//     }
// }



// 2D array

// #include<iostream>
// using namespace std;
// int main(){
//     int arr[3][2];
//     for(int i=0;i<3;i++){
//         for(int j=0;j<2;j++){
//             cin>>arr[i][j];
//         }
//     }

//      for(int i=0;i<3;i++){
//         for(int j=0;j<2;j++){
//            cout<<arr[i][j]<<" ";
//         }
//     }
// }




// #spiral matrix


// #include<iostream>
// using namespace std;
// int main(){
//     int arr[3][3];
//     for(int i=0;i<3;i++){
//         for(int j=0;j<3;j++){
//             cin>>arr[i][j];
//         }
//     }

//     // for(int i=0;i<3;i++){
//     //     for(int j=0;j<3;j++){
//     //         cout<<arr[i][j]<<" ";
//     //     }
//     //     cout<<endl;
//     // }

//     int sr=0,sc=0;
//     int er=2,ec=2;
//     while(sr<=er && sc<=ec){
// // top
// for(int i=sc;i<=ec;i++){
//     cout<<arr[sr][i]<<" ";
// }
// sr++;
// // right
// for(int i=sr;i<=er;i++){
//  cout<<arr[i][ec]<<" ";
// }
// ec--;
// // bottom
// for(int i=ec;i>=sc;i--){
//     cout<<arr[er][i]<<" ";
// }
// er--;
// for(int i=er;i>=sr;i--){
//     cout<<arr[i][sc]<<" ";
// }
// sc++;

//     }
// }


// diagonal sum

// #include<iostream>
// using namespace  std;
// int main(){
//     int row,col;
//     cin>>row>>col;
//     int arr[row][col];
//      for(int i=0;i<row;i++){
//         for(int j=0;j<col;j++){
//             cin>>arr[i][j];
//         }
//     }
//     int sum=0;
//      for(int i=0;i<row;i++){
//         for(int j=0;j<col;j++){
//             if(i==j){sum+=arr[i][j];
//             // primary dia
//             }
//             else if(j==col-i-1){
//                 sum+=arr[i][j];
//                 // second diagonal
//             }
//         }
//     }
//     if(row==col && row%2==1){
//         int center = row / 2;
//         sum -= arr[center][center];
//         // removing duplicate
//     }
    
//         cout<<sum;
    

 
// }







// String(it is mutable in c++)

// A string is represented as an array of characters ending with a special null character: '\0'.
// eg:
// char name[] = "Hello";
// This is actually stored as: 'H' 'e' 'l' 'l' 'o' '\0'





// #include<iostream>

// using namespace std;
// int main(){
//     char arr[50];
    // cin>>arr;
    // it will only take singal word
    // cout<<arr;

    // cin.getline(arr,50);
    // for taking multiple word 
    // but it will only store 49 char beacuse 50 char is \0 char 
    // cout<<arr;

    // cin.getline(arr,50,'.');
    // cout<<arr;
    // // '.' delimeter that indicate that it will store the val before the delimeter

    

// }


// strcat(destination,source)
// strlen(str)
// strcpy(dest,src)
// strcmp(str1,str2)

// this function only work with char array not with string object 

// insted of this we use this with object
// + operator for concat
// == compare
// direct assign
// obj.length() for length



// Operation	     C-style (char array)	                    C++ std::string
// Concatenation	 strcat(a, b)	                        a + b or a += b
// Comparison	     strcmp(a, b) == 0	                    a == b, a != b, etc.
// Assignment	     strcpy(a, b)	                        a = b
// Length	         strlen(a)	                            a.length() or a.size()
// Substring search substr(a, "text")	                    a.find("text")
// Character access	a[i] (works for both types)	a[i] or a.at(i)




// #include<iostream>
// #include<cstring>
// using namespace std;
// int main(){
//     char arr[50];
//     char arr1[50];
//     cin.getline(arr,50,'.');
//     cin.getline(arr1,50,'.');
//     // strcat(arr,arr1);
//     // cout<<arr<<endl;
//     // strcpy(arr1,arr);
//     // cout<<arr1;
//     cout<<strlen(arr)<<endl;
//     cout<<strcmp(arr,arr1);

// }




// std::string is a class in the C++ Standard Library (in <string> header).
// It represents strings as objects that manage character data dynamically.
// Easier and safer to use than raw char arrays.

// include<cstring>


// #include<cstring>
// #include<iostream>
// using namespace std;
// int main(){
//     string str="mahi";
//     string str2="ray";
//    string con=str+str2;
// //    this way to conacat into string object

// int a=str==str2;
// cout<<a;
// cout<<str.length();

// }



// Practice question

// reverse the string
// #include<iostream>
// #include<cstring>
// using namespace std;
// int main(){
// char arr[50];
// cin.getline(arr,50,'.');

// int size=strlen(arr);
// for(int i=0;i<strlen(arr)/2;i++){
// char ch=arr[i];
// arr[i]=arr[size-1-i];
// arr[size-1-i]=ch;
// }
// cout<<arr;



// }


// palindrom
// #include<iostream>
// #include<cstring>

// using namespace std;
// int main(){
//     string str;
//     getline(cin,str);
//     int st=0,end=str.length()-1;
//     while(st<=end){
//         if(str[st]!=str[end]){
//             cout<<"invalid palindrom";
//             return 0;
//         }
//         st++;
//         end--;
//     }
//     cout<<"palindrom";
// }



// finding word

// #include<iostream>
// #include<cstring>
// using namespace std;
// int main(){
//     string str;
//     getline(cin,str);
//     string key="mahi";
//     int n=str.find(key);
//     // give the index from where key start (first time);
//     cout<<n;
// }



// DML
// DYNAMIC MEMORY ALLOCATION

// when we decalare allocate space stack it will be automatically delete when function will be complete 
// but in heap we have to do free the space by delete keyword

// #include<iostream>
// using namespace std;
// int main(){
//     int size;
//     cin>>size;
//     int * ptr=new int[size];
//     for(int i=0;i<size;i++){
//         cin>>ptr[i];
//     }
//     for(int i=0;i<size;i++){
//         cout<<ptr[i]<<" ";
//     }
//     delete []ptr;
// }





// Vector
// <vector> header. It’s a dynamic array that can resize itself as elements are inserted or deleted.
// #include <vector>
// Commonly Used Member Functions of vector

// Function	          Description
// v.size()	          Returns the number of elements.

// v.empty()	Returns true if the vector is empty.

// v.resize(n)	Resizes the container to contain n elements.

// v.reserve(n)	Requests that the capacity be at least enough to contain n elements

// v.push_back(x)	Adds an element to the end.

// v.pop_back()	Removes the last element.

// v.insert(pos, x)	Inserts element x before position pos.

// v.erase(pos)	Removes element at pos.

// v.swap(v2)	Swaps contents with vector v2.

// v[i] or v.at(i)	Access element at index i (at() is bounds-checked).

// v.front()	Access the first element.

// v.back()	Access the last element.

// v.begin()	Returns iterator to the first element.

// It gives you a pointer-like object (called an iterator) that points to the first element

// v.end()	Returns iterator to past-the-end.



// #include<iostream>
// #include<vector>
// using namespace std;
// int main(){
//     vector<int>vec1(5,-1);
//     vector<int>vec2;
//     // for(int i=0;i<5;i++){
//     //     cin>>vec1[i];
//     // }
//     // cout<<vec1.size();
//     // for(int i=0;i<5;i++){
//     //     cout<<vec1[i]<<" ";
//     // }
    
//     // vec1.resize(6);

//     // for(int i=0;i<6;i++){
//     //     // cin>>vec1[i];
//     //     // thi will work only in the case where vactor have predife size
//     // }
  
//     // vec2.swap(vec1);

//     // for(int i=0;i<6;i++){
//     //     cout<<vec2[i]<<" ";
//     // }
//     // cout<<vec2.empty();


//     // vec2.insert(vec2.begin()+2,26);

//     // cout<<vec2.front();
        


//     push back used for insertion but if you have fixed the vector size after you are using the push back then it will increase the vector size
//      while(true){
//             int i;
//             cin>>i;
//             if(i==-1){
//                 break;
//             }
//             vec2.push_back(i);
//                 }


//     vec2.push_back(99);


//      for(int i=0;i<vec2.size();i++){
//         cout<<vec2[i]<<" ";
//     }
 

// }




// find if any pair in sorted vector has targed val

// #include<iostream>
// #include<vector>
// #include<cstring>
// using namespace  std;
// int main(){
//     vector<int>vec1;
//     for(int i=0;i<5;i++){
//         int val;
//         cin>>val;
//         vec1.push_back(val);
//     }
//     int target;
//     cin>>target;

//     int st=0;
//     int end=vec1.size()-1;
    
//     int sum=0;
//     while(st<end){
//         sum=vec1[st]+vec1[end];
//         if(sum>target){
//             end--;
//         }
//         else if(sum<target){
//             st++;
//         }
//         else if(sum==target){
//             cout<<st<<" "<<end<<" present";
//             return 1;
//         }
//     }

//     cout<<"not exist";
  
   
// }


// 2D vector















// // Note 
// // Stack me: "Object ka naam hai, directly kaam kar sakte ho"
// // Heap me: "Naam nahi, sirf address hai — pointer se kaam hota hai"





