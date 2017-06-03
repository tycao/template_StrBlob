#include <iostream>
#include <memory>
using namespace std;

class DebugDelete
{
public:
    DebugDelete(std::ostream& s = std::cerr) : os(s) { }
    template<typename T> void operator()(T *p) const { os << "deleting unique_ptr..." << endl; delete p; }
private:
    std::ostream& os;
};



int main()
{
    double *p = new double;
    DebugDelete d(cout);
    d(p);

    int *i = new int;
    DebugDelete()(i);

    std::unique_ptr<int, DebugDelete> pp(new int, d);
    std::unique_ptr<std::string, DebugDelete> sp(new std::string, DebugDelete());

    return 0;
}
