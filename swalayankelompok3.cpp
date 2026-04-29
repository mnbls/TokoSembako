#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// struct
struct DataBarang{
	int id_barang;
	string nama_barang;
	int harga_barang;
	int stok_barang;
	}data[100];

void init_barang() {
    data[0] = {1, "Beras", 12000, 100};
    data[1] = {2, "Gula", 14000, 80};
    data[2] = {3, "Minyak", 15000, 60};
    data[3] = {4, "Telur", 25000, 50};
    data[4] = {5, "MieInstan", 3000, 200};
    data[5] = {6, "Susu", 10000, 70};
    data[6] = {7, "Kopi", 8000, 90};
    data[7] = {8, "Teh", 5000, 85};
    data[8] = {9, "Sabun", 4000, 120};
    data[9] = {10, "Shampo", 12000, 75};
}
	

struct DetailBarang {
    int no_urut;
    int id_barang;
    int jumlah;
    int total_harga;
};

struct Transaksi {
    int id_pelanggan;
    int jumlah_item;
    DetailBarang barang[100];
    int total_transaksi;
	}tran;

//ini untuk pengunaan
struct Utama{
	int kesempatan = 3;
	int tanggal;
	int bulan;
	int tahun;
	int menuutamakasir;
	int no_pelanggan = 0;
	}utama;


void menuKasir(); 

void header_utama(){
	cout << "\n==============================\n";
    cout << "   TOKO SEMBAKO MAJU JAYA\n";
    cout << "==============================\n";
}

void header_kasir(){
	cout << "\n==============================\n";
    cout << "   KASIR TOKO SEMBAKO MAJU JAYA\n";
    cout << "==============================\n";
}

void header_gudang(){
	cout << "\n==============================\n";
    cout << "   GUDANG TOKO SEMBAKO MAJU JAYA\n";
    cout << "==============================\n";
}

void header_admin(){
	cout << "\n==============================\n";
    cout << "   ADMIN TOKO SEMBAKO MAJU JAYA\n";
    cout << "==============================\n";
}

void header_finansial(){
	cout << "\n==============================\n";
    cout << "   FINANSIAL TOKO SEMBAKO MAJU JAYA\n";
    cout << "==============================\n";
}

// ================= MENU KASIR =================
void SimpanRekapHarian(){
	int grand_total = 0;

    for (int i = 0; i < tran.jumlah_item; i++) {
        int idx = tran.barang[i].id_barang - 1;

        int harga = data[idx].harga_barang;
        int total = harga * tran.barang[i].jumlah;

        grand_total += total;
    }


	string nama_file = 	"RekapHarian\\" +
						to_string(utama.tahun) + "-" +
						to_string(utama.bulan) + "-" +
						to_string(utama.tanggal) + ".txt";

    ofstream file(nama_file, ios::app);
    if (!file.is_open()) {
        cout << "Gagal membuat file!\n";
        return;
    }
    file << left << setw(5) << tran.id_pelanggan
         << setw(15) << "Admin"
         << setw(10) << tran.jumlah_item
         << setw(10) << grand_total<< endl;

    file.close();

    cout << "\nRekap berhasil disimpan ke file: " << nama_file << endl;

	}
void bikinfilerekap() {
    string nama_file = 	"RekapHarian\\" +
						to_string(utama.tahun) + "-" +
						to_string(utama.bulan) + "-" +
						to_string(utama.tanggal) + ".txt";

    ofstream file(nama_file, ios::app);

    if (!file.is_open()) {
        cout << "Gagal membuat file!\n";
        return;
    }
    file << left << setw(5) << "ID"
         << setw(15) << "Admin"
         << setw(10) << "jumlah item"
         << setw(10) << "total" << endl;

    file.close();
    
}
    
void simpan_struk_file() {
    // buat nama file otomatis
    
    string nama_file = 	"StructHarian\\" +
						to_string(utama.tahun) + "-" +
						to_string(utama.bulan) + "-" +
						to_string(utama.tanggal) + ".txt";

    ofstream file(nama_file, ios::app);

    if (!file.is_open()) {
        cout << "Gagal membuat file!\n";
        return;
    }

    file << "==============================================\n";
    file << "              STRUK PEMBELIAN\n";
    file << "==============================================\n";
    file << "ID Pelanggan : " << tran.id_pelanggan << "\n";
    file << "Tanggal      : " << utama.tanggal << "-" << utama.bulan << "-" << utama.tahun << "\n";
    file << "Nama Kasir   : admin\n";
    file << "Jumlah Item  : " << tran.jumlah_item << "\n";
    file << "----------------------------------------------\n";

    file << left << setw(5) << "No"
         << setw(15) << "Nama"
         << setw(10) << "Harga"
         << setw(10) << "Jumlah"
         << setw(10) << "Total" << endl;

    file << "----------------------------------------------\n";

    int grand_total = 0;

    for (int i = 0; i < tran.jumlah_item; i++) {
        int idx = tran.barang[i].id_barang - 1;

        int harga = data[idx].harga_barang;
        int total = harga * tran.barang[i].jumlah;

        grand_total += total;

        file << left << setw(5) << tran.barang[i].no_urut
             << setw(15) << data[idx].nama_barang
             << setw(10) << harga
             << setw(10) << tran.barang[i].jumlah
             << setw(10) << total << endl;
    }

    file << "----------------------------------------------\n";
    file << right << setw(40) << "TOTAL : " << grand_total << endl;
    file << "==============================================\n";

    file.close();

    cout << "\nStruk berhasil disimpan ke file: " << nama_file << endl;
}


void struk_pembelian() {
    header_kasir();

    cout << "==============================================\n";
    cout << "              STRUK PEMBELIAN\n";
    cout << "==============================================\n";
    cout << "ID Pelanggan : " << tran.id_pelanggan << "\n";
    cout << "Tanggal      : " << utama.tanggal << "-" << utama.bulan << "-" << utama.tahun << "\n";
    cout << "Nama Kasir   : admin\n";
    cout << "Jumlah Item  : " << tran.jumlah_item << "\n";
    cout << "----------------------------------------------\n";

    cout << left << setw(5) << "No"
         << setw(15) << "Nama"
         << setw(10) << "Harga"
         << setw(10) << "Jumlah"
         << setw(10) << "Total" << endl;

    cout << "----------------------------------------------\n";
    int grand_total = 0;
    for (int i = 0; i < tran.jumlah_item; i++) {
        int idx = tran.barang[i].id_barang - 1; 
        int harga = data[idx].harga_barang;
        int total = harga * tran.barang[i].jumlah;
        grand_total += total;
        cout << left << setw(5) << tran.barang[i].no_urut
             << setw(15) << data[idx].nama_barang
             << setw(10) << harga
             << setw(10) << tran.barang[i].jumlah
             << setw(10) << total << endl;
    }

    cout << "----------------------------------------------\n";
    cout << right << setw(40) << "TOTAL : " << grand_total << endl;
    cout << "==============================================\n";
    
}

void kasir_penjualan(){
	header_kasir();
	utama.no_pelanggan++;
	tran.id_pelanggan=utama.no_pelanggan;
	cout << "Id Pelanggan : " << tran.id_pelanggan;
	cout << "Jumlah Item  : ";
	cin >> tran.jumlah_item ;
	for (int i = 0; i < tran.jumlah_item; i++) {
        tran.barang[i].no_urut = i+1;
        cout << "Barang ke-" << tran.barang[i].no_urut << endl;
        cout << "Kode Barang : ";
        cin >> tran.barang[i].id_barang;
        cout << "Jumlah barang : ";
        cin >> tran.barang[i].jumlah;
		}
	struk_pembelian();
	simpan_struk_file();
	SimpanRekapHarian();
	}
	
void seting_jumlah_pelanggan(){
	cout << "Masukan jumlah pelanggan yang telah di layani di hari ini : ";
	cin >> utama.no_pelanggan;
	menuKasir();
	}
	
	
void menuKasir() {
    do {
        header_kasir();
		cout << "Adna telah melayani pelanggan sejumlah " << utama.no_pelanggan << "\n";
		cout << "1. Transaksi Baru\n";
		cout << "2. Seting jumlah pelanggan\n";
		cout << "3. Keluar\n";
		cout << "==============================\n";
		cout << "Pilih menu: ";
		cin >> utama.menuutamakasir;

        switch(utama.menuutamakasir) {
            case 1:
				kasir_penjualan();
                break;
            case 2:
                seting_jumlah_pelanggan();
                break;
            case 3:
                cout << "Kembali ke menu utama...\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while(utama.menuutamakasir != 3);
}
void login_kasir(){
	string username_kasir, password_kasir;
	header_kasir();
    cout << "Masukan Username : ";
    cin >> username_kasir;
    cout << "Masukan Password : ";
    cin >> password_kasir;
    cout << "====================================\n";
	
	if (username_kasir=="admin" && password_kasir == "admin123"){
		cout << "Selamat anda berhasil login" << endl;
		cout << "\n====================================\n";
		cout << "   KASIR TOKO SEMBAKO MAJU JAYA\n";
		cout << "====================================\n";
		cout << "Masukan Tanggal : ";
		cin >> utama.tanggal;
		cout << "Masukan Bulan : ";
		cin >> utama.bulan;
		cout << "Masukan Tahun : ";
		cin >> utama.tahun;
		cout << "====================================\n";
		bikinfilerekap();
		menuKasir();
		
		}else{
			cout << "Login Gagal Username atau Password salah" << endl;
			utama.kesempatan--;
			
			if (utama.kesempatan == 0) {
				cout << "Selamat tinggal";
				}else {
					}
			}
	}
	
// ================= MENU GUDANG =================
void menuGudang() {
    int pilih;
    do {
        header_gudang();
        cout << "1. Data Barang\n";
        cout << "2. Supplier\n";
        cout << "3. Supply Barang\n";
        cout << "4. Cek Stok\n";
        cout << "5. Laporan\n";
        cout << "6. Back\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch(pilih) {
            case 1: cout << "-> Data Barang\n"; break;
            case 2: cout << "-> Supplier\n"; break;
            case 3: cout << "-> Supply Barang\n"; break;
            case 4: cout << "-> Cek Stok\n"; break;
            case 5: cout << "-> Laporan\n"; break;
            case 6: cout << "Kembali...\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while(pilih != 6);
}

// ================= MENU FINANSIAL =================
void menuFinansial() {
    int pilih;
    do {
        header_finansial();
        cout << "1. Stok Pelanggan\n";
        cout << "2. Penjualan Harian\n";
        cout << "3. Bulanan\n";
        cout << "4. Total Profit\n";
        cout << "5. Back\n";
        cout << "==============================\n";
        cout << "Pilih: ";
        cin >> pilih;
        cout << "==============================\n";

        switch(pilih) {
            case 1: cout << "-> Stok Pelanggan\n"; break;
            case 2: cout << "-> Penjualan Harian\n"; break;
            case 3: cout << "-> Bulanan\n"; break;
            case 4: cout << "-> Total Profit\n"; break;
            case 5: cout << "Kembali...\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while(pilih != 5);
}

// ================= MENU ADMIN =================
void menuAdmin() {
    int pilih;
    do {
        header_admin();
        cout << "1. Cek Username\n";
        cout << "2. Edit Username\n";
        cout << "3. Back\n";
        cout << "==============================\n";
        cout << "Pilih: ";
        cin >> pilih;
		cout << "==============================\n";
		
        if (pilih == 1) {
            int sub;
            cout << "\n-- Cek Username --\n";
            cout << "1. Kasir\n2. Gudang\n3. Admin\nPilih: ";
            cin >> sub;

            switch(sub) {
                case 1: cout << "Username Kasir\n"; break;
                case 2: cout << "Username Gudang\n"; break;
                case 3: cout << "Username Admin\n"; break;
                default: cout << "Salah!\n";
            }

        } else if (pilih == 2) {
            int sub;
            cout << "\n-- Edit Username --\n";
            cout << "1. Kasir\n2. Gudang\n3. Admin\nPilih: ";
            cin >> sub;

            switch(sub) {
                case 1: cout << "Edit Username Kasir\n"; break;
                case 2: cout << "Edit Username Gudang\n"; break;
                case 3: cout << "Edit Username Admin\n"; break;
                default: cout << "Salah!\n";
            }
        }

    } while(pilih != 3);
}

// ================= MENU UTAMA =================
int main() {
	init_barang();
    int pilih;

    do {
        header_utama();
        cout << "1. Kasir\n";
        cout << "2. Gudang\n";
        cout << "3. Finansial\n";
        cout << "4. Admin\n";
        cout << "5. Keluar\n";
        cout << "==============================\n";
        cout << "Pilih: ";
        cin >> pilih;
        cout << "==============================\n";

        switch(pilih) {
            case 1: login_kasir(); break;
            case 2: menuGudang(); break;
            case 3: menuFinansial(); break;
            case 4: menuAdmin(); break;
            case 5: cout << "Program selesai.\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }

    } while(pilih != 5);

    return 0;
}
