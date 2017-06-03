#include <iostream>
#include <vector>
#include <memory>
#include <initializer_list>
using namespace std;

template<typename T> class Blob
{
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;

    //构造函数
    Blob();
    Blob(std::initializer_list<T>);

    //Blob中的元素数目
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    //添加和删除元素
    void push_back(const T& t) { data->push_back(t); }
    void push_back(const T&& t) { data->push_back(std::move(t)); }
    void pop_back();

    //元素访问
    T& back() const;
    T& operator[](size_type i) const;
private:
    std::shared_ptr<std::vector<T>> data;
    void check(size_type i, const std::string& msg) const;
};

template<typename T> void Blob<T>::check(size_type i, const std::string& msg) const {
    if (i >= data->size())
        throw std::out_of_range(msg);
}

template<typename T> T& Blob<T>::back() const {
    check(0, "back on the empty Blob");
    return data->back();
}

template<typename T> T& Blob<T>::operator[](size_type i) const {
    check(i, "out of range Error");
    return (*data)[i];
}

template<typename T> void Blob<T>::pop_back(){
    check(0, "pop_back on an empty Blob");
    data->pop_back();
}

template<typename T> Blob<T>::Blob() : data(make_shared<std::vector<T>>()) {}



int main()
{
    Blob<string> b;
    string str = "the first element of the array";
    b.push_back(str);
    cout << b.back() << endl;
    b.pop_back();
    try
    {
        b.back();
    }
    catch(std::out_of_range& e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
