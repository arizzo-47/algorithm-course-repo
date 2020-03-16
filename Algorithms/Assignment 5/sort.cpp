//Anthony Rizzo - February 14, 2019
//Homework 3
//Sorting Algorithms

#include "sort.h"
#include <iostream>
#include <stdlib.h>

int moves;  
int comps; 

void initAvg(int array[], int size){
    
    for(int i = 0; i < size; i++)
        array[i] = rand() % size;
}

void initBest(int array[], int size){

    for(int i = 0; i < size; i++)
        array[i] = i;
}

void initWorst(int array[], int size){

    for(int i = 0; i < size; i++)
        array[i] = size - i;
}

void copyAvg(int origArr[], const int copyArray[], int size){
    for(int i = 0; i < size; i++)
        origArr[i] = copyArray[i];
}

int IndexOfLargest(const int array[], int size){
    
    int indexSoFar = 0; //index of element with largest value

    //search for largest value
    for(int currIndex = 1; currIndex < size; currIndex++){
        
        if(++comps && array[currIndex] > array[indexSoFar]){
            indexSoFar = currIndex; //reassign index of largest
        }
    }

    return indexSoFar;
}

//Selection Sort Algo
void Selection(int array[], int size){

    //Loop from last to first
    for(int last = size - 1; last >= 1; last--){
        int largestIndex = IndexOfLargest(array, last+1);     //find max value of current array

        //only swap if different indices 
        if(largestIndex != last){     
            std::swap(array[largestIndex], array[last]);   
            moves += 3; //3 moves for std::swap
        }
    }
}

void Bubble(int array[], int size){
    bool sorted = false;    //array assumed not sorted
    int pass = 1;           //times looped thru

    //keep ordering if not sorted & passes is less than array size
    while(sorted == false && pass < size){

        sorted = true;      //assume 2 elements ordered correctly

        for(int i = 1; i < size - pass + 1; i++){
                
                if(++comps && array[i-1] > array[i]){
                    std::swap(array[i-1], array[i]);    //swap
                    moves += 3; //3 moves for std::swap
                    sorted = false;     //not ordered correctly, keep ordering
                }
        }

        pass++;     //increment
    }
}

void Insertion(int array[], int size){

    for(int unsorted = 1; unsorted < size; unsorted++){
        int copy = array[unsorted]; //copy of next location
        int location = unsorted;    //location index

        //while prior element is greater than current
        while((location > 0) && (array[location - 1] > copy)){
            comps++;
            moves++;
            array[location] = array[location - 1];  //shift
            location--;
        }

        //if shift occured
        if(location != unsorted){                
            array[location] = copy;     //reassign copy
            moves++;
        }

    }
}

void Merge(int array[], int first, int mid, int last){
    int tempArray[MAX_SIZE];    //temp copy array

    int first1 = first;     //beginning of first subarray
    int last1  = mid;       //end of first sub array
    int first2 = mid + 1;   //beginning of second subarray
    int last2  = last;      //end of second subarray

    int index  = first1;    //index for tempArray beginning at start

    //while both subarrays are not empty, copy the smaller
    //item into the tempArray
    while((first1 <= last1) && (first2 <= last2)){
        //tempArray from first to index - 1 is in order
        if(++comps && array[first1] <= array[first2]){
            tempArray[index] = array[first1];
            moves++;
            first1++;
        }
        else{
            tempArray[index] = array[first2];
            moves++;
            first2++;
        }

        index++;    //increment tempArray index
    }

    //Finish first subarray
    while(first1 <= last1){
        //tempArray from first to index - 1 is in order
        tempArray[index] = array[first1];
        moves++;
        first1++;
        index++;
    }

    //Finish off the second subarray
    while(first2 <= last2){
        //tempArray from first to index - 1 is in order
        tempArray[index] = array[first2];
        moves++;
        first2++;
        index++;
    }

    //Copy back to original array
    for(index = first; index <= last; index++){
        moves++;
        array[index] = tempArray[index];
    }
}

void mergeSort(int array[], int first, int last){
    if(first < last){
        int mid = first + (last - first) / 2;   //midpoint

        mergeSort(array, first, mid);       //divide first to mid

        mergeSort(array, mid + 1, last);    //divide mid to last

        Merge(array, first, mid, last);     //merge
    }
}

void order(int array[], int i, int j){
    if(++comps && array[i] > array[j]){
        std::swap(array[i], array[j]); // Exchange entries
        moves += 3;
    }
} // end order

int sortFirstMiddleLast(int array[], int first, int last){
    int mid = first + (last - first) / 2;

    order(array, first, mid); // Make theArray[first] <= theArray[mid]
    order(array, mid, last); // Make theArray[mid] <= theArray[last]
    order(array, first, mid); // Make theArray[first] <= theArray[mid]
    return mid;
} // end sortFirstMiddleLast

int partition(int array[], int first, int last){ 
    // Choose pivot using median of three selection

    int pivotIndex = sortFirstMiddleLast(array, first, last);
    // Reposition pivot so it is last in the array
    std::swap(array[pivotIndex], array[last- 1]);
    moves += 3;

    pivotIndex = last - 1;
    int pivot = array[pivotIndex];
    // Determine the regions S1 and S2
    int indexFromLeft = first + 1;
    int indexFromRight = last - 2;
    bool done = false;
    while(!done){
    // Locate first entry on left that is >= pivot
        while(++comps && array[indexFromLeft] < pivot)
            indexFromLeft = indexFromLeft + 1;

        // Locate first entry on right that is <= pivot
        while(++comps && array[indexFromRight] > pivot){
            indexFromRight = indexFromRight - 1;
        }

        if(indexFromLeft < indexFromRight){
            std::swap(array[indexFromLeft], array[indexFromRight]);
            moves += 3;
            indexFromLeft = indexFromLeft + 1;
            indexFromRight = indexFromRight - 1;
        }
        else{
            done = true;
        } 
    } // end while
// Place pivot in proper position between S1 and S2, and mark its new location
    std::swap(array[pivotIndex], array[indexFromLeft]);
    moves += 3;
    pivotIndex = indexFromLeft;
    return pivotIndex;
} // end partition

void quickSort(int array[], int first, int last){
    int sz = last - first + 1;
    if(sz < MIN_SIZE)
        Insertion(array+first, sz);
    else{
    // Create the partition: S1| Pivot| S2
    int pivotIndex = partition(array, first, last);
    // Sort subarrays S1 and S2
    quickSort(array, first, pivotIndex - 1);
    quickSort(array, pivotIndex + 1, last);
    } // end if
} // end quickSort

/* ------------------------ Assignment 5 Heap ------------------------ */
void heapCreate(int items[], int itemCount){
    //Rebuild the heap starting from the last non-leaf node
    //Recall the index of the first leaf is n/2
    for(int index = ((itemCount/2)-1); index >= 0; index--){
        heapRebuild(index, items, itemCount);
    }
} //end heapCreate

//Make heap
void heapRebuild(int root, int items[], int itemCount){

    int largerChildIndex = 2 * root + 1; //assume left larger 

    //if root is not leaf
    if(largerChildIndex < itemCount){

        int rightChildIndex = 2 * root + 2; //right index 

        //root has right child
        if(rightChildIndex < itemCount){

            comps++;

            //determine larger child
            if(items[rightChildIndex] > items[largerChildIndex]){
                largerChildIndex = rightChildIndex;
            }
        }

        comps++;

        if(items[root] < items[largerChildIndex]){

            std::swap(items[root], items[largerChildIndex]);
            moves += 3;

            heapRebuild(largerChildIndex, items, itemCount);
        }
    }
}

//heap sort
void heapSort(int anArray[], int n){
    int heapSize = n;

    heapCreate(anArray, heapSize);

    while(heapSize > 1){

        //swap first and last
        std::swap(anArray[0], anArray[heapSize - 1]);
        moves += 3;
        heapSize--;

        //rebuild heap
        heapRebuild(0, anArray, heapSize);
        
    }
}