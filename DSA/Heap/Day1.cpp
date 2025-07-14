// A Heap is a special binary tree that satisfies two main properties:

// Complete Binary Tree
// All levels are completely filled except possibly the last, which is filled from left to right.
// This structure allows us to implement heaps efficiently using arrays.

// Heap Property
// Max-Heap: The value of each parent is greater than or equal to its children.
// Min-Heap: The value of each parent is less than or equal to its children.
// NOTE: Heap is not a sorted structure, and it’s not a BST.

// why Heap is special Binary tree
// A binary tree is a tree where each node has at most two children, typically referred to as the left child and right child.

// 🔸 What Makes a Heap a “Special” Binary Tree?
// A heap is a special kind of binary tree because it must satisfy two additional properties beyond just being binary
// Complete Binary Tree
// Heap Property


// Type	             Root Node	              Usage Example
// Max-Heap	         Largest	            Priority queues, heapsort
// Min-Heap	         Smallest	           Dijkstra’s algorithm (shortest path)

// Because a heap is a complete binary tree, we can use an array to store

// why we choose array ? it is complete binary tree does it mean use array?

// You can number its nodes level by level (top to bottom, left to right) without gaps.
// That’s why you can store it in an array without wasting space or needing NULL pointers.


// General Binary Tree
//        10
//       /  
//     20   
//       \
//       30

// This is NOT a complete binary tree.

// If we try to use an array:
// We’ll have to leave gaps (unused indices)
// Mapping parent and children becomes unreliable

// ➡You can’t use an array efficiently for general trees.


// Complete Binary Tree:
// Every node has a fixed position:
 //       10
 //      /  \
 //    20    30
 //   / \
 // 40   50

// Index 0 → root
// Index 1 → root.left
// Index 2 → root.right
// Index 3 → root.left.left
// and so on…

// No gaps, no nulls — fits cleanly into an array.
// That’s why if your tree is complete, an array is the best choice to store it.


// Practical & Performance Reasons 

// Reason 1: Fast Parent/Child Access via Index
// No need for pointers. Just use math:
// parent = (i-1)/2
// left child= 2*i + 1
// right child= 2*i + 2
// This makes operations like heapify or insert/delete blazing fast 

// Reason 2: No Extra Memory (no pointers/nulls)
// In pointer-based trees:
// You store pointers
// You need memory for left and right even when they’re NULL
// In array:
// No waste. Just pure data.

// Reason 3: Cache Efficiency
// Array is stored in contiguous memory
// CPU loves that — it’s fast
// Tree nodes with pointers? Spread across memory — slow


//  # Array Representation of Heaps
// Because a heap is a complete binary tree, we can use an array to store it:

// For index i:
// Parent: (i - 1) / 2
// Left Child: 2 * i + 1
// Right Child: 2 * i + 2

// ->This mapping removes the need for pointers.

//  Example
// Heap: [10, 20, 30, 40, 50]
// Index mapping:

//         10(0)
//        /    \
//    20(1)    30(2)
//    /   \
// 40(3) 50(4)


// #Heap Operations (with Explanation & Complexity)
// A. Insert Element
// Add element at end of array (heap.push_back).
// Perform Heapify-Up (a.k.a bubble-up):
// Compare child with parent.
// If violates heap condition → swap.
// Repeat until heap property is restored.

// Time: O(log n)

//  B. Delete Top (Extract Min/Max)
// Replace root with last element.
// Remove last element.
// Perform Heapify-Down:
// Compare with left/right child.
// Swap with appropriate child.
// Repeat.

// Time: O(log n)

// C. Peek
// Return root: heap[0]
// Time: O(1)


// Applications of Heap
// Application	                                        Explanation
// Priority Queue	                                   Efficient retrieval of highest/lowest
// Dijkstra's Algorithm	                              To fetch min distance node fast
// Median in Data Stream	                             Use max-heap (lower half) + min-heap (upper)
// Top K Elements	                                   Keep heap of size K
// Merge K Sorted Lists	                             Use min-heap for merging
// Huffman Coding	                                    Build optimal prefix codes using min-heap
// Heap Sort	                                         Efficient sorting algorithm



