#include<iostream>
using namespace std;
class node{
    public:
    string key;
    int val;
    node * next;
    node(string key,int val){
        this->key=key;
        this->val=val;
        next=nullptr;
    }


};
class HashTable{
    int totalsize;
    int currsize;
    node ** arr;

 
    int hashfunction(string key){
        int ind=0;
        for(int i=0;i<key.size();i++){
            ind=(ind+key[i])%totalsize;
        }
        return ind%totalsize;
    }

    void rehashing(){
        node **oldtable=arr;
        int oldsize=totalsize;

        totalsize=2*totalsize;
        currsize=0; //agar yeah nahi kara ga to baar reshaing hoga

        arr=new node *[totalsize];
        for(int i=0;i<totalsize;i++){
            arr[i]=nullptr;  //reinitlize
        }

        // reenter the element into new table
        for(int i=0;i<oldsize;i++){
            node * temp=oldtable[i];
            while(temp!=nullptr){
                insert(temp->key,temp->val);
                temp=temp->next;
            }
           
        }

          // Free memory of old table's linked lists
    for (int i = 0; i < oldsize; i++) {
        node *temp = oldtable[i];
        while (temp != nullptr) {
            node *nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }

    delete[]oldtable;

}

    public:

       HashTable(int size){
        totalsize=size;
        currsize=0;
        arr=new node *[totalsize];
        for(int i=0;i<totalsize;i++){
            arr[i]=nullptr;
        }
    }

    void insert(string key,int val){
        int ind=hashfunction(key);
        node * newnode=new node(key,val);
        newnode->next=arr[ind];
        arr[ind]=newnode;
        currsize++;

        double lam=currsize/(double)totalsize;
        // lem=load factor 
        // insertion time complexity based on lam it's avergae no of element in rach linklist
        // so we have to fixed the threshold value of lam so when it cross the value rehashing perform 

        if(lam>1){
            rehashing();
        }
    
    }

    //  the count() function is used with hash-based containers like unordered_map and unordered_set from the Standard Template Library (STL). It checks whether a key exists in the hash table and returns how many times it appears.

    bool count(string key){
        for(int i=0;i<totalsize;i++){
            node * temp=arr[i];
            while(temp!=nullptr){
                if(temp->key==key){
                    return true;
                    
                }
                temp=temp->next;
            }
        }
        return false;
    }


    void search(string key){

         for(int i=0;i<totalsize;i++){
            node * temp=arr[i];
            while(temp!=nullptr){
                if(temp->key==key){
                   cout<<temp->key<<" "<<temp->val;
                   break;
                    
                }
                temp=temp->next;
            }
        }
        

    }

    void print(){
         for(int i=0;i<totalsize;i++){
            node * temp=arr[i];
            while(temp!=nullptr){
               
                   cout<<temp->key<<" "<<temp->val<<endl;
                 
                    
                temp=temp->next;
            }
        }
    }

    void erase(string key){
      int  ind=hashfunction(key);
      node *temp=arr[ind];
      node *pre=nullptr;
      while(temp!=nullptr){
        if(temp->key==key){
            if(pre==nullptr){
                arr[ind]=temp->next;
                
            }
            else{
                pre->next=temp->next;
               
            }
            delete temp;
            currsize--;
            break;
           }
         pre=temp;
        temp=temp->next;
      }
    }


};

int main(){
    HashTable h1(5);
    h1.insert("india",150);
    h1.insert("us",100);
    h1.insert("uea",90);
    h1.insert("china",120);
    h1.insert("nepal",50);

    // h1.print();
    h1.search("nepal");
    h1.erase("nepal");
    h1.search("nepal");

}
