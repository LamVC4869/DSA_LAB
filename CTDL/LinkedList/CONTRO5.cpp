#include <iostream>
#define ifile freopen(".inp", "r", stdin)
#define ofile freopen(".out", "w", stdout)
#define TIME (1.0*clock()/CLOCKS_PER_SEC)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

struct Node {
    int data;
    Node *next;
};

typedef Node* node;

node make_node (int x) {
    node p = new Node;
    if (p == nullptr) return nullptr;
    p->data = x;
    p->next = nullptr;
    return p;
}

struct LinkedList {
    node head = nullptr;

    int size();
    bool empty();
    void push_back(node x);
    void push_front(node x);
    void pop_back();
    void pop_front();
    int getMAX();
    int getMIN();
    void print();
    ~LinkedList();
};

int LinkedList::size () {
    int size = 0;
    for (node curr = head; curr != nullptr; curr = curr->next) {
        ++size;
    }
    return size;
}

bool LinkedList::empty () {
    return head == nullptr;
}

void LinkedList::push_back (node x) {
    if (empty()) {
        head = x;
        return;
    }
    node curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = x;
}

void LinkedList::push_front (node x) {
    if (empty()) {
        head = x;
        return;
    }
    x->next = head;
    head = x;
}

void LinkedList::pop_back () {
    if (empty()) return;
    if (head->next == nullptr) {
        node temp = head;
        head = nullptr;
        delete temp;
        return;
    }
    node curr = head;
    while (curr->next->next != nullptr) {
        curr = curr->next;
    }
    node temp = curr->next;
    curr->next = nullptr;
    delete temp;
}

void LinkedList::pop_front () {
    if (empty()) return;
    if (head->next == nullptr) {
        node temp = head;
        head = nullptr;
        delete temp;
        return;
    }
    node temp = head;
    head = head->next;
    delete temp;
}

int LinkedList::getMAX () {
    int total = head->data;
    for (node curr = head->next; curr != nullptr; curr = curr->next) {
        total = max(total, curr->data);
    }
    return total;
}

int LinkedList::getMIN () {
    int total = head->data;
    for (node curr = head->next; curr != nullptr; curr = curr->next) {
        total = min(total, curr->data);
    }
    return total;
}

void LinkedList::print () {
    node curr = head;
    while (curr != nullptr) {
        cout << curr->data << ' ';
        curr = curr->next;
    }
}

LinkedList::~LinkedList () {
    node p = nullptr;
    while (!empty()) {
        p = head;
        head = head->next;
        delete p;
    }
}

bool isValid (int a, int b, int c) {
    return a + b == c || a + c == b || b + c == a;
}

bool solve (const LinkedList& myList) {
    node prev = myList.head;
    while (prev->next->next != nullptr) {
        node curr = prev->next;
        while (curr->next != nullptr) {
            node next = curr->next;
            while (next != nullptr) {
                if (isValid(prev->data, curr->data, next->data)) {
                    return cout << "YES", true;
                }
                next = next->next;
            }
            curr = curr->next;
        }
        prev = prev->next;
    }
    return false;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    LinkedList myList;
    int n; cin >> n;
    for (int i = 0, digit; i < n; ++i) {
        cin >> digit;
        myList.push_back(make_node(digit));
    }
    if (!solve(myList)) cout << "NO";
    cerr << "Time elapsed: " << TIME << "s.";
    return 0;
}