/*
||===================================||
||           Kelompok  3             ||
||===================================||
|| Musaid Nabil Susena  || 124250056 ||
|| Vanessa Putri Anazwa || 124250061 ||
||===================================||
*/
	
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

struct NodeUser {
    string username;
    string password;
    NodeUser* next;
};

struct NodeBarang {
    int id_barang;
    string nama_barang;
    string kategori;
    int harga_jual;
    int harga_beli;
    int stok_barang;
    int terjual_sebanyak;
    NodeBarang* next;
};

NodeBarang* headBarang = nullptr;
int jumlahbarang = 0;

struct UsernamePW {
    string username;
    string password;
} user[50];

struct DetailBarang {
    int id_barang;
    int jumlah;
};

struct Transaksi {
    int id_pelanggan;
    int jumlah_item;
    DetailBarang detail[100];
    int total_transaksi;
} tran;

struct Utama {
    int kesempatan = 3;
    int tanggal;
    int bulan;
    int tahun;
    int no_pelanggan;
} utama;

void menuGudang();
void menuAdmin();
void menuFinansial();


NodeUser* BuatNodeUser(string username, string password) {
    NodeUser* node = new NodeUser();
    node->username = username;
    node->password = password;
    node->next     = nullptr;
    return node;
}

void TambahNodeUserKeAkhir(NodeUser*& head, NodeUser* node) {
    if (head == nullptr) {
        head = node;
    } else {
        NodeUser* curr = head;
        while (curr->next != nullptr) curr = curr->next;
        curr->next = node;
    }
}

void HapusSemualUser(NodeUser*& head) {
    NodeUser* curr = head;
    while (curr != nullptr) {
        NodeUser* temp = curr;
        curr = curr->next;
        delete temp;
    }
    head = nullptr;
}

int MuatUserDariLinkedList(NodeUser* head) {
    int n = 0;
    NodeUser* curr = head;
    while (curr != nullptr && n < 50) {
        user[n].username = curr->username;
        user[n].password = curr->password;
        n++;
        curr = curr->next;
    }
    for (int i = n; i < 50; i++) {
        user[i].username = "";
        user[i].password = "";
    }
    return n;
}

NodeBarang* BuatNode(int id, string nama, string kategori,
                     int harga_beli, int harga_jual,
                     int stok, int terjual) {
    NodeBarang* node = new NodeBarang();
    node->id_barang        = id;
    node->nama_barang      = nama;
    node->kategori         = kategori;
    node->harga_beli       = harga_beli;
    node->harga_jual       = harga_jual;
    node->stok_barang      = stok;
    node->terjual_sebanyak = terjual;
    node->next             = nullptr;
    return node;
}

void TambahNodeKeAkhir(NodeBarang* node) {
    if (headBarang == nullptr) {
        headBarang = node;
    } else {
        NodeBarang* curr = headBarang;
        while (curr->next != nullptr) curr = curr->next;
        curr->next = node;
    }
    jumlahbarang++;
}

void HapusSemua() {
    NodeBarang* curr = headBarang;
    while (curr != nullptr) {
        NodeBarang* temp = curr;
        curr = curr->next;
        delete temp;
    }
    headBarang = nullptr;
    jumlahbarang = 0;
}

NodeBarang* CariNodeByID(int id) {
    NodeBarang* curr = headBarang;
    while (curr != nullptr) {
        if (curr->id_barang == id) return curr;
        curr = curr->next;
    }
    return nullptr;
}

NodeBarang* CariNodeByNama(string nama) {
    NodeBarang* curr = headBarang;
    while (curr != nullptr) {
        if (curr->nama_barang == nama) return curr;
        curr = curr->next;
    }
    return nullptr;
}

void pause() {
    cout << "\nTekan ENTER untuk lanjut";
    cin.get();
}

int ValidasiAngka(string teks) {
    int angka;

    while (true) {
        cout << teks;

        if (cin >> angka) {
            cin.ignore();
            return angka;
        } else {
            cout << "Input harus berupa angka!\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

void Header(string judul) {
    cout << "==================================================\n";

    int lebar = 50; 
    int padding = (lebar - judul.length()) / 2;
    if (padding < 0) padding = 0;

    cout << setw(padding + judul.length()) << judul << "\n";

    cout << "==================================================\n";
}

string FormatRupiah(long long angka) {
    string s = to_string(angka);
    int n = s.length();
    string hasil = "";
    int sisaDigit = n % 3;
    for (int i = 0; i < n; i++) {
        if (i != 0 && (i - sisaDigit) % 3 == 0) hasil += ".";
        hasil += s[i];
    }
    return "Rp " + hasil;
}

NodeUser* BacaFileUser(string role) {
    string path = "Admin\\" + role + ".txt";
    ifstream file(path);

    NodeUser* head = nullptr;
    if (!file.is_open()) return head;

    string uname, pw;
    while (file >> uname >> pw) {
        NodeUser* node = BuatNodeUser(uname, pw);
        TambahNodeUserKeAkhir(head, node);
    }
    file.close();
    return head;
}

void SimpanFileUser(string role, NodeUser* head) {
    string path = "Admin\\" + role + ".txt";
    ofstream file(path);

    if (!file.is_open()) {
        cout << "Gagal menyimpan file user!\n";
        return;
    }

    NodeUser* curr = head;
    while (curr != nullptr) {
        file << curr->username << " " << curr->password << "\n";
        curr = curr->next;
    }
    file.close();
}

bool Login(int jumlahUser) {
    string username, password;
    cout << "Username : ";
    cin >> username;
    cout << "Password : ";
    cin >> password;

    for (int i = 0; i < jumlahUser; i++) {
        if (username == user[i].username &&
            password == user[i].password) {
            return true;
        }
    }
    return false;
}

void ReloadUsername(string fungsi) {
    NodeUser* head = BacaFileUser(fungsi);
    int n = MuatUserDariLinkedList(head);
    HapusSemualUser(head);
    if (n == 0) cout << "Tidak ada user terdaftar untuk " << fungsi << "!\n";
}

void ReloadBarang() {
    HapusSemua();
    ifstream file("Barang\\DataBarang.txt");
    if (!file.is_open()) return;

    int    id, harga_beli, harga_jual, stok, terjual;
    string nama, kategori;

    while (file >> id >> nama >> kategori
                >> harga_beli >> harga_jual
                >> stok >> terjual) {
        TambahNodeKeAkhir(BuatNode(id, nama, kategori,
                                   harga_beli, harga_jual,
                                   stok, terjual));
    }
    file.close();
}

void SimpanSemuaBarang() {
    ofstream file("Barang\\DataBarang.txt");
    if (!file.is_open()) { cout << "Gagal membuka file!"; return; }

    NodeBarang* curr = headBarang;
    while (curr != nullptr) {
        file << curr->id_barang        << " "
             << curr->nama_barang      << " "
             << curr->kategori         << " "
             << curr->harga_beli       << " "
             << curr->harga_jual       << " "
             << curr->stok_barang      << " "
             << curr->terjual_sebanyak << "\n";
        curr = curr->next;
    }
    file.close();
}

void TampilHeaderTabel() {
    cout << "=======================================================================================================\n";
    cout << left
         << setw(10) << "ID"
         << setw(25) << "Nama Barang"
         << setw(20) << "Kategori"
         << setw(15) << "Harga Beli"
         << setw(15) << "Harga Jual"
         << setw(10) << "Stok"
         << setw(10) << "Terjual"
         << "\n";
    cout << "-------------------------------------------------------------------------------------------------------\n";
}

void TampilSatuNode(NodeBarang* node) {
    cout << left
         << setw(10) << node->id_barang
         << setw(25) << node->nama_barang
         << setw(20) << node->kategori
         << setw(15) << node->harga_beli
         << setw(15) << node->harga_jual
         << setw(10) << node->stok_barang
         << setw(10) << node->terjual_sebanyak
         << "\n";
}

void TampilkanBarang() {
    ReloadBarang();
    TampilHeaderTabel();
    NodeBarang* curr = headBarang;
    while (curr != nullptr) { TampilSatuNode(curr); curr = curr->next; }
    cout << "=======================================================================================================\n";
}

void Tambah_Barang() {
    Header("TAMBAH BARANG");
    int    idBaru;
    string namaBaru;

    while (true) {
        idBaru = ValidasiAngka("ID Barang : ");
        if (CariNodeByID(idBaru) == nullptr) break;
        cout << "ID sudah digunakan!\n";
    }

    while (true) {
        cout << "Nama Barang : ";
        getline(cin, namaBaru);
        if (CariNodeByNama(namaBaru) == nullptr) break;
        cout << "Nama barang sudah ada!\n";
    }

    string kategori;
    int harga_beli, harga_jual, stok;

    cout << "Kategori : ";    getline(cin, kategori);
    harga_beli = ValidasiAngka("Harga Beli : ");
    harga_jual = ValidasiAngka("Harga Jual : ");
    stok = ValidasiAngka("Stok : ");

    TambahNodeKeAkhir(BuatNode(idBaru, namaBaru, kategori,
                               harga_beli, harga_jual, stok, 0));
    SimpanSemuaBarang();
    cout << "Barang berhasil ditambahkan!";
}

void EditBarang() {
    int id;
    id = ValidasiAngka("Masukkan ID Barang : ");

    NodeBarang* node = CariNodeByID(id);
    if (node == nullptr) { cout << "Barang tidak ditemukan!"; return; }

    cout << "Nama Baru : ";     getline(cin, node->nama_barang);
    cout << "Kategori Baru : "; getline(cin, node->kategori);
    node->harga_beli = ValidasiAngka("Harga Beli : ");
    node->harga_jual = ValidasiAngka("Harga Jual : ");
    node->stok_barang = ValidasiAngka("Stok : ");

    SimpanSemuaBarang();
    cout << "Barang berhasil diupdate!";
}

void HapusBarang() {
    int id;
    id = ValidasiAngka("Masukkan ID Barang : ");

    if (headBarang == nullptr) { cout << "Barang tidak ditemukan!"; return; }

    char yakin;
    cout << "Yakin hapus? (y/t) : ";
    cin >> yakin;
    if (yakin != 'y' && yakin != 'Y') return;

    if (headBarang->id_barang == id) {
        NodeBarang* temp = headBarang;
        headBarang = headBarang->next;
        delete temp;
        jumlahbarang--;
        SimpanSemuaBarang();
        cout << "Barang berhasil dihapus!";
        return;
    }

    NodeBarang* prev = headBarang;
    NodeBarang* curr = headBarang->next;
    while (curr != nullptr) {
        if (curr->id_barang == id) {
            prev->next = curr->next;
            delete curr;
            jumlahbarang--;
            SimpanSemuaBarang();
            cout << "Barang berhasil dihapus!";
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "Barang tidak ditemukan!";
}

void StokSedikit() {
    ReloadBarang();
    TampilHeaderTabel();
    bool ditemukan = false;
    NodeBarang* curr = headBarang;
    while (curr != nullptr) {
        if (curr->stok_barang < 10) { ditemukan = true; TampilSatuNode(curr); }
        curr = curr->next;
    }
    if (!ditemukan) cout << "Tidak ada stok sedikit\n";
}

void bestseller() {
    ReloadBarang();
    NodeBarang* temp[100];
    int n = 0;
    NodeBarang* curr = headBarang;
    while (curr != nullptr) { temp[n++] = curr; curr = curr->next; }

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (temp[j]->terjual_sebanyak < temp[j+1]->terjual_sebanyak)
                swap(temp[j], temp[j+1]);

    TampilHeaderTabel();
    for (int i = 0; i < n; i++) TampilSatuNode(temp[i]);
    cout << "=======================================================================================================\n";
}

void CariBarangByID() {
    int id;
    Header("Cari Barang By ID");
    id = ValidasiAngka("Masukkan ID Barang : ");
    NodeBarang* node = CariNodeByID(id);
    if (node == nullptr) { cout << "Barang tidak ditemukan!"; return; }
    TampilHeaderTabel();
    TampilSatuNode(node);
}

void CariBarangByNama() {
    string nama;
    Header("Cari Barang By Nama");
    cout << "Masukkan Nama Barang : ";
    getline(cin, nama);
    NodeBarang* node = CariNodeByNama(nama);
    if (node == nullptr) { cout << "Barang tidak ditemukan!"; return; }
    TampilHeaderTabel();
    TampilSatuNode(node);
}

void CariBarang() {
    int pilih;
    Header("Cari Barang");
    pilih = ValidasiAngka("1. Cari ID\n2. Cari Nama\nPilih : ");
    switch (pilih) {
        case 1: CariBarangByID();   break;
        case 2: CariBarangByNama(); break;
        default: cout << "\nPilihan salah!\n";
    }
}


void BacaFileHarian() {
    string nama_file = "RekapHarian\\" +
                       to_string(utama.tahun) + "-" +
                       to_string(utama.bulan) + "-" +
                       to_string(utama.tanggal) + ".txt";
    ifstream file(nama_file);
    string line;
    int i = 0;
    while (getline(file, line)) i++;
    utama.no_pelanggan = i;
    file.close();
}

void SimpanRekapHarian() {
    string nama_file = "RekapHarian\\" +
                       to_string(utama.tahun) + "-" +
                       to_string(utama.bulan) + "-" +
                       to_string(utama.tanggal) + ".txt";
    ofstream file(nama_file, ios::app);
    file << tran.id_pelanggan << " "
         << tran.jumlah_item  << " "
         << tran.total_transaksi << "\n";
    file.close();
}


void struk_pembelian() {
    Header("STRUK PEMBELIAN");
    cout << "ID Pelanggan : " << tran.id_pelanggan << "       ";
    cout << "Tanggal : " << utama.tanggal << "-"
         << utama.bulan << "-" << utama.tahun << "\n";
    cout << "=========================================================\n";
    cout << left << setw(3) << "No" << setw(20) << "Produk"
         << setw(10) << "Harga" << setw(10) << "Jumlah"
         << setw(10) << "Total" << "\n";
    cout << "=========================================================\n";

    int grand_total = 0;
    for (int i = 0; i < tran.jumlah_item; i++) {
        NodeBarang* node = CariNodeByID(tran.detail[i].id_barang);
        if (node == nullptr) continue;
        int total = node->harga_jual * tran.detail[i].jumlah;
        grand_total += total;
        cout << left << setw(3) << i+1 << setw(20) << node->nama_barang
             << setw(10) << node->harga_jual << setw(10) << tran.detail[i].jumlah
             << setw(10) << total << "\n";
    }
    cout << "=========================================================\n";
    cout << "TOTAL : " << grand_total << "\n";
    cout << "=========================================================\n";
}

void kasir_penjualan() {
    Header("KASIR TOKO SEMBAKO MAJU JAYA");
    tran.id_pelanggan = utama.no_pelanggan + 1;
    tran.jumlah_item = ValidasiAngka("Jumlah Item : ");

    int grand_total = 0;
    for (int i = 0; i < tran.jumlah_item; i++) {
        int id, jumlah;
        cout << "Barang ke-" << i+1 << "\n";
        cout << "ID Barang : ";
        cin >> id;

        NodeBarang* node = CariNodeByID(id);
        if (node == nullptr) { cout << "Barang tidak ditemukan!"; return; }

        jumlah = ValidasiAngka("Jumlah : ");
        if (jumlah > node->stok_barang) { cout << "Stok tidak cukup!"; return; }

        node->stok_barang      -= jumlah;
        node->terjual_sebanyak += jumlah;
        tran.detail[i].id_barang = id;
        tran.detail[i].jumlah    = jumlah;
        grand_total += node->harga_jual * jumlah;
    }

    tran.total_transaksi = grand_total;
    SimpanSemuaBarang();
    struk_pembelian();
    SimpanRekapHarian();
    cout << "Transaksi berhasil!";
}

void menuKasir() {
    int pilih;
    do {
        Header("KASIR TOKO SEMBAKO MAJU JAYA");

        cout << "1. Transaksi Baru\n";
        cout << "2. Cari Barang\n";
        cout << "3. Kembali\n";
        cout << "--------------------------------------------------\n";

        pilih = ValidasiAngka("Pilih : ");
        
        switch (pilih) {
            case 1: kasir_penjualan(); break;
            case 2: CariBarang();      break;
            case 3: cout << "Kembali..."; break;
            default: cout << "\nPilihan salah!\n";
        }
        if (pilih != 3) pause();
        system("cls");
    } while (pilih != 3);
}

void TampilkanUser(NodeUser* head, string role) {
    cout << "----------------------------------------\n";
    cout << left << setw(5) << "No" << setw(20) << "Username" << "Password\n";
    cout << "----------------------------------------\n";
    int no = 1;
    NodeUser* curr = head;
    if (curr == nullptr) cout << "(Tidak ada user terdaftar)\n";
    while (curr != nullptr) {
        cout << left << setw(5) << no++
             << setw(20) << curr->username
             << curr->password << "\n";
        curr = curr->next;
    }
    cout << "----------------------------------------\n";
}

void TambahUser(string role) {
    Header("TAMBAH USER - " + role);
    NodeUser* head = BacaFileUser(role);
    TampilkanUser(head, role);

    string uname, pw;

    while (true) {
        cout << "Username baru : ";
        getline(cin, uname);
        bool duplikat = false;
        NodeUser* curr = head;
        while (curr != nullptr) {
            if (curr->username == uname) { duplikat = true; break; }
            curr = curr->next;
        }
        if (!duplikat) break;
        cout << "Username sudah digunakan!\n";
    }

    cout << "Password baru : ";
    getline(cin, pw);

    TambahNodeUserKeAkhir(head, BuatNodeUser(uname, pw));
    SimpanFileUser(role, head);
    HapusSemualUser(head);
    cout << "User berhasil ditambahkan!";
}

void HapusUser(string role) {
    Header("HAPUS USER - " + role);
    NodeUser* head = BacaFileUser(role);

    if (head == nullptr) {
        cout << "Tidak ada user terdaftar untuk " << role << "!\n";
        return;
    }

    TampilkanUser(head, role);

    string uname;
    cout << "Username yang dihapus : ";
    getline(cin, uname);

    if (head->username == uname) {
        NodeUser* temp = head;
        head = head->next;
        delete temp;
        SimpanFileUser(role, head);
        HapusSemualUser(head);
        cout << "User berhasil dihapus!";
        return;
    }

    NodeUser* prev = head;
    NodeUser* curr = head->next;
    while (curr != nullptr) {
        if (curr->username == uname) {
            prev->next = curr->next;
            delete curr;
            SimpanFileUser(role, head);
            HapusSemualUser(head);
            cout << "User berhasil dihapus!";
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    cout << "User tidak ditemukan!";
    HapusSemualUser(head);
}

void LihatUser(string role) {
    Header("DAFTAR USER - " + role);
    NodeUser* head = BacaFileUser(role);
    TampilkanUser(head, role);
    HapusSemualUser(head);
}

void menuKelolaUser(string role) {
    int pilih;
    do {
        Header("KELOLA USER - " + role);
        cout << "1. Lihat User\n";
        cout << "2. Tambah User\n";
        cout << "3. Hapus User\n";
        cout << "4. Kembali\n";
        cout << "--------------------------------------------------\n";
        pilih = ValidasiAngka("Pilih : ");

        switch (pilih) {
            case 1: LihatUser(role);  break;
            case 2: TambahUser(role); break;
            case 3: HapusUser(role);  break;
            case 4: cout << "Kembali..."; break;
            default: cout << "\nPilihan salah!\n";
        }
        if (pilih != 4) pause();
        system("cls");
    } while (pilih != 4);
}

void menuAdmin() {
    int pilih;
    do {
        Header("MANAJEMEN USER - ADMIN");
        cout << "1. User Kasir\n";
        cout << "2. User Gudang\n";
        cout << "3. User Finansial\n";
        cout << "4. Kembali\n";
        cout << "--------------------------------------------------\n";
        pilih = ValidasiAngka("Pilih : ");

        switch (pilih) {
            case 1: menuKelolaUser("Kasir");    break;
            case 2: menuKelolaUser("Gudang");   break;
            case 3: menuKelolaUser("Finansial"); break;
            case 4: cout << "Kembali..."; break;
            default: cout << "\nPilihan salah!\n";
        }
        if (pilih != 4) pause();
        system("cls");
    } while (pilih != 4);
}

void menuGudang() {
    int pilih;
    do {
        Header("GUDANG TOKO SEMBAKO MAJU JAYA");
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Barang\n";
        cout << "3. Edit Barang\n";
        cout << "4. Stok Menipis\n";
        cout << "5. Barang Terlaris\n";
        cout << "6. Cari Barang\n";
        cout << "7. Hapus Barang\n";
        cout << "8. Kembali\n";
        cout << "--------------------------------------------------\n";
        pilih = ValidasiAngka("Pilih : ");

        switch (pilih) {
            case 1: Tambah_Barang();   break;
            case 2: TampilkanBarang(); break;
            case 3: EditBarang();      break;
            case 4: StokSedikit();     break;
            case 5: bestseller();      break;
            case 6: CariBarang();      break;
            case 7: HapusBarang();     break;
            case 8: cout << "Kembali..."; break;
            default: cout << "\n salah!\n";
        }
        if (pilih != 8) pause();
        system("cls");
    } while (pilih != 8);
}

struct NodeRekap {
    int id_pelanggan;
    int jumlah_item;
    int total_transaksi;
    NodeRekap* next;
};

NodeRekap* BuatNodeRekap(int idPel, int jmlItem, int total) {
    NodeRekap* node = new NodeRekap();
    node->id_pelanggan    = idPel;
    node->jumlah_item     = jmlItem;
    node->total_transaksi = total;
    node->next            = nullptr;
    return node;
}

void TambahNodeRekap(NodeRekap*& head, NodeRekap* node) {
    if (head == nullptr) { head = node; return; }
    NodeRekap* curr = head;
    while (curr->next != nullptr) curr = curr->next;
    curr->next = node;
}

void HapusSemuaRekap(NodeRekap*& head) {
    NodeRekap* curr = head;
    while (curr != nullptr) {
        NodeRekap* temp = curr;
        curr = curr->next;
        delete temp;
    }
    head = nullptr;
}

NodeRekap* BacaFileRekapHarian(int tgl, int bln, int thn) {
    string nama_file = "RekapHarian\\" +
                       to_string(thn) + "-" +
                       to_string(bln) + "-" +
                       to_string(tgl) + ".txt";
    ifstream file(nama_file);
    NodeRekap* head = nullptr;

    if (!file.is_open()) return head;

    int idPel, jmlItem, total;
    while (file >> idPel >> jmlItem >> total) {
        TambahNodeRekap(head, BuatNodeRekap(idPel, jmlItem, total));
    }
    file.close();
    return head;
}

long long HitungPendapatanDariRekap(NodeRekap* head) {
    long long total = 0;
    NodeRekap* curr = head;
    while (curr != nullptr) {
        total += curr->total_transaksi;
        curr = curr->next;
    }
    return total;
}

int HitungJumlahTransaksiDariRekap(NodeRekap* head) {
    int n = 0;
    NodeRekap* curr = head;
    while (curr != nullptr) { n++; curr = curr->next; }
    return n;
}

long long HitungModalBarang() {
    ReloadBarang();
    long long modal = 0;
    NodeBarang* curr = headBarang;
    while (curr != nullptr) {
        modal += (long long)curr->harga_beli * curr->terjual_sebanyak;
        curr = curr->next;
    }
    return modal;
}

long long HitungPendapatanBarang() {
    ReloadBarang();
    long long pendapatan = 0;
    NodeBarang* curr = headBarang;
    while (curr != nullptr) {
        pendapatan += (long long)curr->harga_jual * curr->terjual_sebanyak;
        curr = curr->next;
    }
    return pendapatan;
}

void LaporanHarian() {
    Header("LAPORAN KEUANGAN HARIAN");

    int tgl, bln, thn;
    tgl = ValidasiAngka("Tanggal : ");
    bln = ValidasiAngka("Bulan   : ");
    thn = ValidasiAngka("Tahun   : ");

    NodeRekap* head = BacaFileRekapHarian(tgl, bln, thn);

    if (head == nullptr) {
        cout << "\nTidak ada data transaksi pada tanggal "
             << tgl << "-" << bln << "-" << thn << ".\n";
        return;
    }

    int jumlahTrx  = HitungJumlahTransaksiDariRekap(head);
    long long pendapatan = HitungPendapatanDariRekap(head);

    cout << "\nTanggal  : " << tgl << "-" << bln << "-" << thn << "\n";
    cout << "--------------------------------------------------------\n";
    cout << left << setw(8) << "ID Pel" << setw(12) << "Jml Item"
         << setw(20) << "Total Transaksi" << "\n";
    cout << "--------------------------------------------------------\n";

    NodeRekap* curr = head;
    while (curr != nullptr) {
        cout << left << setw(8)  << curr->id_pelanggan
                     << setw(12) << curr->jumlah_item
                     << setw(20) << FormatRupiah(curr->total_transaksi)
                     << "\n";
        curr = curr->next;
    }

    cout << "--------------------------------------------------------\n";
    cout << "Jumlah Transaksi : " << jumlahTrx << "\n";
    cout << "Total Pendapatan : " << FormatRupiah(pendapatan) << "\n";
    cout << "--------------------------------------------------------\n";
    cout << "* Untuk laporan keuntungan detail, lihat Laporan Bulanan\n";
    cout << "  (keuntungan dihitung berdasarkan kumulatif data barang)\n";

    HapusSemuaRekap(head);
}


void LaporanBulanan() {
    Header("LAPORAN KEUANGAN BULANAN");

    int bln, thn;
    bln = ValidasiAngka("Bulan : ");
    thn = ValidasiAngka("Tahun : ");

    long long totalPendapatan = 0;
    int totalTrx = 0;
    int hariAda  = 0;

    struct RekapPerHari {
        int tanggal;
        int jumlahTrx;
        long long pendapatan;
    } rekapHari[31];

    for (int tgl = 1; tgl <= 31; tgl++) {
        NodeRekap* head = BacaFileRekapHarian(tgl, bln, thn);
        if (head == nullptr) continue;

        int trx            = HitungJumlahTransaksiDariRekap(head);
        long long pend     = HitungPendapatanDariRekap(head);

        rekapHari[hariAda].tanggal    = tgl;
        rekapHari[hariAda].jumlahTrx  = trx;
        rekapHari[hariAda].pendapatan = pend;
        hariAda++;

        totalPendapatan += pend;
        totalTrx        += trx;
        HapusSemuaRekap(head);
    }

    if (hariAda == 0) {
        cout << "\nTidak ada data transaksi pada bulan "
             << bln << "-" << thn << ".\n";
        return;
    }

    ReloadBarang();
    long long totalModal      = 0;
    long long totalPendBrg    = 0;
    NodeBarang* currBrg = headBarang;
    while (currBrg != nullptr) {
        totalModal   += (long long)currBrg->harga_beli * currBrg->terjual_sebanyak;
        totalPendBrg += (long long)currBrg->harga_jual * currBrg->terjual_sebanyak;
        currBrg = currBrg->next;
    }
    long long keuntunganKotor = totalPendBrg - totalModal;

    double marginPersen = 0;
    if (totalPendBrg > 0)
        marginPersen = (double)keuntunganKotor / totalPendBrg * 100.0;

    long long estimasiKeuntunganBulan = (long long)(totalPendapatan * marginPersen / 100.0);

    cout << "\nBulan : " << bln << " | Tahun : " << thn << "\n";
    cout << "------------------------------------------------------\n";
    cout << left << setw(10) << "Tanggal"
                 << setw(15) << "Jml Transaksi"
                 << setw(20) << "Pendapatan" << "\n";
    cout << "------------------------------------------------------\n";

    for (int i = 0; i < hariAda; i++) {
        cout << left << setw(10) << rekapHari[i].tanggal
                     << setw(15) << rekapHari[i].jumlahTrx
                     << setw(20) << FormatRupiah(rekapHari[i].pendapatan)
                     << "\n";
    }

    cout << "------------------------------------------------------\n";
    cout << "Total Hari Aktif   : " << hariAda << " hari\n";
    cout << "Total Transaksi    : " << totalTrx << "\n";
    cout << "Total Pendapatan   : " << FormatRupiah(totalPendapatan) << "\n";
    cout << "======================================================\n";
    cout << "RINGKASAN KEUNTUNGAN (berdasarkan data barang)\n";
    cout << "------------------------------------------------------\n";
    cout << "Total Pendapatan (seluruh stok terjual) : " << FormatRupiah(totalPendBrg) << "\n";
    cout << "Total Modal      (seluruh stok terjual) : " << FormatRupiah(totalModal) << "\n";
    cout << "Keuntungan Kotor                        : " << FormatRupiah(keuntunganKotor) << "\n";
    cout << "Margin Rata-rata                        : " << fixed << setprecision(2) << marginPersen << " %\n";
    cout << "------------------------------------------------------\n";
    cout << "Estimasi Keuntungan Bulan " << bln << "/" << thn
         << " : " << FormatRupiah(estimasiKeuntunganBulan) << "\n";
    cout << "======================================================\n";
    cout << "* Estimasi keuntungan dihitung dengan margin rata-rata\n";
    cout << "  dari seluruh data barang yang pernah terjual.\n";
}

void KeuntunganPerBarang() {
    Header("KEUNTUNGAN PER BARANG");
    ReloadBarang();

    cout << "=========================================================================================\n";
    cout << left
         << setw(25) << "Nama Barang"
         << setw(12) << "Terjual"
         << setw(16) << "Modal"
         << setw(16) << "Pendapatan"
         << setw(16) << "Keuntungan"
         << setw(10) << "Margin"
         << "\n";
    cout << "-----------------------------------------------------------------------------------------\n";

    long long grandModal      = 0;
    long long grandPendapatan = 0;
    long long grandKeuntungan = 0;

    NodeBarang* curr = headBarang;
    if (curr == nullptr) { cout << "(Tidak ada data barang)\n"; return; }

    while (curr != nullptr) {
        long long modal      = (long long)curr->harga_beli * curr->terjual_sebanyak;
        long long pendapatan = (long long)curr->harga_jual * curr->terjual_sebanyak;
        long long keuntungan = pendapatan - modal;
        double margin = 0;
        if (pendapatan > 0) margin = (double)keuntungan / pendapatan * 100.0;

        grandModal      += modal;
        grandPendapatan += pendapatan;
        grandKeuntungan += keuntungan;

        cout << left
             << setw(25) << curr->nama_barang
             << setw(12) << curr->terjual_sebanyak
             << setw(16) << FormatRupiah(modal)
             << setw(16) << FormatRupiah(pendapatan)
             << setw(16) << FormatRupiah(keuntungan)
             << setw(8) << (to_string((int)margin) + " %") << "\n";

        curr = curr->next;
    }

    cout << "=========================================================================================\n";
    cout << left
         << setw(37) << "TOTAL"
         << setw(16) << FormatRupiah(grandModal)
         << setw(16) << FormatRupiah(grandPendapatan)
         << setw(16) << FormatRupiah(grandKeuntungan)
         << "\n";
    cout << "=========================================================================================\n";
}

void RingkasanKeuangan() {
    Header("RINGKASAN KEUANGAN TOKO");

    ReloadBarang();
    long long totalModal      = 0;
    long long totalPendapatan = 0;
    int totalTerjual          = 0;
    int jumlahBrg             = 0;

    NodeBarang* curr = headBarang;
    while (curr != nullptr) {
        totalModal      += (long long)curr->harga_beli * curr->terjual_sebanyak;
        totalPendapatan += (long long)curr->harga_jual * curr->terjual_sebanyak;
        totalTerjual    += curr->terjual_sebanyak;
        jumlahBrg++;
        curr = curr->next;
    }
    long long keuntungan = totalPendapatan - totalModal;
    double margin = 0;
    if (totalPendapatan > 0)
        margin = (double)keuntungan / totalPendapatan * 100.0;

    cout << "\n";
    cout << "  Jumlah Jenis Barang  : " << jumlahBrg << " item\n";
    cout << "  Total Unit Terjual   : " << totalTerjual << " unit\n";
    cout << "  ------------------------------------------\n";
    cout << "  Total Modal Keluar   : " << FormatRupiah(totalModal) << "\n";
    cout << "  Total Pendapatan     : " << FormatRupiah(totalPendapatan) << "\n";
    cout << "  ------------------------------------------\n";
    cout << "  KEUNTUNGAN BERSIH    : " << FormatRupiah(keuntungan) << "\n";
    cout << "  Margin Keuntungan    : " << fixed << setprecision(2) << margin << " %\n";
    cout << "  ------------------------------------------\n";
    cout << "\n";
    cout << "  (Data dihitung dari seluruh riwayat penjualan)\n";
}

struct NodeFile {
    string nama_file;   
    int tahun, bulan, tanggal;
    int jumlah_transaksi;
    long long total_pendapatan;
    NodeFile* next;
};

NodeFile* BuatNodeFile(string nama, int thn, int bln, int tgl,
                       int jmlTrx, long long pend) {
    NodeFile* node = new NodeFile();
    node->nama_file        = nama;
    node->tahun            = thn;
    node->bulan            = bln;
    node->tanggal          = tgl;
    node->jumlah_transaksi = jmlTrx;
    node->total_pendapatan = pend;
    node->next             = nullptr;
    return node;
}

void TambahNodeFile(NodeFile*& head, NodeFile* node) {
    if (head == nullptr) { head = node; return; }
    NodeFile* curr = head;
    while (curr->next != nullptr) curr = curr->next;
    curr->next = node;
}

void HapusSemuaFile(NodeFile*& head) {
    NodeFile* curr = head;
    while (curr != nullptr) {
        NodeFile* temp = curr;
        curr = curr->next;
        delete temp;
    }
    head = nullptr;
}

NodeFile* ScanFolderRekap() {
    NodeFile* head = nullptr;
    int jumlah = 0;

    for (int thn = 2020; thn <= 2030; thn++) {
        for (int bln = 1; bln <= 12; bln++) {
            for (int tgl = 1; tgl <= 31; tgl++) {
                string nama_file = "RekapHarian\\" +
                                   to_string(thn) + "-" +
                                   to_string(bln) + "-" +
                                   to_string(tgl) + ".txt";
                ifstream f(nama_file);
                if (!f.is_open()) continue;

                int jmlTrx = 0;
                long long totalPend = 0;
                int idP, jmlI, totT;
                while (f >> idP >> jmlI >> totT) {
                    jmlTrx++;
                    totalPend += totT;
                }
                f.close();

                string tampil = to_string(tgl) + "-" +
                                to_string(bln) + "-" +
                                to_string(thn) + ".txt";
                TambahNodeFile(head, BuatNodeFile(tampil, thn, bln, tgl,
                                                  jmlTrx, totalPend));
                jumlah++;
            }
        }
    }
    return head;
}

void DaftarFileRekap() {
    Header("DAFTAR FILE REKAP HARIAN");
    cout << "Memindai folder RekapHarian...\n\n";

    NodeFile* head = ScanFolderRekap();

    if (head == nullptr) {
        cout << "Tidak ada file rekap ditemukan di folder RekapHarian.\n";
        return;
    }

    int totalFile = 0;
    NodeFile* tmp = head;
    while (tmp != nullptr) { totalFile++; tmp = tmp->next; }

    cout << "Ditemukan " << totalFile << " file rekap:\n\n";
    cout << "--------------------------------------------------------------------\n";
    cout << left
         << setw(5)  << "No"
         << setw(22) << "Nama File"
         << setw(18) << "Jml Transaksi"
         << setw(25) << "Total Pendapatan"
         << "\n";
    cout << "--------------------------------------------------------------------\n";

    int no = 1;
    long long grandTotal = 0;
    int grandTrx = 0;
    NodeFile* curr = head;
    while (curr != nullptr) {
        cout << left
             << setw(5)  << no++
             << setw(22) << curr->nama_file
             << setw(18) << curr->jumlah_transaksi
             << setw(25) << FormatRupiah(curr->total_pendapatan)
             << "\n";
        grandTotal += curr->total_pendapatan;
        grandTrx   += curr->jumlah_transaksi;
        curr = curr->next;
    }

    cout << "====================================================================\n";
    cout << left
         << setw(5)  << ""
         << setw(22) << "TOTAL"
         << setw(18) << grandTrx
         << setw(25) << FormatRupiah(grandTotal)
         << "\n";
    cout << "====================================================================\n";

    HapusSemuaFile(head);
}


void menuFinansial() {
    int pilih;
    do {
        Header("FINANSIAL - TOKO SEMBAKO MAJU JAYA");
        cout << "1. Ringkasan Keuangan\n";
        cout << "2. Laporan Harian\n";
        cout << "3. Laporan Bulanan\n";
        cout << "4. Keuntungan Per Barang\n";
        cout << "5. Daftar File Rekap Harian\n";
        cout << "6. Kembali\n";
        cout << "--------------------------------------------------\n";
        pilih = ValidasiAngka("Pilih : ");

        switch (pilih) {
            case 1: RingkasanKeuangan();   break;
            case 2: LaporanHarian();       break;
            case 3: LaporanBulanan();      break;
            case 4: KeuntunganPerBarang(); break;
            case 5: DaftarFileRekap();     break;
            case 6: cout << "Kembali...";  break;
            default: cout << "\nPilihan salah!\n";
        }
        if (pilih != 6) pause();
        system("cls");
    } while (pilih != 6);
}


void login_kasir() {
    NodeUser* head = BacaFileUser("Kasir");
    int n = MuatUserDariLinkedList(head);
    HapusSemualUser(head);

    if (Login(n)) {
        cout << "==============================\nLogin berhasil!\n==============================\n";
        utama.tanggal = ValidasiAngka("Tanggal : ");
        utama.bulan = ValidasiAngka("Bulan : ");
        utama.tahun = ValidasiAngka("Tahun : ");
        BacaFileHarian();
        menuKasir();
    } else {
        cout << "\nUsername atau password salah\n";
    }
}

void login_Finansial() {
    NodeUser* head = BacaFileUser("Finansial");
    int n = MuatUserDariLinkedList(head);
    HapusSemualUser(head);

    if (Login(n)) {
        cout << "==============================\nLogin berhasil!\n==============================\n";
        menuFinansial();
    } else {
        cout << "\nUsername atau password salah\n";
    }
}

void login_Admin() {
    NodeUser* head = BacaFileUser("Admin");
    int n = MuatUserDariLinkedList(head);
    HapusSemualUser(head);

    if (Login(n)) {
        cout << "==============================\nLogin berhasil!\n==============================\n";
        menuAdmin();
    } else {
        cout << "\nUsername atau password salah\n";
    }
}

void login_gudang() {
    NodeUser* head = BacaFileUser("Gudang");
    int n = MuatUserDariLinkedList(head);
    HapusSemualUser(head);

    if (Login(n)) {
        cout << "==============================\nLogin berhasil!\n==============================\n";
        menuGudang();
    } else {
        cout << "\nUsername atau password salah\n";
    }
}


int main() {
    ReloadBarang();

    int pilih;
    do {
        Header("TOKO SEMBAKO MAJU JAYA");
        cout << "1. Kasir\n";
        cout << "2. Gudang\n";
        cout << "3. Finansial\n";
        cout << "4. Admin\n";
        cout << "5. Keluar\n";
        cout << "--------------------------------------------------\n";
        pilih = ValidasiAngka("Pilih : ");

        switch (pilih) {
            case 1: login_kasir();     break;
            case 2: login_gudang();    break;
            case 3: login_Finansial(); break;
            case 4: login_Admin();     break;
            case 5: cout << "Program selesai"; break;
            default: cout << "\nPilihan salah!\n";
        }
    } while (pilih != 5);

    HapusSemua();
    return 0;
}
