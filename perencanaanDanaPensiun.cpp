#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#define ll long long
using namespace std;

// Deklarasi struct untuk menyimpan data pengguna
struct data {
    string nama;
    ll setoranPerBulan;
    int tahunPensiun;
    double sukuBungaTahunan;
};

// Fungsi untuk menghitung setoran bulanan
ll hitungSetoranBulanan(ll targetPensiun, double sukuBungaTahunan, int tahunHinggaPensiun, int frekuensiSetoran) {
    double sukuBungaBulanan = sukuBungaTahunan / frekuensiSetoran;
    ll jumlahSetoran = tahunHinggaPensiun * frekuensiSetoran;
    ll setoranBulanan = targetPensiun * sukuBungaBulanan / (pow(1 + sukuBungaBulanan, jumlahSetoran) - 1);
    return setoranBulanan;
}

// Fungsi untuk menampilkan hasil investasi per tahun
void tampilkanInvestasiPerTahun(ll setoranBulanan, double sukuBungaBulanan, int jumlahSetoran) {
    ll totalPensiun = 0;
    cout << "\nHasil investasi per tahun:" << endl;
    for (int i = 0; i < jumlahSetoran; i++) {
        totalPensiun = (totalPensiun + setoranBulanan) * (1 + sukuBungaBulanan);
        if ((i + 1) % 12 == 0) {
            cout << "Tahun " << (i + 1) / 12 << ": " << totalPensiun << endl;
        }
    }
}

// Fungsi untuk membaca data dari file
vector<data> bacaDataPengguna(string& filePath) {
    vector<data> dataPengguna;
    ifstream file(filePath);
    data pengguna;
    while (file >> pengguna.nama >> pengguna.setoranPerBulan >> pengguna.tahunPensiun >> pengguna.sukuBungaTahunan) {
        dataPengguna.push_back(pengguna);
    }
    file.close();
    return dataPengguna;
}

// Fungsi untuk menulis data ke file
void tambahDataPengguna(string& filePath, data& pengguna) {
    ofstream file(filePath, ios::app);
    file << pengguna.nama << " " << pengguna.setoranPerBulan << " " << pengguna.tahunPensiun << " " << pengguna.sukuBungaTahunan << endl;
    file.close();
}

// Fungsi pencarian manual dengan simulasi tahunan
void cariPengguna(vector<data>& dataPengguna, string& nama) {
    bool ditemukan = false;
    for (const auto& pengguna : dataPengguna) {
        if (pengguna.nama == nama) {
            ditemukan = true;
            cout << "Nama: " << pengguna.nama << endl
                 << "Setoran Per Bulan: " << pengguna.setoranPerBulan << endl
                 << "Tahun Pensiun: " << pengguna.tahunPensiun << endl
                 << "Suku Bunga Tahunan: " << pengguna.sukuBungaTahunan << endl;

            double sukuBungaBulanan = pengguna.sukuBungaTahunan / 12;
            int jumlahSetoran = pengguna.tahunPensiun * 12;

            tampilkanInvestasiPerTahun(pengguna.setoranPerBulan, sukuBungaBulanan, jumlahSetoran);
            break;
        }
    }
    if (!ditemukan) {
        cout << "Pengguna dengan nama " << nama << " tidak ditemukan." << endl;
    }
}

// Fungsi pengurutan manual menggunakan bubble sort
void urutkanData(vector<data>& dataPengguna) {
    int n = dataPengguna.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (dataPengguna[j].setoranPerBulan < dataPengguna[j + 1].setoranPerBulan) {
                swap(dataPengguna[j], dataPengguna[j + 1]);
            }
        }
    }
}

int main() {
    string filePath = "data.csv";
    vector<data> dataPengguna = bacaDataPengguna(filePath);
    
    ll targetPensiun;
    double sukuBungaTahunan;
    int tahunHinggaPensiun, frekuensiSetoran = 12;
    string namaPengguna;

    cout << "Program Perencanaan Pensiun" << endl;
    cout << "---------------------------" << endl;

    int opt = -1;

    while (opt != 0) {
        cout << "\nPilih fitur:" << endl;
        cout << "1. Menghitung target pensiun" << endl;
        cout << "2. Menampilkan semua data pengguna" << endl;
        cout << "3. Mencari data pengguna" << endl;
        cout << "0. Keluar dari program" << endl;
        cout << "Masukkan pilihan: ";
        cin >> opt;

        switch (opt) {
            case 0:
                cout << "\nTerima kasih telah menggunakan jasa kami." << endl;
                cout << "--------------by: Kelompok 10--------------" << endl;
                break;

            case 1: {
                //Mencari setoran bulanan pengguna dan melakukan proyeksinya
                cout << "\nMasukkan nama Anda: ";
                cin >> namaPengguna;
                cout << "Masukkan target pensiun: ";
                cin >> targetPensiun;
                cout << "Masukkan suku bunga tahunan (dalam desimal): ";
                cin >> sukuBungaTahunan;
                cout << "Masukkan tahun hingga pensiun: ";
                cin >> tahunHinggaPensiun;

                ll setoranBulanan = hitungSetoranBulanan(targetPensiun, sukuBungaTahunan, tahunHinggaPensiun, frekuensiSetoran);
                data penggunaBaru = {namaPengguna, setoranBulanan, tahunHinggaPensiun, sukuBungaTahunan};
                tambahDataPengguna(filePath, penggunaBaru);

                int jumlahSetoran = tahunHinggaPensiun * 12;
                double sukuBungaBulanan = sukuBungaTahunan / 12;

                cout << "\nSetoran bulanan: " << setoranBulanan << endl;

                tampilkanInvestasiPerTahun(setoranBulanan, sukuBungaBulanan, jumlahSetoran);

                // Refresh data pengguna
                dataPengguna = bacaDataPengguna(filePath);
                break;
            }

            case 2: {
                //Menampilkan seluruh data pengguna
                cout << "\nData Pengguna (diurutkan berdasarkan setoran per bulan):" << endl;
                urutkanData(dataPengguna);
                for (const auto& pengguna : dataPengguna) {
                    cout << "Nama: " << pengguna.nama << ", Setoran Per Bulan: " << pengguna.setoranPerBulan 
                         << ", Tahun Pensiun: " << pengguna.tahunPensiun 
                         << ", Suku Bunga Tahunan: " << pengguna.sukuBungaTahunan << endl;
                }
                break;
            }

            case 3: {
                //Mencari pengguna pada data
                string cariNama;
                cout << "\nMasukkan nama yang ingin dicari: ";
                cin >> cariNama;
                cariPengguna(dataPengguna, cariNama);
                break;
            }

            default:
                //Keluar dari program
                cout << "Input tidak sesuai. Silakan coba lagi." << endl;
                break;
        }
    }

    return 0;
}
