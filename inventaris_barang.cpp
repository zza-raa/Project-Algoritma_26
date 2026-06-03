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

void clearScreen() {
    system("cls");
}

void pauseProgram() {
    cout << "\nTekan Enter untuk kembali ke menu utama ... ";
    cin.get();
}

int main(){
    int pilihan;

    do {
        clearScreen();
        cout << "===== SISTEM INVENTARIS BARANG =====\n"
             << "[1] Kelola Data Barang" << endl
             << "[2] Pencarian dan Filter Barang" << endl
             << "[3] Pengurutan Data Barang" << endl
             << "[4] Laporan dan Statistik" << endl
             << "[5] Penyimpanan Data" << endl
             << "[0] Keluar" << endl;
        cout << "Pilih Menu : "; 
        cin >> pilihan;
        cin.ignore();
        system("cls");

        switch (pilihan) {
            case 1: 
                clearScreen();
                kelolaData(); 
                pauseProgram();
                break;
            case 2: 
                clearScreen();
                pencarianFilter();
                pauseProgram();
                break;
            case 3: 
                clearScreen();
                pengurutan();
                pauseProgram();
                break;
            case 4: 
                clearScreen();
                if (jumlah_barang <= 0){
                    cout << "Data barang masih kosong!" << endl
                         << "Kembali ke Menu Utama..." << endl << endl;
                    system("pause");
                    system("cls");
                } else {
                    laporanStatistik(); 
                } 
                break;
                pauseProgram();
            case 5:
                clearScreen();
                penyimpananData();
                break;
            case 0: 
                cout << "Keluar dari program...\n\n"; 
                system("pause");
                break;
            default: 
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }

    } while (pilihan != 0);
}

void kelolaData(){};
void pencarianFilter(){};
void pengurutan(){};

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

void penyimpananData() {
    int pilih;
    string fileUtama = "inventaris.txt";
    string fileBackup = "backup_inventaris.txt";

    // Membuat pointer yang menunjuk ke array global 'db'
    // Ini untuk memenuhi materi "Pointer" dalam pembagian tugas
    Barang *ptr = db;

    do {
        clearScreen();
        cout << "===== MENU PENYIMPANAN DATA =====" << endl
             << "[1] Simpan ke File" << endl
             << "[2] Baca dari File" << endl
             << "[3] Backup Data (Salinan)" << endl
             << "[4] Kosongkan Data File (Hapus Semua)" << endl
             << "[0] Kembali ke Menu Utama" << endl;
        cout << "Pilih Menu : "; cin >> pilih;
        cin.ignore();

        switch(pilih) {
            case 1: {
                // 1. SIMPAN KE FILE
                ofstream outFile(fileUtama);
                if (!outFile) {
                    cout << "]\nERROR: Gagal membuka file untuk menyimpan data!" << endl;
                } else {
                    if (jumlah_barang == 0) {
                        cout << "\nPeringatan:\nData di program kosong. File akan disimpan sebagai data kosong." << endl;
                    }
                    
                    // Baris pertama file diisi oleh jumlah barang saat ini
                    outFile << jumlah_barang << endl;

                    // Menulis data barang ke file menggunakan operasi POINTER
                    for (int i = 0; i < jumlah_barang; i++) {
                        outFile << (ptr + i)->id << endl;
                        outFile << (ptr + i)->nama << endl;
                        outFile << (ptr + i)->stok << endl;
                        outFile << (ptr + i)->harga << endl;
                        outFile << (ptr + i)->kategoriBarang.idKategori << endl;
                        outFile << (ptr + i)->kategoriBarang.namaKategori << endl;
                    }
                    outFile.close();
                    cout << "Ada " << jumlah_barang << " data barang telah disimpan ke '" << fileUtama << "'." << endl << endl;
                }
                pauseProgram();
                break;
            }
            case 2: {
                // 2. BACA DARI FILE
                ifstream inFile(fileUtama);
                if (!inFile) {
                    cout << "ERROR: File '" << fileUtama << "' tidak ditemukan atau belum pernah dibuat!" << endl;
                } else {
                    // Membaca baris pertama untuk mengetahui jumlah data
                    inFile >> jumlah_barang;
                    inFile.ignore(); // Abaikan sisa newline setelah membaca integer

                    // Membaca seluruh data barang dari file menggunakan operasi POINTER
                    for (int i = 0; i < jumlah_barang; i++) {
                        inFile >> (ptr + i)->id;
                        inFile.ignore(); // Abaikan newline setelah ID
                        
                        getline(inFile, (ptr + i)->nama);
                        
                        inFile >> (ptr + i)->stok;
                        inFile >> (ptr + i)->harga;
                        inFile >> (ptr + i)->kategoriBarang.idKategori;
                        inFile.ignore(); // Abaikan newline sebelum membaca string kategori
                        
                        getline(inFile, (ptr + i)->kategoriBarang.namaKategori);
                    }
                    inFile.close();
                    cout << "\nBerhasil! Memuat " << jumlah_barang << " data dari '" << fileUtama << "' ke dalam sistem." << endl;
                }
                pauseProgram();
                break;
            }
            case 3: {
                // 3. BACKUP DATA
                ofstream backupFile(fileBackup);
                if (!backupFile) {
                    cout << "ERROR: Gagal membuat file backup!" << endl;
                } else {
                    // Proses backup sama seperti simpan file, menggunakan POINTER
                    backupFile << jumlah_barang << endl;
                    for (int i = 0; i < jumlah_barang; i++) {
                        backupFile << (ptr + i)->id << endl;
                        backupFile << (ptr + i)->nama << endl;
                        backupFile << (ptr + i)->stok << endl;
                        backupFile << (ptr + i)->harga << endl;
                        backupFile << (ptr + i)->kategoriBarang.idKategori << endl;
                        backupFile << (ptr + i)->kategoriBarang.namaKategori << endl;
                    }
                    backupFile.close();
                    cout << "\nBerhasil! Salinan data (backup) telah dibuat di '" << fileBackup << "'." << endl;
                }
                pauseProgram();
                break;
            }
            case 4: {
                // 4. HAPUS DATA DI FILE (Sesuai catatan tambahanmu: "user bisa hapus ke file")
                char konfirmasi;
                cout << "\nApakah Anda yakin ingin menghapus seluruh isi data pada file '" << fileUtama << "'? (y/n) : ";
                cin >> konfirmasi;
                cin.ignore();
                
                if (konfirmasi == 'y' || konfirmasi == 'Y') {
                    // Membuka file dengan mode ios::trunc akan menghapus/mengosongkan seluruh isinya
                    ofstream outFile(fileUtama, ios::trunc); 
                    if (outFile) {
                        outFile << 0 << endl; // Tulis isi bahwa data sekarang ada 0
                        outFile.close();
                        cout << "Berhasil! Seluruh isi file '" << fileUtama << "' telah dikosongkan." << endl;
                    } else {
                        cout << "ERROR: Gagal membuka file!" << endl;
                    }
                } else {
                    cout << "Aksi pembatalan berhasil dilakukan." << endl;
                }
                pauseProgram();
                break;
            }
            case 0:
                pauseProgram();
                return;
                
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
                pauseProgram();
        }
    } while (pilih != 0);
}
