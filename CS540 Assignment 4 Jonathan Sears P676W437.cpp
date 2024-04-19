// CS540 Assignment 4 Jonathan Sears P676W437.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
using namespace std;

void LRUAlgorithm(int pages[], int frameNumber, int size) //Does the LRU Algorithm
{
    unordered_set<int> pageList;
    unordered_map<int, int> position;
    int faults = 0;
    int hits = 0;
    for (int i = 0; i < size; i++)
    {
        if (pageList.size() < size)
        {
            if (pageList.find(pages[i]) == pageList.end())
            {
                pageList.insert(pages[i]);
                faults++;
            }
            position[pages[i]] = i;
        }
        else
        {
            if (pageList.find(pages[i]) == pageList.end())
            {
                int lru = INT_MAX, val;
                for (auto it = pageList.begin(); it != pageList.end(); it++)
                {
                    if (position[*it] < lru)
                    {
                        lru = position[*it];
                        val = *it;
                    }

                }
                pageList.erase(val);
                pageList.insert(pages[i]);
                faults++;
            }
            position[pages[i]] = i;
        }
      
    }
    cout << "Number of Page Faults: " << faults << endl;
}

void OptimalAlgorithm(int pages[], int frameNumber, int size) //Does the Optimal Algorithm
{
    int newPages[12];
    memset(newPages, -1, sizeof(newPages));

    int hit = 0;
    for (int i = 0; i < size; i++) //loops through looking if the page is found in newPages
    {
        bool found = false;
        for (int j = 0; j < frameNumber; j++)
        {
            if (newPages[j] == pages[i]) 
            {
                hit++;
                found = true;
                break;
            }
        }

        if (found) //if the value is found, continue the function
            continue;

        bool emptyFrame = false; //if it is not an empty frame, loop through until an empty frame is found
        for (int j = 0; j < size; j++)
        {
            if (newPages[j] == -1) 
            {
                newPages[j] = pages[i];
                emptyFrame = true;
                break;
            }
        }

        if (emptyFrame) //once an empty frame is found, continue
            continue;


        int farthest = -1, replaceIndex = -1;
        for (int j = 0; j < size; j++) 
        {
            int k;
            for (k = i + 1; k < size; k++) 
            {
                if (newPages[j] == pages[k]) 
                {
                    if (k > farthest) 
                    {
                        farthest = k;
                        replaceIndex = j;
                    }
                    break;
                }
            }
            if (k == size) 
            {
                replaceIndex = j;
                break;
            }
        }
        newPages[replaceIndex] = pages[i];
    }
    
    cout << "Number of Pages Faults: " << size - hit << endl;
}

void FIFOAlgorithm(int pages[], int frameNumber, int size) //Does the FIFO Algorithm
{
    queue<int> pageQueue;
    unordered_set<int> pageSet;
    int faults = 0;

    for (int i = 0; i < size; i++) {
        if (pageSet.size() < frameNumber) 
        {
            if (pageSet.find(pages[i]) == pageSet.end()) 
            {
                pageSet.insert(pages[i]);
                faults++;
                pageQueue.push(pages[i]);
            }
        }
        else if (pageSet.find(pages[i]) == pageSet.end()) 
        {
            int val = pageQueue.front();
            pageQueue.pop();
            pageSet.erase(val);
            pageSet.insert(pages[i]);
            pageQueue.push(pages[i]);
            faults++;
        }
    }

    cout << "Number of Page Faults: " << faults << endl;

}


int main()
{
    cout << "Input Page Reference String (Maximum 12 inputs): "; //takes in user input for what the page reference string is
    int input;
    int page[12];
    for (int i = 0; i < 12; i++)
    {
        cin >> input;
        page[i] = input;
    }
    int size = sizeof(page) / sizeof(page[0]);
    cout << endl << "Input Number of Frames: "; //takes in the user input for what the max number of frames is
    cin >> input;
    int frameNumber = input;
   
    FIFOAlgorithm(page, frameNumber, size);
    OptimalAlgorithm(page, frameNumber, size); 
    LRUAlgorithm(page, frameNumber, size);

}
