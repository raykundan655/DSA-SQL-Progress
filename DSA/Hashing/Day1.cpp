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















