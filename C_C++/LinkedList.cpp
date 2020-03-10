#include <iostream>
using namespace std;

// [간단하게 구조체로 구현한 Node]
typedef struct Node
{
    struct ListElement *next; // 같은 유형의 구조체에 대한 포인터
    int data;
} ListElement;

// [class template을 이용한 리스트 원소용 템플릿]
// template <class T>
// class Node
// {
// public:
//     // C++ 에서 템플릿으로 클래스를 정의했으므로, 컴파일러에서 만들어준 버전을 쓰지 않아도 되도록 복사생성자, 대입 연산자를 명시했다.
//     Node(const T &value) : next(NULL), data(value) {}
//     ~Node() {}

//     Node *getNext() const { return next; }          // Node 에 연결된 next 를  반환
//     const T &value() const { return data; }         // Node 의 data를 반환
//     void setNext(Node *elem) { next = elem; }       // Node를 인자로 받아 next*로 가리키게 해줌
//     void setValue(const T &value) { data = value; } // 새로운 값을 인자로 받아 data로 덮어씀

// private:
//     Node *next;
//     T data;
// };

bool insertInFront(Node *head, int data)
{
    Node *newElem = new Node;
    if (!newElem)
        return false;

    newElem->data = data;
    newElem->next = *head; // 새로 넣은 노드의 next는 현재 head 노드를 가리키자
    *head = newElem;       // *head // head 포인터가 가리키고 있을 친구는 이제 newElem!
    return true;
}
