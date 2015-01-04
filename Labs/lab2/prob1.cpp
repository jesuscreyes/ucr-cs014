/*
 * Given the following pseudo code for bubble sort: Implement it in C++
 * 
 * void bubbleSort(int[] a){
     * for(i = 0; i < a.length; ++i){
         * if(a[j+1] > a[j]){
             * swap a[j+1],a[j];
        * }
    * }
*/
#include <iostream>
using namespace std;

void bubbleSort(int* a,int size){
        int temp;
    for(int i = 0; i < size; ++i){
        for(int j = 0; i < size-1; ++j){
            if(a[j+1] < a[j]){
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

int main(){
    
    int size = 5;
    int arr[size];
    arr[0] = 4;
    arr[1] = 8;
    arr[2] = 2;
    arr[3] = 1;
    arr[4] = 5;
    
    bubbleSort(arr,size);
    cout << arr[0] << " ";
    cout << arr[1] << " ";
    cout << arr[2] << " ";
    cout << arr[3] << " ";
    cout << arr[4] << " ";
    
    return 0;
    }
