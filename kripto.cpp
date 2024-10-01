#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string enkripsi_caesar(string plaintext, int kunci) {
    string ciphertext = "";
    for (char c : plaintext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            ciphertext += char((c - base + kunci) % 26 + base);
        } else {
            ciphertext += c;
        }
    }
    return ciphertext;
}

string dekripsi_caesar(string ciphertext, int kunci) {
    return enkripsi_caesar(ciphertext, -kunci);  // Dekripsi adalah kebalikan dari enkripsi
}

int main() {
    string pesan_caesar;
    int kunci_ceasar;

    cout << "Masukkan pesan: ";
    getline(cin, pesan_caesar);
    cout << "Masukkan kunci (bilangan bulat): ";
    cin >> kunci_ceasar;

    string pesan_terenkripsi = enkripsi_caesar(pesan_caesar, kunci_ceasar);
    cout << "Pesan terenkripsi: " << pesan_terenkripsi << endl;

    string pesan_terdekripsi = dekripsi_caesar(pesan_terenkripsi, kunci_ceasar);
    cout << "Pesan terdekripsi: " << pesan_terdekripsi << endl;



    return 0;
}