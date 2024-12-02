//
// Created by afra-laptop on 28/11/2024.
//

#include "disjoint.h"

#include <iostream>
#include <random>

namespace lab8
{
    class DisjointSet
    {
    private:
        struct Node
        {
            int parent;
            int rank;
            int data;

            Node(int val) : parent(val), rank(0), data(val)
            {
            }
        };

        std::vector<Node> sets;

    public:
        void MAKE_SET(int x)
        {
            if (x >= sets.size())
            {
                sets.resize(x + 1, Node(x));
            }
            sets[x] = Node(x);
        }

        int FIND_SET(int x)
        {
            if (x >= sets.size())
            {
                return -1;
            }
            if (sets[x].parent != x)
            {
                sets[x].parent = FIND_SET(sets[x].parent);
            }
            return sets[x].parent;
        }

        void UNION(int x, int y)
        {
            int root_x = FIND_SET(x);
            int root_y = FIND_SET(y);

            if (root_x == root_y)
            {
                return;
            }

            if (sets[root_x].rank < sets[root_y].rank)
            {
                sets[root_x].parent = root_y;
            }
            else if (sets[root_x].rank > sets[root_y].rank)
            {
                sets[root_y].parent = root_x;
            }
            else
            {
                sets[root_y].parent = root_x;
                sets[root_x].rank++;
            }
        }

        void printSets()
        {
            for (size_t i = 0; i < sets.size(); i++)
            {
                if (sets[i].parent == i)
                {
                    std::cout << "Node: " << i << " Parent: " << sets[i].parent << " Rank: " << sets[i].rank <<
                        std::endl;
                }
            }
        }
    };

    struct Edge
    {
        int src, dest, weight;

        Edge(int s, int d, int w) : src(s), dest(d), weight(w)
        {
        }

        bool operator<(const Edge& other) const
        {
            return weight < other.weight;
        }
    };

    class KruskalMST
    {
    private:
        std::vector<Edge> edges;
        int num_vertices;

    public:
        KruskalMST(int vertices) : num_vertices(vertices)
        {
        }

        void addEdge(int src, int dest, int weight)
        {
            edges.emplace_back(Edge(src, dest, weight));
        }

        std::vector<Edge> computeMST()
        {
            std::sort(edges.begin(), edges.end());

            DisjointSet ds;
            std::vector<Edge> mst;

            for (int i = 0; i < num_vertices; ++i)
            {
                ds.MAKE_SET(i);
            }

            for (const auto& edge : edges)
            {
                int src_root = ds.FIND_SET(edge.src);
                int dest_root = ds.FIND_SET(edge.dest);

                if (src_root != dest_root)
                {
                    mst.emplace_back(edge);
                    ds.UNION(src_root, dest_root);
                }
            }
            return mst;
        }

        void evaluatePerformance(Profiler& profiler)
        {
            std::cout << "Performance Evaluation of Disjoint Set Operations:\n";

            std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());

            std::cout << "n\tMake\tUnion\tFind\tTotal\n";

            for (int n = 100; n <= 10000; n += 100)
            {
                auto ops = profiler.createOperation("DisjointSet", n);

                DisjointSet ds;
                std::vector<Edge> graph_edges;
                std::uniform_int_distribution<> node_dist(0, n - 1);
                std::uniform_int_distribution<> weight_dist(1, 1000);

                for (int i = 0; i < n * 4; ++i)
                {
                    int src = node_dist(gen);
                    int dest = node_dist(gen);
                    int weight = weight_dist(gen);

                    if (src != dest)
                    {
                        graph_edges.emplace_back(src, dest, weight);
                    }
                }

                for (int i = 0; i < n; ++i)
                {
                    ops.count(1);
                    ds.MAKE_SET(i);
                }

                std::sort(graph_edges.begin(), graph_edges.end());

                for (const auto& edge : graph_edges)
                {
                    int src_root = ds.FIND_SET(edge.src);
                    ops.count(1);

                    int dest_root = ds.FIND_SET(edge.dest);
                    ops.count(1);

                    if (src_root != dest_root)
                    {
                        ds.UNION(edge.src, edge.dest);
                        ops.count(1);
                    }
                }
                profiler.createGroup("DisjointSetOps", "DisjointSet");
            }
        }
    };

    void demonstrate(int n)
    {
        std::cout << "Part 1: Disjoint Set Demonstration\n";
        DisjointSet ds;

        for (int i = 0; i < 10; ++i)
        {
            ds.MAKE_SET(i);
        }

        std::cout << "Initial sets:\n";
        ds.printSets();

        ds.UNION(2, 4);
        ds.UNION(5, 7);
        ds.UNION(2, 5);

        std::cout << "\nAfter UNION operations:\n";
        ds.printSets();

        std::cout << "\nPart 2: Kruskal's Algorithm Demonstration\n";
        KruskalMST graph(5);

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
        for (const auto& edge : mst)
        {
            std::cout << edge.src << " - " << edge.dest << " : " << edge.weight << std::endl;
        }
    }

    void performance(Profiler& profiler, AnalysisCase whichCase)
    {
        KruskalMST perf_graph(1);
        perf_graph.evaluatePerformance(profiler);
    }

    void benchmark(Profiler& profiler, AnalysisCase whichCase)
    {
        return;
    }
}
