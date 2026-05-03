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
#include<condition_variable>

using namespace std;

// utilizing mutex to sement knowledge learned in class
mutex mtx;
// condition variable so i can lock and unlock
condition_variable cv;
bool finished = false;

void countUpTo20(){
	for(int i=1; i <= 20; i++){
		//lock_guard releases in case there is an error
		lock_guard<mutex> lock(mtx);
		cout << "thread 1: " << i << endl;
	}

	// notify thread 2 of status
	{
		lock_guard<mutex> lock(mtx);
		finished = true;
	}
	// wake up thread
	cv.notify_one();
}
void countDownto0(){
	// wait for finished to be true to unlock
	unique_lock<mutex> ulock(mtx);
	cv.wait(ulock, [] {return finished;});
	for(int j=20; j >= 0; j--){

//		lock_guard<mutex> lock(mtx); not needed when use unique lock
		cout << "thread 2: " << j << endl;
	}
}

int main (){
	cout << "Starting  thread 1 " << endl;
	thread t1(countUpTo20);
	thread t2(countDownto0);


	cout << "Starting  thread 2 " << endl;
	t1.join();
	t2.join();
	cout << " Completed counting up and down" << endl;

	return 0;
}






