#pragma once
#include <iostream>
#include <cassert>
#define RAND_MAX 32767.00
#define __throwif__(expression,notification) if(expression){throw notification;}

template<class Type>
class TQueue {
	Type* pMem;
	size_t size = 0;
	int count = 0;
	size_t setPointer = 0;
	size_t getPointer = 0;

public:
	TQueue(int _size = 0) {
		if (_size > 0) {
			setSize(_size);
		}
	}
	void setSize(int _size) {
		__throwif__(_size <= 0);
		size = _size;
		pMem = new Type[size];
	}
	void Put(Type& v) {
		__throwif__(count == size);
		pMem[setPointer] = v;
		setPointer = ++setPointer % size;
		++count;
	}
	Type Get() {
		__throwif__(count == 0);
		Type _temp = pMem[getPointer];
		getPointer = ++getPointer % size;
		--count;
		return _temp;
	}
	bool isEmpty() {
		return (count == 0);
	}
	bool isFull() {
		return (size == count);
	}
	~TQueue() {
		delete[] pMem;
	}
};

class Kernel {
	double q;
	bool ready = true;
	size_t taskCounter = 0;
public:
	Kernel() {}
	void setParams(double _q) {
		q = _q;
	}
	void addTask(unsigned int _index) {
		ready = false;
		++taskCounter;
	}
	unsigned int getTaskCount() {
		return taskCounter;
	}
	bool isReady() {
		return ready;
	}
	bool isDone() {
		bool _temp = ((rand() / RAND_MAX) < q) && !ready;
		if (_temp) {
			ready = true;
		}
		return _temp;
	}
};


class TaskManager {
	double q;
	TQueue<size_t> TaskList;
	Kernel* kernelArray;
	size_t kernelCount = 0;
	size_t startCountTacts = 0;
	size_t countTacts = 0;
	size_t taskIndex = 0;
	size_t taskOff = 0;
	size_t taskDone = 0;

public:
	TaskManager(double _qTask, double __qKernel, size_t _kerCount, size_t _countTact, size_t _queueSize) :q(_qTask) {
		srand(0);
		kernelCount = _kerCount;
		countTacts = _countTact;
		TaskList.setSize(_queueSize);
		startCountTacts = _countTact;
		kernelArray = new Kernel[_kerCount];

		for (size_t i = 0; i < _kerCount; i++) {
			kernelArray[i].setParams(__qKernel);
		}
	}

	void StartManage() {
		size_t i;
		double _q;

		while (countTacts) {

			_q = rand() / RAND_MAX;

			if (_q < q) {
				if (!TaskList.isFull()) {
					TaskList.Put(taskIndex);
					++taskIndex;
				}
				else {
					++taskOff;
				}
			}

			for (i = 0; i < kernelCount; i++) {

				if (kernelArray[i].isDone()) {
					++taskDone;
				}

				if (kernelArray[i].isReady()){ 
					if (!TaskList.isEmpty()) {
						kernelArray[i].addTask(TaskList.Get());
					}
				}
			}
			countTacts--;
		}

		taskIndex += taskOff;
		std::cout << "Count of kernels: " << kernelCount << std::endl;
		std::cout << "Count tacts: " << startCountTacts << std::endl;
		std::cout << "-----------------------------" << std::endl;
		std::cout << "Count of tasks: " << taskIndex << std::endl;
		std::cout << "Count of tasks off: " << ((double)taskOff / (double)taskIndex) * 100 << "%" << std::endl;
		std::cout << "Count of unfinished tasks: " << taskIndex - taskDone << std::endl;
		std::cout << "Count of tasks done: " << taskDone << std::endl;
	}
};

