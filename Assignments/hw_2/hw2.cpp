#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <fstream>
using namespace std;


class WordLadder{
    private:
        list<string> D;
        list<string> tempD;
        
    //Helper Functions
    bool isOneLetterDifferent(string a, string b){
        int cnt = 0;
        for(unsigned int i = 0; i < a.size(); i++){
            if(a.at(i) != b.at(i)){
                cnt++;
            }
        }
        if((cnt == 0) || (cnt >= 2)){
            return false;
        }
        return true;
    }
    
    public:
        WordLadder(const string &listFile);
        
        void outputLadder(const string &start, const string &end);
};

WordLadder::WordLadder(const string &listFile){
    //String variable to be used to push dictionary words onto queue
    string line;
    ifstream myfile (listFile.c_str());
    if(myfile.is_open()){
        while(getline(myfile,line)){
            //Enqueues dictionary words onto Queue
            D.push_back(line);
        }
        myfile.close();
    }
}

void WordLadder::outputLadder(const string &start, const string&end){
    string startW = start.c_str();
    string endW = end.c_str();
    
    if(startW == endW){
        cout << startW << endl;
        return;
    }
    //list<string>::iterator it;
    
    //cout << "StartW: " << startW << endl;
    //cout << "EndW: " << endW << endl;
    ////Algorithm for outputting ladder
    //for(it = D.begin(); it != D.end(); ++it){
    //    cout << *it << " ";
    //}
    //cout << endl;
    
    //Create a stack of strings
    stack<string> myStack;
    //Push the start word on this stack
    myStack.push(startW);
    //Create a queue of stacks
    queue<stack<string> > myQ;
    //Enqueue this stack
    myQ.push(myStack);

    
    
    //While the queue is not empty
    while(!myQ.empty()){
        cout << "-" << endl;
        stack<string> current = myQ.front();
        myQ.pop();
        //cout << "=========OUTPUT CURRENT==========" << endl;
        stack<string> temp = current;
        //while(!temp.empty()){
        //    cout << temp.top() << endl;
        //    temp.pop();
        //}
        //cout << " ==================================" << endl;
        list<string>::iterator it;
        //For each word in the dictionary
        for(it = D.begin(); it != D.end(); ++it){
            //cout << "Current word in dictionary: " << *it << endl;
            //cout << "Current top word on stack: " << current.top() << endl;
            //If a word is one letter different (in any position)
            //than the top string of the front stack
            if(isOneLetterDifferent(current.top(), *it)){
                //for loop for deleting words from the dict
                //that are one letter away
                tempD.push_front(*it);
                //cout << "Current top word: " << current.top() << endl;
                //cout << "Current word in dict: " << *it << endl;
                //cout << "WORDS ARE ONE LETTER DIFFERENT!!!!" << endl;
                //cout << "End word: " << endW << endl;
                //If this word is the end word
                if(*it == endW){
                    //cout << "Dict word same as end word!!!!!!!!!!!!!" << endl;
                    //You are done. The front stack plus this word is
                    //your word ladder. Don't forget to output this word ladder.
                    //cout << "**Size of current**: " << current.size() << endl;
                    current.push(*it);
                    //cout << "**Size of current after pushing endW**: " << current.size() << endl;
                    //cout << "Top of CurrentStack: " << current.top() << endl;
                    //cout << "=========OUTPUT CURRENT2==========" << endl;
                    stack<string> temp2 = current;
                    //while(!temp2.empty()){
                    //    cout << temp2.top() << endl;
                    //    temp2.pop();
                   // }
                    //cout << " ==================================" << endl;
                    stack<string> finalStack;
                    //Reverses the current stack in order from
                    //first word to last word
                    //cout << "Original top of stack: " << myQ.back().top() << endl;
                    //cout << "current.size(): " << current.size() << endl;
                    //cout << "===FOR Loop for reversing Current Stack===" << endl;
                    unsigned int tempCurrSize = current.size();
                    for(unsigned int i = 0; i < tempCurrSize; i++){
                        //cout << "Top of Current: " << current.top() << endl;
                        finalStack.push(current.top());
                        //cout << "Top of finalStack: " << finalStack.top() << endl;
                        current.pop();
                        //cout << "Size of current in LOOP: " << current.size() << endl;
                        //cout << "Size of finalstack: " << finalStack.size() << endl;
                    }
                    //cout << "New top of stack: " << finalStack.top() << endl;
                    //cout << "Size of finalStack: " << finalStack.size() << endl;
                    //cout << startW << " ";
                    while(!finalStack.empty()){
                        cout << finalStack.top() << " ";
                        finalStack.pop();
                    }
                    cout << endl;
                    //cout << *it << endl;
                    //cout << "SIZE OF DICTIONARY: " << D.size() << endl;
                    return;
                }
                //Make a copy of the front stack
                stack<string> copy = current;
                //Push the found word onto the copy
                //cout << "Initial size of copy: " << copy.size() << endl;
                copy.push(*it);
                //cout << "Final size of copy: " << copy.size() << endl;
                //cout << "Top of copy: " << copy.top() << endl;
                //Enqueue the copy
                //cout << "Initial size of queue: " << myQ.size() << endl;
                myQ.push(copy);
                //cout << "Final size of queue: " << myQ.size() << endl;
                //if(myQ.size() != 0){
                //    cout << "Top last stack of Queue: " << myQ.back().top() << endl;
                //}
                cout << endl;
            }
        }
        //Removes all words that are already on stacks off the Dictionary List
        list<string>::iterator tempIt;
        for(tempIt = tempD.begin(); tempIt != tempD.end(); ++tempIt){
            D.remove(*tempIt);
        }
        tempD.clear();
    }
}

int main(int argc, char* argv[]){
    
    if(argc != 4){
        cout << "Error: Incorrect number of arguments" << endl;
        return 0;
    }
    
    string startW;
    string endW;

    startW = argv[1];
    endW = argv[2];
    
    WordLadder Dict (argv[3]);
    Dict.outputLadder(startW, endW);

     

    /*Calling this function will take in start word and end word
     * and output the correct word ladder
     * */
    //outputLadder(start, end);

    return 0;
}
