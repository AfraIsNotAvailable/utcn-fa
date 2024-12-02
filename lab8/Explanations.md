I'll solve this assignment using C++ with custom data structures for disjoint sets and Kruskal's algorithm.

```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

// Disjoint Set class with rank and path compression
class DisjointSet {
private:
    struct Node {
        int parent;
        int rank;
        int data;
        
        Node(int val) : parent(val), rank(0), data(val) {}
    };
    
    std::vector<Node> sets;

public:
    // Make set operation
    void MAKE_SET(int x) {
        if (x >= sets.size()) {
            sets.resize(x + 1, Node(x));
        }
        sets[x] = Node(x);
    }

    // Find set with path compression
    int FIND_SET(int x) {
        if (x >= sets.size()) {
            MAKE_SET(x);
            return x;
        }
        
        if (sets[x].parent != x) {
            sets[x].parent = FIND_SET(sets[x].parent);
        }
        return sets[x].parent;
    }

    // Union by rank
    void UNION(int x, int y) {
        int root_x = FIND_SET(x);
        int root_y = FIND_SET(y);

        if (root_x == root_y) return;

        // Union by rank
        if (sets[root_x].rank < sets[root_y].rank) {
            sets[root_x].parent = root_y;
        } else if (sets[root_x].rank > sets[root_y].rank) {
            sets[root_y].parent = root_x;
        } else {
            sets[root_y].parent = root_x;
            sets[root_x].rank++;
        }
    }

    // Print set contents
    void printSets() {
        for (size_t i = 0; i < sets.size(); ++i) {
            if (sets[i].parent == i) {
                std::cout << "Set root: " << i << std::endl;
            }
        }
    }
};

// Edge structure for graph and Kruskal's algorithm
struct Edge {
    int src, dest, weight;
    
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
    
    // For sorting edges
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Kruskal's algorithm implementation
class KruskalMST {
private:
    std::vector<Edge> edges;
    int num_vertices;

public:
    KruskalMST(int vertices) : num_vertices(vertices) {}

    void addEdge(int src, int dest, int weight) {
        edges.emplace_back(src, dest, weight);
    }

    // Kruskal's algorithm to find Minimum Spanning Tree
    std::vector<Edge> computeMST() {
        // Sort edges by weight
        std::sort(edges.begin(), edges.end());
        
        DisjointSet ds;
        std::vector<Edge> mst;

        // Initialize sets
        for (int i = 0; i < num_vertices; ++i) {
            ds.MAKE_SET(i);
        }

        for (const auto& edge : edges) {
            int src_root = ds.FIND_SET(edge.src);
            int dest_root = ds.FIND_SET(edge.dest);

            // Add edge if it doesn't create a cycle
            if (src_root != dest_root) {
                mst.push_back(edge);
                ds.UNION(edge.src, edge.dest);
            }
        }

        return mst;
    }

    // Performance evaluation
    void evaluatePerformance() {
        std::cout << "Performance Evaluation of Disjoint Set Operations:\n";
        
        // Seed for random number generation
        std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
        
        std::cout << "n\tMake\tUnion\tFind\tTotal\n";
        
        // Vary n from 100 to 10000
        for (int n = 100; n <= 10000; n += 100) {
            // Random graph generation
            DisjointSet ds;
            std::vector<Edge> graph_edges;
            std::uniform_int_distribution<> node_dist(0, n-1);
            std::uniform_int_distribution<> weight_dist(1, 1000);

            // Create graph with n nodes and 4n edges
            for (int i = 0; i < n * 4; ++i) {
                int src = node_dist(gen);
                int dest = node_dist(gen);
                int weight = weight_dist(gen);
                
                if (src != dest) {
                    graph_edges.emplace_back(src, dest, weight);
                }
            }

            // Tracking operations
            int make_ops = 0, union_ops = 0, find_ops = 0;

            // Perform Kruskal's algorithm with operation counting
            for (int i = 0; i < n; ++i) {
                make_ops++;
                ds.MAKE_SET(i);
            }

            std::sort(graph_edges.begin(), graph_edges.end());

            for (const auto& edge : graph_edges) {
                int src_root = ds.FIND_SET(edge.src);
                find_ops++;
                
                int dest_root = ds.FIND_SET(edge.dest);
                find_ops++;

                if (src_root != dest_root) {
                    ds.UNION(edge.src, edge.dest);
                    union_ops++;
                }
            }

            int total_ops = make_ops + union_ops + find_ops;
            
            std::cout << n << "\t" 
                      << make_ops << "\t" 
                      << union_ops << "\t" 
                      << find_ops << "\t" 
                      << total_ops << std::endl;
        }
    }
};

int main() {
    // Part 1: Demonstrate MAKE_SET, UNION, and FIND_SET
    std::cout << "Part 1: Disjoint Set Demonstration\n";
    DisjointSet ds;
    
    // Create 10 sets
    for (int i = 0; i < 10; ++i) {
        ds.MAKE_SET(i);
    }
    
    std::cout << "Initial sets:\n";
    ds.printSets();

    // Perform UNION and FIND_SET operations
    ds.UNION(2, 4);
    ds.UNION(5, 7);
    ds.UNION(2, 5);

    std::cout << "\nAfter UNION operations:\n";
    ds.printSets();

    // Part 2: Kruskal's Algorithm Demonstration
    std::cout << "\nPart 2: Kruskal's Algorithm Demonstration\n";
    KruskalMST graph(5);
    
    // Create a graph with 5 nodes and 9 edges
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 2);
    graph.addEdge(2, 3, 5);
    graph.addEdge(2, 4, 6);
    graph.addEdge(3, 4, 7);
    graph.addEdge(0, 3, 8);
    graph.addEdge(1, 4, 9);

    std::vector<Edge> mst = graph.computeMST();

    std::cout << "Minimum Spanning Tree Edges:\n";
    for (const auto& edge : mst) {
        std::cout << edge.src << " - " << edge.dest << " : " << edge.weight << std::endl;
    }

    // Part 3: Performance Evaluation
    std::cout << "\nPart 3: Performance Evaluation\n";
    KruskalMST perf_graph(1);
    perf_graph.evaluatePerformance();

    return 0;
}
```

I've implemented a solution that addresses all three requirements of the assignment:

1. Disjoint Set Implementation:
    - Custom `DisjointSet` class with `MAKE_SET`, `FIND_SET`, and `UNION` operations
    - Uses rank-based union and path compression optimizations
    - Demonstrates creating 10 sets and performing UNION/FIND operations

2. Kruskal's Algorithm:
    - Implemented in `KruskalMST` class
    - Demonstrates on a 5-node graph with 9 edges
    - Computes and displays the Minimum Spanning Tree

3. Performance Evaluation:
    - Evaluates disjoint set operations
    - Varies n from 100 to 10000
    - Generates random graphs
    - Counts MAKE, UNION, and FIND operations
    - Outputs performance metrics for each graph size

Key Features:
- Custom implementation without using standard library set data structures
- Efficient disjoint set operations with path compression and union by rank
- Comprehensive performance analysis
- Demonstrates algorithmic concepts with practical examples

The code will output detailed information about the disjoint set operations, Kruskal's algorithm demonstration, and performance metrics when run.

Let me break down the `MAKE_SET` function in detail:

```c++
void MAKE_SET(int x) {
    // Check if the vector is large enough to hold the element at index x
    if (x >= sets.size()) {
        // If not, resize the vector to accommodate x
        // The new elements will be initialized with Node(x)
        sets.resize(x + 1, Node(x));
    }
    // Create or reset the element at index x to a new Node
    sets[x] = Node(x);
}
```

This implementation handles three key scenarios:

1. **Dynamic Sizing**:
    - It allows creating sets for indices that haven't been used before
    - If you try to create a set with an index larger than the current vector size, it automatically expands the vector
    - The `resize()` method ensures the vector is large enough to hold the new element

2. **Initialization**:
    - Each element is initialized as its own set
    - The `Node` constructor sets:
        - `parent` to the element's own index (x)
        - `rank` to 0 (initial tree height)
        - `data` to the element's value

3. **Idempotency**:
    - If you call `MAKE_SET` multiple times on the same element, it resets the element to a fresh, single-element set

Example walkthrough:
```c++
// Initial state: sets is empty []

ds.MAKE_SET(5);  
// Now sets becomes [0, 1, 2, 3, 4, 5]
// sets[5] has parent=5, rank=0, data=5

ds.MAKE_SET(10); 
// Now sets becomes [0, 1, 2, 3, 4, 5, null, null, null, null, 10]
// sets[10] has parent=10, rank=0, data=10
```

This approach provides flexibility and robustness:
- Handles arbitrary set indices without manual pre-allocation
- Ensures each element starts as its own independent set
- Prevents out-of-bounds errors when working with disconnected indices

The method is particularly useful in disjoint set implementations where you might not know in advance how many or which elements you'll be working with.

Would you like me to elaborate on any part of this explanation?

Let me break down the `FIND_SET` function in detail:

```c++
int FIND_SET(int x) {
    // Check if x is beyond the current vector size
    if (x >= sets.size()) {
        // If so, create a new set for x
        MAKE_SET(x);
        // Return x as its own root
        return x;
    }
    
    // Path compression step
    if (sets[x].parent != x) {
        // Recursively find the root of the set
        // And update x's parent to point directly to the root
        sets[x].parent = FIND_SET(sets[x].parent);
    }
    // Return the root of the set
    return sets[x].parent;
}
```

This implementation combines two critical optimizations:

1. **Dynamic Set Creation**:
    - If the requested element doesn't exist in the sets, it automatically creates a new set
    - This prevents errors when working with previously unseen indices
    - Ensures every element can be part of a set

2. **Path Compression**:
    - This is the key optimization that makes disjoint set operations nearly constant time
    - When finding the root of a set, it flattens the tree structure
    - Every node on the path to the root is directly linked to the root

Let's walk through an example to illustrate:

```
Initial tree structure:
0 -> 1 -> 2 -> 3 (root)

When FIND_SET(0) is called:
1. It recursively finds the root (3)
2. As it returns, it updates each node's parent to point directly to the root

Final optimized structure:
0 -> 3 (direct link)
1 -> 3 (direct link)
2 -> 3 (direct link)
3 (root)
```

Detailed step-by-step example:

```c++
// Assume we have a tree like this:
// 0's parent is 1
// 1's parent is 2
// 2's parent is 3
// 3's parent is itself (root)

// When we call FIND_SET(0):
FIND_SET(0) {
    // 0's parent is 1, not itself
    sets[0].parent = FIND_SET(1)  // Recursive call
        // 1's parent is 2, not itself
        sets[1].parent = FIND_SET(2)  // Another recursive call
            // 2's parent is 3, not itself
            sets[2].parent = FIND_SET(3)  // Final recursive call
                // 3's parent is 3 (root), so return 3
            // Update 2's parent to 3
            return 3
        // Update 1's parent to 3
        return 3
    // Update 0's parent to 3
    return 3
}

// After this call, the tree looks like:
// 0 -> 3 (direct)
// 1 -> 3 (direct)
// 2 -> 3 (direct)
// 3 (root)
```

Benefits of this approach:
- Drastically reduces the time complexity of set operations
- Flattens the tree structure with each find operation
- Ensures subsequent operations on the same set are very fast
- Handles dynamic set creation seamlessly

The time complexity is nearly constant (amortized almost O(1)) due to path compression, which is a significant improvement over the naive O(log n) approach.

Would you like me to elaborate on any part of this explanation or provide more context?

Let me break down the `UNION` function in detail:

```c++
void UNION(int x, int y) {
    // First, find the roots of the sets containing x and y
    int root_x = FIND_SET(x);
    int root_y = FIND_SET(y);

    // If x and y are already in the same set, do nothing
    if (root_x == root_y) return;

    // Union by rank optimization
    if (sets[root_x].rank < sets[root_y].rank) {
        // If root_y's tree is taller, make root_y the parent
        sets[root_x].parent = root_y;
    } else if (sets[root_x].rank > sets[root_y].rank) {
        // If root_x's tree is taller, make root_x the parent
        sets[root_y].parent = root_x;
    } else {
        // If trees have the same rank, arbitrarily choose one as the parent
        // And increment its rank
        sets[root_y].parent = root_x;
        sets[root_x].rank++;
    }
}
```

This implementation uses two key optimizations:

1. **Root Identification**:
    - Uses `FIND_SET` to locate the root of each set
    - This ensures we're working with the representative elements of the sets

2. **Union by Rank**:
   This is a critical optimization that keeps the tree balanced and prevents it from becoming too deep.

Let's break down the different scenarios:

### Scenario 1: Different Rank Trees
```
Before UNION:
Tree A (root_x):    Tree B (root_y):
   1 (rank 2)          5 (rank 3)
  / \                 / \
 2   3               6   7

After UNION:
The lower-ranked tree is attached to the higher-ranked tree
   5 (rank 3)
  / | \
 1  6  7
/ \
2  3
```

### Scenario 2: Equal Rank Trees
```
Before UNION:
Tree A (root_x):    Tree B (root_y):
   1 (rank 2)          5 (rank 2)
  / \                 / \
 2   3               6   7

After UNION:
One tree is chosen as the parent, and its rank is incremented
   1 (rank 3)
  / | \
 2  3  5
     / \
     6  7
```

### Code Walkthrough:

```c++
// Example 1: Trees with different ranks
UNION(1, 5) {
    root_x = 1 (rank 2)
    root_y = 5 (rank 3)
    
    Since root_x.rank < root_y.rank:
    sets[1].parent = 5  // Attach lower-ranked tree to higher-ranked tree
}

// Example 2: Trees with equal ranks
UNION(1, 5) {
    root_x = 1 (rank 2)
    root_y = 5 (rank 2)
    
    Since ranks are equal:
    sets[5].parent = 1  // Arbitrarily choose 1 as parent
    sets[1].rank++      // Increment the rank
}
```

Benefits of Union by Rank:
1. Prevents the tree from becoming a long, linear chain
2. Keeps the tree relatively balanced
3. Ensures near-constant time complexity for future operations
4. Provides an efficient way to merge sets

Key Points:
- The rank is an upper bound on the tree's height
- Rank is different from the actual height (it doesn't always decrease precisely)
- This method ensures that the more balanced tree becomes the parent

The time complexity of UNION becomes nearly constant (amortized O(α(n)), where α is the inverse Ackermann function, which grows extremely slowly).

Would you like me to elaborate on any part of this explanation or provide more context?

Let me break down the `operator<` method for the `Edge` struct in detail:

```c++
bool operator<(const Edge& other) const {
    return weight < other.weight;
}
```

This is a custom comparison operator that defines how `Edge` objects should be ordered or compared. In this context, it's used to sort edges by their weight, which is crucial for Kruskal's algorithm.

### Purpose of the Operator

1. **Sorting Edges**:
    - Allows edges to be sorted in ascending order based on their weight
    - Used when `std::sort()` is called on a vector of edges
    - Enables the greedy approach in Kruskal's algorithm (selecting the lowest weight edges first)

### How It Works

```c++
// Example edges
Edge edge1(0, 1, 4);   // From node 0 to node 1, weight 4
Edge edge2(1, 2, 2);   // From node 1 to node 2, weight 2
Edge edge3(2, 3, 6);   // From node 2 to node 3, weight 6

std::vector<Edge> edges = {edge1, edge2, edge3};
std::sort(edges.begin(), edges.end());

// After sorting, edges will be ordered:
// edge2 (weight 2)
// edge1 (weight 4)
// edge3 (weight 6)
```

### Detailed Explanation

- `const Edge& other`:
    - Takes a constant reference to another `Edge` object
    - Prevents unnecessary copying
    - `const` ensures the method doesn't modify the compared object

- `const` at the end of the method:
    - Promises not to modify the current object during comparison
    - Allows the method to be called on const objects

### Comparison Semantics

- Returns `true` if the current edge's weight is less than the other edge's weight
- Used by sorting algorithms to determine the relative order of edges

### Example Implementation Variations

```c++
// Alternative implementations with the same core logic:

// 1. Explicit comparison
bool operator<(const Edge& other) const {
    if (weight != other.weight) {
        return weight < other.weight;
    }
    // Optional: secondary sorting criteria
    if (src != other.src) {
        return src < other.src;
    }
    return dest < other.dest;
}

// 2. Using std::tie for multi-level comparison
bool operator<(const Edge& other) const {
    return std::tie(weight, src, dest) < 
           std::tie(other.weight, other.src, other.dest);
}
```

### Use in Kruskal's Algorithm

```c++
std::vector<Edge> computeMST() {
    // Sort edges by weight in ascending order
    std::sort(edges.begin(), edges.end());

    // Now edges are processed from lowest weight to highest
    for (const auto& edge : edges) {
        // Check if adding this edge creates a cycle
        if (canAddEdge(edge)) {
            addToMST(edge);
        }
    }
}
```

### Why This Matters

1. **Greedy Algorithm Support**:
    - Kruskal's algorithm works by selecting the lowest weight edges first
    - This comparison operator enables that selection process

2. **Efficiency**:
    - Allows standard library sorting algorithms to work efficiently
    - Provides a clear, consistent way to order edges

3. **Flexibility**:
    - Can be extended to include more complex comparison logic if needed

Practical Tip:
- This method is critical when you want to sort a collection of custom objects
- Provides a natural ordering for the object

Would you like me to elaborate on any part of this explanation or provide more context?

Let me break down the `addEdge` method in detail:

```c++
void addEdge(int src, int dest, int weight) {
    edges.emplace_back(src, dest, weight);
}
```

### Purpose
This method adds a new edge to the graph's list of edges by creating an `Edge` object.

### Detailed Breakdown

1. **Method Parameters**:
    - `src`: Source node of the edge
    - `dest`: Destination node of the edge
    - `weight`: The cost or weight of the edge

2. **`emplace_back()` vs `push_back()`**:
   ```c++
   // Using push_back()
   edges.push_back(Edge(src, dest, weight));

   // Using emplace_back()
   edges.emplace_back(src, dest, weight);
   ```
    - `emplace_back()` is more efficient
    - It constructs the `Edge` object directly in the vector's memory
    - Avoids creating a temporary object and then copying/moving it

### Practical Example

```c++
KruskalMST graph(5);  // Graph with 5 nodes

// Adding edges to the graph
graph.addEdge(0, 1, 4);  // Edge from node 0 to node 1 with weight 4
graph.addEdge(1, 2, 2);  // Edge from node 1 to node 2 with weight 2
graph.addEdge(2, 3, 6);  // Edge from node 2 to node 3 with weight 6
```

### What Happens Internally

```c++
// Conceptually similar to:
class KruskalMST {
private:
    // Vector to store all edges in the graph
    std::vector<Edge> edges;

public:
    void addEdge(int src, int dest, int weight) {
        // Create an Edge object and add it to the vector
        Edge new_edge(src, dest, weight);
        edges.push_back(new_edge);
        
        // Or more efficiently:
        edges.emplace_back(src, dest, weight);
    }
};

// Edge struct for reference
struct Edge {
    int src, dest, weight;
    
    // Constructor
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};
```

### Why This Method is Important

1. **Graph Construction**:
    - Allows step-by-step building of the graph
    - Flexible for creating graphs of any size and structure

2. **Kruskal's Algorithm Preparation**:
    - Collects all edges before running the MST algorithm
    - Enables sorting and processing edges later

### Performance Considerations

```c++
// If you know the number of edges in advance
graph.edges.reserve(num_edges);  // Optional optimization
```
- `reserve()` can improve performance by avoiding multiple reallocations
- Reduces memory reallocation overhead for large graphs

### Typical Usage Scenario

```c++
// Creating a graph for Minimum Spanning Tree
KruskalMST graph(5);  // 5 nodes

// Adding edges (node1, node2, weight)
graph.addEdge(0, 1, 4);   // Connect node 0 and 1 with weight 4
graph.addEdge(0, 2, 3);   // Connect node 0 and 2 with weight 3
graph.addEdge(1, 2, 1);   // Connect node 1 and 2 with weight 1
graph.addEdge(1, 3, 2);   // Connect node 1 and 3 with weight 2
graph.addEdge(2, 3, 5);   // Connect node 2 and 3 with weight 5

// Compute Minimum Spanning Tree
std::vector<Edge> mst = graph.computeMST();
```

Key Points:
- Simple method to add edges to the graph
- Uses efficient object construction
- Supports building complex graph structures

Would you like me to elaborate on any part of this explanation or provide more context?