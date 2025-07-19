// Heap Sort

// Heap Sort is a comparison-based sorting algorithm that uses a special data structure called a heap 
// (usually a binary heap) to sort elements.It is known for its O(n log n) time complexity
//  and in-place sorting (no extra space needed).

// Build a Max-Heap (for ascending sort):

// Arrange the array into a max-heap, where the largest element is at the root.

// Extract elements from the heap one by one:
// Swap the root (maximum element) with the last element of the heap.
// Reduce the heap size by 1 (ignore the last element which is now sorted).
// Heapify the root to maintain the max-heap property.
// Repeat until only one element is left.

#include<iostream>
using namespace std;

class heap{
    int arr[100];
    int size=0;
    public:

    // Bottom-Up
    void insert(int val){
        arr[size]=val;
        int ind=size;
        size++;

        while(ind>0){
            int par=(ind-1)/2;
            if(arr[par]<arr[ind]){
                swap(arr[par],arr[ind]);
                ind=par;
            }
            else{
                break;
            }
        }

    }

    // top-bottom approach
    void heapify(int size,int ind){
        int largest=ind;
        int left=2*ind+1;
        int right=2*ind+2;
        if(left<size && arr[left]>arr[largest]){
            largest=left;
        }
        if(right<size && arr[right]>arr[largest]){
            largest=right;
        }
        if(largest!=ind){
            swap(arr[largest],arr[ind]);
            heapify(size,largest); //it's for cheacking jaha swap hua hai woha property full fill ho raha hai yeah nahi
        }
    }

    
    void heapsort(){
        int n=size;
        while(n>1){
            swap(arr[n-1],arr[0]);
            n--;
            heapify(n,0);
        }
    }

    void display(){
        for(int i=0;i<size;i++){
            cout<<arr[i]<<" ";
        }
    }
};
int main(){
    heap h1;
    while(true){
        int val;
        cin>>val;
        if(val==-1){
            break;
        }
        h1.insert(val);
    }

    h1.display();
    cout<<endl;
    h1.heapsort();
    h1.display();

}

// / Descending Heap Sort

// Step 1: Build a Min-Heap
// Rearrange the array so that the smallest element is at the root (index 0).
// A min-heap ensures the parent is smaller than or equal to its children.

// Step 2: Sort the array
// Repeat until heap size becomes 1:
// Swap the root (smallest element) with the last element of the heap.
// Reduce the size of the heap by 1.
// Heapify the root again to maintain the min-heap property.


#include<iostream>
using namespace std;

// min heap
void insert(int arr[],int val,int ind){
    arr[ind]=val;
    // min heap
    while(ind>0){
        int par=(ind-1)/2;
        if(arr[par]>arr[ind]){
            swap(arr[par],arr[ind]);
            ind=par;
        }
        else{
            break;
        }
    }
}

void heapify(int arr[],int size,int ind){
    int smaller=ind;
    int left=2*ind+1;
    int right=2*ind+2;

    // finding smallest node in b/w child
    
    if(left<size && arr[left]<arr[smaller]){
        smaller=left;
    }

    if(right<size && arr[right]<arr[smaller]){
        smaller=right;
    }

    if(smaller!=ind){
        swap(arr[smaller],arr[ind]);
        heapify(arr,size,smaller); //smaller child index that replace with root pass for checking that ->jaha root replace hua hai ush place pe heap property maintain haii yeah nahi
        }

    
}

// decending order
void heapsort(int arr[],int size){
    int n=size;
    while(n>0){
        swap(arr[n-1],arr[0]);
        n--;
        heapify(arr,n,0);

    }
}

void display(int arr[],int size){
    for(int i=0;i<size;i++){
        cout<<arr[i];
    }
}

int main(){
    int arr[100];
    int size=0;
    while(true){
        int val;
        cin>>val;
        if(val==-1){
            break;
        }
        insert(arr,val,size);
        size++;
    }

    display(arr,size);

   
    heapsort(arr,size);
    cout<<endl;

    display(arr,size);

     

}







