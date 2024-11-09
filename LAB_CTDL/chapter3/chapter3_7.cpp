#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>

using namespace std;

//Đơn thức
class DonThuc {
private:
    int heSo, soMu;
public:
    void setHeSo(int heSo) {
        this->heSo = heSo;
    }
    void setSoMu(int soMu) {
        this->soMu = soMu;
    }
    int getHeSo() const {
        return heSo;
    }
    int getSoMu() const {
        return soMu;
    }
    friend istream& operator >> (istream& is, DonThuc& donThuc) {
        is >> donThuc.heSo >> donThuc.soMu;
        return is;
    }
    friend ostream& operator << (ostream& os, const DonThuc& donThuc) {
        if (abs(donThuc.heSo) == 1 && donThuc.soMu != 0) {
            os << "x";
            if (donThuc.soMu != 1) os << '^' << donThuc.soMu;
        }
        else {
            if (donThuc.heSo != 0) {
                os << abs(donThuc.heSo);
                if (donThuc.soMu > 0) {
                    os << 'x';
                    if (donThuc.soMu != 1) os << '^' << donThuc.soMu;
                }
            }
        }
        return os;
    }
    double value(double x) const {
        return double(this->heSo * pow(x, soMu));
    }
};

class Node {
private:
    DonThuc data;
    Node* next;
    friend class DaThuc;
public:
    Node(const DonThuc& data) : data(data), next(nullptr) {}
};

//Đa thức
class DaThuc {
private:
    Node* head;
public:
    DaThuc() : head(nullptr) {}
    void push_back(const DonThuc& donThuc) {
        if (!donThuc.getHeSo()) return;
        if (!head) {
            head = new Node(donThuc);
            return;
        }
        Node* curr = head;
        while (curr->next)
            curr = curr->next;
        curr->next = new Node(donThuc);
    }
    bool empty() const {
        return head == nullptr;
    }
    //Đạo hàm
    DaThuc daoHam() const {
        DaThuc result;
        Node* curr = this->head;
        while (curr != nullptr) {
            DonThuc temp;
            int heSo = curr->data.getHeSo() * curr->data.getSoMu();
            int soMu = curr->data.getSoMu() - 1;
            if (soMu >= 0) {
                temp.setHeSo(heSo);
                temp.setSoMu(soMu);
                result.push_back(temp);
            }
            curr = curr->next;
        }
        return result;
    }
    void disPlay() {
        if (!head) {
            cout << 0 << '\n';
            return;
        }
        Node* curr = head;
        if (curr->data.getHeSo() < 0) cout << '-';
        cout << curr->data;
        for (Node* ptr = curr->next; ptr != nullptr; ptr = ptr->next) {
            if (ptr != nullptr) {
                if (ptr->data.getHeSo() > 0)
                    cout << " + ";
                else
                    cout << " - ";
            }
            cout << ptr->data;
        }
        cout << '\n';
    }
    double value(const double x) const {
        if (!head) return (double)0;
        double result(0);
        for (Node* curr = head; curr != nullptr; curr = curr->next)
            result += curr->data.value(x);
        return result;
    }
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    bool found(const DonThuc& donThuc) const {
        for (Node* curr = head; curr != nullptr; curr = curr->next) {
            if (curr->data.getSoMu() == donThuc.getSoMu())
                return true;
        }
        return false;
    }
    DaThuc& operator = (const DaThuc& other) {
        if (this != &other) {
            this->clear();
            for (Node* curr = other.head; curr != nullptr; curr = curr->next) {
                this->push_back(curr->data);
            }
        }
        return *this;
    }
    void interchangeSort() {
        for (Node* curr = head; curr->next != nullptr; curr = curr->next) {
            for (Node* next = curr->next; next != nullptr; next = next->next) {
                if (curr->data.getSoMu() < next->data.getSoMu())
                    swap(curr->data, next->data);
            }
        }
    }
    DaThuc operator + (const DaThuc& other) {
        DaThuc F;
        Node* f1 = this->head;
        Node* f2 = other.head;
        while (f1 != nullptr && f2 != nullptr) {
            if (f1->data.getSoMu() > f2->data.getSoMu()) {
                F.push_back(f1->data);
                f1 = f1->next;
            }
            else if (f1->data.getSoMu() < f2->data.getSoMu()) {
                F.push_back(f2->data);
                f2 = f2->next;
            }
            else {
                DonThuc donThuc;
                donThuc.setHeSo(f1->data.getHeSo() + f2->data.getHeSo());
                donThuc.setSoMu(f1->data.getSoMu());
                F.push_back(donThuc);
                f1 = f1->next;
                f2 = f2->next;
            }
        }
        while (f1 != nullptr) {
            F.push_back(f1->data);
            f1 = f1->next;
        }
        while (f2 != nullptr) {
            F.push_back(f2->data);
            f2 = f2->next;
        }
        F.interchangeSort();
        return F;
    }
    DaThuc operator * (const DaThuc& other) {
        DaThuc F;
        if (!empty() && !other.empty()) {
            for (Node* f1 = this->head; f1 != nullptr; f1 = f1->next) {
                for (Node* f2 = other.head; f2 != nullptr; f2 = f2->next) {
                    DonThuc donThuc;
                    donThuc.setHeSo(f1->data.getHeSo() * f2->data.getHeSo());
                    donThuc.setSoMu(f1->data.getSoMu() + f2->data.getSoMu());
                    if (!F.found(donThuc)) {
                        F.push_back(donThuc);
                    }
                    else {
                        for (Node* curr = F.head; curr != nullptr; curr = curr->next) {
                            if (curr->data.getSoMu() == donThuc.getSoMu()) {
                                curr->data.setHeSo(curr->data.getHeSo() + donThuc.getHeSo());
                                break;
                            }
                        }
                    }
                }
            }
            F.interchangeSort();
        }
        return F;
    }
    ~DaThuc() {
        clear();
    }
};

void init (DaThuc& F) {
    string s;
    getline(cin, s);
    stringstream ss(s);
    vector<string> v;
    while (ss >> s) {
        v.push_back(s);
    }
    for (int i = 1; i < v.size(); i += 2) {
        DonThuc dt;
        dt.setHeSo(stoi(v[i - 1]));
        dt.setSoMu(stoi(v[i]));
        F.push_back(dt);
    }
}

int main() {
    //a
    DaThuc F1, F2;
    init(F1);
    init(F2);
    //b
    cout << "F1 = ";
    F1.disPlay();
    cout << "F2 = ";
    F2.disPlay();
    //c
    DaThuc F1_daoham = F1.daoHam();
    DaThuc F2_daoham = F2.daoHam();
    cout << "F1' = ";
    F1_daoham.disPlay();
    cout << "F2' = ";
    F2_daoham.disPlay();
    //d
    double x;
    cin >> x;
    cout << "F1(" << x << ") = " << F1.value(x) << '\n';
    cout << "F2(" << x << ") = " << F2.value(x) << '\n';
    //e
    DaThuc F3 = F1 + F2;
    cout << "F1 + F2 = ";
    F3.disPlay();
    DaThuc F4 = F1 * F2;
    cout << "F1 * F2 = ";
    F4.disPlay();
    return 0;
}