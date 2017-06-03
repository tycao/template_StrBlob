#include <iostream>
#include <vector>
#include <initializer_list>
#include <memory>

using namespace std;

class StrBlob
{
public:
    typedef std::vector<std::string>::size_type size_type;

    //默认构造函数
    StrBlob();

    //（调用initializer_list的拷贝构造函数）
    StrBlob(std::initializer_list<std::string>&);

    //（调用initializer_list的移动构造函数）
    StrBlob(std::initializer_list<std::string>&&);

    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    //添加或者删除元素
    void push_back(const std::string& s){ data->push_back(s); }
    void pop_back();

    //元素访问
    std::string& back() const;
    std::string& front() const;
private:
    std::shared_ptr<std::vector<std::string>> data;
    //若data[i]不合法，则抛出异常
    void check(size_type, const std::string&) const;
};

StrBlob::StrBlob() : data(make_shared<std::vector<std::string>>()) {}
StrBlob::StrBlob(std::initializer_list<std::string>& il) : data(make_shared<std::vector<std::string>>(il)) {}
StrBlob::StrBlob(std::initializer_list<std::string>&& il)
            : data(make_shared<vector<string>>(std::move(il))) {}

void StrBlob::check(size_type i, const string& msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

void StrBlob::pop_back()
{
    check(0, "pop_back on an empty Blob");
    data->pop_back();
}

std::string& StrBlob::back() const
{
    check(0, "back on an empty Blob");
    return data->back();
}

std::string& StrBlob::front() const
{
    check(0, "front an the empty Blob");
    return data->front();
}


int main()
{
    std::initializer_list<std::string> ini{"1st element", "2nd element", "3rd element", "4th element"};
    StrBlob blob = std::move(ini);
    cout << blob.front() << endl;
    cout << blob.back() << endl;
    if (!blob.empty())
    {
        blob.pop_back();
        cout << "blob.size()= " << blob.size() << endl;
    }
    cout << blob.back() << endl;
    try
    {
        for (int i = 0; i != 4; ++i)
            blob.pop_back();
    }
    catch(std::out_of_range& e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
