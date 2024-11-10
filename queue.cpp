#include <iostream>

using namespace std;

template<class DataType>
class Queue;

template<class DataType>
class Node {
    private:
        DataType data;
        Node<DataType>* next;
        friend class Queue<DataType>;
    public:
        Node(const DataType& data) : data(data), next(nullptr) {}
};

template<class DataType>
class Queue {
    private:
        Node<DataType>* head;
        Node<DataType>* tail;
    public:
        Queue() : head(nullptr), tail(nullptr) {}

        bool empty () const {
            return !head && !tail;
        }

        int size () const {
            if (empty()) {
                return 0;
            }
            int result(0);
            for (Node<DataType>* p = head; p != nullptr; p = p->next) {
                result += 1;
            }
            return result;
        }

        void push (const DataType& data) {
            if (empty()) {
                head = tail = new Node(data);
                return;
            }
            tail->next = new Node(data);
            tail = tail->next;
        }

        void pop () {
            if (empty()) {
                return;
            }
            if (head == tail) {
                delete head;
                head = tail = nullptr;
                return;
            }
            Node<DataType>* rmd = head;
            head = head->next;
            delete rmd;
        }

        DataType& front () const {
            if (empty()) {
                cout << "Empty!\n";
                exit(0);
            }
            return head->data;
        }

        void display () {
            if (empty()) {
                cout << "Empty!\n";
                exit(0);
            }
            for (Node<DataType>* p = head; p != nullptr; p = p->next) {
                cout << p->data << ' ';
            }
            cout << '\n';
        }

        void clear () {
            while (!empty()) {
                pop();
            }
        }

        ~Queue() {
            clear();
        }
};

int main () {

    return 0;
}