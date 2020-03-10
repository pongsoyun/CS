C++의 특징 중 하나로, `generic programming`이 있다. 이는 데이터를 중시하는 객체지향 프로그래밍과는 달리 **프로그램의 알고리즘**에 중점을 둔다. 그 프로그램의 알고리즘 기능을 제공하는 기능중 하나가 바로 template이다.

## template 이란?

매개변수의 타입에 따라 함수, 클래스를 생성하는 매커니즘을 의미한다. 템플릿을 사용하면 타입마다 별도의 함수나 클래스를 만들 지 않아도 여러 타입엥서 동작할 수 있는 단 하나의 클래스/함수를 작성하는 것이 가능하다. 그래서 **일반화 된 선언**이라고도 한다.

```
int _sumInt(int a, int b) {
    return a+b;
}

float _sumFloat(float a, float b) {
    return a+b;
}

```

이런식으로 같은 동작을 하는 함수를 여러개로 생성하지 않아도 된다는 뜻이다.

# 1. 함수 템플릿

```
template <typename T>
void Func(T &n1, T &n2) { ... }
```

의 형태로 써주면 되고, 위에서 T타입으로 정의된 함수 Func를 호출 할 때, 매개변수로 int형을 전달하면 함수의 원형과 본체에서 정의된 타입 이름은 모두 int 형으로 바뀌게 된다. 쉽게 말해 T함수템플릿으로 저장한 함수의 자료형은 parameter의 자료형에 맞추어진다는 뜻.

## 함수 템플릿의 인스턴스 화

위 경우의 시나리오를 다시 보자. 함수 템플릿이 각각의 타입에 대해 처음으로 호출 될 때, C++ 컴파일러는 **해당 타입의 인스턴스를 생성**한다.

그렇게 생성된 인스턴스는 해당 타입에 대해 특수화된 **템플릿함수**이다.

이 인스턴스는 함수 템플릿에 해당 타입이 사용될 떄 마다 호출된다.

## 명시적 특수화

C++ 함수 템플릿은 특정 타입에 대해 특별한 동작을 정의할 수 있게 해준다. 다시말해, 컴파일러는 호출된 함수와 일치하는 자료형의 정의를 발견하면 더는 템플릿을 찾지 않고 해당 자료형의 정의를 사용한다.

예를들어

```
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
```

의 함수가 있다면 double 형의 param이 들어오는 경우는 swap되지 않고 해당 문구만 프린트 될 것이고, 나머지 자료형의 경우는 전부 swap될 것이다.

# 2. 클래스 템플릿

앞서 functoin template은 함수의 일반화 된 선언이었다. class template이란 클래스의 일반화 된 선언을 의미한다. 동작은 같다. 하지만 전달된 매개변수의 타입을 가지고 컴파일러가 해당 타입에 맞는 함수를 생성해주는 함수 템플릿과는 달리, 클래스 템플릿은 사용자가 사용하고자 하는 타입을 명시적으로 제공해야한다.

```
template <typename T>
class Data
{
private:
    T data;

public:
    Data(T dt);
    T get_data();
};
```

## 클래스 템플릿의 특징

1. 하나 이상의 템플릿 인수를 가지는 클래스 템플릿을 선언할 수 있다.

```
template <typename T, int i> // 두개의 템플릿 인수를 가지는 클래스 템플릿을 선언
class X {... }
```

2. 클래스 템플릿에 default 템플릿 인수를 명시할 수 있다.

```
template <typename T=int, int i> // default 템플릿 인수의 타입을 int형으로 명시
class X{...}
```

3. 클래스 템플릿을 부모클래스로 하여 상속가능하다.

```
template <typename Type> // 그래서 Y는 X클래스의 템플릿 Type을 상속받아 사용이 가능함
class Y : public X<Type> {... } // 클래스 템플릿 X를 상속받음
```

## 명시적 특수화

함수에서와 마찬가지로, 컴파일러가 전달된 인수의 타입에 정확하게 대응하는 특수화된 정의를 발견하면 다른 템플릿을 더이상 찾지 않고 해당 정의를 사용한다.

```
template <> class X<double> {...};
```

## 부분 특수화

템플릿의 파라미터가 여러개일 경우, 몇개는 타입이 정해져있고 몇개는 정해지지 않아도 괜찮은 경우가 대다수일것이다. 그럴 때 부분적으로 template 키워드 다음에 오는 <>에 특수화하지 않은 타입의 템플릿 인수를 명시하고, 그 다음에 <> 에 특수화하는 타입을 명시하면 된다.

```
// 파라미터 2개를 갖는 template class
template <> class X<double, double> { ... }; // 파라미터 모두 double 로 특수화
template <typename T1> class X<T1, double> { ... } ; // 부분 특수화
template <typename T1, T2> class X{...}; // 특수화 하지 않음
```

## `typedef` 키워드를 이용한 템플릿 특수화

```
typedef X<double, 3.14> DoubleX;
DoubleX double_x; // double_x는 X<double, 3.14> 타입이다.
```
