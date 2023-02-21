/*
 * EECS 368 Extra Credit Lab
 *
 *  Created on: Feb 8, 2023
 *      Author: n892s973
 *      Description: Matches 5 Departments with 5 Programmers
                    based on preference.
 */
#include <iostream>
#include <fstream>

using namespace std;

//MATCHES signifies the number of departments and also programmers separately
const int MATCHES = 5;

//progPrefCur checks to see if the programmer prefers the currently assigned department,
//if they do, return true, if not, return false
bool progPrefCur(int pref[2*MATCHES][MATCHES],int pIndex,int dep,int curDep)
{
    for(int i = 0; i < MATCHES; i++)
    {
        if(pref[pIndex][i] == curDep)
        {
            return true;
        }
        if(pref[pIndex][i] == dep)
        {
            return false;
        }
    }
    //if there is an error, returns false
    return false;
}

void thePreferences(int pref[2*MATCHES][MATCHES])
{  
    int prog[MATCHES] = {-1,-1,-1,-1,-1};
    //keeps track of departments that have matches/not
    bool takenDepartment[MATCHES] = {};
    int freeDep = 5;

    while(freeDep > 0)
    {
        int d;
        //looks for a department to match
        for(d = 0; d < MATCHES; d++)
        {
            if(takenDepartment[d] == false)
            {
                break;
            }
        }
        //search through department matches
        for(int a = 0; a < MATCHES && takenDepartment[d] == false; a++)
        {
            //progPref is initialized as the currently preferred programmer
            int progPref = pref[d][a];
            //assign this programmer to department if no one else is assigned
            if(prog[progPref - 1]== -1)
            {
                prog[progPref - 1]= d;
                takenDepartment[d]= true;
                freeDep--;
            }
            else
            {
                //the currently assigned department
                int curDep = prog[progPref - 1];
                //checks programmer preferences and acts accordingly
                if(progPrefCur(pref, progPref + 4, d + 1, curDep+1) == false)
                {
                    prog[progPref - 1]= d;
                    takenDepartment[d]= true;
                    takenDepartment[curDep]=false;
                }
            }
        }
    }
    //prints final matching solution
    for (int i = 0; i < MATCHES; i++)
    {
        for(int j = 0; j < MATCHES; j++)
        {
            if(i == prog[j])
            {
                cout << "Department #" << i + 1 << " will get Programmer " << j + 1 << "\n"; 
            }
        }
    }
}
int main()
{
    //initializes pref values as -1
    int pref[2*MATCHES][MATCHES] = {-1};
    
    //gathers file input from file.txt and puts it into pref array
    ifstream inFile;
    inFile.open("file.txt");
    
    if(inFile.fail())
    {
        cout << "File opening failed. \n"; 
    }
    else
    {
        while(inFile)
        {
            for(int i = 0; i < MATCHES; i++)
            {
                for(int j = 0; j < MATCHES; j++)
                {
                    inFile >> pref[j][i];                    
                }
            }
            for(int i = 0; i < MATCHES; i++)
            {
                for(int j = MATCHES; j < MATCHES*2; j++)
                {
                    inFile >> pref[j][i];             
                }
            }
        }
    }
    inFile.close();

    thePreferences(pref);
    return 0;
}