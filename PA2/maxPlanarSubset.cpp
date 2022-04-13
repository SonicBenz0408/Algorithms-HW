#include "maxPlanarSubset.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

// QuickSort in PA1 (the same as PA1, no change)
//----------------------------------------------------------------
int Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    
    //initialization
    int key, index ;
    key = data[high] ;
    index = low - 1;
    
    for(int i=low ; i < high ; i++){
        if(data[i] <= key){
            index ++ ;
            swap(data[index], data[i]) ;
        }
    }
    index ++ ;
    swap(data[index], data[high]) ;
    return index ;
}

// Sort subvector (Quick sort)
void QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    int divIndex ;

    if(low < high){
        divIndex = Partition(data, low, high) ;
        QuickSortSubVector(data, low, divIndex - 1) ;
        QuickSortSubVector(data, divIndex + 1, high) ;
    }
}

// Quick sort method
void QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
//--------------------------------------------------------------

MPS::MPS() {}

// Read the data from .in and store them in Chord map.
void MPS::getChordMap(char* fpath){
    char buffer[200] ;
    int num1, num2;
    fstream fin(fpath);
    
    fin.getline(buffer, 200) ;
    planarSize = atoi(buffer) ;
    cout << "size: " << planarSize << endl ;

    C = vector<int>(planarSize) ;
    M = vector< vector<int> >(planarSize, vector<int>(planarSize, -1)) ;
    P = vector< vector<bool> >(planarSize, vector<bool>(planarSize, false)) ;
    while(fin >> num1 >> num2){
        C[num1] = num2 ;
        C[num2] = num1 ;
    }
    cout << "map over!" << endl ;
    fin.close() ;
}

// Top Down Recursive Function
// Find the maximum number of chords and keep the steps in P to reconstruct the chord pairs
// Due to Recursion, use "inline"
inline int MPS::Process(int start, int end){
    
    // Boundary condition
    if(start >= end){
        return 0 ;
    }

    if(M[start][end] != -1){
        return M[start][end] ;
    }
    int k = C[end] ;
    
    // case 1:  k not in [i, j]
    if(k < start || k > end){
        return M[start][end] = Process(start, end-1) ;
    }

    // case 2: k in (i, j)
    else if(k > start && k < end){
        int ans1 = Process(start, end-1) ;
        int ans2 = Process(start, k-1) + Process(k+1, end-1) + 1;
        
        if(ans2 >= ans1){
            P[start][end] = true ;
            return M[start][end] = ans2 ;
        }
        else{
            return M[start][end] = ans1 ;
        }

    }
    // case 3: k == i
    else if(k == start){
        P[start][end] = true ;
        return M[start][end] = Process(start+1, end-1) + 1 ;
    }
}


// Top Down Recursive Function
// Use P to reconstruct the chord pairs and store them in output
inline void MPS::getAnswer(int start, int end, vector<int>& output){
    
    if(start >= end){
        return ;
    }

    int k = C[end];
    
    if(k < start || k > end){
        getAnswer(start, end-1, output);
    }
    else if(k > start){
        if(P[start][end]){
            output.push_back(k);
            getAnswer(start, k-1, output);
            getAnswer(k+1, end-1, output);
        }
        else{
            getAnswer(start, end-1, output);
        }
    }
    else if(k == start){
        output.push_back(k);
        getAnswer(start+1, end-1, output); 
    }   
}

// Sort the output and generate the output file
void MPS::Write(char* fpath){
    fstream fout;
    vector<int> result;
    fout.open(fpath, ios::out);

    int len = Process(0, planarSize-1) ;
    
    cout << "process over!" << endl;
    getAnswer(0, planarSize-1, result) ;
    cout << "get pairs!" << endl;

    QuickSort(result) ;
    cout << "sort over!" << endl;

    fout << len << endl ;
    cout << "Number over!" << endl;

    for (int i = 0; i < result.size(); i++){
        fout << result[i] << " " << C[result[i]] << endl;
    }

    fout.close() ;
}
