#pragma once
#include "Array.h"
#include "Stack.h"
#include "Queue.h"
#include "Heap.h"
#include "List.h"
#include "Map.h"
#include "Ordered_Map.h"

#ifndef GRAPH_H
#define GRAPH_H
template<typename V, typename W>
class Graph{
private:
public:
    class Vertex{
    public:
        V value;

        Vertex(V val) : value(val){}

        ~Vertex(){}

        friend std::ostream& operator<<(std::ostream& os, const Vertex& v){
            os << v.value;
        }

        bool operator<(const Vertex& other) const{
            return value < other.value;
        }
    };
    class Edge{
    public:
        Vertex* src;
        Vertex* dest;
        W weight;

        Edge(Vertex* s, Vertex* d, W wt) : src(s), dest(d), weight(wt){}

        ~Edge(){}

        bool operator<(const Edge& other) const{
            return weight < other.weight;
        }
    };

    // Ordered_Map<Vertex*, List<Edge* >* > adj;
    Map<Vertex*, List<Edge* >* > adj;

    // struct compare_weight{
    //     bool operator()(Edge* a, Edge* b){
    //         return a->weight < b->weight;
    //     }
    // };

    int graphsize(){
        return adj.size();
    }

    // void display(){
    //     for(auto i : adj){
    //         std::cout << i.first->value << " -> ";
    //         for(Edge* j : *i.second){
    //             std::cout << "(" << j->src->value << ", " << j->dest->value << ", wt: " << j->weight << ") => ";
    //         }
    //         std::cout << std::endl;
    //     }
    //     return;
    // }

    Vertex* createVertex(V val){
        Vertex* vertex = new Vertex(val);
        List<Edge*>* edges = new List<Edge*>();

        // std::cout << "Vertex Initialized: " << *vertex << std::endl;
        adj.insert(vertex, edges);
        return vertex;
    }

    Vertex* getVertex(V val){
        // for(Pair<Vertex*, List<Edge* >* > i : adj){
        for(auto i : adj){
            if(i.first->value == val){
                return i.first;
            }
        }
        return NULL;
    }

    void addedges(Vertex* src, Vertex* dest, W weight){
        // std::cout << "At addedges" << std::endl;
        Edge* e1 = new Edge(src, dest, weight);
        Edge* e2 = new Edge(dest, src, weight);
        // std::cout << "Edge initialized: " << e1->src->value << ", " << e1->dest->value << std::endl;
        List<Edge*>* edges = adj[src];
        if(edges == NULL){
            throw std::out_of_range("Edge not Found");
        }
        // std::cout << "edge check: " << std::endl;
        edges->push_back(e1);

        edges = adj[dest];
        if(edges == NULL){
            throw std::out_of_range("Edge not Found");
        }
        edges->push_back(e2);
    }

    class DFSIterator{
    private:
        Map<Vertex*, bool> visit;
        // Ordered_Map<Vertex*, List<Edge*>*>& adj;
        Map<Vertex*, List<Edge*>*>& adj;
        Stack<Vertex*> StackFrontier;
        // typename Stack<Vertex*>::Iterator it;

        void advanceToValid(){
            while(!StackFrontier.empty() && visit[StackFrontier.top()]){
                // std::cout << "Visit is true for: " << StackFrontier.top()->value;
                StackFrontier.pop();
            }
        }

    public:
        // DFSIterator(Ordered_Map<Vertex*, List<Edge*>*>& a, Vertex* s) : adj(a){
        DFSIterator(Map<Vertex*, List<Edge*>*>& a, Vertex* s) : adj(a){
            StackFrontier.push(s);
            visit[s] = true;
        }

        V& operator*() const{ return StackFrontier.top()->value; }
        V* operator->() const{ return &(StackFrontier.top()->value); }

        DFSIterator& operator++(){
            if(!StackFrontier.empty()){
                Vertex* vertex = StackFrontier.top();
                StackFrontier.pop();
                visit[vertex] = true;
                for(Edge* edge : *adj[vertex]){
                    if(!visit[edge->dest]){
                        StackFrontier.push(edge->dest);
                    }
                }
                advanceToValid();
            }
            return *this;
        }

        bool operator!=(const DFSIterator& other) const{
            if(StackFrontier.empty() && other.StackFrontier.empty()){
                return true;
            }
            if(StackFrontier.empty() || other.StackFrontier.empty()){
                return false;
            }
            return StackFrontier.top() != other.StackFrontier.top();
        }
    };

    DFSIterator dfsbegin(Vertex* start){
        return DFSIterator(adj, start);
    }
    DFSIterator dfsend(){
        return DFSIterator(adj, NULL);
    }

    class BFSIterator{
    private:
        Map<Vertex*, bool> visit;
        Ordered_Map<Vertex*, List<Edge*>*>& adj;
        Queue<Vertex*> QueueFrontier;

        void advanceToValid(){
            while(!QueueFrontier.empty() && visit[QueueFrontier.front()]){
                QueueFrontier.pop();
            }
        }

    public:
        BFSIterator(Ordered_Map<Vertex*, List<Edge*>*>& a, Vertex* s) : adj(a){
            QueueFrontier.push(s);
            visit[s] = true;
        }

        Vertex& operator*() const{ return *QueueFrontier.front(); }

        Vertex* operator->() const{ return QueueFrontier.front(); }

        BFSIterator& operator++(){
            if(!QueueFrontier.empty()){
                Vertex* vertex = QueueFrontier.front();
                QueueFrontier.pop();
                visit[vertex] = true;
                for(Edge* edge : *adj[vertex]){
                    if(!visit[edge->dest]){
                        QueueFrontier.push(edge->dest);
                    }
                }
                advanceToValid();
            }
            return *this;
        }

        bool operator!=(const BFSIterator& other) const{
            if(QueueFrontier.empty() && other.QueueFrontier.empty()){
                return true;
            }
            if(QueueFrontier.empty() || other.QueueFrontier.empty()){
                return false;
            }
            return QueueFrontier.front() != other.QueueFrontier.front();
        }
    };

    BFSIterator bfsbegin(Vertex* start){
        return BFSIterator(adj, start);
    }
    BFSIterator bfsend(){
        return BFSIterator(adj, NULL);
    }

    class GBFSIterator{
    private:
        Map<Vertex*, bool> visit;
        Ordered_Map<Vertex*, List<Edge*>*>& adj;
        Heap<Edge*> QueueFrontier;

        void advanceToValid(){
            while(!QueueFrontier.empty() && visit[QueueFrontier.front()->dest]){
                QueueFrontier.pop();
            }
        }

    public:
        GBFSIterator(Ordered_Map<Vertex*, List<Edge*>*>& a, Vertex* s) : adj(a){
            QueueFrontier.push(new Edge(s, s, 0));
            visit[s] = true;
        }

        Vertex& operator*() const{ return *(QueueFrontier.front()->dest); }

        Vertex* operator->() const{ return QueueFrontier.front()->dest; }

        GBFSIterator& operator++(){
            if(!QueueFrontier.empty()){
                Edge* edge = QueueFrontier.front();
                QueueFrontier.pop();
                visit[edge->dest] = true;
                for(Edge* i : *adj[edge->dest]){
                    if(!visit[i->dest]){
                        QueueFrontier.push(i);
                    }
                }
                advanceToValid();
            }
            return *this;
        }

        bool operator!=(const GBFSIterator& other) const{
            if(QueueFrontier.empty() && other.QueueFrontier.empty()){
                return true;
            }
            if(QueueFrontier.empty() || other.QueueFrontier.empty()){
                return false;
            }
            return QueueFrontier.front() != other.QueueFrontier.front();
        }
    };

    GBFSIterator gbfsbegin(Vertex* start){
        return GBFSIterator(adj, start);
    }
    GBFSIterator gbfsend(){
        return GBFSIterator(adj, NULL);
    }

    void shortest_path_queue(Vertex* start){
        // Heap<Edge*, compare_weight> HeapFrontier;
        Heap<Edge*> HeapFrontier;
        Map<Vertex*, bool> visit;
        Map<Vertex*, W> distance;
        for(auto i : adj){
            distance[i.first] = INT32_MAX;
        }

        distance[start] = 0;
        Edge* e0 = new Edge(start, start, 0);

        HeapFrontier.push(e0);

        while(!HeapFrontier.empty()){
            Edge* edge = HeapFrontier.front();
            HeapFrontier.pop();

            if(!visit[edge->dest]){
                visit[edge->dest] = true;

                for(auto i : *adj[edge->dest]){
                    if(distance[edge->dest] + i->weight < distance[i->dest]){
                        distance[i->dest] = distance[edge->dest] + i->weight;
                        // std::cout << "\n(" << i->src->value << ", " << i->dest->value << ", wt: " << i->weight << ") { ";
                        HeapFrontier.push(i);
                    }
                }
            }
        }

        // for(auto i : adj){
        //     std::cout << "(" << distance[i.first] << ") ";
        // }
        // std::cout << std::endl;
        return;
    }
};

#endif