#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_BUKU = 100;

struct Buku {
    string kode;
    string judul;
    string penulis;
    int tahun;
    int stok;
};

class ManajemenBuku {
private:
    Buku daftarBuku[MAX_BUKU];
    int jumlahBuku;
    string namaFile;

    void tukarBuku(Buku &a, Buku &b) {
        Buku temp = a;
        a = b;
        b = temp;
}

public:
    ManajemenBuku() : jumlahBuku(0), namaFile("databuku.txt") {}

void simpanKeFile() {
        ofstream file("databuku.txt");
        if (!file.is_open()) {
            cout << "Gagal menyimpan data ke file\n"; 
            return;
}

        for (int i = 0; i < jumlahBuku; i++) {
            file << daftarBuku[i].kode << "\n"
                << daftarBuku[i].judul << "\n"
                << daftarBuku[i].penulis << "\n"
                << daftarBuku[i].tahun << "\n"
                << daftarBuku[i].stok << "\n";
        }

        file.close();
        cout << "Data berhasil disimpan ke " << namaFile << endl;
}

void tambahBukuBaru() {
        if (jumlahBuku >= MAX_BUKU) {
            cout << "Database buku penuh!\n";
            return;
        }

        cout << "\nMasukkan data buku baru:\n";
        
        bool valid=false;
        while(!valid){
            cout<<"KodeBuku(01-10):";
            cin>>daftarBuku[jumlahBuku].kode;
            if(daftarBuku[jumlahBuku].kode.size()==2&&
                daftarBuku[jumlahBuku].kode>="01"&&
                daftarBuku[jumlahBuku].kode<="10"){
                valid=true;
            }else{
                cout<<"Kode harus antara 01-10 Silakancobalagi.\n";
            }
        }
        cin.ignore();
        cout<<"JudulBuku:";
        getline(cin,daftarBuku[jumlahBuku].judul);
        cout<<"Penulis:";
        getline(cin,daftarBuku[jumlahBuku].penulis);
        cout<<"TahunPenerbit:";
        cin>>daftarBuku[jumlahBuku].tahun;
        cout<<"Stok:";
        cin>>daftarBuku[jumlahBuku].stok;
        jumlahBuku++;
        cout<<"Buku berhasil ditambahkan!\n";
}

void cariBerdasarkanPenulis(const string& penulis) {
        ofstream outFile("hasil_cari_penulis.txt");
        bool found = false;

        cout <<"\nHasil pencarian untuk penulis '"<<penulis<<"':\n";
        outFile << "Hasil pencarian untuk penulis '" <<penulis<<"':\n";

        for (int i = 0; i < jumlahBuku; i++) {
            if (daftarBuku[i].penulis.find(penulis) != string::npos) {
                cout << "Kode:" << daftarBuku[i].kode << ",Judul:" << daftarBuku[i].judul
                    << ",Penulis:" << daftarBuku[i].penulis << ",Tahun:" << daftarBuku[i].tahun
                    << ",Stok:" << daftarBuku[i].stok << endl;
                outFile << "Kode:" << daftarBuku[i].kode << ",Judul:" << daftarBuku[i].judul
                        << ",Penulis:" << daftarBuku[i].penulis << ",Tahun:" << daftarBuku[i].tahun
                        << ",Stok:" << daftarBuku[i].stok << endl;
                found = true;
            }
        }

        if (!found) {
            cout<<"Tidak ditemukan buku dengan penulis '" <<penulis<<endl;
            outFile<<"Tidak ditemukan buku dengan penulis '"<<penulis<<endl;
        }

        outFile.close();
}

void cariBerdasarkanJudul(const string& judul) {
        ofstream outFile("hasil_cari_judul.txt");
        bool found = false;

        cout << "\nHasil pencarian untuk judul '" << judul << "':\n";
        outFile << "Hasil pencarian untuk judul '" << judul << "':\n";

        for (int i = 0; i < jumlahBuku; i++) {
            if (daftarBuku[i].judul.find(judul) != string::npos) {
                cout << "Kode:" << daftarBuku[i].kode << ",Judul:" << daftarBuku[i].judul
                    << ",Penulis:" << daftarBuku[i].penulis << ",Tahun:" << daftarBuku[i].tahun
                    << ",Stok:" << daftarBuku[i].stok << endl;
                outFile << "Kode:" << daftarBuku[i].kode << ",Judul:" << daftarBuku[i].judul
                        << ",Penulis:" << daftarBuku[i].penulis << ",Tahun:" << daftarBuku[i].tahun
                        << ",Stok:" << daftarBuku[i].stok << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "Tidak ditemukan buku dengan judul '" << judul << "'\n";
            outFile << "Tidak ditemukan buku dengan judul '" << judul << "'\n";
        }

        outFile.close();
}

void cariBerdasarkanStok(int tstok, bool kurangDari) {
        cout<<"\nHasil pencarian untuk stok "<<(kurangDari?"kurang dari ":"lebih dari atau sama dengan ")<<tstok<< ":\n";

        for (int i = 0; i < jumlahBuku; i++) {
            if ((kurangDari && daftarBuku[i].stok < tstok) || (!kurangDari && daftarBuku[i].stok >= tstok)) {
                cout << "Kode:" << daftarBuku[i].kode << ",Judul:" << daftarBuku[i].judul
                    << ",Penulis:" << daftarBuku[i].penulis << ",Tahun:" << daftarBuku[i].tahun
                    << ",Stok:" << daftarBuku[i].stok << endl;
            }
    }
}

void cariStokTerbanyak() {
        if (jumlahBuku == 0) {
            cout << "Tidak ada data buku.\n";
            return;
        }

        int maxStock = daftarBuku[0].stok;
        for (int i = 1; i < jumlahBuku; i++) {
            if (daftarBuku[i].stok > maxStock) {
                maxStock = daftarBuku[i].stok;
            }
        }

        cout << "\nBuku dengan stok terbanyak (" << maxStock << "):\n";
        for (int i = 0; i < jumlahBuku; i++) {
            if (daftarBuku[i].stok == maxStock) {
                cout << "Kode:" << daftarBuku[i].kode << ",Judul:" << daftarBuku[i].judul
                    << ",Penulis:" << daftarBuku[i].penulis << ",Tahun:" << daftarBuku[i].tahun
                    << ",Stok:" << daftarBuku[i].stok << endl;
            }
    }
}

void urutkanBukuAZ() {
        for (int i = 0; i < jumlahBuku - 1; i++) {
            for (int j = 0; j < jumlahBuku - i - 1; j++) {
                if (daftarBuku[j].judul > daftarBuku[j + 1].judul) {
                    tukarBuku(daftarBuku[j], daftarBuku[j + 1]);
                }
            }
}

        cout << "\nDaftar buku terurut A-Z:\n";
        for (int i = 0; i < jumlahBuku; i++) {
            cout << "Kode:" << daftarBuku[i].kode << ",Judul:" << daftarBuku[i].judul
                << ",Penulis:" << daftarBuku[i].penulis << ",Tahun:" << daftarBuku[i].tahun
                << ",Stok:" << daftarBuku[i].stok << endl;
        }
}

void urutkanBukuZA() {
        for (int i = 0; i < jumlahBuku - 1; i++) {
            for (int j = 0; j < jumlahBuku - i - 1; j++) {
                if (daftarBuku[j].judul < daftarBuku[j + 1].judul) {
                    tukarBuku(daftarBuku[j], daftarBuku[j + 1]);
        }
    }
}

        cout << "\nDaftar buku terurut Z-A:\n";
        for (int i = 0; i < jumlahBuku; i++) {
            cout << "Kode:" << daftarBuku[i].kode << ",Judul:" << daftarBuku[i].judul
                << ",Penulis:" << daftarBuku[i].penulis << ",Tahun:" << daftarBuku[i].tahun
                << ",Stok:" << daftarBuku[i].stok << endl;
    }
}

void tampilkanSemuaBuku() {
        if (jumlahBuku == 0) {
            cout << "Tidak ada data buku.\n";
            return;
        }

        cout << "\nDaftar Semua Buku:\n";
        for (int i = 0; i < jumlahBuku; i++) {
            cout << "Kode:" << daftarBuku[i].kode << ",Judul:" << daftarBuku[i].judul
                << ",Penulis:" << daftarBuku[i].penulis << ",Tahun:" << daftarBuku[i].tahun
                << ",Stok:" << daftarBuku[i].stok << endl;
    }
}

void buatDataContoh() {
        string contohNomor[10] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10"};
        string contohJudul[10] = {"wongireng", "Bumi", "Harry Potter", "The Hobbit", "bumimeletop", "Filosofi kalimantan", "Pulang", "Pergi", "Negeri muanipulasi", "bertemu crush"
};
        string contohPenulis[10] = {"wongputih", "satya", "muchsin", "haidar","edoedi", "ramaikn mangkrak", "rafi", "lagi", "bagassigma", "eko"
};
        int contohTahun[10] = {2008, 1980, 1997, 1937, 1949, 2018, 2012, 2015, 2009, 1982};
        int contohstok[10] = {10, 8, 20, 12, 10, 25, 7, 5, 99, 6};

        for (int i = 0; i < 10; i++) {
            daftarBuku[i].kode = contohNomor[i];
            daftarBuku[i].judul = contohJudul[i];
            daftarBuku[i].penulis = contohPenulis[i];
            daftarBuku[i].tahun = contohTahun[i];
            daftarBuku[i].stok = contohstok[i];
        }
        jumlahBuku = 10;
}

void tampilkanMenu() {
        cout<<"\n===Sistem Manajemen Buku Perpustakaan===\n";
        cout<<"1.Tampilkan semua buku\n";
        cout<<"2.Cari buku berdasarkan penulis\n";
        cout<<"3.Cari buku berdasarkan judul\n";
        cout<<"4.Cari buku berdasarkan stok (kurang dari)\n";
        cout<<"5.Cari buku berdasarkan stok (lebih dari atau sama dengan)\n";
        cout<<"6.Cari buku dengan stok terbanyak\n";
        cout<<"7.Urutkan buku berdasarkan judul (A-Z)\n";
        cout<<"8.Urutkan buku berdasarkan judul (Z-A)\n";
        cout<<"9.Tambah buku baru\n";
        cout<<"10.Simpan data ke file\n";
        cout<<"11.Keluar\n";
        cout<<"Pilihan: ";
    }
};

int main() {
    ManajemenBuku manajemenBuku;
    int pilihan;
    
    cout << "==========SeLaMaT DaTaNg===========\n";
    cout << "1. Lihat Data-Data Buku Yang tersimpan\n";
    cout << "===================================\n";
    cout << "Pilihan: ";
   
    cin >> pilihan;
    cin.ignore();
    if (pilihan == 1) {
	manajemenBuku.buatDataContoh();
    cout<<"Data-Data buku telah dimuat.\n";
}

    int pilih;
    do {
        manajemenBuku.tampilkanMenu();
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1:
                manajemenBuku.tampilkanSemuaBuku();
                break;
            case 2: {
                string penulis;
                cout << "Masukkan nama penulis: ";
                getline(cin, penulis);
                manajemenBuku.cariBerdasarkanPenulis(penulis);
                break;
            }
            case 3: {
                string judul;
                cout << "Masukkan judul buku: ";
                getline(cin, judul);
                manajemenBuku.cariBerdasarkanJudul(judul);
                break;
            }
            case 4: {
                int tstok;
                cout << "Masukkan batas stok: ";
                cin >> tstok;
                manajemenBuku.cariBerdasarkanStok(tstok, true);
                break;
            }
            case 5: {
                int tstok;
                cout << "Masukkan batas stok: ";
                cin >> tstok;
                manajemenBuku.cariBerdasarkanStok(tstok, false);
                break;
            }
            case 6:
                manajemenBuku.cariStokTerbanyak();
                break;
            case 7:
                manajemenBuku.urutkanBukuAZ();
                break;
            case 8:
                manajemenBuku.urutkanBukuZA();
                break;
            case 9:
                manajemenBuku.tambahBukuBaru();
                break;
            case 10:
                manajemenBuku.simpanKeFile();
                break;
            case 11:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilih != 11);

    return 0;
}

