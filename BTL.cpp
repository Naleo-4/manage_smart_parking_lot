#include <iostream>
#include <time.h>
#include <cstdio>
#include <stdlib.h>
using namespace std;

std::string currentDateTime(){                                                              //tao chuoi ngay gio
    time_t now= time(0);
    struct tm tstruct;
    char buf[80];

    tstruct =*gmtime(&now);
    tstruct.tm_hour+=7;
    strftime(buf, sizeof(buf),"%Y/%m/%d     %X",&tstruct);

    return buf;
};

struct HOUR_MIN_SEC{                                                                        //Tao struct Gio,phut,giay
    int Hour;
    int Min;
    int Sec;
};

struct HOUR_MIN_SEC currentHourTime(){                                                      //Tao ham tra ve Struct HOUR_MIN_SEC
    time_t currentTime;
    struct tm *localTime;

    time( &currentTime );
    localTime = localtime( &currentTime );
    HOUR_MIN_SEC h;

    h.Hour   = localTime->tm_hour;
    h.Min    = localTime->tm_min;
    h.Sec    = localTime->tm_sec;
    //std::cout<<h.Hour<<":"<<h.Min<<":"<<h.Sec<<std::endl;
    return h;
}

bool isNumber(std::string s)                                                                //kiem tra xem kieu co phai la so nguyen
{
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)                                                         //kiem tra tung phan tu trong string co phai so nguyen
            return false;
 
    return true;
}


class Revenue{                                                                              //class Doanh thu
    public: 
        static int revenue;                                                                 //Doanh thu(revenue)
    public:
        static int getRevenue(){                                                            // Tra ve gia tri Doanh Thu
            return revenue;
        }
        static void update(int money){                                                      //cap nhat gia tri Doanh Thu
            revenue+=money;
        }
        friend void sale(int);
};

int Revenue::revenue=0;

class Hoadon{                                                                               //class Hoa Don
    private: 
        int PhiGuiXe=0;
        int TienKhachTra=0;
        int TienThua=0;
        std::string CurTime;
    public:
        void InHoaDon(){                                                                    //In Hoa Don
        std::string CurTime=currentDateTime();                                              //In thoi gian hien tai
            std::cout<<"Hoa Don: "<< std::endl;
            std::cout<<CurTime<<std::endl;
            std::cout<<"Phi Gui Xe: "<<PhiGuiXe<<" dong"<<std::endl;
            std::cout<<"Tien Khach Tra: "<<TienKhachTra<<" dong"<<std::endl;
            std::cout<<"Tien Tra Lai:  "<<TienKhachTra-PhiGuiXe<<" dong"<<std::endl;
        }
        int Inp(){                                                                          //Nhap Tien Khach Tra
            std::cout<<"Tien Khach Dua: ";
            std::string str;
            std::cin>>str;
            if (!isNumber(str)) {
                std::cout<<"Khong hop le. Vui long nhap lai."<<std::endl;                   //kiem tra so nhap vao co phai la so nguyen
                return 1;
            }
            if (check(str)){
                std::cout<<"Tien khach dua khong du. Vui long tra them!"<<std::endl;        //kiem tra so tien khach tra co du hay khong
                return 1;
            }
            TienKhachTra= std::stoi(str,nullptr,10);
            return 0;
        }
        void setPhiGuiXe(int set){                                                          //Dat phi gui xe ( phan nay co the tuy chinh them de thay doi gia gui xe theo dieu kien nhat dinh)
            PhiGuiXe=set;
        }
        int check(std::string str){
            if (std::stoi(str)>=PhiGuiXe) return 0 ;else return 1;
        }
        friend void sale(int);
};

void sale(int money){                                                                       //cap nhat Doanh thu
    Revenue::update(money);
};

int main(){
    system("cls");
    int input;                                                     
    while (true){
        using namespace std;

        system("cls");                                                                      //xoa man hinh

        cout<<"0-Thoat chuong trinh."<<endl;
        cout<<"1-Them hoa don."<<endl;
        cout<<"2-In Tong doanh thu."<<endl<<endl;
        cout<<"Chon: "; 
        std::string t;
        cin>>t;

        while (!isNumber(t)) {                                                              //kiem tra so nhap vao
            cout<<"Khong hop le. Vui long nhap lai."<<endl; 
            cin>>t;
        }         

        input = std::stoi(t);                                                               //string to int
        cout<<endl;

        if (input==0) break;
            else if (input==1) {
                Hoadon *temp =new Hoadon;                                                   //tao hoa don moi
                int ticket_price=10000;      
                HOUR_MIN_SEC hour=currentHourTime();                                        //lay ngay gio hien tai
                if  ((hour.Hour>18) || (hour.Hour=18 && hour.Min>=30))  ticket_price=20000; //Dat phi gui xe
                temp->setPhiGuiXe(ticket_price);
                while (temp->Inp()) {                                                       //Nhap tien khach tra
 
                }
                temp->InHoaDon();                                                           //In Hoa don
                cout<<endl;
                sale(ticket_price);                                                         //Tang danh thu len
                delete temp; 
            }
                else if(input==2) {
                    cout<<"Tong doanh thu :"<<Revenue::getRevenue()<<endl<<endl;            //In Tong doanh thu
                }
                    else cout<<"Khong hop le. Vui long nhap lai."<<endl; 
        system("pause");                                                                    //Dung lai cho nhap 1 phim bat ky
    }
    system("pause");
    system("cls");
}
