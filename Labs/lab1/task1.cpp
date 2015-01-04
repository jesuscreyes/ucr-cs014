#include <iostream>
using namespace std;

class Queue{
	public:
	virtual void enqueue(int n) = 0;
	virtual int dequeue() = 0;
	virtual void print() = 0;
	virtual bool isEmpty() = 0;
};

class ArrayQueue : public Queue{
	public:
		ArrayQueue(){
			max_size = 5; //arbitrary size
			front = 0; //initial position of front of queue
			back = 0; //initial position of back of queue
			arr = new int[max_size];
			arr[front] = -1;
		}
		
		//Enqueue(Push) function
		void enqueue(int n){
			//if queue is FULL
			if(arr[front] != -1 && front == back){
				return;
			}
			arr[back] = n;
			if(back == max_size - 1){
				back = 0;
			}
			else{
				back++;
			}
		}
		
		//Dequeue(Pop) function
		int dequeue(){
			//if queue is EMPTY
			if(arr[front] == -1 && front == back){
				return -1;
			}
			int returnVal = arr[front];
			arr[front] = -1;
			if(front == max_size - 1){
				front = 0;
			}
			else{
				front++;
			}
			return returnVal;
		}
		
		//isEmpty function
		bool isEmpty(){
			if(front == back && arr[front] == -1){
				return true;
			}
			else{
				return false;
			}
		}
		
		//Prints Array Queue
		void print(){
			if(arr[front] == -1){
				cout << "Empty ArrayQueue" << endl;
				return;
			}
			
			if(front < back){
				for(int i = front; i < back; i++){
					cout << arr[i] << " ";
				}
			}
			else if(back <= front){
				for(int i = front; i < max_size; i++){
					cout << arr[i] << " ";
				}
				for(int i = 0; i < back; i++){
					cout << arr[i] << " ";
				}
			}
		}

			
		
		~ArrayQueue(){
			delete[] arr;
			arr = NULL;
		}
		
		private:
			int * arr;
			int front;
			int back;
			int max_size;
		
};

int main(){
	
	ArrayQueue first;
	
	if(first.isEmpty()){
		cout << "EMPTY" << endl;
	}
	else{
		cout << "NOT EMPTY" << endl;
	}

	cout << endl;
	
	cout << "Enqueue Test " << endl;
	first.enqueue(1);
	first.enqueue(2);
	first.enqueue(3);
	first.enqueue(4);
	first.enqueue(5);
	
	first.print();
	
	cout << endl << endl;
	
	if(first.isEmpty()){
		cout << "EMPTY" << endl;
	}
	else{
		cout << "NOT EMPTY";
	}
	
	cout << endl << endl;
	
	cout << first.dequeue() << " ";
	cout << first.dequeue() << " ";

	cout << endl << endl;
	
	first.print();
	
	first.enqueue(6);
	first.enqueue(7);
	first.enqueue(8);

	cout << endl << endl;

	first.print();
	
	return 0;
}
