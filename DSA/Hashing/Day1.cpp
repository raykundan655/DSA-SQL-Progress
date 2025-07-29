// Hashing is a technique used to convert a given input (called a key) into a fixed-size value (usually an integer). 
// This value is used as an index to store or retrieve data in a data structure called a hash table.

// eg
// Imagine a library has 1000 books. You want to quickly find a book by its name.
// One way: you search each book one by one → very slow (takes time).
// A better way: assign each book a code number (like a shortcut) and store it at a specific shelf (position) based on that number.
// Now, if you know the code number, you can go directly to the shelf.

// This is what hashing does:
// It takes a value (like book name)
// Runs it through a formula (called hash function)
// That gives you a number (index) to store it or find it fast


// You need to find Bob’s marks quickly.
//  Convert "Bob" into a number → e.g., 2
// Store his marks at position 2 in an array
// int hashIndex = hash("Bob"); // Let's say this gives 2
// marks[2] = 85;

// Next time you want Bob’s marks → do marks[2] ✅
// ⏱️ Fast and direct!


// Hash Table
// A Hash Table is a data structure that stores data in key–value pairs.
// We can imagine this as table with two col->key|value
// NOTE
// Key will be always unique
// key and value can be any data type

// hash table is Unordered data struture, data is stored based on hash values.
// That means the order is decided by the hash function, not by insertion or sorting or key,

// // eg
// unordered_map<int, string> umap;
// umap[10] = "Apple";
// umap[5]  = "Banana";
// umap[20] = "Cherry";
//  for (auto &p : umap) {
//         cout << p.first << " -> " << p.second << endl;
//     }
// // output
// 20 -> Cherry  
// 10 -> Apple  
// 5 -> Banana    //order are not based on key not on insertion order it is based on hash values

// Hash table support three Operation
// It allows you to 
// insert, 
// delete, and search data in constant time (O(1)) on average.

// Use a Hash Table When:
// 1. You Need Fast Lookup / Search
// Want to check if a key exists.
// Want to find a value by its key quickly. 

// 2. You Need to Map One Thing to Another
// Like a dictionary.
// Example:
// Student ID → Name
// Country code → Country name
// IP address → Location

//  3. You Don't Care About Order
// Order of elements doesn’t matter to you.

// 4. You Need Fast Insertion & Deletion
// Adding and removing data frequently.



// Hash Function
// In C++, there is no table-like structure, so we use arrays like data struture that have fixed set index value
// the key is transformed into an array index using a hash function, which converts the key (like a number or string) into a valid index within the array.
// and the value at that index is the value.
// this make easy access,search,delition


// A hash function is a function that takes an input (called a key) and returns a fixed-size value (called a hash or hash code).
  
// Think of it as:
// 🧠 Input (Key) → 🎲 Hash Function → 🔢 Output (Index / Hash Code)
// This output is typically used to quickly access data in a hash table.

// Purpose of Hash Function
// To map a large/unlimited set of inputs (like strings, names, large numbers)
// → into a smaller fixed range of integers (array index).
// To enable fast data lookup, insertion, and deletion — ideally in O(1) time.

// Eg:
// we have a hash table of size 10, and we want to insert a name like "Alice".

// We apply a hash function:
// int hash = some_hash_function("Alice") % 10;  // returns index 3
// So, "Alice" will be stored at index 3 in the array.

 // Collisions
// Two different keys may produce the same hash index. This is called a collision.

// Collision Resolution Techniques:
// Chaining – Store multiple values at the same index using a linked list or vector.

// We’ll define two classes:
// Node – to represent each linked list node.
// HashTable – to represent the hash table itself, with an array of pointers to linked lists.

#include <iostream>
using namespace std;

const int TABLE_SIZE = 10;

// Node class
class Node {
public:
    int key;
    Node* next;

    Node(int k) {
        key = k;
        next = nullptr;
    }
};

// HashTable class
class HashTable {
private:
    Node* table[TABLE_SIZE];

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    // Constructor to initialize table with nullptr
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    // Insert key into hash table
    void insert(int key) {
        int index = hashFunction(key);
        Node* newNode = new Node(key);
        newNode->next = table[index];
        table[index] = newNode;
    }

    // Search key in hash table
    bool search(int key) {
        int index = hashFunction(key);
        Node* temp = table[index];
        while (temp != nullptr) {
            if (temp->key == key)
                return true;
            temp = temp->next;
        }
        return false;
    }

    // Display hash table
    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << ": ";
            Node* temp = table[i];
            while (temp != nullptr) {
                cout << temp->key << " -> ";
                temp = temp->next;
            }
            cout << "NULL\n";
        }
    }

    // Destructor to free memory
    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
    }
};

int main() {
    HashTable ht;

    ht.insert(10);
    ht.insert(20);
    ht.insert(25);
    ht.insert(15);
    ht.insert(35);

    ht.display();

    cout << "Search 25: " << (ht.search(25) ? "Found" : "Not Found") << endl;
    cout << "Search 99: " << (ht.search(99) ? "Found" : "Not Found") << endl;

    return 0;
}

// NOTE
// "No hash function is perfect enough to completely avoid collisions."
































