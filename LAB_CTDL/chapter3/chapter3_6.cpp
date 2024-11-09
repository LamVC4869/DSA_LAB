#include <iostream>

using namespace std;

template<class DataType>
class LinkedList;

template<class DataType>
class Node {
private:
    DataType data;
    Node* next;
    friend class LinkedList<DataType>;
public:
    Node(const DataType& data) : data(data), next(nullptr) {}
};

template<class DataType>
class LinkedList {
private:
    Node<DataType>* root;
public:
    LinkedList() : root(nullptr) {}
    bool empty() const {
        return root == nullptr;
    }
    int getSize() const {
        if (empty())
            return 0;
        int count = 0;
        for (Node<DataType>* curr = root; curr != nullptr; curr = curr->next) {
            count += 1;
        }
        return count;
    }
    void push_back(const DataType& data) {
        if (empty()) {
            root = new Node<DataType>(data);
            return;
        }
        Node<DataType>* curr = root;
        while (curr->next) curr = curr->next;
        curr->next = new Node<DataType>(data);
    }
    void push_front(const DataType& data) {
        if (empty()) {
            root = new Node<DataType>(data);
            return;
        }
        Node<DataType>* newNode = new Node<DataType>(data);
        newNode->next = root;
        root = newNode;
    }
    void pop_front() {
        if (empty())
            return;
        Node<DataType>* temp = root;
        root = root->next;
        delete temp;
    }
    void pop_back() {
        if (empty())
            return;
        if (!root->next) {
            delete root;
            root = nullptr;
            return;
        }
        Node<DataType>* curr = root;
        while (curr->next->next != nullptr) {
            curr = curr->next;
        }
        Node<DataType>* temp = curr->next;
        curr->next = nullptr;
        delete temp;
    }
    void disPlay() {
        for (Node<DataType>* curr = root; curr != nullptr; curr = curr->next) {
            cout << curr->data << ' ';
        }
        cout << '\n';
    }
    void clear() {
        while (root) {
            Node<DataType>* temp = root;
            root = root->next;
            delete temp;
        }
    }
    ~LinkedList() {
        clear();
    }
};

template<class DataType>
void init(LinkedList<DataType>& List, const int& size) {
    for (int i = 0; i < size; ++i) {
        DataType data;
        cin >> data;
        List.push_back(data);
    }
}

int main() {
    LinkedList<int> integerList;
    LinkedList<double> doubleList;
    LinkedList<char> charList;
    LinkedList<string> stringList;
    int size; cin >> size;

    init(integerList, size);
    init(doubleList, size);
    init(charList, size);
    init(stringList, size);

    cout << "Integer List: "; integerList.disPlay();
    cout << "Double List: "; doubleList.disPlay();
    cout << "Character List: "; charList.disPlay();
    cout << "String List: "; stringList.disPlay();

    return 0;
}