#include <iostream>

using namespace std;

template<class DataType>
class Stack;

template<class DataType>
class Node {
    private:
        DataType data;
        Node* next;
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

bool kiemTra (string s) {
    Stack<char> st;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            st.push(s[i]);
        }
        else {
            if ((s[i] == ')' && st.top() != '(') || (s[i] == ']' && st.top() != '[') || (s[i] == '}' && st.top() != '{')) {
                return false;
            }
            else {
                st.pop();
            }
        }
    }
    return st.empty();
}

int main () {
    string s; cin >> s;
    cout << (kiemTra(s) ? "true" : "false");
    return 0;
}