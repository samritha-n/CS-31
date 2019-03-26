//
//  main.cpp
//  Project6
//
//  Created by Samritha Nagesh on 11/20/18.
//  Copyright © 2018 Samritha Nagesh. All rights reserved.
//

#include <iostream>
using namespace std;

void removeS(char* msg)
{
    char* newMsg = msg;
    while(*msg != 0){
        if(*msg == 's' || *msg == 'S'){
            msg++;
        }
        else
        {
            *newMsg = *msg;
            *msg++;
            *newMsg++;
        }
    }
    *newMsg = 0;
    
}
int main()
{
    char msg[50] = "She'll be a massless princess.";
    removeS(msg);
    cout << msg;  // prints   he'll be a male prince.
}
