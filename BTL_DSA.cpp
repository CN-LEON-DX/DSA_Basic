#include <bits/stdc++.h>
using namespace std;

// thanh toán khác. 
// Khách hàng d?n thuê phòng thu?ng g?m các thông tin sau mã khách hàng, tên, dia chi, so dien thoai, ngày den, ngày di (d? r?ng n?u chua r?i), s? dêm..
// Phòng g?m mã phòng, day phong, chi tiet them.
// Nhân viên gồm các thông tin tên, dia chi, so dien thoai, cccd, he so luong, ch?c v? (Qu?n lý, thu ngân, …). 
// Khi khách hàng d?t phòng có th? d?t thêm các D?ch v? khác nhu gi?t ?i, minbar, .. v?i các thông tin liên quan nhu ngày d?t, s? lu?ng d?ch v? d?t, giá ti?n c?a d?ch v? dó.
// Hóa don thanh toán d?ch v? s? bao g?m các thông tin nhu: Mã hóa don, ngày thanh toán , thông tin c?a khách hàng, thông tin d?ch v? khách hàng dã s? d?ng(Ngày, Chi Ti?t, T?ng S? Ti?n). Trong dó T?ng s? ti?n = T?ng d?ch v? * giá d?ch v?.
// KhachHang
struct KhachHang{
    string sTenKH, sMaKH, sDiaChi, sSoDT, sNgayDen, sNgayDi;
};
// Phong
struct Phong{
    string sMaPH, sTenPhong, sDayPhong, sChiTietThem;
};
// Nhan Vien
struct NhanVien{
    string sMaNV, sTenNV, sDiaChi, sSoDT, sCCCD, sChucVu;
    float fHSL;
};
// Dich vu
struct DichVu{
    string sMaDV, sTenDV;
    float fGiaDV;
    string sNgaySDDV;
};
// Hóa don 
struct HoaDon_DV{
    string sMaHD, sNgayLapHD;
    struct KhachHang kh;
    vector<Phong> ph;
    struct NhanVien nv;
    vector<DichVu> dv;
};
 
struct Node{
    struct HoaDon_DV hd;
    Node* next;
    Node* prev;
};
struct List{
    Node* head; 
    Node* tail;
};
// Tao mot danh sach
void init(List &Q){
    Q.head = NULL;
    Q.tail = NULL;
}

// Các hàm ở đây thao tác:
// Ngoài ra còn cần xử lý các yêu cầu như: 
/*
    + Mã hóa đơn không được trùng nhau.
    + Mã phòng không được trùng nhau.
    + Mã dịch vụ không được trùng nhau.
    + Mã nhân viên không được trùng nhau.
    + Mã khách hàng không được trùng nhau.
    + Hóa đơn phải in theo mẫu có sẵn bên ảnh
*/
// + Mã hóa đơn không được trùng nhau.
bool checkExists_HD(List Q, string sMaHD){
    for (auto p = Q.head;p!=NULL;p = p->next){
        if (p->hd.sMaHD == sMaHD){
            return 1;
        }
    }
    return 0;
}
//   + Mã phòng không được trùng nhau.
bool checkExists_PH(List Q, string sMaPH){
    for (auto p = Q.head;p!=NULL;p = p->next){
        for (Phong x : p->hd.ph){
            if (x.sMaPH == sMaPH){
                return 1;
            }
        }
    }
    return 0;
}
// + Mã dịch vụ không được trùng nhau.
bool checkExists_DV(List Q, string sMaDV){
    for (auto p = Q.head;p!=NULL;p = p->next){
        for (DichVu x : p->hd.dv){
            if (x.sMaDV == sMaDV){
                return 1;
            }
        }
    }
    return 0;
}
// +Ma nhan vien khong duoc trung nhau
bool checkExists_NV(List Q, string sMaNV){
    for (auto p = Q.head;p!=NULL;p = p->next){
        if (p->hd.nv.sMaNV == sMaNV){
            return 1;
        }
    }
    return 0;
}
// + Ma khach hang khong duoc trung nhau
bool checkExists_KH(List Q, string sMaKH){
    for (auto p = Q.head;p!=NULL;p = p->next){
        if (p->hd.kh.sMaKH == sMaKH){
            return 1;
        }
    }
    return 0;
}
// Tinh so dem khach hang o ?
int soDem_KH(string sNgayDen, string sNgayDi){
    // 21-07-2023
    // 11-10-2023
    // Chưa xây dựng đc
    int year1 = stoi(sNgayDen.substr(6,4));
    int year2 = stoi(sNgayDi.substr(6,4));
    int moth1 = stoi(sNgayDen.substr(3,2));
    int moth2 = stoi(sNgayDi.substr(3,2));
    int day1 = stoi(sNgayDen.substr(0,2));
    int day2 = stoi(sNgayDi.substr(0,2)); 
    return abs((day2 - day1) + 30*(abs(moth1 - moth2)) + 365*(abs(year1 - year2)));
}

// Ham tính tổng tiền mà khách hàng sử dụng dvu
float tongTien_DV(vector<DichVu> dv){
    float tongTien = 0;
    for (DichVu x : dv){
        tongTien += x.fGiaDV;
    }
    return tongTien;
}
// KHÁCH HÀNG
void nhapKhachHang(List Q, KhachHang& kh){
    do{
        cout << "Nhap ten khach hang: "; cin >> kh.sTenKH;
    } while(checkExists_KH(Q, kh.sTenKH) || kh.sTenKH == "");
    cout << "Nhap ma khach hang: "; cin >> kh.sMaKH;
    cin.ignore();
    cout << "Nhap dia chi khach hang: "; getline(cin, kh.sDiaChi);
    cout << "Nhap so dien thoai khach hang: "; getline(cin, kh.sSoDT);
    cout << "Nhap ngay den: "; cin >> kh.sNgayDen;
    cout << "Nhap ngay di: "; cin >> kh.sNgayDi;
}
void hienKhachHang(KhachHang kh){
    cout << "Ma khach hang: " << kh.sMaKH << endl;
    cout << "Ho ten: " << kh.sTenKH << endl;
    cout << "Dia chi: " << kh.sDiaChi << endl;
    cout << "So dien thoai: " << kh.sSoDT << endl; 
    cout << "Ngay den: " << kh.sNgayDen << endl;
    cout << "Ngay di: " << kh.sNgayDi << endl;
}
void suaThongTinKH_Ten(KhachHang &kh){
    string name="";
    cin.ignore(1);
    do {
        cout << "Nhap ten de doi: "; getline(cin, name);
    }while (name == "");
    kh.sTenKH = name;
    cout << "Doi ten thanh cong !\n";
}

// PHÒNG

void nhapPhong(List Q, Phong &ph){
    do {
        cout << "Nhap vao ma phong: "; cin >> ph.sMaPH;
    }while (checkExists_PH(Q, ph.sMaPH) || ph.sMaPH == "");
    cout << "Nhap vao ten phong: "; cin >> ph.sTenPhong;
    cout << "Nhap vao day phong: "; cin >>  ph.sDayPhong;
    cout << "Nhap vao chi tiet them: "; cin >> ph.sChiTietThem;
}
void hienPhong(Phong ph){
    cout << "Ma phong: " << ph.sMaPH << endl;
    cout << "Ten phong: " << ph.sTenPhong << endl;
    cout << "Day phong: " << ph.sDayPhong << endl;
    cout << "Chi tiet: " << ph.sChiTietThem << endl;
}
void suaThongTinPH_ChitietThem(Phong &ph){
    string chiTiet = "";
    do{
        cout << "Nhap vao chi tiet them :"; getline(cin, chiTiet);
    }while (chiTiet == "");
    ph.sChiTietThem = chiTiet;
    cout << "Them chi tiet thanh cong !\n";
}

// NHÂN VIÊN
void nhapNhanVien(List Q, NhanVien &nv){
    do{
        cout << "Nhap ma nhan vien :"; cin >> nv.sMaNV;
    } while (checkExists_NV(Q, nv.sMaNV) || nv.sMaNV == "");
    cout << "Nhap ten nhan vien :"; cin >> nv.sTenNV;
    cout << "Nhap dia chi: "; cin >> nv.sDiaChi; 
    cout << "Nhap so dien thoai: "; cin >> nv.sSoDT;
    cout << "Nhap can cuoc cong dan: "; cin >> nv.sCCCD;
    cout << "Nhap chuc vu: "; cin >> nv.sChucVu;
    cout << "Nhap he so luong: "; cin >> nv.fHSL; 
}
void hienNhanVien(NhanVien nv){
    cout << "Ma nhan vien: " << nv.sMaNV << endl;
    cout << "Ten nhan vien: " << nv.sTenNV << endl;
    cout << "Dia chi: " << nv.sDiaChi << endl;
    cout << "So dien thoai: " << nv.sSoDT << endl;
    cout << "CCCD: " << nv.sCCCD << endl;
    cout << "Chuc vu: " << nv.sChucVu << endl;
    cout << "He so luong: " << nv.fHSL << endl;
}
void chinhSua_HSL_NhanVien(NhanVien &nv){
    double hsl_new;
    do {
        cout << "Nhap vao he so luong: "; cin >> hsl_new;
    } while (hsl_new <=0);
    nv.fHSL = hsl_new;
    cout << "Cap nhat he so luong thanh cong !\n";
}

// DỊCH VỤ
void nhapDichVu(List Q, DichVu &dv){
    do{
    cout << "Nhap ma dich vu: "; cin >> dv.sMaDV;
    }while(checkExists_DV(Q, dv.sMaDV) || dv.sMaDV == "");
    cout << "Nhap ten dich vu: "; cin >> dv.sTenDV;
    cout << "Nhap gia dich vu: "; cin >> dv.fGiaDV;
    cout << "Nhap ngay su dung dich vu: "; cin >> dv.sNgaySDDV;
}
void hienDichVu(DichVu dv){
    cout << "Ma dich vu: "<< dv.sMaDV << endl;
    cout << "Ten dich vu: "<< dv.sTenDV << endl;
    cout << "Gia dich vu: "<< dv.fGiaDV << endl;
    cout << "Ngay su dung dich vu: "<< dv.sNgaySDDV << endl;
}
void capNhat_Gia_DV(vector<DichVu> &dv, string sMaDV){
    float gia_new;
    bool check_found = false;
    for (DichVu &x : dv){
        if (x.sMaDV == sMaDV){
            check_found = true;
            do{
                cout << "Nhap gia dich vu: "; cin >> gia_new;
            }while(gia_new<=0);
            x.fGiaDV = gia_new;
            cout << "Cap nhat thanh cong !\n";
            break;
        }
    }
    if (!check_found) cout << "Khong tim thay dich vu ban can cap nhat !\n";
}

// THAO TÁC VỚI DANH SÁCH ;
// Tao mot nut moi 
Node* Get_Node(HoaDon_DV x){
    Node *p;
    p = new Node;
    if (p==NULL){
        cout << "Khong du bo nho: ";
        return NULL;
    }
    p->hd = x;
    p->next = NULL;
    p->prev = NULL;
    return p;
}
// them vao dau danh sach 
void AddFirst(List &Q, Node *new_element){
    if (Q.head == NULL){
        Q.head = new_element;
        Q.tail = Q.head;
    }else{
        new_element -> next = Q.head;
        Q.head ->prev = new_element;
        Q.head = new_element;
    }
}
// Them voa cuoi danh sach
void AddLast(List &Q, Node *new_element){
    if (Q.head == NULL){
        Q.head = new_element;
        Q.tail = Q.head;
    }
    else {
        Q.tail -> next = new_element;
        new_element -> prev = Q.tail;
        Q.tail = new_element;
    }
}


void nhapHoaDon(List &Q){
    HoaDon_DV hd;
    int soHD;
    cout << "Ban can nhap bao nhiêu hoa don:"; cin >> soHD;
    for (int i=1;i<=soHD;i++){
        cin.ignore(1);
        cout << "Nhap ma hoa don :"; getline(cin, hd.sMaHD);
        if (checkExists_HD(Q, hd.sMaHD)){
            cout << "Ma hoa don da ton tai !\n";
            continue;
        }
        cout << "Nhap ngay lap hoa don:"; getline(cin, hd.sNgayLapHD);
        nhapKhachHang(Q, hd.kh);
        int soPhong;
        do{
            cout << "Ban can nhap bao nhieu phong:"; cin >> soPhong;
        }while (soPhong<=0||soPhong>=10);
        for (int i = 1;i<=soPhong;i++){
            Phong ph;
            nhapPhong(Q, ph);
            hd.ph.push_back(ph);
        }
        nhapNhanVien(Q, hd.nv);
        int soDV;
        do{
            cout << "Ban can nhap bao nhieu dich vu:"; cin >> soDV;
        }while (soDV<=0 || soDV>10);
        for (int i=1;i<=soDV;i++){
            DichVu dv;
            nhapDichVu(Q, dv);
            hd.dv.push_back(dv);
        }
        // Tao mot node chua thong tin hoa don 
        Node *p = Get_Node(hd);
        // Sau no them vao cuoi danh sach 
        if (p != NULL) {
            AddLast(Q, p);
            cout << "Them thanh cong!\n";
        }else cout << "Error!\n";
    }
}
void hienHoaDon(HoaDon_DV hd){
    cout << "--- Thong tin hoa don ---\n";
    cout << "Ma hoa don: " << hd.sMaHD << endl;
    cout << "Ngay lap hoa don: " << hd.sNgayLapHD << endl;
    cout << "Thong tin khach hang: " << endl;
    hienKhachHang(hd.kh);
    cout << "Thong tin phong: " << endl;
    for (Phong x : hd.ph){
        hienPhong(x);
    }
    cout << "Thong tin nhan vien: " << endl;
    hienNhanVien(hd.nv);
    cout << "Thong tin dich vu: " << endl;
    for (DichVu x : hd.dv){
        hienDichVu(x);
    }
}
void chinhSuaThongTin_HoaDon(List &Q){
    string sMaHD;
    cout << "Nhap vao ma hoa don ban can chinh sua thong tin:"; cin >> sMaHD;
    bool check_found = false;
    for (auto p = Q.head;p!=NULL;p = p->next){
        if (p->hd.sMaHD==sMaHD){
            check_found = true;
            int chon = -1;
            do{
                cout << "Ban muon chinh sua thong tin gi ?\n";
                cout << "1. Chinh sua thong tin ten khach hang !\n";
                cout << "2. Chinh sua thong tin chi tiet them cua phong !\n";
                cout << "3. Chinh sua thong tin he so luong nhan vien !\n";
                cout << "4. Chinh sua thong tin gia dich vu !\n";
                cout << "5. Chinh sua thong tin hoa don !\n";
                cout << "0. Thoat chinh sua !\n";
                cout << "Moi ban chon:"; cin >> chon;
                switch (chon){
                    case 1:{
                        suaThongTinKH_Ten(p->hd.kh);
                        break;
                    }
                    case 2:{
                        int soPhong;
                        do{
                            cout << "Nhap vao so can phong thu ?:"; cin >> soPhong;
                        }while (soPhong<=0 || soPhong>(int)p->hd.ph.size());
                        cin.ignore(1);
                        suaThongTinPH_ChitietThem(p->hd.ph[soPhong-1]);
                        break;
                    }
                    
                    case 3:{
                        chinhSua_HSL_NhanVien(p->hd.nv);
                        break;
                    }
                    case 4:{
                        string sMaDV;
                        cout << "Nhap vao ma dich vu can chinh sua:"; cin >> sMaDV;
                        capNhat_Gia_DV(p->hd.dv, sMaDV);
                        break;
                    }
                    case 5:{
                        cout << "Nhap vao ngay lap hoa don moi:"; getline(cin, p->hd.sNgayLapHD);
                        cout << "Cap nhat thanh cong !\n";
                        break;
                    }
                    default:{
                        if (chon <= 0 || chon >=6)
                        cout << "Ban chon sai roi moi ban chon lai !\n";
                    }
                }
            }while (chon>=1 && chon<=5);
            break;
        }
    }
    if (!check_found) cout << "Khong tim thay hoa don cua ban !\n";
}


// Ham lay so luong danh sach hoa don 
int soLuongHoaDon(List Q){
    Node *p = Q.head;
    int cnt = 0;
    for (auto it = p;it != NULL;it = it->next) cnt++;
    return cnt;
}

// Hien danh sach hoa don dang co !
void HienDS_DSHD(List Q){
    Node *p = Q.head;
    if (soLuongHoaDon(Q)==0) {
        cout << "Danh sach trong !" << endl;
        return;
    }
    for (auto i=1;i<=soLuongHoaDon(Q);i++){
        hienHoaDon(p->hd);
        p = p->next;
    }
    cout << "------------------------------------" << endl;
}
// Xóa mot phan tu trong danh sách sau khi tìm du?c p;
void DeleteNode(Node* p, List &Q){
    if(p==Q.head && p==Q.tail){
        Q.head = NULL;
        Q.tail = NULL;
    }
    else if(Q.head == p){
        Q.head = p->next;
    }else if (p==Q.tail){
        p->prev -> next = NULL;
        Q.tail = p->prev;
    }else {
        p->prev -> next = p->next;
        p->next -> prev = p->prev;
    }
    delete p;
}
// Xoa mot hoa don ra khoi danh sach dua vao ma hoa don
void XoaHD_MaHD(List &Q) {
    string sMaHD;
    cout << "Nhap vao ma hoa don can xoa: ";
    cin.ignore();
    getline(cin, sMaHD);

    Node* prev = NULL;
    Node* curr = Q.head;

    while (curr != NULL) {
        if (curr->hd.sMaHD == sMaHD) {
            if (prev == NULL) {
                Q.head = curr->next;
            } else {
                prev->next = curr->next;
            }
            delete curr;
            cout << "Xoa hoa don thanh cong!\n";
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    cout << "Khong tim thay hoa don voi ma hoa don " << sMaHD << "!\n";
}
// Hoán đổi node của danh sách 2 chiều



// Tim kiem hoa don theo ma hoa don !
void TimHD_maHD(List Q){
    string sMaHD;
    cout << "Nhap vao ma hoa don can tim kiem:"; cin >> sMaHD;
    bool check_found = false;
    for (auto p = Q.head;p!=NULL;p = p->next){
        if (p->hd.sMaHD == sMaHD){
            check_found = true;
            cout << "Tìm thấy hoa don cua ban !\n";
            hienHoaDon(p->hd);
            break;
        }
    }
    if (!check_found) cout << "Khong tim thay hoa don \n";
}
void TimHD_TenKH(List Q){
    string sTenKH;
    cin.ignore(1);
    cout << "Nhap vao ten khach hang can tim kiem:"; getline(cin, sTenKH);
    bool check_found = false;
    for (auto p = Q.head;p!=NULL;p = p->next){
        if (p->hd.kh.sTenKH == sTenKH){
            check_found = true;
            cout << "Tìm thấy hoa don cua ban !\n";
            hienHoaDon(p->hd);
            break;
        }
    }
    if (!check_found) cout << "Khong tim thay hoa don \n";
}


void sapXep_DSHD_MaHD(List &Q){
    cout << "Danh sach ma hoa don luc dau la: \n";
    for (auto p = Q.head;p!=NULL;p = p->next){
        cout << p->hd.sMaHD << endl;
    }
    for (auto i = Q.head;i!= Q.tail;i = i->next){
        for (auto j=i->next;j!=NULL;j = j->next){
            if (i->hd.sMaHD > j->hd.sMaHD){
                swap(i->hd.sMaHD, j->hd.sMaHD);
            }
        }
    }
    cout << "Danh sach ma hoa don sau khi sap xep la: \n";
    for (auto p = Q.head;p!=NULL;p = p->next){
        cout << p->hd.sMaHD << endl;
    }
    cout << "Danh sach da xap xep thanh cong !\n";
}
void sapXep_DSHD_NgayLapHD(List &Q){
    cout << "Cac ngay lap luc dau la: \n";
    for (auto p = Q.head;p!=NULL;p = p->next){
        cout << p->hd.sNgayLapHD << endl;
    }
    for (auto i = Q.head;i!= Q.tail;i = i->next){
        for (auto j=i->next;j!=NULL;j = j->next){
            if (i->hd.sNgayLapHD > j->hd.sNgayLapHD){
               swap(i->hd.sNgayLapHD, j->hd.sNgayLapHD);
            }
        }
    }
    cout << "Cac ngay lap sau khi sap xep la: \n";
    for (auto p = Q.head;p!=NULL;p = p->next){
        cout << p->hd.sNgayLapHD << endl;
    }
    cout << "Danh sach da xap xep thanh cong !\n";
}
void sapXep_DSHD_TenKH(List &Q){
    cout << "Danh sach ten khach hang luc dau la: \n";
    for (auto p = Q.head;p!=NULL;p = p->next){
        cout << p->hd.kh.sTenKH << endl;
    }
    for (auto i = Q.head;i!= Q.tail;i = i->next){
        for (auto j=i->next;j!=NULL;j = j->next){
            if (i->hd.kh.sTenKH > j->hd.kh.sTenKH){
                 swap(i->hd.kh.sTenKH, j->hd.kh.sTenKH);
            }
        }
    }
    cout << "Danh sach ten khach hang sau khi sap xep la: \n";
    for (auto p = Q.head;p!=NULL;p = p->next){
        cout << p->hd.kh.sTenKH << endl;
    }
    cout << "Danh sach da xap xep thanh cong !\n";
}
// Tinh tong tien tung hoa don 1 cach rieng le

void sapXep_DSHD_TongTien(List &Q){
    cout << "Danh sach tong tien luc dau la: \n";
    for (auto p = Q.head;p!=NULL;p = p->next){
        cout << fixed << tongTien_DV(p->hd.dv) << endl;
    }
    for (auto i = Q.head;i!= Q.tail;i = i->next){
        for (auto j=i->next;j!=NULL;j = j->next){
            if (tongTien_DV(i->hd.dv) > tongTien_DV(j->hd.dv)){
                swap(i->hd.dv, j->hd.dv);
            }
        }
    }
    cout << "Danh sach tong tien sau khi sap xep la: \n";
    for (auto p = Q.head;p!=NULL;p = p->next){
        cout << fixed <<  tongTien_DV(p->hd.dv) << endl;
    }
    cout << "Danh sach da xap xep thanh cong !\n";
}

void timHD_TongTien_Min(List Q){
    float min = tongTien_DV(Q.head->hd.dv);
    Node *p = Q.head;
    for (auto it = p;it!=NULL;it = it->next){
        if (tongTien_DV(it->hd.dv) < min){
            min = tongTien_DV(it->hd.dv);
        }
    }
    cout << "Hoa don co tong tien thanh toan nho nhat la: \n";
    for (auto it = p;it!=NULL;it = it->next){
        if (tongTien_DV(it->hd.dv) == min){
            hienHoaDon(it->hd);
        }
    }
}
void timHD_TongTien_Max(List Q){
    float max = tongTien_DV(Q.head->hd.dv);
    Node *p = Q.head;
    for (auto it = p;it!=NULL;it = it->next){
        if (tongTien_DV(it->hd.dv) > max){
            max = tongTien_DV(it->hd.dv);
        }
    }
    cout << "Hoa don co tong tien thanh toan lon nhat la: \n";
    for (auto it = p;it!=NULL;it = it->next){
        if (tongTien_DV(it->hd.dv) == max){
            hienHoaDon(it->hd);
        }
    }
}
void timHD_SoNgayLuutru_Max(List Q){
    int max = soDem_KH(Q.head->hd.kh.sNgayDen, Q.head->hd.kh.sNgayDi);
    Node *p = Q.head;
    for (auto it = p;it!=NULL;it = it->next){
        if (soDem_KH(it->hd.kh.sNgayDen, it->hd.kh.sNgayDi) > max){
            max = soDem_KH(it->hd.kh.sNgayDen, it->hd.kh.sNgayDi);
        }
    }
    cout << "Hoa don co so ngay luu tru nhieu nhat la: \n";
    for (auto it = p;it!=NULL;it = it->next){
        if (soDem_KH(it->hd.kh.sNgayDen, it->hd.kh.sNgayDi) == max){
            hienHoaDon(it->hd);
        }
    }
}
void timHD_SoNgayLuutru_Min(List Q){
    int min = soDem_KH(Q.head->hd.kh.sNgayDen, Q.head->hd.kh.sNgayDi);
    Node *p = Q.head;
    for (auto it = p;it!=NULL;it = it->next){
        if (soDem_KH(it->hd.kh.sNgayDen, it->hd.kh.sNgayDi) < min){
            min = soDem_KH(it->hd.kh.sNgayDen, it->hd.kh.sNgayDi);
        }
    }
    cout << "Hoa don co so ngay luu tru it nhat la: \n";
    for (auto it = p;it!=NULL;it = it->next){
        if (soDem_KH(it->hd.kh.sNgayDen, it->hd.kh.sNgayDi) == min){
            hienHoaDon(it->hd);
        }
    }
}

// TInh tong thanh toan  
void tinhtongThanhToan_HD(List Q){
    double tongThanhToan = 0;
    for (auto p = Q.head;p!=NULL;p = p->next){
        tongThanhToan += tongTien_DV(p->hd.dv);
    }
    cout << "Tong thanh toan cua tat ca cac hoa don la: " << fixed << tongThanhToan << endl;
}   
void trungbinhThanhToan_HD(List Q){
    float tongThanhToan = 0;
    for (auto p = Q.head;p!=NULL;p = p->next){
        tongThanhToan += tongTien_DV(p->hd.dv);
    }
    cout << "Trung binh thanh toan cua tat ca cac hoa don la: " << tongThanhToan/soLuongHoaDon(Q) << endl;
}

void demSoNgayLuutru_LonHon5Ngay(List Q){
    int cnt = 0;
    for (auto p = Q.head;p!=NULL;p = p->next){
        if (soDem_KH(p->hd.kh.sNgayDen, p->hd.kh.sNgayDi) > 5){
            cnt++;
        }
    }
    cout << "So hoa don co so ngay luu tru lon hon 5 ngay la: " << cnt << endl;
}
void thongKe_SoLuongHD_TheoThang(List Q){
    int thang;
    cout << "Nhap vao thang can thong ke:"; cin >> thang;
    int cnt = 0;
    for (auto p = Q.head;p!=NULL;p = p->next){
        if (stoi(p->hd.sNgayLapHD.substr(3,2)) == thang){
            cnt++;
        }
    }
    cout << "So luong hoa don trong thang " << thang << " la: " << cnt << endl;
}
void thongKe_SoLuongNV_TheoChucVu(List Q){
    string sChucVu;
    cin.ignore(1);
    cout << "Nhap vao chuc vu can thong ke:"; getline(cin, sChucVu);
    int cnt = 0;
    for (auto p = Q.head;p!=NULL;p = p->next){
        if (p->hd.nv.sChucVu == sChucVu){
            cnt++;
        }
    }
    cout << "So luong nhan vien co chuc vu " << sChucVu << " la: " << cnt << endl;
}
void thongKe_SoLuongKH_TheoThang(List Q){
    int thang;
    cout << "Nhap vao thang can thong ke: ";
    cin >> thang;
    int cnt = 0;
    for (auto p = Q.head; p != NULL; p = p->next){
        string tmp = p->hd.kh.sNgayDen;
        int month = stoi(tmp.substr(3,2));
        if (month == thang){
            cnt++;
        }
    }
    cout << "So luong khach hang den trong thang " << thang << " la: " << cnt << endl;
}
void thongKe_SoLuongPH_TheoDayNha(List Q){
    string sDayNha;
    cin.ignore(1);
    cout << "Nhap vao day nha can thong ke: ";
    getline(cin, sDayNha);
    int cnt = 0;
    for (auto p = Q.head; p != NULL; p = p->next){
        for (Phong ph : p->hd.ph){
            if (ph.sDayPhong == sDayNha){
                cnt++;
            }
        }
    }
    cout << "So luong phong trong day nha " << sDayNha << " la: " << cnt << endl;
}

// Doc file DSHD.txt de nhan vao cac thong tin cua danh sach !
void readFile_AddHD(List &Q){
    ifstream readfile;
    string empty_line;
    readfile.open("D:/DSA2023-1/BTL/Input_DSHD.txt", ios::in | ios::out);
    if (readfile.fail()){
        cout << "Khong the mo file !\n";
        return;
    }else {
        try {
            while (!readfile.eof()){
                HoaDon_DV hd;
                do {
                    getline(readfile, hd.sMaHD);
                    if (hd.sMaHD == "ENDFILE") return;
                }while (hd.sMaHD == "");
                getline(readfile, hd.sNgayLapHD);
                getline(readfile, hd.kh.sMaKH);
                getline(readfile, hd.kh.sTenKH);
                getline(readfile, hd.kh.sDiaChi);
                getline(readfile, hd.kh.sSoDT);
                getline(readfile, hd.kh.sNgayDen);
                getline(readfile, hd.kh.sNgayDi);
                int soPhong;
                readfile >> soPhong;
                char xu_ly_troi_lenh; readfile >> xu_ly_troi_lenh;
                for (int i=1;i<=soPhong;i++){
                    Phong ph;
                    getline(readfile, ph.sMaPH);
                    getline(readfile, ph.sTenPhong);
                    getline(readfile, ph.sDayPhong);
                    getline(readfile, ph.sChiTietThem);
                    hd.ph.push_back(ph);
                }
                getline(readfile, hd.nv.sMaNV);
                getline(readfile, hd.nv.sTenNV);
                getline(readfile, hd.nv.sDiaChi);
                getline(readfile, hd.nv.sSoDT);
                getline(readfile, hd.nv.sCCCD);
                getline(readfile, hd.nv.sChucVu);
                readfile >> hd.nv.fHSL;
                int soDV;
                cout << soDV << endl;
                readfile >> soDV;
                readfile >> xu_ly_troi_lenh;
                for (int i=1;i<=soDV;i++){
                    DichVu dv;
                    getline(readfile, dv.sMaDV);
                    getline(readfile, dv.sTenDV);
                    readfile >> dv.fGiaDV;
                    readfile >> xu_ly_troi_lenh;
                    getline(readfile, dv.sNgaySDDV);
                    hd.dv.push_back(dv);
                }
                Node *p = Get_Node(hd);
                if (p != NULL) {
                    bool duplicate = false;
                    for (auto node = Q.head; node != NULL; node = node->next) {
                        if (node->hd.sMaHD == hd.sMaHD) {
                            duplicate = true;
                            return;
                        }
                    }
                    if (!duplicate) {
                        AddLast(Q, p);
                        cout << "Them vao tu file thanh cong !\n";
                    } else {
                        cout << "Hoa don da ton tai, bo qua hoa don nay!\n";
                    }
                } else {
                    cout << "Error!\n";
                }
            }
        } catch(exception e){
            cout << e.what() << endl;
            cout << "Loi doc file ! Kiem tra lai file input !\n";
        }
    }
    readfile.close();
    readfile.clear();
}
// In danh sach cac hoa don theo file danh sach !
void writeFile_DSHD(List Q){
    ofstream writefile;
    writefile.open("D:/DSA2023-1/BTL/Output_DSHD.txt", ios::out | ios::app);
    if (writefile.fail()){
        cout << "Khong the mo file !\n";
        return;
    }else {
        try{
            cout<<"Bat dau ghi file !\n";
            writefile << "Danh sach hoa don hien co la: \n";
            for (Node* p = Q.head;p!=NULL;p = p->next){
                writefile << setw(20) << "                     HOA DON THANH TOAN DICH VU           " << endl;
                writefile << setw(15) << "Ngày " << p->hd.sNgayLapHD << setw(30) << "Mã hóa đơn: " << p->hd.sMaHD << endl;
                writefile << "-----------------------------------------------------------------------------------\n";
                writefile << setw(10) << "Ten               :" << p->hd.kh.sTenKH << setw(20) << "Ngay den:" << p->hd.kh.sNgayDen << endl;
                writefile << setw(10) << "Dia chi           :" << p->hd.kh.sDiaChi << setw(15) << "Ngay di:" << p->hd.kh.sNgayDi << endl;
                writefile << setw(10) << "So dien thoai     :" << p->hd.kh.sSoDT << setw(26) << "So dem :" << soDem_KH(p->hd.kh.sNgayDen, p->hd.kh.sNgayDi) << endl;
                writefile << setw(10) << "Ma so thue        :" << "VCB2023" << setw(30) << "Thu ngan:" << " Quan tri" << endl;
                writefile << setw(10) << "Phong             :" << p->hd.ph[0].sMaPH << setw(36) << "Thanh toan: "<< "Chua thanh toan " << endl;
                writefile << "-----------------------------------------------------------------------------------\n";
                writefile << setw(10) << "Ngay              " <<setw(15) << "Chi Tiet " << setw(19) << "So tien " << endl;  
                for (DichVu x : p->hd.dv){
                    writefile << setw(8) << x.sNgaySDDV << setw(20) << x.sTenDV << setw(19) << fixed << setprecision(2) << x.fGiaDV << endl;
                }
                writefile << "Tong thanh toan: " << fixed << setprecision(2) << tongTien_DV(p->hd.dv) << endl;
                writefile << "-----------------------------------------------------------------------------------\n";
            }
            cout << "Ghi file thanh cong !\n";
        } catch (exception e){
            cout << e.what() << endl;
            cout << "Loi ghi file !\n";
        }
    }
    writefile.close();
    writefile.clear();
}
int main(){
    List Q;
    init(Q);
    int chon = -1;
    do{
        cout << "-----------------QUAN LY HOA DON DICH VU-------------\n";
        cout << "1. Them vao cuoi danh cac hoa don !\n";
        cout << "2. Hien danh sach hoa don hien co !\n";
        cout << "3. Tim kiem hoa don theo ma hoa don !\n";
        cout << "4. Tìm kiếm hóa đơn theo tên khách hàng !\n";
        cout << "5. Xoa hoa don bang ma hoa don nhap vao !\n";
        cout << "6. Chinh sua thong tin cua cac hoa don (Chon de biet them chi tiet !)\n";
        cout << "7. Sap xep danh sach hoa don theo ma hoa don !\n";
        cout << "8. Sap xep danh sach hoa don theo ngay lap hoa don !\n";
        cout << "9. Sap xep danh sach hoa don theo ten khach hang !\n";  
        cout << "10. Sap xep danh sach hoa don theo so tien thanh toan !\n";
        cout << "11. Tìm hóa đơn có tổng thanh toán nhỏ nhất !\n";
        cout << "12. Tìm hóa đơn có tổng thanh toán lớn nhất !\n";
        cout << "13. Tìm hóa đơn có số ngày lưu trú dài nhất !\n";
        cout << "14. Tìm hóa đơn có số ngày lưu trú ngắn nhất !\n";
        cout << "15. Tính tổng thanh toán các hóa đơn !\n";
        cout << "16. Tính trung bình thanh toán các hóa đơn !\n";
        cout << "17. Đếm số hóa đơn có số ngày lưu trú lớn hơn 5 ngày !\n";
        cout << "18. Thống kê số lượng hóa đơn theo từng tháng !\n";
        cout << "19. Thống kê số lương nhân viên theo từng chức vụ !\n";
        cout << "20. Thống kê số lượng khách hàng theo từng tháng !\n";
        cout << "21. Thống kê số lượng phòng theo từng dãy phòng !\n";
        cout << "22. Them cac hoa don duoc doc tu  file Input_DSHD.txt !\n";
        cout << "23. Viet danh sach cac hoa don ra file Output_DSHD.txt !\n";
        cout << "0. Thoat chuong trinh !\n";
        cout << "Moi ban chon:"; cin >> chon;
        switch (chon){
            case 1:
                nhapHoaDon(Q);
                break;
            case 2:
                HienDS_DSHD(Q);
                break;
            case 3:
                TimHD_maHD(Q);
                break;
            case 4:
                TimHD_TenKH(Q);
                break;
            case 5:
                XoaHD_MaHD(Q);
                break;
            case 6:
                chinhSuaThongTin_HoaDon(Q);
                break;
            case 7:
                sapXep_DSHD_MaHD(Q);
                break;
            case 8:
                sapXep_DSHD_NgayLapHD(Q);
                break;
            case 9:
                sapXep_DSHD_TenKH(Q);
                break;
            case 10:
                sapXep_DSHD_TongTien(Q);
                break;
            case 11:
                timHD_TongTien_Min(Q);
                break;
            case 12:
                timHD_TongTien_Max(Q);
                break;
            case 13:
                timHD_SoNgayLuutru_Max(Q);
                break;
            case 14:
                timHD_SoNgayLuutru_Min(Q);
                break;
            case 15:
                tinhtongThanhToan_HD(Q);
                break;
            case 16:
                trungbinhThanhToan_HD(Q);
                break;
            case 17:
                demSoNgayLuutru_LonHon5Ngay(Q);
                break;
            case 18:
                thongKe_SoLuongHD_TheoThang(Q);
                break;
            case 19:
                thongKe_SoLuongNV_TheoChucVu(Q);
                break;
            case 20:
                thongKe_SoLuongKH_TheoThang(Q);
                break;
            case 21:
                thongKe_SoLuongPH_TheoDayNha(Q);
                break; 
            case 22:
                readFile_AddHD(Q);
                break;
            case 23:
                writeFile_DSHD(Q);
                break;
            default:
                cout << "Ban chon sai roi moi ban chon lai !\n";
        }
    } while (chon>=1 && chon<=23);
    return 0;
}
