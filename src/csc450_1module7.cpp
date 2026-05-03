/*
 * CSC450_1Module7.cpp
 *
 *  Created on: May 3, 2026
 *      Author: jonathan Greene
 */

// pseudocode
/*
 *  use automic to  create a thread safe counter since it is a simple data type
 *  Switched to using mutex to help better understand the concept and explored condition variables
 *  opted to not use it as seems overcomplicated for the assignment at hand.
 *  start the counter at zero and loop over it
 *  increment timer by 1 until 20
 *  once 20 is reach activate thread 2 counting down from 20
 *  implement thread 2 and initialize to 20
 *  decrement by 1 each time the loop runs
 *  until zero then print counter completed count down
 */

#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

// utilizing mutex to sement knowledge learned in class
mutex mtx;

void countUpTo20(){
	for(int i=1; i <= 20; i++){
		//lock_guard releases in case there is an error
		lock_guard<mutex> lock(mtx);
		cout << "thread 1: " << i << endl;
	}
}
void countDownto0(){
	for(int j=20; j >= 0; j--){

		lock_guard<mutex> lock(mtx);
		cout << "thread 2: " << j << endl;
	}
}

int main (){
	cout << "Starting  thread 1" << endl;
	thread t1(countUpTo20);

	t1.join();
	cout << "Starting  thread 2" << endl;
	thread t2(countDownto0);
	t2.join();
	cout << " Completed counting up and down" << endl;

	return 0;
}






