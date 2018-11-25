#include "pch.h"
#include "multicore.h"
#include <iostream>

using namespace std;

int main(){

	double qTask;
	double qKernel;
	int countKernels;
	int countTicks;
	int queueSize;

	cout << "Set the q1 (0 < q1 < 1): " << endl;
	cin >> qTask;
	cout << endl;
	
	qTask = qTask - (int)qTask;

	cout << "Set the q1 (0 < q2 < 1): " << endl;
	cin >> qKernel;
	cout << endl;

	qKernel = qKernel - (int)qKernel;

	cout << "Set the count of Kernels: " << endl;
	cin >> countKernels;
	cout << endl;

	cout << "Set the count of Ticks: " << endl;
	cin >> countTicks;
	cout << endl;


	cout << "Set the size of Queue: " << endl;
	cin >> queueSize;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	TaskManager tProcessor(qTask, qKernel, countKernels, countTicks, queueSize);
	tProcessor.StartManage();
	
	system("pause");
	return 0;
}
