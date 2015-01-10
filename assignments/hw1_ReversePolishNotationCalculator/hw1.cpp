//Global variable of output statement. string output
//Multiple statements, that overwrite each other, only output at the end
//Figure out how to handle white space after a subtract sign
#include <iostream>
using namespace std;

class stack{
    public:
    virtual void push(int i) = 0;
    virtual int pop() = 0;
    virtual int peek() = 0;
    virtual bool isEmpty() = 0;
};

class ArrayStack : public stack{
    public:
        ArrayStack(){
            top = 0;
            max_size = 100;
            arr = new int[max_size];
        }
        
        void push(int i){
            if(top == max_size){
                return;
            }
            arr[top++] = i;
        }
        
        int pop(){
            if(top == 0){
                return -999;
            }
            int returnVal = arr[--top];
            arr[top] = 0;
            return returnVal;
        }
        
        int peek(){
            if(top == 0){
                return -999;
            }
            return arr[top - 1];
        }
        
        bool isEmpty(){
            if(top == 0){
                return true;
            }else{
                return false;
            }
        }
            
        
        ~ArrayStack(){
            delete[] arr;
            arr = NULL;
        }
        
        
    
    private:
        int * arr;
        int top;
        int max_size;
};

int main(){

    ArrayStack stack1;
    string input;
    int tokenError = 0;
    int paramError = 0;
    int operError = 0;
    int flag = 0;
    while(flag == 0){
        cout << "> ";
        
        //Gets input from user
        getline(cin, input);
        if(input == "^D"){
            flag = 1;
        }
        else{
/*==============================================================================
Checks if characters are valid, if not, error message appears
==============================================================================*/
            const int inputSize = input.size();
            //cout << "inputSize: " << inputSize << endl;
            for(unsigned int i = 0; i < input.size(); i++){
                int asciiVal = input.at(i);
                int val;
                //cout << "Current asciiVal: " << asciiVal << endl;
                //cout << "BEGINNING OF FOR LOOP" << endl << endl;
                if((asciiVal < 48 ||    //Character is not a number
                    asciiVal > 57) &&    //
                   (asciiVal != 43 &&   //Character is not "+"
                    asciiVal != 45 &&    //Character is not "-"
                    asciiVal != 42 &&    //Character is not "*"
                    asciiVal != 47 &&    //Character is not "/"
                    asciiVal != 37 &&    //Character is not "%"
                    asciiVal != 32)){    //Character is not white space
                    
                    tokenError = 1;
                }

/*==============================================================================
Handles Numbers (Positive)
==============================================================================*/

                //Checks if current character is a number
                else if(asciiVal >= 48 && asciiVal <= 57){
                     //cout << "Curr. Char  is #" << endl;
                     val = asciiVal - '0';
                     //cout << "Curr. Val = " << val << endl << endl;
                     if((i + 1) < input.size()){
                        int nextChar = input.at(i + 1);
                        if(nextChar >= 48 && nextChar <= 57){
                            //cout << "Next char is #" << endl;
                            val = ((asciiVal - '0') * 10) + (input.at(i + 1) - '0');
                            ++i;
                        }
                        else if(nextChar != 32){
                            tokenError = 1;
                        }
                    }
                    //cout << "VAL IS: " << val << endl;
                    stack1.push(val);
                    //cout << "CURR PEEK: " << stack1.peek() << endl;
                }
/*==============================================================================
Handles Subtraction
==============================================================================*/
                //Checks case when character is '-' for subtraction
                else if(asciiVal == 45 && (i+1) >= input.size()){
                    //cout << "SUBTRACTION DETECTED" << endl;
                    int val1 = stack1.pop();
                    //If there is only one number left in stack
                    //POP POP PUSH
                    int val2 = stack1.pop();
                    //cout << "Val2: " << val2 << endl;
                    if(val2 == -999){
                        paramError = 1;
                    }
                    else{
                        //cout << "val1: " << val1 << endl;
                        //cout << "val2: " << val2 << endl;
                        stack1.push(val2 - val1);
                        
                        //cout << "Current Stack top: " << stack1.peek() << endl;
                    }
                }
/*==============================================================================
Handles Numbers (negative) & Subtraction
==============================================================================*/

                //Checks case when character is '-' for numbers
                else if(asciiVal == 45 && (i + 1) < input.size()){
                    //if(
                    //cout << "SOMETHING AFTER '-' DETECTED" << endl;
                    //cout << "Curr. Char is '-'" << endl;
                    //Checks if character after '-' is a number
                    if((i + 1) < input.size()){
                        //cout << "Next position is in range" << endl;
                        int nextChar = input.at(i + 1);
                        //cout << "ASCII of nextCHAR: " << nextChar << endl;
                        if(nextChar >= 48 && nextChar <= 57){
                            //cout << "NEXT CHAR is a #" << endl;
                            //cout << "NEXTCHAR is: " << nextChar - '0' << endl;
                            //Check first to see if single digit negative number
                            //cout << endl << "single digit is " << input.at(i+1)-'0' << endl;
                            val = (input.at(i + 1) - '0');
                            val = val * -1;
                            ++i;
                            //Checks if character after "-X_" is a number
                            //cout << "CURR i VAL: " << i << endl;
                            //cout << "input size: " << input.size() << endl;
                            if(i < input.size()){
                                int nextChar2 = input.at(i + 1);
                                //if Character after "-X_" is a number
                                //Then it's a two digit negative number
                                if(nextChar2 >= 48 && nextChar <= 57){
                                    //cout << "second digit is " << input.at(i+1) - '0' << endl;
                                    val = ((input.at(i) - '0') * 10) + (input.at(i + 1) - '0');
                                    val = val * -1;
                                    i = i + 1;
                                }
                                else if(nextChar2 != 32){
                                    tokenError = 1;
                                }
                            }
                            stack1.push(val);
                        }
                        else if(nextChar != 32){
                            tokenError = 1;
                        }
                        else{
                            //cout << "SUBTRACTION DETECTED" << endl;
                            int val1 = stack1.pop();
                            //If there is only one number left in stack
                            //POP POP PUSH
                            int val2 = stack1.pop();
                            if(val2 == -999){
                                paramError = 1;
                            }
                            else{
                                //cout << "val1: " << val1 << endl;
                                //cout << "val2: " << val2 << endl;
                                stack1.push(val2 - val1);
                                
                                //cout << "Current Stack top: " << stack1.peek() << endl;
                            }
                        }
                    }
                }

/*==============================================================================
Handles Addition
==============================================================================*/
                //Checks case when character is '+'
                else if(asciiVal == 43){
                    //cout << "ADDITION DETECTED" << endl;
                    int val1 = stack1.pop();
                    //If there is only one number left in stack
                        //POP POP PUSH
                        int val2 = stack1.pop();
                        if(val2 == -999){
                            paramError = 1;
                        }
                        else{
                            //cout << "val1: " << val1 << endl;
                            //cout << "val2: " << val2 << endl;
                            stack1.push(val2 + val1);
                            //cout << "Current Stack top: " << stack1.peek() << endl;
                        }
                }
/*==============================================================================
Handles Multiplication
==============================================================================*/
                //Checks case when character is '*'
                else if(asciiVal == 42){
                    //cout << "MULTIPLICATION DETECTED" << endl;
                    int val1 = stack1.pop();
                    //If there is only one number left in stack
                        //POP POP PUSH
                    int val2 = stack1.pop();
                    if(val2 == -999){
                        paramError = 1;
                    }
                    else{
                        //cout << "val1: " << val1 << endl;
                        //cout << "val2: " << val2 << endl;
                        stack1.push(val2 * val1);
                        //cout << "Current Stack top: " << stack1.peek() << endl;
                    }
                }
/*==============================================================================
Handles Division
==============================================================================*/
                //Checks case when character is '/'
                else if(asciiVal == 47){
                    //cout << "DIVISION DETECTED" << endl;
                    int val1 = stack1.pop();
                    //cout << "val1: " << val1 << endl;
                    //If there is only one number left in stack

                    //POP POP PUSH
                    int val2 = stack1.pop();
                    if(val2 == -999){
                        paramError = 1;
                    }
                    else{
                        //cout << "val1: " << val1 << endl;
                        //cout << "val2: " << val2 << endl;
                        stack1.push(val2 / val1);
                        //cout << "Current Stack top: " << stack1.peek() << endl;
                    }
                }
/*==============================================================================
Handles mod (%)
==============================================================================*/
                //Checks case when character is '%'
                else if(asciiVal == 37){
                    //cout << "DIVISION DETECTED" << endl;
                    int val1 = stack1.pop();
                    //cout << "val1: " << val1 << endl;
                    //If there is only one number left in stack

                    //POP POP PUSH
                    int val2 = stack1.pop();
                    if(val2 == -999){
                        paramError = 1;
                    }
                    else{
                        //cout << "val1: " << val1 << endl;
                        //cout << "val2: " << val2 << endl;
                        stack1.push(val2 % val1);
                        //cout << "Current Stack top: " << stack1.peek() << endl;
                    }
                }
/*==============================================================================
Handles White Space
==============================================================================*/
                //IF WHITE SPACE
                else if(asciiVal == 32){
                //    cout << endl << "WHITE SPACE WHITE SPACE" << endl << endl;
                }
                
                //If the end of the string is reached
                //cout << "CURR POS: " << i << endl;
                //cout << "SIZE: " << inputSize << endl;
                if(i >= inputSize - 1){
                    int finalVal = stack1.peek();
                    stack1.pop();
                    //cout << "stack1.pop(): " << stack1.peek() << endl;
                    //cout << "current token error: " << tokenError << endl;
                    if(tokenError){
                        cout << "Error: invalid token" << endl;
                        tokenError = 0;
                    }
                    else if(stack1.peek() != -999){
                        cout << "Error: not enough operators" << endl;
                    }
                    else if(paramError){
                        cout << "Error: not enough parameters" << endl;
                        paramError = 0;
                    }
                    else{
                        cout << finalVal << endl;
                    }
                    //ArrayStack newStack;
                    //stack1 = newStack;
                    while(stack1.peek() != -999){
                        stack1.pop();
                    }
                    //cout << "Token error at end of execution: " << tokenError << endl;
                }
                    
            }
        }
    }


    return 0;
}
