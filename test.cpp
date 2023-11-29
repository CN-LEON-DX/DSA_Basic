#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

struct SANPHAM
{
	string smasanpham,stensanpham,sdongia;
	int isoluong;
};
// nhap dssp
void nhapdssp(SANPHAM &x)
{ 
	cout<<"Nhap Ma SP: ";
	cin>>x.smasanpham;
	cout<<"Nhap Ten San Pham  : ";cin.ignore();
	getline(cin,x.stensanpham);
	cout<<"Nhap Don Gia: ";
	getline(cin,x.sdongia);
	cout<<"Nhap So Luong: ";
	cin>>x.isoluong;
}
void nhapdssp(int &n, SANPHAM ds[])
{
	cout<<"Nhap danh sach san pham:";	cin>>n;
	for(int i=0; i<n; i++)
		nhapdssp( ds[i ]);
}
// indssp
void indssp(SANPHAM x)
{
		cout<<"\n"<<setw(10)<<x.smasanpham;
		cout<<setw(20)<<x.stensanpham;
		cout<<setw(4)<<x.sdongia;
		cout<<setw(5)<<x.isoluong;
}
void indssp(int n, SANPHAM ds[])
{
	cout<<"\n DSSP \n";
	for(int i=0; i<n; i++)
		indssp(ds[i]);
}
//ghi dssp vao file
void ghiDSSPFile(int n,SANPHAM x[])
{
	ofstream f;
	f.open("sp.dat",ios::binary|ios::out);
	f.write((char*)&n,sizeof(int));
	f.write((char*) x,sizeof(SANPHAM)*n);
	f.close();
	if(!f.good())
	{
		cout<<"\n Xay ra loi trong khi ghi file"<<endl;
		return;
	}
	cout<<"\n Ghi file thanh cong";
}
void hienDSSPFile(int &n,SANPHAM x[])
{
	ifstream f ;
	f.open("sp.dat",ios::in|ios::binary);
	if(!f)
	{
		cout<<"\n File khong ton tai"<<endl;
		return;
		f.read((char*)&n,sizeof(int));
		f.read((char*) x,sizeof(SANPHAM)*n);
		f.close();
		cout<<"Doc file thanh cong"<<endl;
	}
}
void sapXep_DSSP_Ten(SANPHAM a[], int n){
	for (int i = 0;i<n-1;i++){
		for (int j = i + 1;j<n;j++){
			if (a[i].stensanpham < a[j].stensanpham){
				swap(a[i], a[j]);
			}
		}
	}
	cout << "Danh sach da sap xep " << endl;
}
void thongke_SP_slnho5(SANPHAM a[], int n){
	cout << "San pham co so luong nho hon 5:" << endl;
	for (int i = 0;i<n;i++){
		if (a[i].isoluong < 5){
			cout<<"\n"<<setw(10)<<a[i].smasanpham;
			cout<<setw(20)<<a[i].stensanpham;
			cout<<setw(4)<<a[i].sdongia;
			cout<<setw(5)<<a[i].isoluong;
		}
	}
}
void tinhTBC_SLSP_Nhap(SANPHAM a[], int n){
	double tbc = 0;
	for (int i = 0;i<n;i++){
		tbc += a[i].isoluong;
	}
	cout << "Trung binh cong so luong san pham la :" << tbc << endl;
}
int main()
{
	SANPHAM a[20];
	int n=0,chon;
	do
	{
		cout<<"\n 1 Nhap danh sach san pham";
		cout<<"\n 2 In danh sach san pham";
		cout<<"\n 3 Luu danh sach san pham vao file";
		cout<<"\n 4 Hien danh sach san pham tu file";
		cout <<"\n 5 Sap xep danh sach cac san pham theo thu tu alphabet ten san pham ";
		cout << "\n 6 Thong ke so luong san pham ";
		cout << "\n 7 Tinh trung binh cong so luong san pham nhap ";
		cout<<"\n 0 Thoat";
		cout<<"\n MOI BAN CHON : ";cin>>chon;
		switch(chon)
		{
		case 1 : nhapdssp(n,a);break;
		case 2 : indssp(n,a);break;
		case 3 : ghiDSSPFile(n,a);break;
		case 4 : hienDSSPFile(n,a);
				indssp(n,a);break;
		case 5: sapXep_DSSP_Ten(a, 20);
		case 6: thongke_SP_slnho5(a, 20);
		case 7: tinhTBC_SLSP_Nhap(a, 20);
		case 0 : break;
		
		}
	}while(chon!=0);
	return 0;
}