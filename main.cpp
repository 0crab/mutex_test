#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

#include "tracer.h"

using namespace std;

#define THREAD_NUM 2
#define TEST_NUM 10000000

volatile int value = 0;

unsigned long runtimelist[THREAD_NUM];

pthread_spinlock_t lock_;
mutex mtx;


int loop(int tid,bool inc, int limit) {
    std::cout << "Started " << inc << " " << limit << std::endl;
    Tracer tracer;
    tracer.startTime();
    for (int i = 0; i < limit; ++i) {
        //pthread_spin_lock(&lock_);
        mtx.lock();
        if (inc) {
            ++value;
        } else {
            --value;
        }
        //pthread_spin_unlock(&lock_);
        mtx.unlock();
    }
    runtimelist[tid]+=tracer.getRunTime();
    return 0;
}

int main() {

    pthread_spin_init(&lock_,0);

    vector<thread> threads;
    for(int i =0; i < THREAD_NUM; i++){
        if(i%2==0){
            threads.push_back(thread(loop,i,true,2*TEST_NUM));
        }else{
            threads.push_back(thread(loop,i,false,TEST_NUM));
        }

    }

    for(int i = 0; i < THREAD_NUM; i++){
        threads[i].join();
    }

    uint64_t runtime = 0;
    for(int i = 0 ; i < THREAD_NUM; i++) runtime +=runtimelist[i];
    cout<<"runtime:"<<runtime/THREAD_NUM<<endl;


    std::cout << value << std::endl;
}