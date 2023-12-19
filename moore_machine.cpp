#include <iostream>
#include <fstream>
#include <string>

using namespace std;
ifstream fin("input.txt");

struct States
{
    string output;
} state[100];

struct Transitions
{
    int sourceState;
    int destinationState;
    char info;
} transition[100];

int main()
{
    int numOfStates;
    int numOfTransitions;
    int initialState;
    int numOfFinalStates;
    int finalState[100];
    int numOfInputStrings;
    string inputString;
    int path[100];
    int pathLength;
    int i, j, stringIndx;

    fin >> numOfStates >> numOfTransitions;
    for (i = 0; i < numOfStates; ++i)
        fin >> state[i].output;
    for (i = 0; i < numOfTransitions; ++i)
        fin >> transition[i].sourceState >> transition[i].destinationState >> transition[i].info;
    fin >> initialState;
    fin >> numOfFinalStates;
    for (i = 0; i < numOfFinalStates; ++i)
        fin >> finalState[i];
    fin >> numOfInputStrings;

    for (i = 0; i < numOfInputStrings; ++i)
    {
        bool accepted = false;
        bool foundTransition; // used for stopping the inputString parsing for efficiency :_)
        int presentState = initialState;
        fin >> inputString;
        for (stringIndx = 0; stringIndx < inputString.size(); ++stringIndx)
        {
            foundTransition = false;
            for (j = 0; j < numOfTransitions && !foundTransition; ++j)
                if (presentState == transition[j].sourceState && transition[j].info == inputString[stringIndx])
                {
                    presentState = transition[j].destinationState;
                    foundTransition = true;
                }
            if (!foundTransition) // end the analysis of the input if a next state doesn't exist
                break;
        }
        if (stringIndx == inputString.size()) // if the inputString is valid
            for (j = 0; j < numOfFinalStates; ++j)
            {
                if (presentState == finalState[j]) // check if the ending state is a final state
                {
                    accepted = true;
                    break;
                }
            }
        if (accepted)
        {
            cout << "\nDA\n";
            pathLength = 0;
            path[pathLength++] = initialState;
            presentState = initialState;
            cout << state[presentState].output;
            // this for is used for printing the outputs of the states while building the path
            for (stringIndx = 0; stringIndx < inputString.size(); ++stringIndx)
            {
                for (j = 0; j < numOfTransitions; ++j)
                    if (presentState == transition[j].sourceState && transition[j].info == inputString[stringIndx])
                    {
                        presentState = transition[j].destinationState;
                        path[pathLength++] = transition[j].destinationState;
                        break;
                    }
                cout << state[presentState].output;
            }

            cout << "\nTraseu: ";
            for (j = 0; j < pathLength; ++j) // printing the path
                cout << path[j] << " ";
        }
        else
            cout << "\nNU";
    }
}