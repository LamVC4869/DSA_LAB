#include <iostream>

using namespace std;

template<class DataType>
class Stack;

template<class DataType>
class Node {
    private:
        DataType data;
        Node<DataType>* next;
        friend class Stack<DataType>;
    public:
        Node(DataType data) : data(data), next(nullptr) {}
};

template<class DataType>
class Stack {
    private:
        Node<DataType>* root;
    public:
        Stack() : root(nullptr) {}

        bool empty () const {
            return !root;
        }

        int size () const {
            if (empty()) {
                return 0;
            }
            int result(0);
            for (Node<DataType>* p = root; p != nullptr; p = p->next) {
                result += 1;
            }
            return result;
        }

        void push (const DataType& data) {
            if (empty()) {
                root = new Node(data);
                return;
            }
            Node<DataType>* newTop = new Node(data);
            newTop->next = root;
            root = newTop;
        }

        void pop () {
            if (empty()) {
                return;
            }
            Node<DataType>* rmd = root;
            root = root->next;
            delete rmd;
        }

        DataType& top () const {
            if (empty()) {
                cout << "Empty!\n";
                exit(0);
            }
            return root->data;
        } 

        void display () {
            if (empty()) {
                cout << "Empty!\n";
                exit(0);
            }
            for (Node<DataType>* top = root; top != nullptr; top = top->next) {
                cout << top->data << ' ';
            }
            cout << '\n';
        }

        void clear () {
            while (!empty()) {
                pop();
            }
        }

        ~Stack() {
            clear();
        }
};

template<class DataType>
void init (int n, Stack<DataType>& st) {
    while (n--) {
        DataType data;
        cin >> data;
        st.push(data);
    }
}

int main () {

    Stack<int> intStack;
    Stack<double> doubleStack;
    Stack<char> charStack;
    Stack<string> stringStack;

    int n; cin >> n;
    init(n, intStack);
    init(n, doubleStack);
    init(n, charStack);
    init(n, stringStack);

    cout << "Integer Stack: "; intStack.display();
    cout << "Double Stack: "; doubleStack.display();
    cout << "Character Stack: "; charStack.display();
    cout << "String Stack: "; stringStack.display();

    return 0;
}
