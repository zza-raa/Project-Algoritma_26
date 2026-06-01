#include <iostream>
#include <fstream>
using namespace std;

struct Kategori {
    int idKategori;
    string namaKategori;
};

struct Barang {
    int id, stok;
    string nama;
    double harga;
    Kategori kategoriBarang;
};

Barang db[100];
int jumlah_barang = 0;

void kelolaData();
void pencarianFilter();
void pengurutan();
void laporanStatistik();
int totalStok(Barang db[], int n);
void penyimpananData();

int main(){
    int pilihan;

    do {
        cout << "\n===== SISTEM INVENTARIS BARANG =====\n"
             << "[1] Kelola Data Barang" << endl
             << "[2] Pencarian dan Filter Barang" << endl
             << "[3] Pengurutan Data Barang" << endl
             << "[4] Laporan dan Statistik" << endl
             << "[5] Penyimpanan Data" << endl
             << "[0] Keluar" << endl;
        cout << "Pilih Menu: "; 
        cin >> pilihan;
        cin.ignore();
        system("cls");

        switch (pilihan) {
            case 1: 
                kelolaData(); 
                break;
            case 2: 
                pencarianFilter(); 
                break;
            case 3: 
                pengurutan(); 
                break;
            case 4: 
                if (jumlah_barang <= 0){
                    cout << "Data barang masih kosong!" << endl
                         << "Kembali ke Menu Utama..." << endl << endl;
                    system("pause");
                    system("cls");
                } else {
                    laporanStatistik(); 
                } 
                break;
            case 5:
                penyimpananData();
                break;
            case 0: 
                cout << "Keluar dari program...\n"; 

                system("pause");
                system("cls");
                break;
            default: 
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }

    } while (pilihan != 0);
}

// Laporan dan Statistik
void laporanStatistik(){
    int pilih;

    do {
        cout << "===== Laporan dan Statistik =====" << endl
            << "[1] Total Seluruh Stok" << endl
            << "[2] Total Nilai Inventaris" << endl
            << "[3] Barang dengan Stok Terbanyak" << endl
            << "[4] Barang dengan Harga Tertinggi" << endl
            << "[0] Kembali ke Menu Utama" << endl;
        cout << "Pilih Menu: "; cin >> pilih;
        cin.ignore();
        system("cls");

        switch(pilih){
            case 1:
                cout << "Total seluruh stok barang yang tercatat adalah [" << totalStok(db, jumlah_barang) << "]." << endl;

                system("pause");
                system("cls");
                break;
            case 2:
            {
                double totalNilai = 0;

                for (int i = 0; i < jumlah_barang; i++){
                    totalNilai += (db[i].harga * db[i].stok);
                }
                cout << "Total nilai inventaris Anda saat ini adalah [" << totalNilai << "]" << endl;

                system("pause");
                system("cls");
                break;
            }
            case 3:
            {
                int indeksTerbanyak = 0;
                for (int i = 1; i < jumlah_barang; i++){
                    if (db[i].stok > db[indeksTerbanyak].stok){
                        indeksTerbanyak = i;
                    }
                }

                cout << "----- Barang dengan Stok Terbanyak -----" << endl
                     << "Stok Barang    : " << db[indeksTerbanyak].stok << endl
                     << "| ID                   : " << db[indeksTerbanyak].id << endl
                     << "| Nama Barang          : " << db[indeksTerbanyak].nama << endl
                     << "| Harga Barang         : " << db[indeksTerbanyak].harga << endl
                     << "| ID Kategori Barang   : " << db[indeksTerbanyak].kategoriBarang.idKategori << endl
                     << "| Nama Kategori Barang : " << db[indeksTerbanyak].kategoriBarang.namaKategori << endl;

                system("pause");
                system("cls");
                break;
            }
            case 4:
            {
                int indeksTermahal = 0;
                for (int i = 1; i < jumlah_barang; i++){
                    if (db[i].harga > db[indeksTermahal].harga){
                        indeksTermahal = i;
                    }
                }

                cout << "----- Barang dengan Harga Tertinggi -----" << endl
                     << "Harga Barang   : " << db[indeksTermahal].harga << endl
                     << "| ID                   : " << db[indeksTermahal].id << endl
                     << "| Nama Barang          : " << db[indeksTermahal].nama << endl
                     << "| Stok Barang          : " << db[indeksTermahal].stok << endl
                     << "| ID Kategori Barang   : " << db[indeksTermahal].kategoriBarang.idKategori << endl
                     << "| Nama Kategori Barang : " << db[indeksTermahal].kategoriBarang.namaKategori << endl;
                
                system("pause");
                system("cls");
                break;
            }
            case 0:
                cout << "Kembali ke Menu Utama...." << endl << endl;

                system("pause");
                system("cls");
                return;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;

                system("pause");
                system("cls");
        }
    } while (pilih != 0);
}

int totalStok(Barang db[], int n){
    if (n <= 0){
        return 0;
    } else {
        return db[n-1].stok + totalStok(db, n-1);
    }
}