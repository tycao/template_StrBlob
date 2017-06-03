#include <iostream>
#include <memory>
#include <vector>
#include <list>
using namespace std;

template<typename T> class Blob
{
public:
    template<typename It> Blob(It e, It b);
    std::vector<T>& show() const { return *data; }
private:
    std::shared_ptr<std::vector<T>> data;
};

template<typename T> template<class It> Blob<T>::Blob(It e, It b)
        : data(std::make_shared<std::vector<T>>(e, b)) { }

int main()
{
    int a1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<long> v1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<const char*> l1 = {"now", "this", "list", "time"};

    Blob<int> b1(begin(a1), end(a1));
    Blob<int> b2(v1.begin(), v1.end());
    Blob<string> b3(l1.begin(), l1.end());

    std::vector<int>& aa = b1.show();
    for (auto i : aa)
        cout << i << " ";
    cout << endl;

    return 0;
}
