//  Created by Samritha Nagesh on 10/2/18.
//  Copyright © 2018 Samritha Nagesh. All rights reserved.
//
//Code for Project 1
//Report poll results
#include <iostream>
using namespace std;

int main()
{
    int numberSurveyed;
    int forNewsom;
    int forCox;
    
    cout << "How many registered voters were surveyed? ";
    cin >> numberSurveyed;
    cout << "How many of them say they will vote for Newsom? ";
    cin >> forNewsom;
    cout << "How many of them say they will vote for Cox? ";
    cin >> forCox;
    
    double pctNewsom = 100.0 * forNewsom / numberSurveyed;
    double pctCox = 100.0 * forCox / numberSurveyed;
    
    cout.setf(ios::fixed);
    cout.precision(1);
    
    cout << endl;
    cout << pctNewsom << "% say they will vote for Newsom." << endl;
    cout << pctCox <<"% say they will vote for Cox." << endl;
    
    if (forNewsom > forCox)
        cout << "Newsom is predicted to win the election." << endl;
    else
        cout << "Cox is predicted to win the election. " << endl;
}
