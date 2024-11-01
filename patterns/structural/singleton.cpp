#include<iostream>
#include<assert.h>
#include<mutex>
#include<thread>
// Singleton pattern, when we want only one instance of the class. Consider a GPU access pointer or something like that.

// The most basic singleton
class BasicSingleton{
	private:
		BasicSingleton(){};
		static BasicSingleton *instance;
	public:
		static BasicSingleton* getInstance();
};
BasicSingleton* BasicSingleton::instance=NULL;
BasicSingleton* BasicSingleton::getInstance(){
	if(instance==NULL){
		instance = new BasicSingleton();
	}
	return instance;
}


// A Thread safe singleton, use a mutex lock around instance init
class ThreadSafeSingleton{
private:
	int value;
	ThreadSafeSingleton(){value=0;};
	static ThreadSafeSingleton *instance;
	static std::mutex *instanceMutex;

public:
	static ThreadSafeSingleton* getInstance();
	void incValue(){
		value++;
	}
	void print(){
		std::cout << "Value: " << value << std::endl;
	}
};
ThreadSafeSingleton* ThreadSafeSingleton::instance=NULL;
std::mutex* ThreadSafeSingleton::instanceMutex=new std::mutex();
ThreadSafeSingleton* ThreadSafeSingleton::getInstance(){
	if(instance==NULL){
		if(instanceMutex->try_lock()){
			instance=new ThreadSafeSingleton();
			instanceMutex->unlock();
		}
	}
	return instance;
}
void initInstance(ThreadSafeSingleton** ts){
	*ts = ThreadSafeSingleton::getInstance();
}
int main(){
	BasicSingleton *bs0 = BasicSingleton::getInstance();
	BasicSingleton *bs1 = BasicSingleton::getInstance();
	assert(bs0 == bs1);

	ThreadSafeSingleton *ts0=NULL,*ts1=NULL;
	std::thread t0(initInstance,&ts0);
	std::thread t1(initInstance,&ts1);
	t0.join();
	t1.join();
	assert(ts0 == ts1);
}