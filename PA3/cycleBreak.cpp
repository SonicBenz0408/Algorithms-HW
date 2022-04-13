#include "cycleBreak.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

// Edge
Edge::Edge(int vi1, int vi2, int wi){
    v1 = vi1 ;
    v2 = vi2 ;
    w = wi ;
}

int Edge::get_v1(){
    return v1 ;
}

int Edge::get_v2(){
    return v2 ;
}

int Edge::get_w(){
    return w ;
}

bool Edge::operator< (Edge& e){
    return w < e.get_w() ;
}

// Disjoint sets
DJS::DJS(int size){
    set = vector<int>(size, 0) ;
    rank = vector<int>(size, 0) ;
    for(int i=0 ; i < size ; i++){
        set[i] = i ;
    }
}

int DJS::find(int x){
    return set[x] == x ? x : set[x] = find(set[x]) ;
}

void DJS::Union(int x, int y){
    x = find(x) ;
    y = find(y) ;
    if(x != y){
        if(rank[x] < rank[y]) set[x] = y ;
        else{
            set[y] = x ;
            if(rank[x] == rank[y]) rank[x]++ ;
        }
    }
}
bool DJS::equal(int x, int y){
    return find(x) == find(y) ;
}

// Cycle Breaking
CB::CB(){};

void CB::getData(char* fpath){
    char buffer[200] ;
    fstream fin(fpath) ;
    
    fin.getline(buffer, 200) ;
    cout << buffer << endl ;
    directed = (buffer[0] == 'd') ;
    fin.getline(buffer, 200) ;
    nV = atoi(buffer) ;
    fin.getline(buffer, 200) ;
    nE = atoi(buffer) ;

    cout << "directed ?  " << directed << endl ; 
    cout << "Num of vertices : " << nV << endl ; 
    cout << "Num of edges ?  " << nE << endl ; 

    int num1, num2, num3 ;
    if(directed){
        
    }
    else{
        while(fin >> num1 >> num2 >> num3){
            edgeList.push_back(Edge(num1, num2, num3)) ;
        }
    }

    fin.close() ;    
}

void CB::Kruskal(){
    DJS dSet(nV) ;
    vector<bool> chosen(nE, false) ;
    sort(edgeList.begin(), edgeList.end()) ;

    for(int i=nE-1 ; i>=0 ; i--){
        if(dSet.find(edgeList[i].get_v1()) != dSet.find(edgeList[i].get_v2())){
            
            chosen[i] = true ;
            dSet.Union(edgeList[i].get_v1(), edgeList[i].get_v2()) ;
        }
    }
    
    for(int i=0 ; i < nE ; i++){
        if(!chosen[i]){
            ansEdge.push_back(edgeList[i]) ;
            ansW = ansW + edgeList[i].get_w() ;
        }
    }
}

void CB::Solve(){
    if(directed){
        dSolver() ;
    }
    else{
        uSolver() ;
    }
}

void CB::dSolver(){
    
}

void CB::uSolver(){
    Kruskal() ;
}

void CB::writeAns(char* fpath){
    
    Solve() ;

    fstream fout ;
    fout.open(fpath, ios::out) ;
    
    fout << ansW << endl ;
    for(int i=0 ; i < ansEdge.size() ; i++){
        fout << ansEdge[i].get_v1() << " " << ansEdge[i].get_v2() << " " << ansEdge[i].get_w() << endl ;
    }

    fout.close();
}