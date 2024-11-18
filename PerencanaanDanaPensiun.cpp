#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#define ll long long
using namespace std;

// Definisi struct untuk menyimpan data pengguna
struct Pengguna {
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
vector<Pengguna> bacaDataPengguna(const string& filePath) {
    vector<Pengguna> data;
    ifstream file(filePath);
    Pengguna pengguna;
    while (file >> pengguna.nama >> pengguna.setoranPerBulan >> pengguna.tahunPensiun >> pengguna.sukuBungaTahunan) {
        data.push_back(pengguna);
    }
    file.close();
    return data;
}

// Fungsi untuk menulis data ke file
void tambahDataPengguna(const string& filePath, const Pengguna& pengguna) {
    ofstream file(filePath, ios::app);
    file << pengguna.nama << " " << pengguna.setoranPerBulan << " " << pengguna.tahunPensiun << " " << pengguna.sukuBungaTahunan << endl;
    file.close();
}

// Fungsi pencarian manual dengan simulasi tahunan
void cariPengguna(const vector<Pengguna>& data, const string& nama) {
    bool ditemukan = false;
    for (const auto& pengguna : data) {
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
void urutkanData(vector<Pengguna>& data) {
    int n = data.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (data[j].setoranPerBulan < data[j + 1].setoranPerBulan) {
                swap(data[j], data[j + 1]);
            }
        }
    }
}

int main() {
    string filePath = "data.csv";
    vector<Pengguna> dataPengguna = bacaDataPengguna(filePath);
    
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
                cout << "Terima kasih telah menggunakan jasa kami." << endl;
                break;

            case 1: {
                cout << "\nMasukkan nama Anda: ";
                cin >> namaPengguna;
                cout << "Masukkan target pensiun: ";
                cin >> targetPensiun;
                cout << "Masukkan suku bunga tahunan (dalam desimal): ";
                cin >> sukuBungaTahunan;
                cout << "Masukkan tahun hingga pensiun: ";
                cin >> tahunHinggaPensiun;

                ll setoranBulanan = hitungSetoranBulanan(targetPensiun, sukuBungaTahunan, tahunHinggaPensiun, frekuensiSetoran);
                Pengguna penggunaBaru = {namaPengguna, setoranBulanan, tahunHinggaPensiun, sukuBungaTahunan};
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
                string cariNama;
                cout << "\nMasukkan nama yang ingin dicari: ";
                cin >> cariNama;
                cariPengguna(dataPengguna, cariNama);
                break;
            }

            default:
                cout << "Input tidak sesuai. Silakan coba lagi." << endl;
                break;
        }
    }

    return 0;
}
