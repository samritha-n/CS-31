//
//  main.cpp
//  Project3
//
//  Created by Samritha Nagesh on 10/23/18.
//  Copyright © 2018 Samritha Nagesh. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
#include <stdlib.h>

using namespace std;

bool hasProperSyntax(string pollData);
int tallySeats(string pollData, char party, int& seatTally);

int main() {
    
    assert(hasProperSyntax("CT5D,NY9R17D1I,VT,ne3r00D"));
    assert(!hasProperSyntax("ZT5D,NY9R17D1I,VT,ne3r00D"));
    int seats;
    seats = -999;    // so we can detect whether tallySeats sets seats
    assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'd', seats) == 0  &&  seats == 22);
    seats = -999;    // so we can detect whether tallySeats sets seats
    assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", '%', seats) == 2  &&  seats == -999);

    cerr << "All tests succeeded" << endl;
}
//Check if stateCode passed in matches an uppercase state code from the list
bool isValidStateCode(string stateCode){
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
    "LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
    "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}
//Check if the string passed in is a valid party result
bool checkPartyResults(string result, int index){
    //Check for tallys
    int numberOfDigits = 0;
    while (isdigit(result[index])){
        index++;
        numberOfDigits++;
    }
    if(index == 2)
        return true;
    if(index > 2 && (numberOfDigits == 1 || numberOfDigits == 2)){
        //Check for party code
        if(isalpha(result[index]))
        {
            //If more than one party results
            if((index < result.size()-1) && (isdigit(result[index+1])))
            {
                return checkPartyResults(result, index+1); //check for more party results
            }
            else
            {
                return true; //return true if only one party result
            }
        }
    }
    return false;
}
//check if string passed in is valid state forecast
bool isStateForecast(string forecast){
    //Convert string to uppercase characters
    string stateCode = forecast.substr(0,2);
    stateCode[0] = toupper(stateCode[0]);
    stateCode[1] = toupper(stateCode[1]);
    
    //Check if valid state code
    if(isValidStateCode(stateCode)){
        int index = 2;
        //Check for digits (party result)
        return checkPartyResults(forecast, index);
    }
    return false;
}
//Check if all forecasts are correctly formatted state forecasts
bool hasMultipleForecasts(string pollData){
    string forecast1 = pollData.substr(0, pollData.find(","));
    if (isStateForecast(forecast1) && (pollData.find(",") != string::npos)){
        pollData = pollData.substr(pollData.find(",")+1, pollData.size());
        return hasMultipleForecasts(pollData);
    }
    else
        return isStateForecast(forecast1);
}
//check if string has characters that are not alphabets, digits, or commas
int hasOnlyAlphaNum(string str){
    for(int i=0; i<str.size(); i++){
        if(!isalpha(str[i]) && !isdigit(str[i])){
            if(str[i] != ','){
                return false;
            }
        }

    }
    return true;
}
//check if pollData has proper syntax
bool hasProperSyntax(string pollData){
    //empty string is valid pollData
    if (pollData == ""){
        return true;
    }
    //if string contains characters other than alphabets, digits, and commas
    else if (!hasOnlyAlphaNum(pollData)){
        return false;
    }
    else if (pollData[0] == ',' || pollData[pollData.size()-1] == ','){
        return false;
    }
    //if string has multiple state forecasts
    else if(pollData.find(",") != string::npos){
          return hasMultipleForecasts(pollData);
    }
    //if string has only one state forecast
    else{
        return isStateForecast(pollData);
    }
}
//Count number of votes for party in the given pollData string
int tallySeats(string pollData, char party, int& seatTally){
    party = toupper(party);
    //check if pollData has proper syntax
    if (!hasProperSyntax(pollData)){
        return 1;
    }
    //check if party is an alphabet
    else if (!isalpha(party)){
        return 2;
    }
    else{
        seatTally = 0;
        for(int index = 0; index < pollData.size();){
            //Parse through alphabets and commas
            while (isalpha(pollData[index]) || pollData[index] == ','){
                index++;
            }
            //add characters to string of votes
            string votes = "";
            while(isdigit(pollData[index])){
                votes += pollData[index];
                index++;
            }
            if(isalpha(pollData[index])){
                pollData[index] = toupper(pollData[index]); //if party matches alphabet after votes
                if(pollData[index] == party){
                    seatTally += stoi(votes); //convert string to integer
                }
                index++;
            }
        }
    }
    return 0;
}

