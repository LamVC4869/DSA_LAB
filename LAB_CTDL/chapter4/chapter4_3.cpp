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

//Độ ưu tiên
int priority (const char& chr) {
    if (chr == '^')
        return 4;
    if (chr == '%' || chr == '*' || chr == '/')
        return 3;
    if (chr == '+' || chr == '-')
        return 2;
    return 1;
}

//Toán tử
bool Operator (const char& chr) {
    return chr == '+' || chr == '-' || chr == '*' || chr == '/' || chr == '^' || chr == '%';
}

//Toán hạng
bool Operand (const char& chr) {
    return isdigit(chr);
}

string hauTo (const string& trungTo) {
    Stack<char> s;
    string result;
    for (int i = 0; i < trungTo.length(); ++i) {
        if (Operand(trungTo[i])) {
            int j = i;
            string temp;
            while (j < trungTo.length() && Operand(trungTo[j])) {
                temp.push_back(trungTo[j]);
                j++;
            }
            result += (temp + ' ');
            i = j - 1;
        }
        else {
            if (trungTo[i] == '(') {
                s.push(trungTo[i]);
            }
            else if (trungTo[i] == ')') {
                while (!s.empty() && s.top() != '(') {
                    result.push_back(s.top());
                    result.push_back(' ');
                    s.pop();
                }
                if (!s.empty() && s.top() == '(') s.pop();
            }
            else {
                while (!s.empty() && priority(s.top()) >= priority(trungTo[i])) {
                    result.push_back(s.top());
                    result.push_back(' ');
                    s.pop();
                }
                s.push(trungTo[i]);
            }
        }
    }
    while (!s.empty()) {
        result.push_back(s.top());
        result.push_back(' ');
        s.pop();
    }
    while (result.back() == ' ') result.pop_back();
    return result;
}

int main () {
    string trungTo;
    getline(cin, trungTo);
    int i = 0;
    while (i < trungTo.length()) {
        if (trungTo[i] == ' ') {
            trungTo.erase(i, 1);
        }
        else {
            i++;
        }
    }
    string HauTo = hauTo(trungTo);
    cout << "Bieu thuc hau to la:\n" << HauTo;
    return 0;
}
