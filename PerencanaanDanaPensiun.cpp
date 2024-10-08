#include <iostream>
#include <cmath>
#define ll long long
using namespace std;

// Fungsi untuk menghitung setoran bulanan
ll hitungSetoranBulanan(ll targetPensiun, double sukuBungaTahunan, int tahunHinggaPensiun, int frekuensiSetoran) {
    double sukuBungaBulanan = sukuBungaTahunan / frekuensiSetoran;
    ll jumlahSetoran = tahunHinggaPensiun * frekuensiSetoran;
    ll setoranBulanan = targetPensiun * sukuBungaBulanan / (pow(1 + sukuBungaBulanan, jumlahSetoran) - 1);
    return setoranBulanan;
}

// Fungsi untuk mensimulasikan total pensiun
ll simulasiTotalPensiun(ll setoranBulanan, double sukuBungaTahunan, int tahunHinggaPensiun, int frekuensiSetoran) {
    double sukuBungaBulanan = sukuBungaTahunan / frekuensiSetoran;
    ll jumlahSetoran = tahunHinggaPensiun * frekuensiSetoran;
    ll totalPensiun = 0;
    for (int i = 0; i < jumlahSetoran; i++) {
        totalPensiun = (totalPensiun + setoranBulanan) * (1 + sukuBungaBulanan);
        if ((i + 1) % frekuensiSetoran == 0) {
            cout << "Tahun " << (i + 1) / frekuensiSetoran << ": " << totalPensiun << endl;
        }
    }
    return totalPensiun;
}

int main() {
    ll targetPensiun;
    double sukuBungaTahunan;
    int tahunHinggaPensiun, frekuensiSetoran=12;

    cout << "Program Perencanaan Pensiun" << endl;
    cout << "---------------------------" << endl;
    cout << "Masukkan target pensiun: ";
    cin >> targetPensiun;
    cout << "Masukkan suku bunga tahunan (dalam desimal): ";
    cin >> sukuBungaTahunan;
    cout << "Masukkan tahun hingga pensiun: ";
    cin >> tahunHinggaPensiun;

    ll setoranBulanan = hitungSetoranBulanan(targetPensiun, sukuBungaTahunan, tahunHinggaPensiun, frekuensiSetoran);
    ll totalPensiun = simulasiTotalPensiun(setoranBulanan, sukuBungaTahunan, tahunHinggaPensiun, frekuensiSetoran);

    cout << "Setoran bulanan: " << setoranBulanan << endl;
    cout << "Total pensiun: " << totalPensiun << endl;

    return 0;
}
