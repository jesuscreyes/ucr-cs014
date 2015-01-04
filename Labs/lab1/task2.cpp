#include <iostream>
using namespace std;

int binaryCount(int n){
	//int count = 0;
	if(n == 1){
		return 1;
	}
	if((n % 2) == 0){
		return binaryCount(n/2);
	}
	return 1 + binaryCount(n/2);
}

int main(){
	
	cout << binaryCount(63) << endl;
	
	return 0;
}
