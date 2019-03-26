//
//  main.cpp
//  Project4
//
//  Created by Samritha Nagesh on 11/2/18.
//  Copyright © 2018 Samritha Nagesh. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int divide(string a[], int n, string divider);

int main()
{
    string h[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(lookup(h, 7, "eleni") == 5);
    assert(lookup(h, 7, "ed") == 2);
    assert(lookup(h, 2, "ed") == -1);
    assert(positionOfMax(h, 7) == 3);
    
    string g[4] = { "greg", "gavin", "fiona", "kevin" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "greg?" && g[3] == "kevin?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "fiona?" && g[3] == "gavin?");
    
    string e[4] = { "ed", "xavier", "", "eleni" };
    assert(subsequence(h, 7, e, 4) == 2);
    
    string d[5] = { "gavin", "gavin", "gavin", "xavier", "xavier" };
    assert(countRuns(d, 5) == 2);
    
    string f[3] = { "fiona", "ed", "john" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "john" && f[2] == "fiona");
    
    assert(divide(h, 7, "fiona") == 3);
    
    cerr << "All tests succeeded" << endl;

}
//Append value to the end of each of the n elements of the array and return n
int appendToAll(string a[], int n, string value){
    //For all functions, return -1 if n is negative
    if(n < 0){
        return -1;
    }
    for(int i=0; i<n; i++){
        a[i] += value;
    }
    return n;
}
//Return the position of a string in the array that is equal to target
int lookup(const string a[], int n, string target){
    if(n <= 0){
        return -1;
    }
    for(int i=0; i<n; i++){
        if(a[i] == target) //if element equals target, return its position
            return i;
    }
    return -1;
}
//Return the position of a string in the array such that that string is >= every string in the array.
int positionOfMax(const string a[], int n){
    if(n <= 0){
        return -1;
    }
    int maxPos = 0;
    for(int i=1; i<n; i++){
        if(a[i] > a[maxPos]){
            maxPos = i; //new largest string
        }    }
    return maxPos;
}
//Eliminate the item at position pos by copying all elements after it one place to the left.
int rotateLeft(string a[], int n, int pos){
    if(n <= 0 || pos < 0 || pos >= n){
        return -1;
    }
    string item = a[pos];
    for(int i=pos; i<n-1; i++){
        a[pos] = a[pos+1]; //shift to the left
    }
    a[n-1] = item; //append item to last index of array
    return pos;
}
//Return the number of sequences of one or more consecutive identical items in a.
int countRuns(const string a[], int n){
    if(n < 0){
        return -1;
    }
    int runs = 1;
    for(int i = 0; i<n-1; i++){
        if(a[i] != a[i+1]){
            runs++; //add to run if consecutive run breaks
        }
    }
    return runs;
}
//Reverse the order of the elements of the array and return n.
int flip(string a[], int n){
    if(n < 0){
        return -1;
    }
    int start = 0;
    int end = n-1;
    //swap elements from second half with first half until all have been swapped
    for(int i=0; i<n/2; i++){
        string temp = a[start];
        a[start] = a[end];
        a[end] = temp;
        start++;
        end--;
    }
    return n;
}
//Return the position of the first corresponding elements of a1 and a2 that are not equal.
int differ(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 < 0 || n2 < 0){
        return -1;
    }
    int min = 0;
    //find smaller array
    if(n1 <= n2){
        min = n1;
    }
    else
        min = n2;
    //parse through smaller array and find first different element
    for(int i=0; i<min; i++){
        if(!(a1[i] == a2[i])){
            return i;
        }
    }
    return min;
}
//If all n2 elements of a2 appear in a1, consecutively and in the same order, then return the position in a1 where that subsequence begins.
int subsequence(const string a1[], int n1, const string a2[], int n2)
{
  //  int num;
    //Check conditions first
    if(n2 == 0)
        return 0;
    else if (n2 > n1 || n1 <= 0 || n2 < 0)
        return -1;
    
    //starting points for each array
    int i1 = 0;
    int i2 = 0;
    int nums = 0;

    for(i1 = 0; i1 < n1; i1++){
        if(a1[i1] == a2[0]){
            nums = 0;
            for(i2 = 0; i2 < n2; i2++){
                if(a2[i2] != a1[i1+i2]) //if elements are not equal then break
                    break;
                else
                    nums++;
            }
            if(nums == n2)
                return i1;
        }
    }

    return -1;
}
//Return the smallest position in a1 of an element that is equal to any of the n2 elements in a2
int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 == 0 && n2 == 0){
        return 0;
    }
    else if(n1 <= 0 || n2 <= 0){
        return -1;
    }
    
    for(int i=0; i<n1; i++){
        for(int j=0; j<n2; j++){
            if(a1[i] == a2[j]){
                return i; //return the first position at which an element in a1 is equal to a2
            }
        }
    }
    return -1;
}
//Rearrange the elements of the array so that all the elements whose value is < divider come before all the other elements, and all the elements whose value is > divider come after all the other elements
int divide(string a[], int n, string divider){
    if(n < 0){
        return -1;
    }
    string temp[100] = {};
    int frontIndex = 0;
    int backIndex = n-1;
    for(int i=0; i<n; i++){
        //if this element is < divider, add it to the first half
        if(a[i] < divider){
            temp[frontIndex] = a[i];
            frontIndex++;
        }
        //if this element is > divider, add it to second half
        else if (a[i] > divider){
            temp[backIndex] = a[i];
            backIndex--;
        }
        //if a contains divider, add divider to the middle of the array
        if(a[i] == divider){
            temp[frontIndex] = a[i];
            frontIndex++;
        }
    }
    //add temp elements to a
    for(int i=0; i<n; i++){
        a[i] = temp[i];
    }
    //find the first instance when a[i] is not < divider
    for(int i=0; i<n; i++){
        if(!(a[i] < divider)){
            return i;
        }
    }
    return n;
}


