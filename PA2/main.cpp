#include "maxPlanarSubset.h"

using namespace std;

int main(int argc, char* argv[]){
        
    MPS MPS ;
    MPS.getChordMap(argv[1]) ;
    MPS.Write(argv[2]) ;
    
    return 0;
}