#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <memory>

using namespace std;


template <typename T>
class SmartPtr{
    public:
        // Doesn't allow to be used as conversion constructor for implicit conversion
        explicit SmartPtr(T *memory);
        ~SmartPtr();

        SmartPtr(const SmartPtr &other);
        SmartPtr& operator = (const SmartPtr &other);


        T& operator * () const;
        T* operator -> () const;
    private:
        struct Data{
            T* res;
            short ref_count;
        };

        Data *data;
        void detach();
        void attach(Data *data);

};

template <typename T>
SmartPtr<T>::SmartPtr(T *mem){
    Data *data = new Data;
    data->res = mem;
    data->ref_count = 1;
    this->data = data;
}

template <typename T>
void SmartPtr<T>::detach(){
    data->ref_count--;
    if(data->ref_count==0){
        delete data->res;
        delete data;
    }
}

template <typename T>
void SmartPtr<T>::attach(Data *data){
    this->data = data;
    this->data->ref_count++;
}

template <typename T>
SmartPtr<T>::SmartPtr(const SmartPtr<T> &other){
    attach(other.data);
}

template <typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr<T> &other){
    if(this!=&other){
        detach();
        attach(other.data);
    }
    return *this;
}

template <typename T>
SmartPtr<T>::~SmartPtr(){
    detach();
}

template <typename T>
T& SmartPtr<T>::operator*() const{
    return *data->res;
}

template <typename T>
T* SmartPtr<T>::operator->() const{
    return data->res;
}

int main(){

    ifstream ifs("sample.txt");
    ofstream ofs;
    int x, y;
    ifs >> x >> y;
    cout << setw(10)<< x << " "<< y << endl;
    ifs.close();

    return 0;
}
