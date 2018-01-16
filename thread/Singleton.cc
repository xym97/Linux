#include<iostream>
#include<mutex>

using namespace std;

template<class T>
class Singleton
{
    static volatile T* inst;
    static std::mutex lock;
public:
    static  T* GetInst(){
        if(inst ==  NULL){
            lock.lock();
            if(inst ==  NULL){
                inst = new T();
            }
            lock.unlock();
        }
        return inst;
    }
};

template<typename T> volatile T* Singleton<T>::inst = NULL;

int main()
{
    Singleton<int> a;
    return 0;
}
