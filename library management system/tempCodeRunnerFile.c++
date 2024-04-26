void kitapkaldir()
{
string kitapisim;
cout << "Silmek istediginiz kitabin adini giriniz: "<<endl;
getline(cin,kitapisim);
getline(cin,kitapisim);

ifstream dosya("kitap.txt");

if (!dosya) {
cout << "Kitaplar dosyasi bulunamadi!" <<endl;
return;
}

vector<string> kitaplar;
string satir;
bool bulundu = false;

while (getline(dosya, satir)) 
{
    if (satir == kitapisim) 
    bulundu = true;
    }
    dosya.close();
    if (!bulundu) {
    cout << "Kitap bulunamadi!" <<endl;
   return;
    }

    ofstream yeni_dosya("kitap.txt");
   if(bulundu==true) {
        yeni_dosya << kitapisim <<endl;
    }
    yeni_dosya.close();

cout << "Kitap basariyla silindi!" << std::endl;

}