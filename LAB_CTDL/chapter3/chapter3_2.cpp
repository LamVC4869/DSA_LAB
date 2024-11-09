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
        void push_back (int x) {
            if (empty()) {
                root = new Node(x);
                return;
            }
            Node* curr = root;
            while (curr->next) curr = curr->next;
            curr->next = new Node(x);
        }
        void push_front (int x) {
            if (empty()) {
                root = new Node(x);
                return;
            }
            Node* newNode = new Node(x);
            newNode->next = root;
            root = newNode;
        }
        void pop_back () {
            if (empty()) {
                return;
            }
            if (!root->next) {
                delete root;
                root = nullptr;
                return;
            }
            Node* rmd = root;
            while (rmd->next->next) rmd = rmd->next;
            Node* ptr = rmd->next;
            rmd->next = nullptr;
            delete ptr;
        }
        void pop_front () {
            if (empty()) {
                return;
            }
            Node* rmd = root;
            root = root->next;
            delete rmd;
        }
        void display () {
            for (Node* p = root; p != nullptr; p = p->next) {
                cout << p->data << ' ';
            }
            cout << '\n';
        }
        void clear () {
            while (!empty()) {
                pop_front();
            }
        }
        bool found (int x) const {
            for (Node* p = root; p != nullptr; p = p->next) {
                if (p->data == x) {
                    return true;
                }
            }
            return false;
        }
        int SUM () const {
            int sum(0);
            for (Node* p = root; p != nullptr; p = p->next) {
                sum += p->data;
            }
            return sum;
        }
        int MAX () const {
            int ans(root->data);
            for (Node* p = root->next; p != nullptr; p = p->next) {
                ans = max(ans, p->data);
            }
            return ans;
        }
        //Phép nối
        LinkedList connectionList (const LinkedList& L1, const LinkedList& L2) {
            LinkedList L3;
            for (Node* p = L1.root; p != nullptr; p = p->next) {
                L3.push_back(p->data);
            }
            for (Node* p = L2.root; p != nullptr; p = p->next) {
                L3.push_back(p->data);
            }
            return L3;
        }
        //Phép hiệu
        LinkedList List_difference (const LinkedList& L1, const LinkedList& L2) {
            LinkedList L3;
            for (Node* current = L1.root; current != nullptr; current = current->next)
                if (!L2.found(current->data)) 
                    L3.push_back(current->data);

            return L3;
        }
        //Phép giao
        LinkedList List_intersection (const LinkedList& L1, const LinkedList& L2) {
            LinkedList L3;
            for (Node* current = L1.root; current != nullptr; current = current->next) {
                if (L2.found(current->data)) {
                    L3.push_back(current->data);
                }
            }
            return L3;
        }
        //Phép hợp
        LinkedList List_union (const LinkedList& L1, const LinkedList& L2) {
            LinkedList L3;
            for (Node* current = L1.root; current != nullptr; current = current->next)
                if (!L3.found(current->data))
                    L3.push_back(current->data);
            for (Node* current = L2.root; current != nullptr; current = current->next)
                if (!L3.found(current->data))
                    L3.push_back(current->data);
            return L3;
        }
        //Danh sách tổng
        LinkedList Sum_List (const LinkedList& L1, const LinkedList& L2) {
            LinkedList L3;
            Node* p1 = L1.root;
            Node* p2 = L2.root;
            while (p1 && p2) {
                L3.push_back((p1->data + p2->data));
                p1 = p1->next;
                p2 = p2->next;
            }
            while (p1) {
                L3.push_back(p1->data);
                p1 = p1->next;
            }
            while (p2) {
                L3.push_back(p2->data);
                p2 = p2->next;
            }
            return L3;
        }
        //Kiểm tra
        bool check (const LinkedList& other) const {
            for (Node* p = root; p != nullptr; p = p->next) {
                if (other.found(p->data)) {
                    return true;
                }
            }
            return false;
        }
        void removeFirstElement (const LinkedList& other) {
            if (!root) return;
            int sumOfList = other.SUM();
            Node* p = root;
            if (p->data > sumOfList) {
                pop_front();
                return;
            }
            Node* pre = p;
            p = p->next;
            while (p) {
                if (p->data > sumOfList) {
                    pre->next = p->next;
                    delete p;
                    break;
                }
                p = p->next;
                pre = pre->next;
            }
        }
        void remove (const LinkedList& other) {
            if (empty()) return;
            int MAX = other.MAX();
            while (!empty() && root->data == MAX) {
                pop_front();
            }
            if (empty()) return;
            Node* pre = root;
            Node* curr = pre->next;
            while (curr) {
                if (curr->data == MAX) {
                    pre->next = curr->next;
                    delete curr;
                    curr = pre->next;
                }
                else {
                    pre = pre->next;
                    curr = curr->next;
                }
            }
        }
};

void init (LinkedList& L) {
    int n; cin >> n;
    while (n--) {
        int x; cin >> x;
        L.push_back(x);
    }
}

int main () {
    LinkedList L1, L2;
    init(L1); init(L2);
    L1.display();
    L2.display();

    /*Tạo danh sách L3 bằng cách nối L2 vào sau L1*/
    LinkedList L3 = L1.connectionList(L1, L2);
    L3.display();

    /*Tạo danh sách L4 bao gồm các phần tử chỉ có trong L1 mà không có trong L2 
      (L4 là hiệu của L1 và L2)*/
    LinkedList L4  = L1.List_difference(L1, L2);
    L4.display();

    /*Tạo danh sách L5 bao gồm các phần tử vừa có trong L1 vừa có trong L2 
      (L5 là giao của L1 và L2)*/
    LinkedList L5  = L1.List_intersection(L1, L2);
    L5.display();

    /*Tạo danh sách L6 bao gồm các phần tử hoặc có trong L1 hoặc có trong L2 
      (L6 là hợp của L1 và L2)*/
    LinkedList L6 = L1.List_union(L1, L2);
    L6.display();

    /*Tạo danh sách tổng L7 sao cho
      - Có độ dài là độ dài lớn nhất của L1 và L2
      - Có giá trị phần tử là tổng các giá trị phần tử tương ứng của L1 và L2 
        (các phần tử bị thiếu trong danh sách ngắn hơn xem như có giá trị 0)*/
    LinkedList L7 = L1.Sum_List(L1, L2);
    L7.display();

    /*Kiểm tra 2 danh sách L1 và L2 có trùng giá trị hay không?*/
    cout << (L1.check(L2) ? "YES" : "NO") << '\n';

    /*Xóa một phần tử đầu tiên được tìm thấy trong L1 thỏa mãn điều kiện:
      giá trị của nó lớn hơn tổng giá trị phần tử của L2*/
    L1.removeFirstElement(L2);
    L1.display();

    /*Xóa tất cả các phần tử trong L1 có giá trị bằng giá trị lớn nhất trong L2*/
    L1.remove(L2);
    L1.display();

    return 0;
}