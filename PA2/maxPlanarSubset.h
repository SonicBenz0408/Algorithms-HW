#ifndef MAXPLANARSUBSET_H
#define MAXPLANARSUBSET_H

#include <vector>
using namespace std;

class MPS {
    
    public:
        MPS() ;
        void getChordMap(char*) ;
        inline int Process(int, int) ;
        inline void getAnswer(int, int, vector<int>&) ;
        void Write(char*);

    private:
        int planarSize ; // size
        vector<int> C ; // chord pairs
        vector< vector<int> > M ; // num of chords
        vector< vector<bool> > P ;  //check if there is a new chord
} ;

#endif