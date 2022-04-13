#ifndef CYCLEBREAK_H
#define CYCLEBREAK_H

#include <vector>
using namespace std;


class Edge {
    public:
        Edge(int vi1, int vi2, int wi);
        int get_v1() ;
        int get_v2() ;
        int get_w() ;
        bool operator< (Edge& e) ;
        
    private:
        int v1, v2, w ;
};

class DJS {
    public:
        DJS(int size) ;
        int find(int x) ;
        void Union(int x, int y) ;
        bool equal(int x, int y) ;
    private:
        vector<int> set ;
        vector<int> rank ;
};

class CB {
    
    public:
        CB() ;
        void getData(char* fpath) ;
        void Solve();
        void uSolver() ;
        void dSolver() ;
        void Kruskal();
        inline bool checkCycle() ;
        void writeAns(char* fpath) ;
    private:
        bool directed ;
        int nV, nE ;
        int ansW = 0 ;
        vector<Edge> edgeList ;
        vector<Edge> ansEdge ;
};

#endif