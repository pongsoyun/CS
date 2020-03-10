# 연결리스트

동적인 데이터를 처리하는 자료구조이다. 관련하여 리스트 traversal, 정렬, 데이터의 삽입/삭제 등에 관한 문제가 면접에서 많이 나오고, 20~30분안에 풀수있는 문제들이 나오곤 한다. 구현하는데는 10분정도가 걸리는 자료구조이므로 해쉬등의 자료구조와 비교하여 비교적 간단하다.

특히나 포인터에 대한 이해를 기반으로 하고있기 때문에, 실제로 링크드 리스트를 직접 만들어서 쓸일은 없고 표준 라이브러리를 사용하면 되지만 면접에서는 내가 100%이해하고있다는 것을 보여주어야한다.

## 연결리스트의 종류

1. 단일 연결 리스트
2. 이중 연결 리스트
3. 원형 연결 리스트

### 단일 연결 리스트

일반적인 연결리스트로, 첫번째 원소인 `head pointer`를 기점으로 `tail`까지 link 되어있는 형태의 자료구조를 뜻한다. 그 연결리스트구조체 하나(원소)를 노드라고 한다. 노드 안에 링크가 1개이고 단방향으로 진행하는 리스트를 말한다.

이를 구현하는 가장 간단한 방법은 포인터와 필요한 데이터 멤버(value들)을 넣은 구조체를 만드는 것이다.

```
// 구조체로 만듬
typedef struct Node {
    struct Node *next; // 같은 유형의 구조체에 대한 포인터
    int data;
} ListElement;

// class template으로 만듬
template <class T>
class Node
{
public:
    // C++ 에서 템플릿으로 클래스를 정의했으므로, 컴파일러에서 만들어준 버전을 쓰지 않아도 되도록 복사생성자, 대입 연산자를 명시했다.
    Node(const T &value) : next(NULL), data(value) {}
    ~Node() {}

    Node *getNext() const { return next; }          // Node 에 연결된 next 를  반환
    const T &value() const { return data; }         // Node 의 data를 반환
    void setNext(Node *elem) { next = elem; }       // Node를 인자로 받아 next*로 가리키게 해줌
    void setValue(const T &value) { data = value; } // 새로운 값을 인자로 받아 data로 덮어씀

private:
    Node *next;
    T data;
};

```

## 이중 연결 리스트

노드 안에 링크가 2개이고, 양방향으로 진행할 수 있는 리스트를 말한다.

```
typedef struct Node {
    struct Node *next;
    int data;
    struct Node *prev;
}
```

사실 면접에서는 이중 연결 리스트보다는 단일 연결리스트를 더 자주 묻곤 한다. 단일 연결 리스트가 더 어려운 경우가 훨씬 많기 떄문이다.

## 원형 연결 리스트

마지막 노드가 첫번째 노드를 가르켜서 계속 회전할 수 있게 만들어진 리스트를 말한다. 이중연결리스트와 마찬가지로 포인터나 레퍼런스에는 반드시 NULL이 아닌 원소가 들어가야하고, 원소가 하나밖에 없는 리스트라면 그냥 자기 자신을 가리키면 된다.

구현을 어떻게 하느냐에 따라 단일 연결 리스트를 원형으로 이을수도, 이중 연결 리스트를 원형으로 이을 수도 있다.tail이 가리키는 값을 head 로 지정해주면 된다.

원형 연결 리스트에서는 사이클 회피 문제가 자주 나온다.

# 기초적인 연결리스트 연산

단일연결리스트로 머리 원소 추적, 리스트 종주, 리스트 원소 추가/제거 를 구현할 때 빠질 수 있는 함정들을 조심해서 구현한다.

## head 원소 추적

반드시 머리 원소 추적을 해야한다. 그러지 못한다면 언어에 따라 GC(가비지 컬렉터)에 의해 제거되거나, 길을 잃고 만다. 따라서, head 원소를 제거하거나 head 앞에 원소를 삽입할 때 리스트의 head 에 대한 포인터/레퍼런스를 꼭!! 신경써주어야한다.

아래는 head 앞에 Node를 추가하는 경우의 코드이다.

```
bool insertInFront(Node *head, int data){
    Node *newElem = new Node;
    if(!newElem) return false;

    newElem -> data = data;
    newElem -> next = *head; // 새로 넣은 노드의 next는 현재 head 노드를 가리키자
    *head = newElem; // *head // head 포인터가 가리키고 있을 친구는 이제 newElem!
    return true;
}
```

## 리스트 종주

리스트를 끝까지 찾아갈 때, **리스트가 끝났는지** 확인을 꼭 해야한다. 예를들어, 더이상의 next가 존재하지 않는 경우에 다음 리스트의 데이터를 찾으려고 한다면 오류를 낼것이다.

```
...
while(elem != null && elem.value() !=data){ elem = elem.next; }
...
```

## 원소의 삽입 및 삭제

```

```
