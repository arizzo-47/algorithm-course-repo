//Anthony Rizzo - February 14, 2019
//Homework 3
//Implementation

#include <stdlib.h>
#include <iostream>
#include <fstream>  
#include <stdexcept>
#include "sort.h"
#define SIZE 1000

int main(){
    srand(time(NULL));

    //Write to text file
    std::ofstream outf;

    outf.open("sort.txt");
    if(outf.fail()){
        std::cerr << "Error: Could not open output file\n";
        exit(1);
    }

    int Best[SIZE];
    int Worst[SIZE];
    int Avg[SIZE];
    int AvgCopy[SIZE];

    outf << "Condition,Moves,Comparisons" << '\n';  //txt file header

    // ------------------ Selection ------------------
 
    initBest(Best, SIZE);
    initWorst(Worst, SIZE);
    initAvg(Avg, SIZE);
    copyAvg(Avg, AvgCopy, SIZE);    //maintain random values
    
    moves = comps = 0;
    Selection(Best, SIZE);   //Sort call
    outf << "Selection Best:," << moves << "," << comps << '\n';

    moves = comps = 0;
    Selection(Worst, SIZE);   //Sort call
    outf << "Selection Worst:," << moves << "," << comps << '\n';

    moves = comps = 0;
    Selection(Avg, SIZE);   //Sort call
    outf << "Selection Average:," << moves << "," << comps << '\n';
    

    // ------------------ Bubble ------------------

    initBest(Best, SIZE);
    initWorst(Worst, SIZE);
    copyAvg(Avg, AvgCopy, SIZE);    //maintain random values 

    moves = comps = 0;
    Bubble(Best, SIZE);  //Sort call
    outf << "Bubble Best:," << moves << "," << comps << '\n';

    moves = comps = 0;
    Bubble(Worst, SIZE);  //Sort call
    outf << "Bubble Worst:," << moves << "," << comps << '\n';

    moves = comps = 0;
    Bubble(Avg, SIZE);  //Sort call
    outf << "Bubble Average:," << moves << "," << comps << '\n';

    
    // ------------------ Insertion ------------------
    initBest(Best, SIZE);
    initWorst(Worst, SIZE);
    copyAvg(Avg, AvgCopy, SIZE);    //maintain random values

    moves = comps = 0; 
    Insertion(Best, SIZE);   //Sort call
    outf << "Insertion Best:," << moves << "," << comps << '\n';

    moves = comps = 0;
    Insertion(Worst, SIZE);   //Sort call
    outf << "Insertion Worst:," << moves << "," << comps << '\n';

    moves = comps = 0;
    Insertion(Avg, SIZE);   //Sort call
    outf << "Insertion Average:," << moves << "," << comps << '\n';
    
    
    // ------------------ MergeSort ------------------
    initBest(Best, SIZE);
    initWorst(Worst, SIZE);
    copyAvg(Avg, AvgCopy, SIZE);    //maintain random values 

    moves = comps = 0;
    mergeSort(Best, 0, SIZE - 1);    //Sort call
    outf << "Merge Best:," << moves << "," << comps << '\n';

    moves = comps = 0;
    mergeSort(Worst, 0, SIZE - 1);    //Sort call
    outf << "Merge Worst:," << moves << "," << comps << '\n';

    moves = comps = 0;
    mergeSort(Avg, 0, SIZE - 1);    //Sort call
    outf << "Merge Average:," << moves << "," << comps << '\n';
    
    //  ------------------QuickSort ------------------
    initBest(Best, SIZE);
    initWorst(Worst, SIZE);
    copyAvg(Avg, AvgCopy, SIZE);    //maintain random values 

    moves = comps = 0;
    quickSort(Best, 0, SIZE - 1);    //Sort call
    outf << "Quick Best:," << moves << "," << comps << '\n';

    moves = comps = 0;
    quickSort(Worst, 0, SIZE - 1);    //Sort call
    outf << "Quick Worst:," << moves << "," << comps << '\n';

    moves = comps = 0;
    quickSort(Avg, 0, SIZE - 1);    //Sort call
    outf << "Quick Average:," << moves << "," << comps << '\n';

    outf.close(); //close file

    return 0;
}
