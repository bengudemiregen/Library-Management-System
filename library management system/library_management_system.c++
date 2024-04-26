#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include <cstdio>
#include <vector>

using namespace std;

string kullanici_girisi();
string kimlik_dogrula(string, string);

int usermenu(string);
int adminmenu(string);
int runtime(int, string);

//runtime fonksiyonlari
void Kitapara();
void Kitapekle();
void Kitapsil();

void kullanicilistele();
void Kullaniciekle();
void kullanicisil();

void kitapodunclistele();
void kitapoduncal(string);
void kitapiadeet();

void cikis();
void resetmenu();
void RESET();

struct Kitap {
    string isim;
    string yazar;
    string sayfaSayisi;
};

//main
int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);// Konsolun arka plan ve yaz? rengini ayarla
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_INTENSITY);//beyaz mavi
    //SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | 0);//beyaz siyah
    system("cls");//sayfay? yenile ki komutumuz back ground güzel dursun

    string username = kullanici_girisi();
    while (true)
    {
        if (!username.empty()) {
            if (username == "admin") {
                adminmenu(username);

            }
            else {

                usermenu(username);
            }
        }
        else {
            main();
        }
    }
    return 0;
}

//sorgu
string kullanici_girisi()
{
    string username, password;
    cout << R"( PROGRAMI SONLANDIRMAK ICIN USERNAME :[z] TUSLAYINIZ.

                                              :::          :::   :::       ::::::::
                                             :+:         :+:+: :+:+:     :+:    :+:
                                            +:+        +:+ +:+:+ +:+    +:+
                                           +#+        +#+  +:+  +#+    +#++:++#++
                                          +#+        +#+       +#+           +#+
                                         #+#        #+#       #+#    #+#    #+#
                                        ########## ###       ###     ########
)";//r"(xxxx)" seklindeki dizin coutta \n ve tekrarl? satr?lar? engeller ascii sanat?nda kullna?rl?r

    cout << "\n\n                                   e-LMS hos geldiniz. Lutfen kimlik bilgilerinizi girin." << endl;
    cout << "                                                       USERNAME: ";
    cin >> username;
    if (username == "z")
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);// Konsolun arka plan ve yaz? rengini ayarla
        SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_RED | 0);//kirmizi siyah
        system("cls");
        cout << R"( 
                                              :::          :::   :::       ::::::::
                                             :+:         :+:+: :+:+:     :+:    :+:
                                            +:+        +:+ +:+:+ +:+    +:+
                                           +#+        +#+  +:+  +#+    +#++:++#++
                                          +#+        +#+       +#+           +#+
                                         #+#        #+#       #+#    #+#    #+#
                                        ########## ###       ###     ########
                   )";//r"(xxxx)" seklindeki dizin coutta \n ve tekrarl? satr?lar? engeller ascii sanat?nda kullna?rl?r
        exit(0);
    }
    else
    {
        cout << "                                                       PASSWORD: ";
        cin >> password;

        system("cls");

        return kimlik_dogrula(username, password);
    }
}
string kimlik_dogrula(string username, string password)
{
    ifstream dosya("kullanicilar.txt");
    string satir, satirUsername, satirPassword;

    while (dosya >> satirUsername >> satirPassword) {
        if (username == satirUsername && password == satirPassword) {
            dosya.close();
            return username;
        }
    }

    dosya.close();
    return "";
}
//menu
int usermenu(string username)
{
    while (true)
    {
        int tercih;
        // Kullanici menusu islemleri
        cout << R"( 
                      .----------------.  .----------------.  .----------------.  .----------------.
                     | .--------------. || .--------------. || .--------------. || .--------------. |
                     | | _____  _____ | || |    _______   | || |  _________   | || |  _______     | |
                     | ||_   _||_   _|| || |   /  ___  |  | || | |_   ___  |  | || | |_   __ \    | |
                     | |  | |    | |  | || |  |  (__ \_|  | || |   | |_  \_|  | || |   | |__) |   | |
                     | |  | '    ' |  | || |   '.___`-.   | || |   |  _|  _   | || |   |  __ /    | |
                     | |   \ `--' /   | || |  |`\____) |  | || |  _| |___/ |  | || |  _| |  \ \_  | |
                     | |    `.__.'    | || |  |_______.'  | || | |_________|  | || | |____| |___| | |
                     | |              | || |              | || |              | || |              | |
                     | '--------------' || '--------------' || '--------------' || '--------------' |
                      '----------------'  '----------------'  '----------------'  '----------------'
                   )";//r"(xxxx)" seklindeki dizin coutta \n ve tekrarl? satr?lar? engeller ascii sanat?nda kullna?rl?r

        cout << "\n\n\t                                              MERHABA " << username << " !" << endl;

        cout << "\n\t                                         Lutfen seciminizi yapin:";
        cout << "\n\t                                         [1] Kitap ara";
        cout << "\n\t                                         [2] kitap odunc al";
        cout << "\n\t                                         [3] kitap iade et";
        cout << "\n\t                                         [4] EXIT";

        cout << "\n\t                                         Tercih: ";
        cin >> tercih;
        system("cls");

        runtime(tercih, username);
        return 0;
    }
}
int adminmenu(string username)
{
    while (true)
    {
        int tercih;
        // Admin menusu islemleri
        cout << R"( 
         .----------------.  .----------------.  .----------------.  .----------------.  .-----------------.
        | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |
        | |      __      | || |  ________    | || | ____    ____ | || |     _____    | || | ____  _____  | |
        | |     /  \     | || | |_   ___ `.  | || ||_   \  /   _|| || |    |_   _|   | || ||_   \|_   _| | |
        | |    / /\ \    | || |   | |   `. \ | || |  |   \/   |  | || |      | |     | || |  |   \ | |   | |
        | |   / ____ \   | || |   | |    | | | || |  | |\  /| |  | || |      | |     | || |  | |\ \| |   | |
        | | _/ /    \ \_ | || |  _| |___.' / | || | _| |_\/_| |_ | || |     _| |_    | || | _| |_\   |_  | |
        | ||____|  |____|| || | |________.'  | || ||_____||_____|| || |    |_____|   | || ||_____|\____| | |
        | |              | || |              | || |              | || |              | || |              | |
        | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |
         '----------------'  '----------------'  '----------------'  '----------------'  '----------------'
                    )";//r"(xxxx)" seklindeki dizin coutta \n ve tekrarl? satr?lar? engeller ascii sanat?nda kullna?rl?r


        cout << "\n\n\t                                          MERHABA " << username << endl;
        cout << "\n\t                                      Lutfen seciminizi yapin:";
        cout << "\n\t                                      [1] Kitap ara";
        cout << "\n\t                                      [2] Kitap ekle";
        cout << "\n\t                                      [3] Kitap sil";
        cout << "\n\t                                      [4] kullanici ara";
        cout << "\n\t                                      [5] Kullanici ekle";
        cout << "\n\t                                      [6] Kullanici sil";
        cout << "\n\t                                      [7] odunc listele";
        cout << "\n\t                                      [8] kitap odunc al";
        cout << "\n\t                                      [9] kitap iade et";
        cout << "\n\t                                      [10] EXIT";

        cout << "\n\n\t                                      [0] TUM VERILERI TEMIZLE";

        cout << "\n\n\t                                      Tercih: ";

        cin >> tercih;

        system("cls");

        runtime(tercih, username);
        return 0;
    }
}

//calistir
int runtime(int x, string u)
{
    if (u == "admin")
    {
        switch (x)
        {
        case 1:
            Kitapara();
            break;
        case 2:
            Kitapekle();
            break;
        case 3:
            Kitapsil();
            break;
        case 4:
            kullanicilistele();
            break;
        case 5:
            Kullaniciekle();
            break;
        case 6:
            kullanicisil();
            break;
        case 7:
            kitapodunclistele();
            break;
        case 8:
            kitapoduncal(u);
            break;
        case 9:
            kitapiadeet();
            break;
        case 10:
            cikis();
            break;
        case 0:
            resetmenu();
            break;
        }
        return 0;
    }

    else
    {
        switch (x) {
        case 1:
            Kitapara();
            break;
        case 2:
            kitapoduncal(u);
            break;
        case 3:
            kitapiadeet();
            break;
        case 4:
            cikis();
            break;
        }
    }
    return 0;
}

//kitap
void Kitapara()
{
    string arananKelime;
    cout << "Aranacak kelimeyi girin: ";
    cin >> arananKelime; cout << endl;

    ifstream dosya("kitap.txt");

    string satir;
    while (getline(dosya, satir)) {
        if (satir.find(arananKelime) != string::npos) {
            cout << satir << endl;
        }
    }
    system("pause");
    system("cls");

    dosya.close();
}
void Kitapekle()
{
    string dosyaAdi = "kitap.txt";
    Kitap yeniKitap;

    cout << "Kitap adini giriniz: ";
    cin.ignore();
    getline(cin, yeniKitap.isim);

    cout << "Yazar adini giriniz: ";
    getline(cin, yeniKitap.yazar);

    cout << "Sayfa sayisini giriniz: ";
    getline(cin, yeniKitap.sayfaSayisi);

    ofstream dosya(dosyaAdi, ios::app);
    dosya << yeniKitap.isim << " / " << yeniKitap.yazar << " / " << yeniKitap.sayfaSayisi << endl;
    dosya.close();

    cout << "\nKitap bilgileri basariyla kaydedildi." << endl;
    system("pause");
    system("cls");
}
void Kitapsil()
{
    string dosyaAdi = "kitap.txt";
    string silinecekKitap;

    cout << "Silinecek kitap adini giriniz: ";
    cin.ignore();
    getline(cin, silinecekKitap);

    ifstream dosya(dosyaAdi);
    string satir;
    bool kitapBulundu = false;
    vector<string> kitaplar;

    while (getline(dosya, satir)) {
        if (satir.find(silinecekKitap) != string::npos) {
            kitapBulundu = true;
        }
        else {
            kitaplar.push_back(satir);
        }
    }
    dosya.close();

    if (kitapBulundu) {
        ofstream Dosya(dosyaAdi);
        for (const string& kitap : kitaplar) {
            Dosya << kitap << endl;
        }
        Dosya.close();
        cout << "Kitap basariyla silindi." << endl;
    }
    else {
        cout << "Kitap bulunamadi." << endl;
    }

    system("pause");
    system("cls");
}

//kullanici
void Kullaniciekle()
{
    string dosyaAdi = "kullanicilar.txt";
    string kullaniciAdi, parola;

    cout << "Kullanici adini giriniz: ";
    cin.ignore();
    //satir atlama hatasi 
    getline(cin, kullaniciAdi);

    cout << "Parolayi giriniz: ";
    getline(cin, parola);

    ofstream dosya(dosyaAdi, ios::app);

    dosya << kullaniciAdi << " " << parola << endl;
    dosya.close();
    cout << "\nKullanici bilgileri basariyla kaydedildi." << endl;

    system("pause");
    system("cls");
}
void kullanicisil()
{
    string dosyaAdi = "kullanicilar.txt";
    string silinecek;

    cout << "Silinecek user adini giriniz: ";
    cin.ignore();
    getline(cin, silinecek);

    ifstream dosya(dosyaAdi);
    string satir;
    bool kitapBulundu = false;
    vector<string> kitaplar;

    while (getline(dosya, satir)) {
        if (satir.find(silinecek) != string::npos) {
            kitapBulundu = true;
        }
        else {
            kitaplar.push_back(satir);
        }
    }
    dosya.close();

    if (kitapBulundu) {
        ofstream Dosya(dosyaAdi);
        for (const string& kitap : kitaplar) {
            Dosya << kitap << endl;
        }
        Dosya.close();
        cout << "user basariyla silindi." << endl;
    }
    else {
        cout << "user bulunamadi." << endl;
    }

    system("pause");
    system("cls");
}
void kullanicilistele()
{
    string arananKelime;
    cout << "NICKNAME: ";
    cin >> arananKelime; cout << endl;
    cout << "NICNAME # PASSWORD" << endl;

    ifstream dosya("kullanicilar.txt");

    string satir;
    while (getline(dosya, satir)) {
        if (satir.find(arananKelime) != string::npos) {
            cout << satir << endl;
        }
    }
    system("pause");
    system("cls");

    dosya.close();
}

//odunc
void kitapoduncal(string username)
{
    string dosyaAdi = "odunc.txt";
    string kitapadi, u;
    u = username;

    cin.ignore(); // Önceki girişlerin tamamını atlamak için cin.ignore() kullanıyoruz.

    cout << "Kitap adini giriniz: ";
    getline(cin, kitapadi);

    ofstream dosya(dosyaAdi, ios::app);

    dosya << kitapadi << " # " << u << endl;

    dosya.close();
    cout << "\nOdunc bilgileri basariyla kaydedildi." << endl;
    cout << "KEYIFLI OKUMALAR.\n\n";

    system("pause");
    system("cls");
}
void kitapiadeet()
{
    string dosyaAdi = "odunc.txt";
    string oduncKitap;

    cout << "odunc vereceginiz kitabın ismi nedir: ";

    cin.ignore();
    getline(cin, oduncKitap);

    ifstream dosya(dosyaAdi);
    string satir;
    bool kitapBulundu = false;
    vector<string> kitaplar;

    while (getline(dosya, satir)) {
        if (satir.find(oduncKitap) != string::npos) {
            kitapBulundu = true;
        }
        else {
            kitaplar.push_back(satir);
        }
    }
    dosya.close();

    if (kitapBulundu) {
        ofstream Dosya(dosyaAdi);
        for (const string& kitap : kitaplar) {
            Dosya << kitap << endl;
        }
        Dosya.close();
        cout << "kitap iade edildi" << endl;
    }
    else {
        cout << "Kitap bulunamadi." << endl;
    }

    system("pause");
    system("cls");
}
void kitapodunclistele()
{
    string arananKelime;
    cout << "ANAHTAR KELIME: ";
    cin >> arananKelime; cout << endl;
    cout << "kitap # nickname" << endl;

    ifstream dosya("odunc.txt");

    string satir;
    while (getline(dosya, satir)) {
        if (satir.find(arananKelime) != string::npos) {
            cout << satir << endl;
        }
    }
    system("pause");
    system("cls");

    dosya.close();
}

//cikis
void cikis()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);// Konsolun arka plan ve yaz? rengini ayarla
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_RED | 0);//kirmizi siyah
    cout << R"(
                                               :::          :::   :::       ::::::::
                                             :+:         :+:+: :+:+:     :+:    :+:
                                            +:+        +:+ +:+:+ +:+    +:+       
                                           +#+        +#+  +:+  +#+    +#++:++#++
                                          +#+        +#+       +#+           +#+
                                         #+#        #+#       #+#    #+#    #+#
                                        ########## ###       ###     ########
)";//r"(xxxx)" seklindeki dizin coutta \n ve tekrarl? satr?lar? engeller ascii sanat?nda kullna?rl?r
    system("pause");
    system("cls");
    main();
}

//reset
void resetmenu()
{
    int x;
    cout << "                                                         !!!!UYARI!!!!" << endl;
    cout << "                                      tum library log dosyalari silinecektir onayliyor mmusunuz?" << endl;
    cout << "                                      [1]EVET" << endl;
    cout << "                                      [2]HAYIR" << endl;
    cout << "\n                                    TERCIH: ";
    cin >> x;

    system("cls");

    if (x == 1)
    {
        RESET();
    }
    else if (x == 2) {}//geri admin menuye

    else resetmenu();
}
void RESET()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);// Konsolun arka plan ve yaz? rengini ayarla
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_RED | 0);//kirmizi siyah
    float i, j = 0;
    for (i = 0; i < 100; i++) {

        cout << R"( 
                                              :::          :::   :::       ::::::::
                                             :+:         :+:+: :+:+:     :+:    :+:
                                            +:+        +:+ +:+:+ +:+    +:+
                                           +#+        +#+  +:+  +#+    +#++:++#++
                                          +#+        +#+       +#+           +#+
                                         #+#        #+#       #+#    #+#    #+#
                                        ########## ###       ###     ########

                                               lms sifirlaniyor... % )" << i << endl;

        for (j = 0; j < i; j += 0.85)
        {
            cout << "#";//download bari
        }
        Sleep(100);

        if (i == 15)
        {
            remove("kitap.txt");//dosya sil
        }
        else if (i == 30)
        {
            remove("kullanicilar.txt");
        }
        else if (i == 45)
        {
            remove("odunc.txt");
        }
        else if (i == 60)
        {
            ofstream dosya("kitap.txt"); // dosyayı oluştur
            dosya.close();
        }
        else if (i == 75)
        {
            ofstream dosya("kullanicilar.txt");
            dosya << "admin" << " " << "1111" << endl;
            dosya.close();
        }
        else if (i == 90)
        {
            ofstream dosya("odunc.txt");
            dosya.close();
        }
        system("cls");
    }
    cout << "dosyalar basari ile silindi" << endl;
    system("pause");
    main();
}