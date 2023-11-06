#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <string>
#include <Windows.h>
#include <regex>

using namespace std;

int introTime = { 1 }; //Intro suresi , varsayilan : 1
int girishakki = { 3 }; //Toplam sifre deneme hakki , varsayilan : 3
const int katSayisi = { 4 }; //kac katli otopark olsun , varsayilan : 5
const int aracKapasite = { 10 }; //kac aracli otopark olsun , varsayilan : 10

/*
GIRIS :

Varsayilan kullanici ismi ve sifre ana klasor icerisindeki Readme.txt dosyasinin icinde tanimlidir .
isterseniz BeniOku kisayolu uzerindende ulasabilirsiniz .













*/

const int pCarLimit = { aracKapasite + 1 };
const int pFloor = { katSayisi + 1 };
int passTryLimit = { girishakki - 1 };

void introP(string introMessage, int introTime)
{
    for (int i = 0; i < introTime; i++)
    {
        string introStatus = (i == 0) ? introMessage : "uygulama " + to_string(introTime - i) + " icinde baslatilacak";
        cout << introStatus;
        Sleep(1000);
        system("CLS");
    }
}

void startParking(string*bUsername) 
{
    bool pLoop = true ;
    int pOperation;
    map<string, string> nameOfParkingCars;

    string ciParkingName = { "" };
    int ciParkingFloor = { 0 };
    int ciParkingArea = { 0 };
    string ciDelCarFloorAndSlot = { "00" };

    int  parkingCars[pFloor][pCarLimit] = { {0, 0}, {0, 1}, };

    nameOfParkingCars["0-0"] = "59 EG 878,04.11.2023,11:19";
    nameOfParkingCars["0-1"] = "59 EG 878,04.11.2023,11:19";

    regex r("\\s+");
    string bciDelCarFloorAndSlot = { "" }; //whitespace silmek icin denemeler yaptigim value

    while (pLoop)
    {
        cout << "\n Aktif kullanici :" <<  * bUsername << "\n\n1. Park Halinde ki Araclarin Listesi \n2. Park Halinde ki Araci Cikisi \n3. Yeni Arac Girisi \n4. Cikis \n";
        cin >> pOperation ;

        switch (pOperation)
        {
        case 1 :
            system("CLS");
            for (auto element : nameOfParkingCars)
            {
                cout << "Kat/Slot :" << element.first << " Parkedilen arac : ";
                cout << element.second << endl;
            }
            break;
        case 2 :
            //arac cikisi
            cout << "Hangi arac cikis yapacak Kat Slot ( 0-0 ile " + to_string(pFloor) + "-" + to_string(pCarLimit) + " arasinda) : \n";
            cin >> ciDelCarFloorAndSlot;
            //cout<< ciDelCarFloorAndSlot;
            //bciDelCarFloorAndSlot = to_string(getline(cin, ciDelCarFloorAndSlot));
            //
            //for (int i = 0; i < bciDelCarFloorAndSlot.length(); i++) {
            //    if (bciDelCarFloorAndSlot[i] == ' ') {
            //        bciDelCarFloorAndSlot.erase(i, 1);
            //        i--;
            //    }
            //}
            nameOfParkingCars.erase(ciDelCarFloorAndSlot);
            introP("\n Arac kaldirildi Kat/Slot :" + ciDelCarFloorAndSlot, introTime);
            break;

        case 3:
            //arac girisi
            cout << "Hangi kata park edeceksin ( 0-" + to_string(pFloor-1)+" ) : \n";
            cin >> ciParkingFloor;
            cout << "Hangi slota park edeceksin ( 0-" + to_string(pCarLimit-1) + " ) : \n";
            cin >> ciParkingArea;
            cout << "Plaka,Giris Tarihi,Giris Saati :\n";
            cin >> ciParkingName;
            if (parkingCars[ciParkingFloor][ciParkingArea] == NULL)
            {
                parkingCars[ciParkingFloor][ciParkingArea] = ciParkingFloor , ciParkingArea ;
                nameOfParkingCars[to_string(ciParkingFloor) +"-" + to_string(ciParkingArea)] = ciParkingName;
                introP("\n Park alanina eklendi Kat/Slot :" + to_string(ciParkingFloor) + "-" + to_string(ciParkingArea) , introTime);
            }
            else if (parkingCars[ciParkingFloor][ciParkingArea] != NULL)
            {
                introP("\n Kat veya Slot sayisini fazla veya eksik girdiniz \n", introTime);
            }
            break;
        case 4:
            pLoop = false;
            introP("Cikis yapiliyor !", introTime);
            break;

        default:
            introP("Hatali giris", introTime);
            break;
        }
    }
}

int main()
{
    //Degiskenler

    string name, password, ciName, ciPassword = { "" };
    int passMisses = { 0 };
    bool bParking = { true };
    ifstream file("Readme.txt");

    //Giris ekrani

    introP("Park uygulamasina hosgeldin !", introTime);

    //Login ekrani
    if (file.is_open()) {
        string line;
        int lineCount = 0;
        while (getline(file, line)) {
            lineCount++;
            if (lineCount == 1 || lineCount == 2) { (lineCount == 1) ? name = line.erase(0, 15) : (lineCount == 2) ? password = line.erase(0, 7) : password = "???"; }
        }file.close();
    }
    string missString = {""};
    while (bParking)
    {
        system("CLS");
        (passTryLimit == 0) ? bParking = false : passTryLimit-- ;
        cout << missString << endl;       
        cout << "KULLANICI ADI:";
        cin >> ciName;
        cout << "SIFRE :";
        cin >> ciPassword;

        if (name == ciName && password == ciPassword)
        {
            introP("basarili ! Hosgeldiniz  ! " + name, introTime);
            bParking = 0;
            startParking(&name);
        }

        passMisses++;
        missString = (passMisses > 0) ? "Toplam hatali giris : " + to_string(passMisses) : "";
        if ((passTryLimit == 0) && (name != ciName) || (password != ciPassword)) { cout << "Giris hakkin tukendi :("; }
    }

    return 0;
}

