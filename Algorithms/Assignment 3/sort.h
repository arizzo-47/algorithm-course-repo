//Anthony Rizzo - February 14, 2019
//Homework 3
//Header File

#ifndef SORT_H
#define SORT_H

extern int moves;  //moves made
extern int comps;  //comparisons made

const int MAX_SIZE = 1000;
static const int MIN_SIZE = 10;

void initAvg(int array[], int size);

void initBest(int array[], int size);

void initWorst(int array[], int size);

void copyAvg(int origArr[], const int copyArray[], int size);

int IndexOfLargest(const int array[], int size);

void Selection(int array[], int size);

void Bubble(int array[], int size);

void Insertion(int array[], int size);

void Merge(int array[], int first, int mid, int last);

void mergeSort(int array[], int first, int last);

void order(int array[], int i, int j);

int sortFirstMiddleLast(int array[], int first, int last);

int partition(int array[], int first, int last);

void quickSort(int array[], int first, int last);

#endif