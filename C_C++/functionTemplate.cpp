#include <iostream>
using namespace std;

template <typename T>
void Swap(T &a, T &b)
{
    T tmp;
    tmp = a;
    a = b;
    b = tmp;
}

template <>
void Swap<double>(double &, double &)
{
    cout << "double type 은 Swap 하지 않는다" << endl;
    // double type으로 특수하게 명시된 템플릿은 다른 자료형템플릿을 찾지 않고 바로 이 함수를 사용한다.
};

int main()
{
    int n1 = 2, n2 = 3;
    cout << n1 << " " << n2 << endl;
    Swap(n1, n2);
    cout << n1 << " " << n2 << endl;

    double d1 = 1.34, d2 = 3.14;
    cout << d1 << " " << d2 << endl;
    Swap(d1, d2);
    cout << d1 << " " << d2 << endl;

    string s1 = "pong", s2 = "bang";
    cout << s1 << " " << s2 << endl;
    Swap(s1, s2);
    cout << s1 << " " << s2 << endl;

    return 0;
}

// --terminal--
// 2 3
// 3 2
// 1.34 3.14
// double type 은 Swap 하지 않는다
// 1.34 3.14
// pong bang
// bang pong