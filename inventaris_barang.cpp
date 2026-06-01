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
};

Barang db[100];
int jumlah_barang = 0;

void kelolaData();
void pencarianFilter();
void pengurutan();
void laporanStatistik();
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
                laporanStatistik(); 
                break;
            case 5:
                penyimpananData();
                break;
            case 0: 
                cout << "Keluar dari program...\n"; 
                break;
            default: 
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }

    }
}