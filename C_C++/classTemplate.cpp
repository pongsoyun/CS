#include <iostream>
using namespace std;

template <typename T>
class Data
{
private:
    T data;

public:
    Data(T dt);
    T get_data();
};

template <>
class Data<double> // double 형에 대한 명시적 특수화.
{
private:
    double data;

public:
    Data(double dt) { data = dt; } // 생성자
    double get_data()
    {
        cout << "double형 데이터 출력" << endl;
        return data;
    }
};

template <typename T>
Data<T>::Data(T dt)
{
    data = dt;
}

template <typename T>
T Data<T>::get_data()
{
    return data;
}

int main()
{
    Data<string> str_data("C++다시보기");
    Data<double> double_data(3.14);

    cout << "str_data : " << str_data.get_data() << endl;
    cout << "double_data : " << double_data.get_data() << endl;
    return 0;
}