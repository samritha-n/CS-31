//
//  rental.cpp
//  rental
//
//  Created by Samritha Nagesh on 10/10/18.
//  Copyright © 2018 Samritha Nagesh. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

int main() {
    //Gather Data and Check Valid Input
    cout << "Odometer at start: ";
    int startMiles;
    cin >> startMiles;
    if(startMiles < 0)
    {
        cout << "---" << endl;
        cout << "The starting odometer reading must be nonnegative." << endl;
        return 1;
    }
    
    cout << "Odometer at end: ";
    int endMiles;
    cin >> endMiles;
    if(endMiles <= startMiles)
    {
        cout << "---" << endl;
        cout << "The final odometer reading must be at least as large as the starting reading." << endl;
        return 1;
    }
    
    cout << "Rental days: ";
    int rentalDays;
    cin >> rentalDays;
    cin.ignore(10000,'\n');
    if(rentalDays <= 0)
    {
        cout << "---" << endl;
        cout << "The number of rental days must be positive." << endl;
        return 1;
    }
    
    cout << "Customer name: ";
    string name;
    getline(cin, name);
    if(name == "")
    {
        cout << "---" << endl;
        cout << "You must enter a customer name." << endl;
        return 1;
    }
    
    cout << "Luxury car? (y/n): ";
    string luxury;
    getline(cin, luxury);
    if (luxury != "y" && luxury != "n")
    {
        cout << "---" << endl;
        cout << "You must enter y or n." << endl;
        return 1;
    }
    
    cout << "Month (1=Jan, 2=Feb, etc.): ";
    int month;
    cin >> month;
    if(month < 1 || month > 12)
    {
        cout << "---" << endl;
        cout << "The month number must be in the range 1 through 12." << endl;
        return 1;
    }
    
    cout << "---" << endl;
    
    cout.setf(ios::fixed);
    cout.precision(2);
    
    
    //Calculate Rental Charges
    double rentalCharge;
    int milesDriven = endMiles - startMiles;
    //Day Charge for Luxury/Non-Luxury
    if(luxury == "n")
    {
        rentalCharge = 33.00 * rentalDays;
    }
    else
    {
        rentalCharge = 61.00 * rentalDays;
    }
    //Per Mile Charge
    //Less than 100 miles driven
    if(milesDriven <= 100)
    {
        rentalCharge = rentalCharge + (0.27 * milesDriven);
    }
    else
    {
        //up to 400 miles
        int remainingMiles = milesDriven - 100;
        if(remainingMiles <= 300)
        {
            //Winter Months - calls the function checkWinter(), which calculates the cost for 300 miles driven in a certain month
            if(month <= 3 || month == 12)
            {
                //charge = first 100 miles charge + 0.27 for remaining miles less than 300
                rentalCharge = rentalCharge + 27.00 + 0.27*(remainingMiles);
            }
            else{ //Other months
                rentalCharge = rentalCharge + 27.00 + 0.21*(remainingMiles);
            }
        }
        //More than 400 miles
        else
        {
            remainingMiles = remainingMiles - 300;
            //Winter Months
            if(month <= 3 || month == 12)
            {
                //charge = first 100 miles charge + charge for 300 miles + charge for remaining miles over 400
                rentalCharge = rentalCharge + 27.00 + 0.27*(300) + 0.19*(remainingMiles);
            }
            else{ //Other months
                rentalCharge = rentalCharge + 27.00 + 0.21*(300) + 0.19*(remainingMiles);
            }
        }
    }
    
    cout << "The rental charge for " << name << " is $" << rentalCharge << endl;
    
}
