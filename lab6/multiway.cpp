//
// Created by afras on 13/11/2024.
//

#include "multiway.h"

#include <catch2.hpp>
#include <iostream>
#include <stack>
#include <unordered_map>

/**
 * Dpdv al operatiilor, atat implementarea iterativa cat si cea recursiva a traversarii arborelui binar sunt O(n).
 */
namespace lab6 {
    /** TODO: Implement three different  multiway tree representations
    * 1. Parent array representation: for each index, the value in the vector represents the parent's
    index, e.g.: 𝛱 = {2,7,5,2,7,7,−1,5,2}
    * 2. Multiway tree representation: each node contains the key and a vector of child nodes
    * 3. Binary representation: each node contains the key and two pointers, one to the first child and the second to the right sibling (e.g., the next sibling).
    */

    struct NodeR1 {
        std::vector<int> parent;
    };

    struct NodeR2 {
        int key{};
        std::vector<NodeR2> children;
    };

    struct NodeR3 {
        int key{};
        NodeR3 *left;
        NodeR3 *right;

        explicit NodeR3(const int k) : key(k), left(nullptr), right(nullptr) {
        } // constructor
    };

    struct NodeBin {
        int key{};
        NodeBin *left;
        NodeBin *right;

        explicit NodeBin(const int k) : key(k), left(nullptr), right(nullptr) {
        }
    };

    void preorderIterative(const NodeBin *root) {
        if (root == nullptr) return;

        std::stack<const NodeBin *> stack;
        stack.push(root);

        while (!stack.empty()) {
            const NodeBin *current = stack.top();
            stack.pop();

            printf("%d ", current->key);

            if (current->right) {
                stack.push(current->right);
            }

            if (current->left) {
                stack.push(current->left);
            }
        }
    }

    void preorderRecursive(const NodeBin *root) {
        if (root == nullptr) return;

        printf("%d ", root->key);
        preorderRecursive(root->left);
        preorderRecursive(root->right);
    }

    void inorderRecursive(const NodeBin *root) {
        if (root == nullptr) return;

        inorderRecursive(root->left);
        printf("%d ", root->key);
        inorderRecursive(root->right);
    }

    void postorderRecursive(const NodeBin *root) {
        if (root == nullptr) return;

        postorderRecursive(root->left);
        postorderRecursive(root->right);
        printf("%d ", root->key);
    }

    void addNode(NodeBin *root, int key) {
        if (root == nullptr) {
            root = new NodeBin(key);
        } else if (key < root->key) {
            if (root->left == nullptr) {
                root->left = new NodeBin(key);
            } else {
                addNode(root->left, key);
            }
        } else {
            if (root->right == nullptr) {
                root->right = new NodeBin(key);
            } else {
                addNode(root->right, key);
            }
        }
    }

    void prettyPrintBinary(const NodeBin *root, int level = 0) {
        if (root == nullptr) {
            return;
        }

        if (level == 0) {
            printf("%d\n", root->key);
            level += 3;
        }

        NodeBin *child = root->left;
        while (child != nullptr) {

            for (int j = 0; j < level; j++) {
                printf(" ");
            }
            printf("%d\n", child->key);

            if (child->left) {
                NodeBin *grandchild = child->left;
                while (grandchild != nullptr) {

                    for (int j = 0; j < level + 3; j++) {
                        printf(" ");
                    }
                    printf("%d\n", grandchild->key);
                    grandchild = grandchild->right;
                }
            }

            child = child->right;
        }
    }

    NodeR2 buildSubtree(const int index, const std::unordered_map<int, std::vector<int> > &childrenMap) {
        NodeR2 node;
        node.key = index + 1; // back to 1-indexed

        auto it = childrenMap.find(index); // children of nod
        if (it != childrenMap.end()) {
            for (const int childIndex: it->second) {
                //subtree
                node.children.push_back(buildSubtree(childIndex, childrenMap));
            }
        }
        return node;
    }

    NodeR2 buildMultiwayTree(const std::vector<int> &parent) {
        int rootIndex = 0;
        for (int i = 0; i < parent.size(); i++) {
            if (parent[i] == -1) {
                rootIndex = i;
                break;
            }
        }

        std::unordered_map<int, std::vector<int> > childrenMap;
        for (int i = 0; i < parent.size(); i++) {
            if (parent[i] != -1) {
                childrenMap[parent[i] - 1].push_back(i);
            }
        }

        return buildSubtree(rootIndex, childrenMap);
    }

    NodeR2 transformR1ToR2(const NodeR1 &r1) {
        return buildMultiwayTree(r1.parent);
    }

    // NodeR2 transformR1toR2(NodeR1 root) {
    //     std::queue<int> q;
    //     q.push(-1);
    //     NodeR2 rootR2; // the return node
    //     // the assignments node
    //     NodeR2 rootAux = rootR2;
    //     int i = 0;
    //     while (!q.empty()) {
    //         int aux = q.front(); // the key to be searched for this loop
    //         if (root.parent[i] == -1) {
    //             q.push(i); // if found, pushed to queue
    //             rootAux.key = i;
    //         } else if (root.parent[i] == aux) {
    //             q.push(i);
    //             NodeR2 child;
    //             child.key = i;
    //             rootAux.children.push_back(child);
    //         }
    //         i++;
    //         q.pop();
    //     }
    // }

    // void transform(NodeR1 root, NodeR2 rootR2, std::queue<int> q) {
    //     if (rootR2.key == q.front()) {
    //         q.pop();
    //         for (int i = 0 ; i < root.parent.size(); i++) {
    //
    //         }
    //     }
    // }

    void prettyPrintR2(const NodeR2 &root, int level) {
        if (root.children.empty()) {
            return;
        }
        if (level == 0) {
            printf("%d\n", root.key);
            level += 3;
        }
        for (int i = 0; i < root.children.size(); i++) {
            for (int j = 0; j < level; j++) {
                printf(" ");
            }
            printf("%d\n", root.children[i].key);
            prettyPrintR2(root.children[i], level + 3);
        }
    }

    void prettyPrintR3(const NodeR3 *root, int level = 0) {
        if (root == nullptr) {
            return;
        }

        if (level == 0) {
            printf("%d\n", root->key);
            level += 3;
        }

        NodeR3 *child = root->left;
        while (child != nullptr) {

            for (int j = 0; j < level; j++) {
                printf(" ");
            }
            printf("%d\n", child->key);

            if (child->left) {
                NodeR3 *grandchild = child->left;
                while (grandchild != nullptr) {

                    for (int j = 0; j < level + 3; j++) {
                        printf(" ");
                    }
                    printf("%d\n", grandchild->key);
                    grandchild = grandchild->right;
                }
            }

            child = child->right;
        }
    }

    NodeR3 *transformR2toR3(const NodeR2 &multiway) {
        auto *binaryNode = new NodeR3(multiway.key);

        if (!multiway.children.empty()) {

            binaryNode->left = transformR2toR3(multiway.children[0]);

            NodeR3 *current = binaryNode->left;
            for (size_t i = 1; i < multiway.children.size(); i++) {
                current->right = transformR2toR3(multiway.children[i]);
                current = current->right;
            }
        }

        return binaryNode;
    }

    void deleteBinaryTree(const NodeR3 *root) {
        if (root == nullptr) return;

        deleteBinaryTree(root->left);
        deleteBinaryTree(root->right);
        delete root;
    }

    // TODO: Observe and analyse the performance and describe it in a comment (1p)
    // TODO: Explain the data structures you used for representations R2 and R3.
    // TODO: Analyse the time and space efficiency of the two transformations. Did you achieve O(n)? Did you use additional memory?

    // TODO: Define Transformation 1 : Parent array representation -> Multi-way tree representation

    // TODO: Define Transformation 2 : Multi-way tree representation -> Binary representation

    // TODO: Implement pretty print for the binary tree representation (1p)

    // TODO: 1. Implementation of iterative and recursive binary tree traversal in O(n) and with constant additional memory(2p)

    // TODO: 2. Comparative analysis of the iterative vs recursive tree traversal from the perspective of the number of operations(2p)

    // TODO: 3. Correct implementation for Pretty-print for R1 (1p)

    // TODO: 4. Correct implementation for T1 and pretty-print for R2 (1p) + T1 in linear time (1p)

    // TODO: 5. Correct implementation for T2 and pretty-print for R3 (2p) + T2 in linear time (1p)

    // TODO: Comparative analysis between the *recursive* and *iterative* !!count only the print key operations

    void demonstrate() {
        printf("\b");

        NodeR1 rootR1;
        rootR1.parent = {2, 7, 5, 2, 7, 7, -1, 5, 2};

        const NodeR2 rootR2 = transformR1ToR2(rootR1);

        printf("Pretty Print R2\n");
        prettyPrintR2(rootR2, 0);

        NodeR3 *rootR3 = new NodeR3(rootR2.key);
        rootR3 = transformR2toR3(rootR2);

        printf("Pretty Print R3\n");
        prettyPrintR3(rootR3);

        printf("\n\n");

        NodeBin rootBin(5); //
        addNode(&rootBin, 2);
        addNode(&rootBin, 3);
        addNode(&rootBin, 1);
        addNode(&rootBin, 4);
        addNode(&rootBin, 8);
        addNode(&rootBin, 6);
        addNode(&rootBin, 7);

        // printf("Pretty Print Binary\n");
        // prettyPrintBinary(&rootBin);

        printf("Inorder Recursive\n");
        inorderRecursive(&rootBin);
        printf("\n");

        printf("Preorder Iterative\n");
        preorderIterative(&rootBin);
        printf("\n");

        printf("Preorder Recursive\n");
        preorderRecursive(&rootBin);
        printf("\n");

        printf("Postorder Recursive\n");
        postorderRecursive(&rootBin);
        printf("\n");

        // preorderRecursive(&rootBin);
        // NodeR2 rootR2;
        // rootR2.key = 1;
        // NodeR2 child1;
        // child1.key = 2;
        // NodeR2 child2;
        // child2.key = 3;
        // NodeR2 child3;
        // child3.key = 4;
        // rootR2.children.push_back(child1);
        // rootR2.children.push_back(child2);
        // rootR2.children.push_back(child3);
        // NodeR2 child4;
        // child4.key = 5;
        // NodeR2 child5;
        // child5.key = 6;
        // NodeR2 child6;
        // child6.key = 7;
        // rootR2.children[0].children.push_back(child4);
        // rootR2.children[0].children.push_back(child5);
        // rootR2.children[1].children.push_back(child6);
        //
        // prettyPrintR2(rootR2, 0);
    }

    void performance(Profiler &profiler, AnalysisCase whichCase) {
    }

    void benchmark(Profiler &profiler, AnalysisCase whichCase) {
    }
}
