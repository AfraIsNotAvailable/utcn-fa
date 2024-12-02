//
// Created by afra-laptop on 11/22/2024.
//

#include "dynamic.h"

#include <iostream>

/**
* Codul implementează un arbore statistic de ordine utilizând un BST echilibrat.
* Arborele este echilibrat prin intermediul funcției buildTree care îl construiește recursiv luând elementul din mijloc
* ca rădăcină și construind recursiv subarborele din stânga/dreapta - similar conversiei unui array sortat într-un BST
* echilibrat. Acest lucru asigură o înălțime O(log n).
* Fiecare nod își stochează dimensiunea subarborelui, permițând operații O(log n) atât pentru selecție (osSelect),
* cât și pentru ștergere (osDelete) după rang. Selecția utilizează dimensiunea pentru a naviga la stânga/dreapta pe baza
* rangului dorit, în timp ce ștergerea păstrează dimensiunile în timpul restructurării.
* Natura echilibrată a arborelui este menținută numai în timpul construcției inițiale - ștergerile ulterioare îl pot
* dezechilibra, deoarece nu este implementată reechilibrarea (ca în cazul arborilor AVL/Red-Black).
 */
namespace lab7
{
    struct Node
    {
        int key;
        int size = 0; // size of subtree rooted at this node
        Node* left = nullptr;
        Node* right = nullptr;

        explicit Node(const int k) : key(k)
        {
        }
    };

    int size(const Node* node)
    {
        return node == nullptr ? 0 : node->size;
    }

    void helperBuildTree(Node*& node, int* keys, const int n, Operation* ops = nullptr)
    {
        if (n == 0)
        {
            node = nullptr;
            return;
        }

        const int mid = n / 2;
        node = new Node(keys[mid]);
        if (ops) ops->count(1); // ass
        helperBuildTree(node->left, keys, mid, ops);
        helperBuildTree(node->right, keys + mid + 1, n - mid - 1, ops);
        node->size = size(node->left) + size(node->right) + 1;
    }

    int* makeKeysArray(int n);

    Node* buildTree(int n, Operation* ops = nullptr)
    {
        int* keys = makeKeysArray(n);
        Node* root = nullptr;
        helperBuildTree(root, keys, n, ops);
        return root;
    }

    int* makeKeysArray(const int n)
    {
        auto* keys = new int[n];
        for (int i = 0; i < n; i++)
        {
            keys[i] = i;
        }
        return keys;
    }

    void helperPrettyPrint(const Node* node, const int indent)
    {
        if (node == nullptr)
        {
            return;
        }

        helperPrettyPrint(node->right, indent + 4);
        for (int i = 0; i < indent; i++)
        {
            std::cout << "-";
        }
        std::cout << node->key << ":" << size(node) << std::endl;
        helperPrettyPrint(node->left, indent + 4);
    }

    void prettyPrint(Node* node)
    {
        std::cout << "\nPretty Print:" << std::endl;
        std::cout << "=============" << std::endl;
        std::cout << "> Legend: key:size" << std::endl << std::endl;
        helperPrettyPrint(node, 0);
    }

    void deletePrettyPrint(Node* node, int i)
    {
        std::cout << "\nPretty Print:" << std::endl;
        if (i % 10 == 1)
        {
            std::cout << "Deleted: " << i << "st" << std::endl;
        }
        else if (i % 10 == 2)
        {
            std::cout << "Deleted: " << i << "nd" << std::endl;
        }
        else if (i % 10 == 3)
        {
            std::cout << "Deleted: " << i << "rd" << std::endl;
        }
        else
        {
            std::cout << "Deleted: " << i << "th" << std::endl;
        }
        std::cout << "=============" << std::endl;
        helperPrettyPrint(node, 0);
    }

    void osSelect(const Node* node, const int i, Operation* ops = nullptr)
    {
        if (node == nullptr)
        {
            return;
        }

        const int r = size(node->left) + 1;
        if (ops) ops->count(1); // comp
        if (i == r)
        {
            std::cout << "Selected: " << node->key << std::endl;
            return;
        }

        if (i < r)
        {
            osSelect(node->left, i, ops);
        }
        else
        {
            osSelect(node->right, i - r, ops);
        }
    }

    void helperOsDelete(Node*& node, const int i, Operation* ops = nullptr)
    {
        if (ops) ops->count(1); // comp
        if (node == nullptr)
        {
            return;
        }

        const int r = size(node->left) + 1;

        if (i < r)
        {
            helperOsDelete(node->left, i, ops);
            return;
        }
        if (i > r)
        {
            helperOsDelete(node->right, i - r, ops);
            return;
        }

        if (ops) ops->count(1); // comp
        if (node->left == nullptr)
        {
            Node* temp = node->right;
            delete node;
            node = temp;
            if (ops) ops->count(2); // ass
        }
        else if (node->right == nullptr)
        {
            Node* temp = node->left;
            delete node;
            node = temp;
            if (ops) ops->count(2); // ass
        }
        else
        {
            Node* temp = node->right;
            if (ops) ops->count(1); // ass
            while (temp->left != nullptr)
            {
                temp = temp->left;
                if (ops) ops->count(1);
            }
            node->key = temp->key;
            helperOsDelete(node->right, 1, ops);
        }
    }

    void osDelete(Node*& node, const int i, Operation* ops = nullptr)
    {
        helperOsDelete(node, i, ops);
        deletePrettyPrint(node, i);
    }

    void demonstrate()
    {
        Node* root = buildTree(10);
        prettyPrint(root);
        osSelect(root, 5);
        osSelect(root, 3);
        osSelect(root, 7);
        osDelete(root, 5);
        osDelete(root, 3);
        osDelete(root, 7);
    }

    void performance(Profiler& profiler, AnalysisCase whichCase)
    {
        for (int n = 100; n <= 10000; n += 100)
        {
            for (int i = 0; i < 5; i++)
            {
                auto opsBuild = profiler.createOperation("ops_Build", n);
                auto opsSelect = profiler.createOperation("ops_Select", n);
                auto opsDelete = profiler.createOperation("ops_Delete", n);

                Node* root = buildTree(n, &opsBuild);
                int m = n;
                while (m)
                {
                    osSelect(root, m / 2, &opsSelect);
                    osDelete(root, m / 2, &opsDelete);
                    m--;
                }
            }
        }

        profiler.divideValues("ops_Build", 5);
        profiler.divideValues("ops_Select", 5);
        profiler.divideValues("ops_Delete", 5);

        profiler.createGroup("BUILD", "ops_Build");
        profiler.createGroup("SELECT", "ops_Select");
        profiler.createGroup("DELETE", "ops_Delete");
        profiler.createGroup("ALL", "ops_Build", "ops_Select", "ops_Delete");
    }

    void benchmark(Profiler& profiler, const AnalysisCase whichCase)
    {
    }
}
