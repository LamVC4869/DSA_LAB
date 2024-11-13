#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class HangHoa {
    private:
        string ma_hang_hoa;
        string ten_hang_hoa;
        int so_luong;
        int don_gia;
    public:
        void setMaHangHoa (string ma_hang_hoa) {
            this->ma_hang_hoa = ma_hang_hoa;
        }
        void setTenHangHoa (string ten_hang_hoa) {
            this->ten_hang_hoa = ten_hang_hoa;
        }
        void setSoLuong (int so_luong) {
            this->so_luong = so_luong;
        }
        void setDonGia (int don_gia) {
            this->don_gia = don_gia;
        }
        string getMaHangHoa () const {
            return ma_hang_hoa;
        }
        string getTenHangHoa () const {
            return ten_hang_hoa;
        }
        int getSoLuong () const {
            return so_luong;
        }
        int getDonGia () const {
            return don_gia;
        }
        /*Mã hàng_Tên hàng_Số lượng_Đơn giá*/
        friend istream& operator >> (istream& is, HangHoa& hangHoa) {
            string str;
            getline(is, str);
            hangHoa.setMaHangHoa(str.substr(0, str.find('_')));
            str = str.substr(str.find('_') + 1);
            hangHoa.setTenHangHoa(str.substr(0, str.find('_')));
            str = str.substr(str.find('_') + 1);
            hangHoa.setSoLuong(stoi(str.substr(0, str.find('_'))));
            str = str.substr(str.find('_') + 1);
            hangHoa.setDonGia(stoi(str));
            return is;
        }

        friend ostream& operator << (ostream& os, const HangHoa& hangHoa) {
            os << "Ma Hang: " << hangHoa.getMaHangHoa() << '\n';
            os << "Ten Hang: " << hangHoa.getTenHangHoa() << '\n';
            os << "So luong: " << hangHoa.getSoLuong() << " - Don gia: " << hangHoa.getDonGia();
            return os;
        }
        void disPlay () {
            cout << "Ma Hang: " << ma_hang_hoa << '\n';
            cout << "Ten Hang: " << ten_hang_hoa << '\n';
            cout << "So luong: " << so_luong << " - Don gia: " << don_gia << '\n';
        }
};

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
            int i = 1;
            for (Node<DataType>* p = head; p != nullptr; p = p->next) {
                cout << "Mat hang thu " << i << '\n';
                cout << p->data << '\n';
                i++;
            }
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

void solve () {
    Queue<HangHoa> q;
    int n; cin >> n;
    cin.ignore();
    for (int i = 0; i < n; ++i) {
        HangHoa hangHoa;
        cin >> hangHoa;
        q.push(hangHoa);
    }
    //Xem tất cả hàng hóa trong kho
    q.display();
    //Xem mặt hàng sắp được xuất kho
    cout << "Mat hang sap duoc xuat kho\n";
    cout << q.front() << '\n';
    //Thêm 1 mặt hàng vào kho
    HangHoa newHangHoa;
    cin >> newHangHoa;
    q.push(newHangHoa);
    cout << "Da them 1 mat hang co ma hang: " << newHangHoa.getMaHangHoa() << " vao kho\n";
    //Xuất 1 mặt hàng ra khỏi kho
    string id = q.front().getMaHangHoa();
    q.pop();
    cout << "Da xuat mat hang co ma hang: " << id << " ra khoi kho";
}

int main () {
    solve();
    return 0;
}

/*
4
AK47_Lap Trinh Co Ban_47_20000
M4A1_Lap Trinh Nang Cao_50_25000
AK74_Cau Truc Du Lieu_30_30000
MBT03_Lap Trinh Python_55_15000
M249_Toan Roi Rac_20_50000
*/