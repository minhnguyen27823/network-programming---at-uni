#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <string.h>
using namespace std;
class con_nguoi{   // NGUYEN HUU MINH (1)
	protected:
		char *hoten;
		string ngaythangnamsinh;
		int madinhdanh;
	public:
		void nhap();
		void xuat();
		~con_nguoi(){
			delete []hoten;
		}
	char* gethoten();
	 string getngaythangnamsinh();
	int getmadinhdanh();
		 virtual void docfile(ifstream &ifs){
		 	int i=0;
		 }
		  virtual void docfilegiaovien(ifstream &ifs){
		  		int i=0;
		 }

};
void con_nguoi::nhap(){
	hoten = new char[50];
	cout << "nhap ho va ten : ";
	int m=0;
	cin.getline(hoten,50);
	cout << endl;
	cout << " nhap ngay thang nam sinh : ";
	cin >> ngaythangnamsinh;
	 cout << endl;
	 cout << "nhap ma dinh danh : ";
	 cin >> madinhdanh;
	 cout << endl;
}
void con_nguoi::xuat(){
	cout << setw(12) << hoten ;
}
char* con_nguoi::gethoten(){
	
	return hoten;
}
string con_nguoi::getngaythangnamsinh(){
	
	return ngaythangnamsinh;
}
int con_nguoi::getmadinhdanh(){
	
	return madinhdanh;
}
class sinh_vien: public con_nguoi {
	private:
		string lop;
		int mssv;
		string thanhvien; //vip hay thuong
		char *sach;
	public:
	   static int soluong;
	   sinh_vien(){
	   	soluong++;
	   }
	   ~sinh_vien(){
	   	delete []sach;
	   }
	   void nhap_sinhvien();
	   void xuat_sinhvien();
	   void chonsach();
	   void luufile(sinh_vien a[],int &n);
	   string getlop();
	   int getmssv();
	   string getthanhvien();
	   char* getsach();
 virtual void docfile(ifstream &ifs);

};
int sinh_vien::soluong;
string sinh_vien::getlop(){

	return lop;
}
int sinh_vien::getmssv(){
	
	return mssv;
}
string sinh_vien::getthanhvien(){
	
	return thanhvien;
}
char* sinh_vien::getsach(){
	
	return sach;
}
void sinh_vien::nhap_sinhvien(){
	nhap();
	cout << "nhap lop dang sinh hoat : ";
	cin >> lop;
	cout << endl;
	cout << "nhap ma so sinh vien: ";
	cin >> mssv;
	cout << endl;
	cout << "day la thanh vien vip hay thuong :";
	cin >> thanhvien;
}
void sinh_vien::chonsach(){
	cout << "nhap loai sach muon: ";
	sach=new char[50];
	int m=0;
	cin.ignore();
	cin.getline(sach,50);
}
void sinh_vien::xuat_sinhvien(){
	xuat();
	cout << setw(11) << thanhvien ;
	cout << setw(16) << mssv ;
	cout << setw(11) << lop;
	cout << setw(13) <<sach;
	if(thanhvien == "vip") cout << setw(10) << "15 ngay";
	else cout << setw(10) << "7 ngay";
	cout << endl;
//	cout << "ma so sinh vien : " << mssv << endl;
//	cout << "thanh vien :" << thanhvien << endl;
}
void xuatmangsinhvien(sinh_vien a[],int &n){
	for(int i=0;i<n;i++){
		a[i].xuat_sinhvien();
	}
}
void luudanhsachsv(sinh_vien a[],int &n){
	
	ofstream ofs;
	ofs.open("sinhvien.txt");
	ofs << n << endl;
	for(int i=0;i<n;i++){
	ofs << a[i].gethoten() << endl;
	ofs << a[i].getlop() << endl;
	ofs << a[i].getmadinhdanh() << endl;
	ofs << a[i].getmssv() << endl;
	ofs << a[i].getngaythangnamsinh() << endl;
	ofs << a[i].getsach() << endl;
	ofs << a[i].getthanhvien() << endl;
}
	ofs.close();
}
void sinh_vien::docfile(ifstream &ifs){
    hoten=new char[50];
    sach=new char[50];
	ifs.getline(hoten,50);
	getline(ifs,lop);
	ifs >> madinhdanh;
    ifs >> mssv;
    ifs.ignore();
    getline(ifs,ngaythangnamsinh);
	ifs.getline(sach,50);
	getline(ifs,thanhvien);
	
}
void nhap1sinhvien(sinh_vien &a){
 a.nhap_sinhvien();
 a.chonsach();
}
void nhapmangsinhvien(sinh_vien a[],int &n){

	cout << "nhap so luong muon muon sach : ";
	cin >> n; 
	cin.ignore();
	cout << endl;
	for(int i=0;i<n;i++){
		cout << "nhap sinh vien " << i+1 << ": " << endl;
	 nhap1sinhvien(a[i]);
}
	}
void nhapthemsinhvien(sinh_vien a[],int &n){
	int x;
	
	cout << "MUON SACH :" << endl;
  	n++;
	nhap1sinhvien(a[n-1]);
}
void xoasinhvien(sinh_vien a[],int &n){
   int masinhvien;
   nhaplai:
   int dem=0;
   int demphu;
   demphu=n;
	cout << "nhap ma sinh vien muon tra sach :";
	cin >> masinhvien;
	for(int i=0;i<n;i++){
		if (masinhvien == a[i].getmssv()){
		for(int q=i;q<n;q++){
			a[q]=a[q+1];
		}
		n--;
	 } else{
	 dem=dem+1;}
	 		}
	if(dem == demphu){
	cout << "khong co ma sinh vien nao ton tai " << endl;
		goto nhaplai;
	}
}
void docfilemangsinhvien(ifstream &ifs,sinh_vien a[],int &n){
	for(int i=0;i<n;i++){
		a[i].docfile(ifs);
	}
}

class giao_vien : public con_nguoi{
	private:
		int magiaovien;
		string user;//tai khoan cua giao vien
		string password;// mat khau cua giao vien
	public:
		void nhapgiaovien();
		void xuatgiaovien();
		virtual void docfilegiaovien(ifstream &ifs);
		int getmagiaovien();
		string getuser();
		string getpassword();
};
void giao_vien::nhapgiaovien(){
	nhap();
	cout << "nhap ma giao vien :";
	cin >> magiaovien;
	cout << endl;
	cout << "dang ky tai khoan mat khau :" << endl;
	cout << " nhap tai khoan :" ;cin >> user;
	cout << endl;
	cout << "nhap mat khau :";
	cin >> password;
	cout << endl;
	}
void giao_vien::xuatgiaovien(){
	xuat();
	cout << setw(12) << magiaovien << endl;
}
int giao_vien::getmagiaovien(){
	    return magiaovien;
	}
string giao_vien::getuser(){
		return user;
	}
string giao_vien ::getpassword(){
		return password;
	}
void nhapmanggiaovien(giao_vien a[],int &n){
	cout << "nhap so luong giao vien can :";
	cin >> n;
	cout << endl;
	cin.ignore()
;	for(int i=0;i<n;i++){
		cout << "nhap giao vien " << i << ":" << endl;
		a[i].nhapgiaovien();	
	}
}
void xuatmanggiaovien(giao_vien a[],int &n){
	for(int i=0;i<n;i++){
		a[i].xuatgiaovien();
	}
}
void nhapthemgiaovien(giao_vien a[],int &n){

	cin.ignore();
	cout << "nhap them giao vien :" << endl;
  	n++;
	a[n-1].nhapgiaovien();

}
void ghifilemanggiaovien(giao_vien a[],int &n){
	ofstream ofs;
	ofs.open("giaovien.txt");
	ofs << n << endl;
	for(int i=0;i<n;i++){
	ofs << a[i].gethoten() << endl;
	ofs << a[i].getmadinhdanh() << endl;
	ofs << a[i].getngaythangnamsinh() << endl;
	ofs << a[i].getmagiaovien() << endl;
	ofs << a[i].getuser() << endl;
	ofs << a[i].getpassword() << endl;
}
	ofs.close();
}
void giao_vien::docfilegiaovien(ifstream &ifs){
	 hoten=new char[50];
	ifs.getline(hoten,50);
	ifs >> madinhdanh;
    ifs.ignore();
    getline(ifs, ngaythangnamsinh);
	ifs >> magiaovien;
	ifs.ignore();
	getline(ifs,user);
	getline(ifs,password);
	}
void docfilemanggiaovien(ifstream &ifs,giao_vien a[],int &n)
{
	ifs >> n;
	ifs.ignore();
	for(int i=0;i<n;i++){
    a[i].docfilegiaovien(ifs);
	}
}
int kiemtraaccount(giao_vien a[],int &n){
	string taikhoan;
	string matkhau;
   lamlai:
	cout << "nhap tai khoan :";
	cin >> taikhoan;
	cout << endl;
	int demtk;
	for(int i=0;i<n;i++){
		int demmk;
		demmk=0; 
		if(taikhoan.compare(a[i].getuser())==0){
			demtk=demtk+1;
			cout << "nhap mat khau :";
			cin >> matkhau;
			while(matkhau.compare(a[i].getpassword()) != 0){
			   if(demmk==3){ cout << "ban da nhap sai qua 3 lan :" << endl;
		exit(0);
		} 
				cout << "nhap lai mat khau :"; 
				cin >> matkhau;
				demmk=demmk+1;
			}
		}
		}
		if(demtk==0){
			cout << "khong co tai khoan nao ton tai :" << endl;
			cout << "nhap lai tai khoan " << endl;
			goto lamlai;
		}
	
}
void menugiaovien(){
		cout << "**********************************" << endl;
	cout << "nhap vao theo so thu tu de thuc hien cong viec :" << endl;
	cout << "1.xem danh sach sinh vien" << endl;
	cout << "2.xem thong tin cac giao vien " << endl;
	cout << "3.nhap them giao vien quan ly khac" << endl;
	cout << "4.them sinh vien muon sach" << endl;
	cout << "5.xem danh sach cac loai sach" << endl;
	cout << "6.them sach" << endl;
	cout << "7.xoa sach" << endl;
	cout << "8.thoat khoi chuong trinh" << endl;
	cout << "***********************************";
}
void menusinhvien(){
	cout << "**********************************" << endl;
	cout << "nhap vao theo so thu tu de thuc hien cong viec :" << endl;
	cout << "1.nhap vao danh sach sinh vien " << endl;
	cout << "2.Muon sach" << endl;
	cout << "3.xem thong tin cac loai sach" << endl;
	cout << "4.tra sach" << endl;
	cout << "5.luu thong tin "<< endl;
	cout << "6.ket thuc" << endl;
	cout << "***********************************";
	cout << endl;              // (1)
}
class sach //NGUYEN NHAT NGUYEN
{
    public:
    char tensach[30],theloai[30];
      char masach[10];
      void nhapsach();
      void insach();
      int sosach;
};
class ds_sach :public sach
{
    public:
      sach *S;
    void nhapds_sach();
      void timsach(char ten[30]);
      void xoasach(char ten[30]);
      void themsach(sach x);
      void inds_sach();
      void thongketheloai();
      void docsach();
      void ghisach();
};
void sach::nhapsach()
{
   cin.ignore(); 
   cout<<"nhap ma sach: ";
    cin.getline(masach,10);
   cout<<"nhap ten sach: ";
    cin.getline(tensach,30);
   cout<<"nhap the loai: ";
    cin.getline(theloai,30);
}
void sach::insach()
{
  cout<<"=========================================================="<<endl;
  cout<<"thong tin sach"<<endl;
  cout<<setw(10)<<"ma sach"<<setw(30)<<"ten sach"<<setw(30)<<"the loai"<<endl;
  cout<<setw(10)<<masach<<setw(30)<<tensach<<setw(30)<<theloai<<setw(10)<<endl;
}
void ds_sach::nhapds_sach()
{
   cout<<"nhap so luong sach: ";
    cin>>sosach;
    S=new sach[50];
    cin.ignore();
   for(int i=1;i<=sosach;i++)
  
    S[i].nhapsach();
}
void ds_sach::timsach(char ten[30])
{
    int i=1;
   while(i<=sosach && strcmp(S[i].tensach,ten)!=0)
    i++;
      if(i>sosach)
        cout<<"khong so sach nay"<<endl;
      else
        {
            cout<<"da tim thay-in thong tin sach"<<endl;
            S[i].insach();
         }
}
void ds_sach::themsach(sach x)
{
    sosach++;
   S[sosach-1]=x;
}
void ds_sach::xoasach(char ten[30])
{
    int i=0;
   while(i<sosach && strcmp(S[i].tensach,ten)!=0)
    i++;
      if(i>sosach)
        cout<<"khong thay sach nay"<<endl;
      else
      {
        cout<<"da tim thay-thuc hien xoa"<<endl;
         sosach--;
         for(int j=i;j<=sosach;j++)
            S[j]=S[j+1];
      }
}
void ds_sach::inds_sach()
{
    cout<<"in danh sach sach"<<endl;
   for(int i=0;i<sosach;i++)
    S[i].insach();
}
void ds_sach::thongketheloai()
{
    char theloai[30];
   int dem=0;
   cin.ignore();
    cout<<"nhap ten the loai: ";
      cin.getline(theloai,30);
   for(int i=1;i<=sosach;i++)
    for(int j=i;j<=sosach+1;j++)
      {
        if(S[i].theloai==S[j].theloai)
            dem++;
            cout<<"so sach trong the loai: "<<dem<<endl;
            cout<<setw(30)<<"the loai"<<S[i].theloai<<endl;
      }
}
void ds_sach::ghisach()
{
    
   ofstream f;
   f.open("train_forexam/DS_sach.txt");
   if(f.bad()!=0)
   {
    cout<<"loi ghi tap tin"<<endl;
      getch();
      exit(1);
   }
   f<<sosach << endl;
   for(int i=0;i<sosach;i++)
   {
    f<<S[i].masach << endl;
	f<<S[i].tensach<< endl;
	f<<S[i].theloai<<endl;
      cout<<"ghi file tot"<<endl;
   }
    f.close();
}
void ds_sach::docsach()
{
	S=new sach[50];
   ifstream f;
   f.open("DS_sach.txt");
   if(f.bad()!=0)
   {
    cout<<"loi doc flie"<<endl;
      getch();
      exit(1);
   }
   f>>sosach;
   f.ignore();
   for(int i=0;i<sosach;i++)
   {
    f.getline(S[i].masach,10);
      f.getline(S[i].tensach,30);
      f.getline(S[i].theloai,30);
  
   }
   cout<<"da doc tot"<<endl;
   f.close();
}  //2
int main(){
		int n;
		ds_sach s;
		int d;
	sinh_vien *a=new sinh_vien[50];
	giao_vien *b=new giao_vien[50];
	int m;
	int chon;
	int chon1;
	cout << "ban la ? ( chon 1 la sinh vien , 2 la giao vien ) :";
	cin >> chon1;
	cout << endl;
	switch (chon1){
case 1:{
	menusinhvien();
	laplai:
		cin >> chon;
		switch (chon){
	case 1:{
	cout << "nhap mang sinh vien :" << endl;
	nhapmangsinhvien(a,n);
	luudanhsachsv(a,n);
	break;}
case 2:
{
	ifstream ifs;
ifs.open("sinhvien.txt");
ifs >> n;
ifs.ignore();
  for (int i=0;i<n;i++){
   a[i].docfile(ifs);
}
cin.ignore();
nhapthemsinhvien(a,n);
ifs.close();
	break;}
	case 3:{
		s.docsach();
		s.inds_sach();
		break;
	}
case 4:{
	ifstream ifs;
ifs.open("sinhvien.txt");
ifs >> n;
ifs.ignore();
  for (int i=0;i<n;i++){
   a[i].docfile(ifs);
}
xoasinhvien(a,n);
	break;
}
case 5:{
	cout << "luu thong tin" << endl;
	luudanhsachsv(a,n);
	break;}
case 6:{
return 0;
break;
 }
}
goto laplai;
break ;
}
case 2:{
ifstream ifs;
ifs.open("giaovien.txt");
docfilemanggiaovien(ifs,b,m);
kiemtraaccount(b,m);
ifs.close();
menugiaovien();
laplaigiaovien:
cin >> chon1;
switch (chon1){
   case 1:{
   	cout << setw(10) <<" HO TEN  ";
	cout << setw(20) << "THANHVIEN ";
	cout << setw(10) << "MSSV";
	cout << setw(10) << "LOP";
    cout << setw(13) << "SACH";
    cout << setw(13) << "THOI HAN";
	cout << endl;
   	ifstream ifs;
ifs.open("sinhvien.txt");
ifs >> n;
ifs.ignore();
docfilemangsinhvien(ifs,a,n);
xuatmangsinhvien(a,n);
ifs.close();
	goto laplaigiaovien;
	break;
   }
   case 2:{
   	cout << "DANH SACH GIAO VIEN QUAN LY THU VIEN" << endl;
   	cout << setw(12) << "HO TEN";
   	cout << setw(20) << "MA GIAO VIEN";
   	cout << endl;
   	ifstream ifs;
ifs.open("giaovien.txt");
docfilemanggiaovien(ifs,b,m);
xuatmanggiaovien(b,m);
ifs.close();
	goto laplaigiaovien;
	break;
   }
   case 3:{
   	ifstream ifs;
   	ifs.open("giaovien.txt");
   	docfilemanggiaovien(ifs,b,m);
   	nhapthemgiaovien(b,m);
   	ifs.close();
   	ghifilemanggiaovien(b,m);
   		goto laplaigiaovien;
	break;
   }
   case 4:{
   	ifstream ifs;
ifs.open("sinhvien.txt");
ifs >> n;
ifs.ignore();
  for (int i=0;i<n;i++){
   a[i].docfile(ifs);
}
cin.ignore();
nhapthemsinhvien(a,n);
ifs.close();
	break;
		goto laplaigiaovien;
   }
case 5:{
	s.docsach();
	s.inds_sach();
	goto laplaigiaovien; 
	break;
}
case 6:{
	sach h;
	h.nhapsach();
	s.docsach();
	s.themsach(h); 
	s.ghisach();
	goto laplaigiaovien; 
	break;
}
case 7:{
	char ten[50];
	cout << "nhap ten sach muon xoa :" ;
	cin.ignore();
	cin.getline(ten,50);
	cout << endl;
	s.docsach(); 
    s.xoasach(ten);
    s.ghisach();
    goto laplaigiaovien; 
	break;
}
case 8 :{
	return 0;
	break;
}

}}
}}



	


