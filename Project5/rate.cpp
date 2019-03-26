//
//  main.cpp
//  Project5
//
//  Created by Samritha Nagesh on 11/8/18.
//  Copyright © 2018 Samritha Nagesh. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cassert>
#include <cstring>
#include <cctype>


const int MAX_WORD_LENGTH = 20;
const int MAX_DOC_LENGTH = 250;

int makeProper(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1],int separation[],int nPatterns);
void makeLowerCase(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1],int nPatterns);
void removeFromCollection(char word1[][MAX_WORD_LENGTH+1],char word2[][MAX_WORD_LENGTH+1], int separation[], int numPatterns, int row);
int removeDuplicates(char word1[][MAX_WORD_LENGTH+1],char word2[][MAX_WORD_LENGTH+1], int separation[], int numPatterns);

int rate(const char document[],const char word1[][MAX_WORD_LENGTH+1],const char word2[][MAX_WORD_LENGTH+1],const int separation[],int nPatterns);
void printDoc(const char document[][MAX_DOC_LENGTH+1],int size);

int main()
{
    const int TEST1_NRULES = 4;
    char test1w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "mad","deranged","nefarious","have"
    };
    char test1w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot","plot","mad"
    };
    int test1dist[TEST1_NRULES] = {
        1, 3, 0,           12
    };

    assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("**** 2018 ****",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0); //WORKS
    assert(rate("  That plot: NEFARIOUS!",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("deranged deranged robot deranged robot robot",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0); //WORKS

}
int makeProper(char word1[][MAX_WORD_LENGTH+1],char word2[][MAX_WORD_LENGTH+1],int separation[],int nPatterns){
    //Negative and 0 values for nPatterns not allowed
    int numPatterns = nPatterns;
    if((nPatterns) <= 1){
        return 0;
    }
    //Convert to lower-case
    makeLowerCase(word1, word2, nPatterns);
    for(int row = 0; row < numPatterns; row++){
        //Check for any empty c-strings
        if(strlen(word1[row]) < 1 || strlen(word2[row]) < 1){
            removeFromCollection(word1, word2,separation, numPatterns,row);
            numPatterns--;
            if(row > 0)
                row--;
        }
        //Check for negative
        if(separation[row] < 0){
            removeFromCollection(word1, word2,separation, numPatterns,row);
            if(row > 0)
                row--;
            numPatterns--;
        }
        //Check for non-letters
        for(int i=0; word1[row][i] != '\0'; i++){
            if(!isalpha(word1[row][i])){
                removeFromCollection(word1, word2,separation, numPatterns,row);
                if(row > 0)
                    row--;
                numPatterns--;
            }
        }
        for(int j=0; word2[row][j] != '\0'; j++){
            if(!isalpha(word2[row][j])){
                removeFromCollection(word1, word2,separation, numPatterns,row);
                if(row > 0)
                    row--;
                numPatterns--;
            }
        }
    }
    //Remove duplicates
    numPatterns = removeDuplicates(word1, word2, separation, numPatterns);
    //return number of patterns
    return numPatterns;
}
   
void makeLowerCase(char word1[][MAX_WORD_LENGTH+1],char word2[][MAX_WORD_LENGTH+1], int nPatterns){
    //Convert each character to lower-case
    for(int row=0; row<nPatterns;row++){
        for(int col = 0; col < MAX_WORD_LENGTH+1; col++){
            if(word1[row][col] != '\0'){
                word1[row][col] = tolower(word1[row][col]);
            }
            if(word2[row][col] != '\0'){
                word2[row][col] = tolower(word2[row][col]);
            }

        }
    }
}
void removeFromCollection(char word1[][MAX_WORD_LENGTH+1],char word2[][MAX_WORD_LENGTH+1], int separation[], int numPatterns, int row){
    //Move each word to the left
    for(int i = row; i < numPatterns-1; i++){
        strcpy(word1[i],word1[i+1]);
        strcpy(word2[i], word2[i+1]);
        separation[i] = separation[i+1];
    }
    //Empty string at end
    strcpy(word1[numPatterns-1],"");
    strcpy(word2[numPatterns-1],"");
}
int removeDuplicates(char word1[][MAX_WORD_LENGTH+1],char word2[][MAX_WORD_LENGTH+1], int separation[], int numPatterns){
    for(int row = 0; row < numPatterns; row++){
        for(int next = row + 1; next < numPatterns; next++){
            if(strcmp(word1[row], word1[next]) == 0){
                if(strcmp(word2[row], word2[next]) == 0){
                    //Remove the lower separation
                    if (separation[next] > separation[row]){
                        //Remove duplicate by adding it to end of array
                        removeFromCollection(word1,word2,separation,numPatterns,row);
                        row--;
                        numPatterns--;
                    }
                    else{
                        //Remove duplicate by adding it to end of array
                        removeFromCollection(word1,word2,separation,numPatterns,next);
                        next--;
                        numPatterns--;
                    }
                }
            }
            if(strcmp(word1[row], word2[next]) == 0){
                if(strcmp(word2[row], word1[next]) == 0){
                    if (separation[next] > separation[row]){
                        //Remove duplicate by adding it to end of array
                        removeFromCollection(word1,word2, separation, numPatterns, row);
                        row--;
                        numPatterns--;
                    }
                    else{
                        //Remove duplicate by adding it to end of array
                        removeFromCollection(word1,word2, separation, numPatterns, next);
                        next--;
                        numPatterns--;
                    }
                }
            }
        }
    }
//    for(int i=0; i<numPatterns; i++){
//        cerr << word1[i] << "+" << word2[i] << endl;
//    }
    return numPatterns;
}
int rate(const char document[],const char word1[][MAX_WORD_LENGTH+1],const char word2[][MAX_WORD_LENGTH+1],const int separation[],int nPatterns){
    if(nPatterns < 0){
        return 0;
    }
    int matches = 0;
    char copyDoc[MAX_DOC_LENGTH+1][MAX_DOC_LENGTH+1];
    int charCount = 0;
    int wordCount = 0;
    int newSepar[MAX_DOC_LENGTH+1];
 
    //Copy alphabetical and space characters only into copyDoc (2D Array)
    for(int i=0; document[i] != '\0'; i++){
        if(isalpha(document[i])){
            copyDoc[wordCount][charCount] = tolower(document[i]);
            charCount++;
            copyDoc[wordCount][charCount] = '\0';
        }
        else if (document[i] == ' '){
            wordCount++;
            charCount = 0;
            while(document[i+1] == ' '){
                i++;
            }
        }

    }
    //Copy separations to new, editable array
    for(int i=0; i< nPatterns;i++){
        newSepar[i] = separation[i];
    }
    //Check for pattern matches
    for(int p=0; p< wordCount+1; p++){
        for(int r=0; r < nPatterns; r++){
            if(strcmp(word1[r], copyDoc[p]) == 0 && newSepar[r] != -1){
                for(int d = 1; d <= newSepar[r]+1; d++){
                    if(p+d <= wordCount && strcmp(word2[r],copyDoc[p+d]) == 0){ //Check if word2 is within separation distance
                        matches++;
                        newSepar[r] = -1;
                    }
                }
            }
            else if(strcmp(word2[r], copyDoc[p]) == 0 && newSepar[r] != -1){
                for(int d = 1; d <= newSepar[r]+1; d++){
                    if(p+d <= wordCount && strcmp(word1[r],copyDoc[p+d]) == 0){
                        matches++;
                        newSepar[r] = -1;
                    }
                }
            }
        }
    }
    return matches;

}


