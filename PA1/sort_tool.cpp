// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include <vector>
#include <iostream>
#include "math.h"
// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int key ;

    for(int i=1 ; i < data.size() ; i++){
        key = data[i] ;
        for(int j=(i-1) ; j >= 0 ; j--){
            if(key < data[j]){
                swap(data[j+1], data[j]) ;
            }
            else{
                break ;
            }
        }
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    int divIndex ;

    if(low < high){
        divIndex = Partition(data, low, high) ;
        QuickSortSubVector(data, low, divIndex - 1) ;
        QuickSortSubVector(data, divIndex + 1, high) ;
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    
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

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    int middle1, middle2 ;
    middle1 = (low + high - 1) / 2 ;
    middle2 = middle1 + 1 ;
    

    if(high > low){
        MergeSortSubVector(data, low, middle1) ;
        MergeSortSubVector(data, middle2, high) ;
        Merge(data, low, middle1, middle2, high) ;
    }
    // Hint : recursively call itself
    //        Merge function is needed

}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    
    vector<int> temp;
    int leftIndex, rightIndex ;
    leftIndex = low ; 
    rightIndex = middle2 ;
    
    while((leftIndex <= middle1) && (rightIndex <= high)){
        if(data[leftIndex] > data[rightIndex]){
            temp.push_back(data[rightIndex]) ;
            rightIndex ++ ;
        }
        else{
            temp.push_back(data[leftIndex]) ;
            leftIndex ++ ;
        }
    }

    if(leftIndex > middle1){
        for(int i=rightIndex ; i <= high ; i++){
            temp.push_back(data[i]) ;
            
        }
    }
    else{
        for(int j=leftIndex ; j <= middle1 ; j++){
            temp.push_back(data[j]) ;
        }
    }
    
    for(int i=low ; i <= high ; i++){
        data[i] = temp[i-low] ;
    }
    //temp.clear() ;
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int level, left, right, largest ;
    level = 1 ;
    while(true){
        if(((root + 1) / pow(2, level)) < 1){
            break ;
        }
        else{
            level ++ ;
        }
    }
    
    left = pow(2, level) + (2 * (root + 1 - pow(2, level-1))) - 1 ;
    right = left + 1 ;
    
    if((left < heapSize) && (data[left] > data[root])){
        largest = left ;
    }
    else{
        largest = root ;
    }

    if((right < heapSize) && (data[right] > data[largest])){
        largest = right ;
    }

    if(largest != root){
        swap(data[root], data[largest]) ;
        MaxHeapify(data, largest) ;
    }
    
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i = (data.size()/2) - 1 ; i >= 0 ; i--){
        MaxHeapify(data, i) ;
    }

}
