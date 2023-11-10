#include <bits/stdc++.h>
using namespace std;

// thanh toán khác. 
// Khách hàng d?n thuê phòng thu?ng g?m các thông tin sau mã khách hàng, tên, dia chi, so dien thoai, ngày den, ngày di (d? r?ng n?u chua r?i), s? dêm..
// Phòng g?m mã phòng, day phong, chi tiet them.
// Nhân viên gồm các thông tin tên, dia chi, so dien thoai, cccd, he so luong, ch?c v? (Qu?n lý, thu ngân, …). 
// Khi khách hàng d?t phòng có th? d?t thêm các D?ch v? khác nhu gi?t ?i, minbar, .. v?i các thông tin liên quan nhu ngày d?t, s? lu?ng d?ch v? d?t, giá ti?n c?a d?ch v? dó.
// Hóa don thanh toán d?ch v? s? bao g?m các thông tin nhu: Mã hóa don, ngày thanh toán , thông tin c?a khách hàng, thông tin d?ch v? khách hàng dã s? d?ng(Ngày, Chi Ti?t, T?ng S? Ti?n). Trong dó T?ng s? ti?n = T?ng d?ch v? * giá d?ch v?.
// o
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
// Các thao tác vói xóa, tìm ki?m, x?p x?p thì theo List
// ? dây ta dùng LinkedList 2 chi?u d? thao tác ! 
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
    int soDem = 0;
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
        cout << "Nhap ten khach hang :"; cin >> kh.sTenKH;
    } while(checkExists_KH(Q, kh.sTenKH) || kh.sTenKH == "");
    cout << "Nhap ma khach hang :"; cin >> kh.sMaKH;
    cout << "Nhap dia chi khach hang :"; cin >> kh.sDiaChi;
    cout << "Nhap so dien thoai khach hang: "; cin >> kh.sSoDT;
    cout << "Nhap ngay den:"; cin >> kh.sNgayDen;
    cout << "Nhap ngay di:"; cin >> kh.sNgayDi;
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
    do {
        cout << "Nhap ten de doi: "; cin >> name;
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
                        cout << "Nhap vao ngay lap hoa don moi:"; cin >> p->hd.sNgayLapHD;
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
    free(p);
}
// Xoa mot hoa don ra khoi danh sach dua vao ma hoa don
void XoaHD_MaHD(List &Q){
    string maHD;
    cout << "Nhap vao ma hoa don can xoa:"; cin >> maHD;
    bool check_found = false;
    for (auto p = Q.head;p!=NULL;p = p->next){
        if (p->hd.sMaHD==maHD){
            check_found = true;
            DeleteNode(p, Q);
            cout << "Hoa don ma " << p->hd.sMaHD << " da duoc xoa!" << endl;
            break;
        }
    }
    if (check_found == false){
        cout << "Khong tim thay hoa don cua ban dinh xoa!" << endl;
    }
}

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

void sapXep_DSHD_MaHD(List &Q){
    for (auto i = Q.head;i!= Q.tail;i = i->next){
        for (auto j=i->next;j!=NULL;j = j->next){
            if (i->hd.sMaHD > j->hd.sMaHD){
                swap(i->hd, j->hd);
            }
        }
    }
    cout << "Danh sach da xap xep thanh cong !\n";
}

// Doc file DSHD.txt de nhan vao cac thong tin cua danh sach !
void readFile_AddHD(List &Q){
    ifstream readfile;
    string empty_line;
    readfile.open("D:/DSA2023-1/Input_DSHD.txt", ios::in | ios::out);
    if (readfile.fail()){
        cout << "Khong the mo file !\n";
        return;
    }else {
        try {
            HoaDon_DV hd;
            while (!readfile.eof()){
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
                if (p!=NULL){
                    AddLast(Q, p);
                    cout << "Them vao tu file thanh cong !\n";
                }else cout << "Error!\n";
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
void writeFile_DSHD(List &Q){
    ofstream writefile;
    writefile.open("D:/DSA2023-1/Output_DSHD.txt", ios::out | ios::app);
    if (writefile.fail()){
        cout << "Khong the mo file !\n";
        return;
    }else {
        try{
            cout<<"Bat dau ghi file !\n";
            writefile << "Danh sach hoa don hien co la: \n";
            for (auto p = Q.head;p!=NULL;p = p->next){
                // writefile << "Ma hoa don: " << p->hd.sMaHD << endl;
                // writefile << "Ngay lap hoa don: " << p->hd.sNgayLapHD << endl;
                // writefile << "Thong tin khach hang: " << endl;
                // writefile << "Ma khach hang: " << p->hd.kh.sMaKH << endl;
                // writefile << "Ten khach hang: " << p->hd.kh.sTenKH << endl;
                // writefile << "Dia chi: " << p->hd.kh.sDiaChi << endl;
                // writefile << "So dien thoai: " << p->hd.kh.sSoDT << endl;
                // writefile << "---Thong tin phong---" << endl;
                // for (Phong x : p->hd.ph){
                //     writefile << "Ma phong: " << x.sMaPH << endl;
                //     writefile << "Ten phong: " << x.sTenPhong << endl;
                //     writefile << "Day phong: " << x.sDayPhong << endl;
                //     writefile << "Chi tiet: " << x.sChiTietThem << endl;
                // }
                // writefile << "---Thong tin nhan vien---" << endl;
                // writefile << "Ma nhan vien: " << p->hd.nv.sMaNV << endl;
                // writefile << "Ten nhan vien: " << p->hd.nv.sTenNV << endl;
                // writefile << "Dia chi: " << p->hd.nv.sDiaChi << endl;
                // writefile << "So dien thoai: " << p->hd.nv.sSoDT << endl;
                // writefile << "CCCD: " << p->hd.nv.sCCCD << endl;
                // writefile << "Chuc vu: " << p->hd.nv.sChucVu << endl;
                // writefile << "He so luong: " << p->hd.nv.fHSL << endl;
                // writefile << "---Thong tin dich vu---" << endl;
                // for (DichVu x : p->hd.dv){
                //     writefile << "Ma dich vu: "<< x.sMaDV << endl;
                //     writefile << "Ten dich vu: "<< x.sTenDV << endl;
                //     writefile << "Gia dich vu: "<< x.fGiaDV << endl;
                // }
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
                    writefile << setw(8) << x.sNgaySDDV << setw(20) << x.sTenDV << setw(19) << x.fGiaDV << endl;
                }
                writefile << "Tong thanh toan: " << tongTien_DV(p->hd.dv) << endl;
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
        cout << "4. Xoa hoa don bang ma hoa don nhap vao !\n";
        cout << "5. Chinh sua thong tin cua cac hoa don (Chon de biet them chi tiet !)\n";
        cout << "6. Sap xep danh sach hoa don theo ma hoa don !\n";
        cout << "7. Them cac hoa don duoc doc tu  file Input_DSHD.txt !\n";
        cout << "8. Viet danh sach cac hoa don ra file Output_DSHD.txt !\n";
        cout << "10. Xoa man hinh !\n";
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
                XoaHD_MaHD(Q);
                break;
            case 5:
                chinhSuaThongTin_HoaDon(Q);
                break;
            case 6:
                sapXep_DSHD_MaHD(Q);
                break;
            case 7:
                readFile_AddHD(Q);
                break;
            case 8:
                writeFile_DSHD(Q);
                break;
            default:
                cout << "Ban chon sai roi moi ban chon lai !\n";
        }
    } while (chon>=1 && chon<=9);
    return 0;
}
