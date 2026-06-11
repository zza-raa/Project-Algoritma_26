#include <iostream>
#include <fstream>
#include <iomanip>
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
void tambahBarang();
void editBarang();
void hapusBarang();
void tampilBarang();

void clearScreen() {
    system("cls");
}

void pauseProgram() {
    cout << "\nTekan Enter untuk kembali... ";
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
                break;
            case 2: 
                clearScreen();
                pencarianFilter();
                break;
            case 3: 
                clearScreen();
                pengurutan();
                break;
            case 4: 
                clearScreen();
                if (jumlah_barang <= 0){
                    cout << "Data barang masih kosong!" << endl;
                    pauseProgram();
                } else {
                    laporanStatistik(); 
                } 
                break;
            case 5:
                clearScreen();
                penyimpananData();
                break;
            case 0: 
                cout << "Keluar dari program...\n\n"; 
                break;
            default: 
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
                pauseProgram();
        }

    } while (pilihan != 0);
    return 0;
}

void kelolaData() {
    int pilih;

    do {
        clearScreen();
        cout << "===== KELOLA DATA =====\n";
        cout << "[1] Tambah\n";
        cout << "[2] Edit\n";
        cout << "[3] Hapus\n";
        cout << "[4] Tampil\n";
        cout << "[0] Kembali\n";
        cout << "Pilih : ";
        cin >> pilih;
        cin.ignore();

        switch(pilih) {
            case 1:
                tambahBarang();
                pauseProgram();
                break;
            case 2:
                editBarang();
                pauseProgram();
                break;
            case 3:
                hapusBarang();
                pauseProgram();
                break;
            case 4:
                tampilBarang();
                pauseProgram();
                break;
            case 0:
                return;
        }

    } while (pilih != 0);
}

// ================== TAMBAH ==================
void tambahBarang() {
    cout << "\nID : ";
    cin >> db[jumlah_barang].id;
    cin.ignore();

    cout << "Nama : ";
    getline(cin, db[jumlah_barang].nama);

    cout << "Harga : ";
    cin >> db[jumlah_barang].harga;

    cout << "Stok : ";
    cin >> db[jumlah_barang].stok;

    cout << "ID Kategori : ";
    cin >> db[jumlah_barang].kategoriBarang.idKategori;
    cin.ignore();

    cout << "Nama Kategori : ";
    getline(cin, db[jumlah_barang].kategoriBarang.namaKategori);

    jumlah_barang++;
    cout << "Berhasil ditambah!\n";
}

// ================== EDIT ==================
void editBarang() {
    int id;
    cout << "ID yang dicari: ";
    cin >> id;
    cin.ignore();

    for(int i=0; i<jumlah_barang; i++){
        if(db[i].id == id){
            cout << "Nama baru: ";
            getline(cin, db[i].nama);

            cout << "Harga baru: ";
            cin >> db[i].harga;

            cout << "Stok baru: ";
            cin >> db[i].stok;

            cout << "ID Kategori baru: ";
            cin >> db[i].kategoriBarang.idKategori;
            cin.ignore();

            cout << "Nama Kategori baru: ";
            getline(cin, db[i].kategoriBarang.namaKategori);

            cout << "Berhasil diubah!\n";
            return;
        }
    }
    cout << "Tidak ditemukan!\n";
}

// ================== HAPUS ==================
void hapusBarang() {
    int id;
    cout << "ID hapus: ";
    cin >> id;
    cin.ignore();

    for(int i=0; i<jumlah_barang; i++){
        if(db[i].id == id){
            for(int j=i; j<jumlah_barang-1; j++){
                db[j]=db[j+1];
            }
            jumlah_barang--;
            cout << "Terhapus!\n";
            return;
        }
    }
    cout << "Tidak ditemukan!\n";
}

// ================== TAMPIL ==================
void tampilBarang() {
    if(jumlah_barang==0){
        cout << "Kosong!\n";
        return;
    }

    for(int i=0; i<jumlah_barang; i++){
        cout << "\nID: " << db[i].id;
        cout << "\nNama: " << db[i].nama;
        // Fix output format layar console
        cout << "\nHarga: " << fixed << setprecision(0) << db[i].harga;
        cout << "\nStok: " << db[i].stok;
        cout << "\nKategori: " << db[i].kategoriBarang.namaKategori;
        cout << "\n-----------------\n";
    }
}

void tukarData(Barang *a, Barang *b) {
    Barang temp = *a;
    *a = *b;
    *b = temp;
}

// ================== PENCARIAN ==================
void pencarianFilter(){
    int pilihan;
    string target;
    
    if (jumlah_barang == 0){
        cout << "Data tidak ditemukan / Data masih kosong\n";
        pauseProgram();
        return;
    }
    
    do {
        clearScreen();
        cout << "===== PENCARIAN DATA =====\n"
             << "[1] Cari berdasarkan ID" << endl
             << "[2] Cari berdasarkan nama" << endl
             << "[3] Cari berdasarkan rentang harga" << endl
             << "[0] Keluar" << endl;
        cout << "Pilih Menu: "; 
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: {
                for (int i = 0; i < jumlah_barang - 1; i++) {
                    for (int j = 0; j < jumlah_barang - i - 1; j++) {
                        if (db[j].id > db[j+1].id) {
                            tukarData(&db[j], &db[j+1]);
                        }
                    }
                }

                int cariID;
                cout << "Masukkan ID Barang yang dicari: "; cin >> cariID;
                cin.ignore();

                int kiri = 0, kanan = jumlah_barang - 1, titikTemu = -1;
                while (kiri <= kanan) {
                    int tengah = kiri + (kanan - kiri) / 2;
                    if (db[tengah].id == cariID) {
                        titikTemu = tengah;
                        break;
                    }
                    if (db[tengah].id < cariID) kiri = tengah + 1;
                    else kanan = tengah - 1;
                }

                if (titikTemu != -1) {
                    cout << "\n--- DATA DITEMUKAN ---\n";
                    cout << "ID           : " << db[titikTemu].id << "\n";
                    cout << "Nama         : " << db[titikTemu].nama << "\n";
                    cout << "Harga        : " << fixed << setprecision(0) << db[titikTemu].harga << "\n";
                    cout << "Stok Barang  : " << db[titikTemu].stok << "\n";
                    cout << "ID Kategori  : " << db[titikTemu].kategoriBarang.idKategori << "\n";
                    cout << "Nama Kategori: " << db[titikTemu].kategoriBarang.namaKategori << "\n";
                    cout << "------------------------------\n";
                } else {
                    cout << "ID Barang: " << cariID << " tidak ditemukan.\n";
                }
                pauseProgram();
                break;
            }
                
            case 2: {
                int titktemu = -1;
                cout << "Masukkan Nama Barang: "; getline(cin, target);
                for (int i = 0; i < jumlah_barang; i++) {
                    if (db[i].nama == target) {
                        titktemu = i;
                        cout << "\n--- DATA DITEMUKAN ---\n";
                        cout << "ID           : " << db[titktemu].id << "\n";
                        cout << "Nama         : " << db[titktemu].nama << "\n";
                        cout << "Harga        : " << fixed << setprecision(0) << db[titktemu].harga << "\n";
                        cout << "Stok Barang  : " << db[titktemu].stok << "\n";
                        cout << "ID Kategori  : " << db[titktemu].kategoriBarang.idKategori << "\n";
                        cout << "Nama Kategori: " << db[titktemu].kategoriBarang.namaKategori << "\n";
                        cout << "------------------------------\n";
                        break;
                    }
                }
                if (titktemu == -1) {
                    cout << "Nama Barang: \"" << target << "\" tidak ditemukan\n";
                }
                pauseProgram();
                break;
            }
                
            case 3: {
                double hargamax = -1, hargamin = -1, tempharga;
                cout << "Masukkan Rentang Harga Terendah : "; cin >> hargamin;
                cout << "Masukkan Rentang Harga Tertinggi: "; cin >> hargamax;
                cin.ignore();
                
                if(hargamax < hargamin) {
                    tempharga = hargamax;
                    hargamax = hargamin;
                    hargamin = tempharga;
                }
                
                bool adaBarang = false;
                cout << "\n--- HASIL PENCARIAN RENTANG HARGA ---\n";
                for (int i = 0; i < jumlah_barang; i++) {
                    if (db[i].harga >= hargamin && db[i].harga <= hargamax) {
                        cout << "ID           : " << db[i].id << "\n";
                        cout << "Nama         : " << db[i].nama << "\n";
                        cout << "Harga        : " << fixed << setprecision(0) << db[i].harga << "\n";
                        cout << "Stok Barang  : " << db[i].stok << "\n";
                        cout << "------------------------------\n";
                        adaBarang = true;
                    }
                }
                if (!adaBarang) {
                    cout << "Tidak ada barang dalam rentang harga tersebut.\n";
                }
                pauseProgram();
                break;
            }
            case 0: 
                break;
            default: 
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
                pauseProgram();
        }
    } while (pilihan != 0);
}

// 1. Urut Harga Naik (Ascending) - Menggunakan Bubble Sort & Pointer
void urutHargaAsc(Barang *ptr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((ptr + j)->harga > (ptr + j + 1)->harga) {
                tukarData((ptr + j), (ptr + j + 1));
            }
        }
    }
    cout << "\n[Sukses] Data berhasil diurutkan berdasarkan harga termurah!\n";
}

// 2. Urut Harga Turun (Descending) - Menggunakan Selection Sort & Pointer
void urutHargaDesc(Barang *ptr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int idxMaks = i;
        for (int j = i + 1; j < n; j++) {
            if ((ptr + j)->harga > (ptr + idxMaks)->harga) {
                idxMaks = j;
            }
        }
        tukarData((ptr + i), (ptr + idxMaks));
    }
    cout << "\n[Sukses] Data berhasil diurutkan berdasarkan harga termahal!\n";
}

// 3. Urut Nama A-Z (Ascending) - Menggunakan Bubble Sort & Pointer
void urutNamaAsc(Barang *ptr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((ptr + j)->nama > (ptr + j + 1)->nama) {
                tukarData((ptr + j), (ptr + j + 1));
            }
        }
    }
    cout << "\n[Sukses] Data berhasil diurutkan berdasarkan Nama A-Z!\n";
}

// 4. Urut Stok Terbanyak (Descending) - Menggunakan Selection Sort & Pointer
void urutStokDesc(Barang *ptr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int idxMaks = i;
        for (int j = i + 1; j < n; j++) {
            if ((ptr + j)->stok > (ptr + idxMaks)->stok) {
                idxMaks = j;
            }
        }
        tukarData((ptr + i), (ptr + idxMaks));
    }
    cout << "\n[Sukses] Data berhasil diurutkan berdasarkan Stok Terbanyak!\n";
}

void pengurutan() {
    if (jumlah_barang <= 0) {
        cout << "Data barang masih kosong!" << endl;
        pauseProgram();
        return;
    }

    int pilih;
    Barang *ptr = db;

    do {
        clearScreen();
        cout << "===== MENU PENGURUTAN DATA BARANG =====" << endl;
        cout << "[1] Urut Harga Naik (Termurah)" << endl;
        cout << "[2] Urut Harga Turun (Termahal)" << endl;
        cout << "[3] Urut Nama A-Z" << endl;
        cout << "[4] Urut Stok Terbanyak" << endl;
        cout << "[0] Kembali ke Menu Utama" << endl;
        cout << "Pilih Menu: "; cin >> pilih;
        cin.ignore();

        switch(pilih) {
            case 1:
                urutHargaAsc(ptr, jumlah_barang);
                pauseProgram();
                break;
            case 2:
                urutHargaDesc(ptr, jumlah_barang);
                pauseProgram();
                break;
            case 3:
                urutNamaAsc(ptr, jumlah_barang);
                pauseProgram();
                break;
            case 4:
                urutStokDesc(ptr, jumlah_barang);
                pauseProgram();
                break;
            case 0:
                break;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
                pauseProgram();
        }
    } while (pilih != 0);
}

void laporanStatistik(){
    int pilih;

    do {
        clearScreen();
        cout << "===== Laporan dan Statistik =====" << endl
            << "[1] Total Seluruh Stok" << endl
            << "[2] Total Nilai Inventaris" << endl
            << "[3] Barang dengan Stok Terbanyak" << endl
            << "[4] Barang dengan Harga Tertinggi" << endl
            << "[0] Kembali ke Menu Utama" << endl;
        cout << "Pilih Menu: "; cin >> pilih;
        cin.ignore();

        switch(pilih){
            case 1:
                cout << "Total seluruh stok barang yang tercatat adalah [" << totalStok(db, jumlah_barang) << "]." << endl;
                pauseProgram();
                break;
            case 2: {
                double totalNilai = 0;
                for (int i = 0; i < jumlah_barang; i++){
                    totalNilai += (db[i].harga * db[i].stok);
                }
                cout << "Total nilai inventaris Anda saat ini adalah [" << fixed << setprecision(0) << totalNilai << "]" << endl;
                pauseProgram();
                break;
            }
            case 3: {
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
                     << "| Harga Barang         : " << fixed << setprecision(0) << db[indeksTerbanyak].harga << endl
                     << "| ID Kategori Barang   : " << db[indeksTerbanyak].kategoriBarang.idKategori << endl
                     << "| Nama Kategori Barang : " << db[indeksTerbanyak].kategoriBarang.namaKategori << endl;
                pauseProgram();
                break;
            }
            case 4: {
                int indeksTermahal = 0;
                for (int i = 1; i < jumlah_barang; i++){
                    if (db[i].harga > db[indeksTermahal].harga){
                        indeksTermahal = i;
                    }
                }
                cout << "----- Barang dengan Harga Tertinggi -----" << endl
                     << "Harga Barang   : " << fixed << setprecision(0) << db[indeksTermahal].harga << endl
                     << "| ID                   : " << db[indeksTermahal].id << endl
                     << "| Nama Barang          : " << db[indeksTermahal].nama << endl
                     << "| Stok Barang          : " << db[indeksTermahal].stok << endl
                     << "| ID Kategori Barang   : " << db[indeksTermahal].kategoriBarang.idKategori << endl
                     << "| Nama Kategori Barang : " << db[indeksTermahal].kategoriBarang.namaKategori << endl;
                pauseProgram();
                break;
            }
            case 0:
                return;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
                pauseProgram();
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
                ofstream outFile(fileUtama);
                if (!outFile) {
                    cout << "\nERROR: Gagal membuka file untuk menyimpan data!" << endl;
                } else {
                    if (jumlah_barang == 0) {
                        cout << "\nPeringatan:\nData di program kosong." << endl;
                    }
                    outFile << jumlah_barang << endl;
                    for (int i = 0; i < jumlah_barang; i++) {
                        outFile << (ptr + i)->id << endl;
                        outFile << (ptr + i)->nama << endl;
                        outFile << (ptr + i)->stok << endl;
                        outFile << fixed << setprecision(0) << (ptr + i)->harga << endl;
                        outFile << (ptr + i)->kategoriBarang.idKategori << endl;
                        outFile << (ptr + i)->kategoriBarang.namaKategori << endl;
                    }
                    outFile.close();
                    cout << "Ada " << jumlah_barang << " data telah disimpan ke '" << fileUtama << "'." << endl;
                    pauseProgram();
                    return;
                }
                break;
            }
            case 2: {
                ifstream inFile(fileUtama);
                if (!inFile) {
                    cout << "ERROR: File '" << fileUtama << "' tidak ditemukan!" << endl;
                    pauseProgram(); 
                } else {
                    inFile >> jumlah_barang;
                    inFile.ignore(); 

                    for (int i = 0; i < jumlah_barang; i++) {
                        inFile >> (ptr + i)->id;
                        inFile.ignore(); 
                        getline(inFile, (ptr + i)->nama);
                        inFile >> (ptr + i)->stok;
                        inFile >> (ptr + i)->harga;
                        inFile >> (ptr + i)->kategoriBarang.idKategori;
                        inFile.ignore(); 
                        getline(inFile, (ptr + i)->kategoriBarang.namaKategori);
                    }
                    inFile.close();
                    cout << "\nBerhasil memuat " << jumlah_barang << " data dari '" << fileUtama << "'." << endl;
                    pauseProgram();                
                    return; 
                }
                break;
            }

            case 3: {
                ofstream backupFile(fileBackup);
                if (!backupFile) {
                    cout << "ERROR: Gagal membuat file backup!" << endl;
                } else {
                    backupFile << jumlah_barang << endl;
                    for (int i = 0; i < jumlah_barang; i++) {
                        backupFile << (ptr + i)->id << endl;
                        backupFile << (ptr + i)->nama << endl;
                        backupFile << (ptr + i)->stok << endl;
                        backupFile << fixed << setprecision(0) << (ptr + i)->harga << endl;
                        backupFile << (ptr + i)->kategoriBarang.idKategori << endl;
                        backupFile << (ptr + i)->kategoriBarang.namaKategori << endl;
                    }
                    backupFile.close();
                    cout << "\nBerhasil! Backup dibuat di '" << fileBackup << "'." << endl;
                }
                pauseProgram();
                break;
            }
            case 4: {
                char konfirmasi;
                cout << "\nApakah Anda yakin ingin menghapus file '" << fileUtama << "'? (y/n) : ";
                cin >> konfirmasi;
                cin.ignore();
                
                if (konfirmasi == 'y' || konfirmasi == 'Y') {
                    ofstream outFile(fileUtama, ios::trunc); 
                    if (outFile) {
                        outFile << 0 << endl; 
                        outFile.close();
                        cout << "Berhasil! File '" << fileUtama << "' telah dikosongkan." << endl;
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
                return;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
                pauseProgram();
        }
    } while (pilih != 0);
}
