#include<iostream>
using namespace std;
#include<fstream>
#include<string>
class NamSinh
{
private:
	int ngay;
	int thang;
	int nam;
public:
	int getter_ngay() {
		return ngay;
	}
	void setter_ngay(int Ngay) {
		 ngay = Ngay;
	}
	int getter_thang() {
		return thang;
	}
	void setter_thang(int Thang) {
		 thang = Thang;
	}
	int getter_nam() {
		return nam;
	}
	void setter_nam(int Nam) {
		 nam = Nam;
	}
};

class NhanVien
{

protected:
	string maNhanVien;
	string tenNhanVien;
	NamSinh namSinh;
	string diaChi;
	float luongCoBan;
	float heSoLuong;
	bool KT;
public:
	virtual void doc_File(ifstream &);
	virtual void xuat_File();
	bool getter_kiemTra() {
		return KT;
	}
	void setter_kiemTra( bool kt) {
		KT = kt;
	}
};
// cai dat phuong thuc doc trong lop cha
void NhanVien::doc_File(ifstream& filein) {
	getline(filein, maNhanVien, ',');
	filein.seekg(1, 1); // so byte can dich + sang phai - trai, tai vi tri hien tai
	getline(filein, tenNhanVien, ',');
	filein.seekg(1, 1);
	int ngay;
	filein >> ngay;
	namSinh.setter_ngay(ngay);
	filein.seekg(1, 1);
	int thang;
	filein >> thang;
	namSinh.setter_ngay(thang);
	filein.seekg(1, 1);
	int nam;
	filein >> nam;
	namSinh.setter_nam(nam);
	filein.seekg(2, 1);
	getline(filein, diaChi, ',');
	filein >> heSoLuong;
	filein.seekg(1, 1);
	filein >> luongCoBan;
	filein.seekg(1, 1);
}
void NhanVien::xuat_File() {
	cout << "\nMa nhan vien : " << maNhanVien;
	cout << "\nTen nhan vien : " << tenNhanVien;
	cout << "\nNam sinh nhan vien : " << namSinh.getter_ngay() << "/" << namSinh.getter_thang() << "/" << namSinh.getter_nam();
	cout << "\nDia chi nhan vien : " << diaChi;
	cout << "\nHe so luong nhan vien : " << size_t(heSoLuong);
	cout << "\nLuong co ban nhan vien : " << size_t(luongCoBan);

}

//=================================
class NhanVienLapTrinh :public NhanVien {
private:
	float tienLamNgoaiGio;
public:
	void doc_File(ifstream&);
	void xuat_File();

};
void NhanVienLapTrinh::doc_File(ifstream& filein) {
	NhanVien::doc_File(filein);
	filein >> tienLamNgoaiGio;	
}
void NhanVienLapTrinh::xuat_File() {
	NhanVien::xuat_File();
	cout << "\nTien lam ngoai gio : " << size_t(tienLamNgoaiGio);

}

//=================================
class NhanVienThietKe :public NhanVien {
private:
	float tienThuong;
public:
	void doc_File(ifstream&);
	void xuat_File();

};
void NhanVienThietKe::doc_File(ifstream& filein) {
	NhanVien::doc_File(filein);
	filein >> tienThuong;
}
void NhanVienThietKe::xuat_File() {
	NhanVien::xuat_File();
	cout << "\nTien thuong : " << size_t(tienThuong);

}
//============================================================
void Menu(NhanVien* ds[], int& n) {
	ifstream filein;
	filein.open("nhanvien.txt", ios_base::in);
	while (true)
	{
		system("cls");
		cout << "\n\n\t\t =========MENU=========";
		cout << "\n1. Doc thong tin trong file";
		cout << "\n2. Xuat thong tin trong file";
		cout << "\n0. Ket thuc";
		cout << "\n\n\t\t =========END=========";
		int luachon;
		cout << "\nNhap lua chon : ";
		cin >> luachon;
		if (luachon == 1) {
			filein >> n;
			NhanVien* nv = NULL;
			for (int i = 0; i < n; i++) {
				char c;
				filein >> c;
				filein.seekg(-1, 1);
				if (c == 'P') {
					nv = new NhanVienLapTrinh();
					nv->doc_File(filein);
					nv->setter_kiemTra(true);
				}
				else if (c == 'D') {
					nv = new NhanVienThietKe();
					nv->doc_File(filein);
					nv->setter_kiemTra(false);
				}
				ds[i] = nv;
			}
		}
		else if (luachon == 2) {
			for (int i = 0; i < n; i++)
			{
				if (ds[i]->getter_kiemTra() == true) {
					cout << "\n\n\t\t Nhan vien lap trinh thu " << i + 1 << ": " << endl;
					ds[i]->xuat_File();
				}
				if (ds[i]->getter_kiemTra() == false) {
					cout << "\n\n\t\t Nhan vien thiet ke thu " << i + 1 << ": " << endl;
					ds[i]->xuat_File();
				}
				
			}
			system("pause");
		}else if (luachon == 0) {
			break;
		}

	}
	filein.close();
}
int main() {
	NhanVien* ds[100];
	int n = 0;
	Menu(ds, n);
	system("pause");
	return 0;
}