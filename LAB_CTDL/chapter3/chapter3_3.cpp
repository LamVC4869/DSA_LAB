#include <iostream>

using namespace std;

class Node {
private:
    int data;
    Node* next;
    friend class LinkedList;
public:
    Node(int data) : data(data), next(nullptr) {}
};

class LinkedList {
private:
    Node* root;
public:
    LinkedList() : root(nullptr) {}

    bool empty() {
        return !root;
    }

    void push_back(int x) {
        if (empty()) {
            root = new Node(x);
            return;
        }
        Node* curr = root;
        while (curr->next) curr = curr->next;
        curr->next = new Node(x);
    }

    bool found(int x) const {
        for (Node* p = root; p != nullptr; p = p->next) {
            if (p->data == x) {
                return true;
            }
        }
        return false;
    }

    void clear() {
        while (root) {
            Node* p = root;
            root = root->next;
            delete p;
        }
    }

    int count (int x) const {
        int ans(0);
        for (Node* p = root; p != nullptr; p = p->next) {
            ans += (p->data == x);
        }
        return ans;
    }

    LinkedList& operator = (const LinkedList& another) {
        if (this != &another) {
            clear();
            Node* current = another.root;
            while (current) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    LinkedList subList(const LinkedList& L1, const LinkedList& L2) {
        LinkedList L3;
        int MAX = 0;
        for (Node* p = L1.root; p != nullptr; p = p->next) {
            if (L2.found(p->data)) {
                int count = L2.count(p->data);
                Node* start = L2.root;
                while (count--) {
                    while (start != nullptr && start->data != p->data) {
                        start = start->next;
                    }
                    Node* curr = start;
                    Node* pre = p;
                    int length = 0;
                    while (curr != nullptr && pre != nullptr && curr->data == pre->data) {
                        length++;
                        curr = curr->next;
                        pre = pre->next;
                    }
                    if (length > MAX) {
                        LinkedList temp;
                        MAX = length;
                        for (int i = 0; i < length; ++i) {
                            temp.push_back(start->data);
                            start = start->next;
                        }
                        L3 = temp;
                    }
                }
                break;
            }
        }
        return L3;
    }

    void display() {
        for (Node* p = root; p != nullptr; p = p->next) {
            cout << p->data << ' ';
        }
        cout << '\n';
    }

    ~LinkedList() {
        clear();
    }
};

void init(LinkedList& L) {
    int n; cin >> n;
    while (n--) {
        int x; cin >> x;
        L.push_back(x);
    }
}

int main() {

    LinkedList L1, L2;
    init(L1); 
    init(L2);
    L1.display();
    L2.display();

    LinkedList L3 = L1.subList(L1, L2);
    L3.display();

    return 0;
}

/*
9
2 6 1 5 4 3 8 7 9
10
8 3 6 1 5 4 3 7 9 0
*/