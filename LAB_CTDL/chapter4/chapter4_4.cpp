#include <iostream>
#include <vector>

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

void quickSort (vector<int>& arr, int left, int right) {
    Stack<pair<int, int>> s;
    s.push({left, right});
    auto partition = [&](vector<int>& arr, int l, int r) {
        int i = l - 1, j = r + 1;
        int pivot = arr[l];
        while (true) {
            do { --j; } while (arr[j] > pivot);
            do { ++i; } while (arr[i] < pivot);
            if (i >= j) {
                return j;
            }
            else {
                swap(arr[i], arr[j]);
            }
        }
    };
    while (!s.empty()) {
        pair<int, int> rmd = s.top();
        s.pop();
        if (rmd.first < rmd.second) {
            int p = partition(arr, rmd.first, rmd.second);
            if (p > rmd.first) {
                s.push({rmd.first, p});
            }
            if (p < rmd.second) {
                s.push({p + 1, rmd.second});
            }
        }
    }
}

int main () {
    vector<int> arr;
    int n; cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    quickSort(arr, 0, n - 1);
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << ' ';
    }
    return 0;
}