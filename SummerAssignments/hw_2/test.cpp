#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <fstream>
using namespace std;

bool isOneLetterDifferent(string a, string b){
    int cnt = 0;
    for(int i = 0; i < a.size(); i++){
        if(a.at(i) != b.at(i)){
            cnt++;
        }
    }
    if((cnt == 0) || (cnt >= 2)){
        return false;
    }
    return true;
}
                

int main(){
    
    string string1 = "style";
    string string2 = "stale";
    
    if(isOneLetterDifferent(string1,string2)){
        cout << "TRUE" << endl;
    }
    else{
        cout << "FALSE" << endl;
    }
    
    return 0;
}
