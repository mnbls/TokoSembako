#include <iostream>
using namespace std;


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
void menuKasir() {
    int pilih;
    do {
        header_kasir();
        cout << "1. Penjualan\n";
        cout << "2. Cek Stok\n";
        cout << "3. Keluar\n";
        cout << "==============================\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch(pilih) {
            case 1:
                cout << "-> Menu Penjualan\n";
                break;
            case 2:
                cout << "-> Menu Cek Stok\n";
                break;
            case 3:
                cout << "Kembali ke menu utama...\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while(pilih != 3);
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
            case 1: menuKasir(); break;
            case 2: menuGudang(); break;
            case 3: menuFinansial(); break;
            case 4: menuAdmin(); break;
            case 5: cout << "Program selesai.\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }

    } while(pilih != 5);

    return 0;
}
