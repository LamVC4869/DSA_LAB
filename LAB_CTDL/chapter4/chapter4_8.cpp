#include <iostream>
#include <sstream>

using namespace std;

template<class DataType>
class Queue;

template<class DataType>
class LinkedList;

template<class DataType>
class Node {
private:
    DataType data;
    Node<DataType>* next;
    friend class Queue<DataType>;
    friend class LinkedList<DataType>;
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

    bool empty() const {
        return !head && !tail;
    }

    int size() const {
        if (empty()) {
            return 0;
        }
        int result(0);
        for (Node<DataType>* p = head; p != nullptr; p = p->next) {
            result += 1;
        }
        return result;
    }

    void push(const DataType& data) {
        if (empty()) {
            head = tail = new Node<DataType>(data);
            return;
        }
        tail->next = new Node<DataType>(data);
        tail = tail->next;
    }

    void pop() {
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

    DataType& front() const {
        if (empty()) {
            cout << "Empty!\n";
            exit(0);
        }
        return head->data;
    }

    DataType& back() const {
        if (empty()) {
            cout << "Empty!\n";
            exit(0);
        }
        return tail->data;
    }

    void display() {
        if (empty()) {
            cout << "Empty!\n";
            return;
        }
        for (Node<DataType>* p = head; p != nullptr; p = p->next) {
            cout << p->data << ' ';
        }
        cout << '\n';
    }

    void clear() {
        while (!empty()) {
            pop();
        }
    }

    ~Queue() {
        clear();
    }
};

class KhachHang {
private:
    int so_ghe;
    string ten_khach_hang;
public:
    void setSoGhe(int so_ghe) {
        this->so_ghe = so_ghe;
    }
    void setTenKhachHang(string ten_khach_hang) {
        this->ten_khach_hang = ten_khach_hang;
    }
    int getSoGhe() const {
        return so_ghe;
    }
    string getTenKhachHang() const {
        return ten_khach_hang;
    }
    friend istream& operator >> (istream& is, KhachHang& khachHang) {
        string s;
        getline(is, s);
        khachHang.setTenKhachHang(s.substr(0, s.find('_')));
        s = s.substr(s.find('_') + 1);
        khachHang.setSoGhe(stoi(s));
        return is;
    }
    friend ostream& operator << (ostream& os, const KhachHang& khachHang) {
        os << khachHang.getTenKhachHang() << " - G" << khachHang.getSoGhe();
        return os;
    }
    bool operator == (const KhachHang& other) {
        return getSoGhe() == other.getSoGhe() && getTenKhachHang() == other.getTenKhachHang();
    }

    bool operator != (const KhachHang& other) {
        return getSoGhe() != other.getSoGhe() && getTenKhachHang() != other.getTenKhachHang();
    }

};

template<class DataType>
class LinkedList {
private:
    Node<DataType>* root;
public:
    LinkedList() : root(nullptr) {}

    bool empty() const {
        return !root;
    }

    bool found(const DataType& data) const {
        if (empty()) {
            return false;
        }
        for (Node<DataType>* p = root; p != nullptr; p = p->next) {
            if (p->data == data) {
                return true;
            }
        }
        return false;
    }

    void push_back(const DataType& data) {
        if (!root) {
            root = new Node<DataType>(data);
            return;
        }
        Node<DataType>* curr = root;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = new Node<DataType>(data);
    }

    void pop_front() {
        if (empty()) {
            return;
        }
        Node<DataType>* p = root;
        root = root->next;
        delete p;
    }

    void display() {
        for (Node<DataType>* p = root; p != nullptr; p = p->next) {
            cout << p->data << '\n';
        }
    }

    void interChangeSort() {
        for (Node<DataType>* p = root; p->next != nullptr; p = p->next) {
            for (Node<DataType>* next = p->next; next != nullptr; next = next->next) {
                if (p->data > next->data) {
                    swap(p->data, next->data);
                }
            }
        }
    }

    void remove(const DataType& data) {
        if (empty()) return;
        if (root->data == data) {
            pop_front();
            return;
        }
        Node<DataType>* p = root;
        while (p->next && (p->next->data != data)) {
            p = p->next;
        }
        if (!p->next) return;
        Node<DataType>* rmd = p->next;
        p->next = rmd->next;
        delete rmd;
    }

    void clear() {
        while (root) {
            Node<DataType>* p = root;
            root = root->next;
            delete p;
        }
    }

    ~LinkedList() {
        clear();
    }
};

class Solution {
private:
    LinkedList<int> A;
    Queue<int> B;
    LinkedList<KhachHang> C;
public:
    void themGheTrong(int k) {
        if (!A.found(k)) {
            A.push_back(k);
        }
    }

    void LaySoThuTu() {
        B.push((B.empty() ? 1 : (B.back() + 1)));
    }

    void ThemThongTinKhachHangDaMuaVe(const KhachHang& khachHang) {
        C.push_back(khachHang);
    }

    void MuaVe(const KhachHang& khachHang) {
        if (B.empty()) {
            cout << "Khong co khach hang trong hang doi\n";
            return;
        }
        if (!A.empty() && !B.empty()) {
            int top = B.front(); B.pop();
            ThemThongTinKhachHangDaMuaVe(khachHang);
            A.remove(top);
        }
    }

    void HuyVe(const KhachHang& khachHang) {
        if (C.empty() || !C.found(khachHang)) {
            return;
        }
        A.push_back(khachHang.getSoGhe());
        C.remove(khachHang);
        cout << "Da huy ve\n";
    }

    void HienThiKhachHangDaMuaVe() {
        cout << "Thong tin nhung khach hang da mua ve\n";
        if (C.empty()) 
            cout << "Khong co khach hang nao mua ve\n";
        else 
            C.display();
    }
};

void Menu() {
    Solution Lab4_8;
    while (true) {
        system("cls");
        cout << "-------------------------MENU-------------------------\n";
        cout << "1. Thoat chuong trinh\n";
        cout << "2. Khoi tao\n";
        cout << "3. Mua ve\n";
        cout << "4. Huy ve\n";
        cout << "5. Thong tin nhung ve da ban\n";
        cout << "6. Lay so xep hang\n";
        cout << "------------------------------------------------------\n";
        int LuaChon;
        cout << "Nhap lua chon: ";
        cin >> LuaChon;
        cin.ignore();
        if (LuaChon == 1) {
            exit(0);
        }
        else if (LuaChon == 2) {
            int n;
            cout << "Nhap so ghe trong: "; cin >> n;
            for (int i = 1; i <= n; ++i) {
                Lab4_8.themGheTrong(i);
            }
        }
        else if (LuaChon == 3) {
            KhachHang khachHang;
            cout << "Thong tin khach hang mua ve\n";
            cin >> khachHang;
            Lab4_8.MuaVe(khachHang);
        }
        else if (LuaChon == 4) {
            KhachHang khachHang;
            cout << "Thong tin khach hang bi huy ve\n";
            cin >> khachHang;
            Lab4_8.HuyVe(khachHang);
        }
        else if (LuaChon == 5) {
            Lab4_8.HienThiKhachHangDaMuaVe();
        }
        else if (LuaChon == 6) {
            Lab4_8.LaySoThuTu();
        }
        system("pause");
    }
}

int main() {
    Menu();
    return 0;
}