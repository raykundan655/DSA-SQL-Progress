// NOTE!!
// C++ STL doesn’t give you a "heap" directly—it gives a priority_queue, which is implemented internally using a heap structure.

// A priority queue is a special type of queue where each element is associated with a priority,
// and elements are served based on their priority, not the order they were inserted (unlike a normal queue).

// In simple terms:
// A normal queue is FIFO — first in, first out.
// A priority queue serves the element with the highest (or lowest) priority first.

// NOTE!!
// A priority queue is implemented using a heap — by default, a max-heap in C++ STL.
// A heap is a complete binary tree:
// In max-heap, every parent node is greater than or equal to its children.
// In min-heap, every parent node is less than or equal to its children.

// So when we insert into the priority queue:
// It maintains this heap property internally using heapify operations.
// When we push, pop, or top:
// It rearranges the structure so the element with the highest (or lowest) priority is always at the top.

// --------------------------------------(VERY imp for understanding)
// INTERNAL PROCESS UNDERSTANDING

// First: Who does the work?
// When you use:
// priority_queue<int, vector<int>, greater<int>> pq;

// You are not writing the heap logic yourself — the C++ Standard Template Library (STL) does all the internal work.

// The STL uses:
// A container (like a vector)
// A heapify process
// A comparator like greater<int>() or less<int>()

// All of it is handled internally by the function:
// std::push_heap() (used internally by priority_queue::push)

// So, what happens when you insert?
  
// pq.push(5);
// STL adds 5 to the end of the vector.
// Then it uses std::push_heap() to bubble up(buttom_up) this value:
// It keeps checking the parent using the comparator.

// For Min Heap: it calls greater<int>()(parent, child)
// If this returns true, STL swaps the parent and child automatically.

// You don't write the swap — STL writes and runs it for you!

// Example: Min Heap
// greater<int>()(parent, child)
// Let’s say parent = 30, child = 5
// Call: greater<int>()(30, 5) → this returns true

// Means: parent (30) is greater than child (5) → ❌ violates min-heap rule
// So STL swaps them → child moves up, parent moves down

// But if:
// Call: greater<int>()(10, 20) → returns false
// Means: parent (10) is not greater than child (20) → ✅ already min-heap → no swap needed

template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>
>
class priority_queue {
protected:
    Container c;     // The underlying container
    Compare comp;    // The comparator (default: max-heap)

public:
    priority_queue() : c(), comp() {}

    void push(const T& val) {
        c.push_back(val); // Add to the end
        std::push_heap(c.begin(), c.end(), comp); // Re-heapify (upward)
    }

    void pop() {
        std::pop_heap(c.begin(), c.end(), comp); // Swap max with last
        c.pop_back(); // Remove the max
    }

    const T& top() const {
        return c.front(); // Largest element
    }

    bool empty() const {
        return c.empty();
    }

    size_t size() const {
        return c.size();
    }
};

// Define inside the algo lib

template <typename RandomIt, typename Compare>
void push_heap(RandomIt first, RandomIt last, Compare comp) {
    auto value = *(last - 1);  // new value added at the end
    int index = last - first - 1;

    while (index > 0) {
        int parent = (index - 1) / 2;
        if (comp(first[parent], value)) { // Compare parent with new value
            first[index] = first[parent]; // Move parent down
            index = parent;
        } else {
            break;
        }
    }
    first[index] = value;
}

template<typename RandomIt, typename Compare>
void pop_heap(RandomIt first, RandomIt last, Compare comp) {
    if (last - first <= 1) return;

    // Move the top (first) element to the end
    std::iter_swap(first, last - 1);

    // Sift down from the root to restore heap in [first, last - 1)
    auto len = last - first - 1;
    auto parent = 0;

    while (true) {
        auto left = 2 * parent + 1;
        auto right = 2 * parent + 2;
        auto largest = parent;

        if (left < len && comp(first[largest], first[left])) {
            largest = left;
        }
        if (right < len && comp(first[largest], first[right])) {
            largest = right;
        }

        if (largest != parent) {
            std::swap(first[parent], first[largest]);
            parent = largest;
        } else {
            break;
        }
    }
}



pq.push(50);

vec.push_back(50);       // append at the end
push_heap(vec.begin(), vec.end()); // fix heap using heapify-up



// MAX HEAP
// priority_queue<int> pq;
// This defaults to a Max-Heap — it means largest element comes first.
// Internally, this is:
// priority_queue<int, vector<int>, less<int>> pq;

// 1. int
//  This is the data type of the elements in the queue.
//  You are storing integers.

// 2. vector<int>
//  This is the underlying container that the priority queue will use.
//  By default, priority_queue uses vector<T> as its storage.
// So, internally, it behaves like a binary heap stored in an array format (via vector).

// 3. less<int>
// This is the comparator — it decides how the elements are ordered in the heap.
// This works like this:
// less<int>: returns true if a < b
// It’s used by the priority queue to arrange the heap such that the largest element comes first.
// So this creates a Max Heap.


// less<int> is the default comparator.
// It means: a < b → then b comes before a, because b is greater.

// bool less(int a, int b) {
//     return a < b;
// }
// so when this function return true swaping happen

// priority_queue<int> pq;
// pq.push(10);
// pq.push(20);
// pq.push(5);

// NOTE!!
// pq.push(val);
// The value is added at the end of the array
// then it "bubbles up"(buttom-up) to the correct position to maintain the heap property

// First insert 10
// → Heap array: [10]

// Insert 20
// New item goes at next available index: [10, 20]
// Now compare 20 with its parent (index 0 → 10)
// 20 > 10 → swap
// → Heap array: [20, 10]

// Insert 5
// New item goes at next available index: [20, 10, 5]
// Index of 5 = 2 → parent index = (2 - 1) / 2 = 0 → parent = 20
// 5 < 20 → No swap needed.

// C++ or any language that offers a priority queue — the library automatically handles 
// the swapping using a data structure called a binary heap

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    priority_queue<int, vector<int>, less<int>> pq;

    pq.push(10);
    pq.push(30);
    pq.push(20);

    cout << "Top element: " << pq.top() << endl; // 30 (max)

    pq.pop();
    cout << "After pop, new top: " << pq.top() << endl; // 20

    return 0;
}



// Declaration of Min Heap:
// priority_queue<int, vector<int>, greater<int>> pq;

// Component Meaning
// int	Type of elements in the priority queue (integers here)
// vector<int>	Underlying container to store the heap (dynamic array)
// greater<int>	Comparator: returns true if a > b

// greater<int>()(30, 10) → true
// a=30,b=10
// It returns true if a > b
// True meaning swaping needed ->heapify


#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    priority_queue<int, vector<int>, greater<int>> pq;

    pq.push(30);
    pq.push(10);
    pq.push(20);

    cout << "Top element: " << pq.top() << endl;  // 10

    pq.pop();
    cout << "After pop, new top: " << pq.top() << endl; // 20

    return 0;
}


// priorty queue operation

// Operation	            queue	               priority_queue	              Description
// Insert element	       q.push(x);	           pq.push(x);	             Adds element to the back (queue) / heap (priority queue)->insert at end of vector and heapify function is called for heap property 
// Access front/top	    q.front();	                pq.top();	               Returns front of queue / largest (or smallest with min-heap)
// Access                back	q.back();	     ❌ Not available           	Back is not meaningful in priority_queue
// Remove element	        q.pop();	             pq.pop();	                    Removes front (queue) / top (priority queue)
// Check empty	            q.empty();	         pq.empty();	                  Returns true if empty
// Get size	             q.size();           	  pq.size();	                      Number of elements



// 1046. Last Stone Weight
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int>q;
        for(int i=0;i<stones.size();i++){
            q.push(stones[i]);
        }
        while(q.size()>1){
            // int first=q.front(); // front function not work in priority queue
            int first=q.top();
            q.pop();
            int sec=q.top();
            q.pop();
            if(first==sec){
                continue;
            }
            else{
                q.push(abs(first-sec));
            }
        }
        return q.empty()? 0: q.top();
    }
};


// 703. Kth Largest Element in a Stream
// Brute force

class KthLargest {
public:
priority_queue<int>q;
int k;
    KthLargest(int k, vector<int>& nums) {
        this->k=k;
        for(int i=0;i<nums.size();i++){
            q.push(nums[i]);
        }
    }
    
    int add(int val) {
        q.push(val);
        vector<int>vec;
        for (int i = 0; i < k && !q.empty(); i++) {
            vec.push_back(q.top());
            q.pop();
        }
           
           
        for(int i=0;i<vec.size();i++){
            q.push(vec[i]);
        }
        return vec.size()==k? vec.back():-1;
        
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */


// optimized
class KthLargest {
public:
priority_queue<int,vector<int>,greater<int>>q;
// min heap only store k element->root is kth highest score
int k;
    KthLargest(int k, vector<int>& nums) {
        this->k=k;
        for(int i=0;i<nums.size();i++){
            q.push(nums[i]);  // buttom up(heapify) the element

            if(q.size()>k){ //checking ->heap mai k se jada to element to nahi hai
                //remove the smallest Score after new score add
                q.pop();
            }
        
        }
    }
    
    int add(int val) {
        q.push(val);
        // heapify
      if(q.size()>k){
        q.pop();
        // maintain top element kth highest
      }
      return q.top();
        
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */










