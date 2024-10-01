#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Fungsi Caesar
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

// Fungsi Vigenere
string enkripsi_viginere(string plaintext, string kunci) {
    string enkripsi = "";
    int keyIndex = 0;
    for (int i = 0; i < plaintext.length(); i++) {
        if (isalpha(plaintext[i])) {
            char offset = isupper(plaintext[i]) ? 'A' : 'a';
            enkripsi += (plaintext[i] - offset + (toupper(kunci[keyIndex]) - 'A')) % 26 + offset;
            keyIndex = (keyIndex + 1) % kunci.length();
        } else {
            enkripsi += plaintext[i];
        }
    }
    return enkripsi;
}

string dekripsi_viginere(string chipertext, string kunci) {
    string plaintext = "";
    int keyIndex = 0;
    for (int i = 0; i < chipertext.length(); i++) {
        if (isalpha(chipertext[i])) {
            char offset = isupper(chipertext[i]) ? 'A' : 'a';
            plaintext += (chipertext[i] - offset - (toupper(kunci[keyIndex]) - 'A') + 26) % 26 + offset;
            keyIndex = (keyIndex + 1) % kunci.length();
        } else {
            plaintext += chipertext[i];
        }
    }
    return plaintext;
}

// Deklarasi fungsi
void caesar();
void viginere();

int main() {
    int pilih;

    cout << "== PROGRAM ENKRIPSI DAN DEKRIPSI FILE ==\n";
    cout << "1. Caesar Chiper\n";
    cout << "2. Vigenere Chiper\n";
    cout << "Silahkan pilih menu: "; 
    cin >> pilih;
    cin.ignore();  // Bersihkan buffer sebelum getline

    switch (pilih)
    {
    case 1:
        caesar();
        break;

    case 2:
        viginere();
        break;

    default:
        cout << "Pilihan tidak valid!" << endl;
        break;
    }

    return 0;
}

// Fungsi untuk Caesar Cipher
void caesar() {
    string pesan_caesar;
    int kunci_caesar;
    
    cout << "Masukkan pesan: ";
    getline(cin, pesan_caesar);
    
    cout << "Masukkan kunci (bilangan bulat): ";
    cin >> kunci_caesar;

    string pesan_terenkripsi = enkripsi_caesar(pesan_caesar, kunci_caesar);
    cout << "Pesan terenkripsi: " << pesan_terenkripsi << endl;

    string pesan_terdekripsi = dekripsi_caesar(pesan_terenkripsi, kunci_caesar);
    cout << "Pesan terdekripsi: " << pesan_terdekripsi << endl;
}

// Fungsi untuk Vigenere Cipher
void viginere() {
    string pesan_viginere;
    string kunci_viginere;

    cout << "Masukkan pesan: ";
    getline(cin, pesan_viginere);

    cout << "Masukkan kunci (kata): ";
    getline(cin, kunci_viginere);

    string pesan_terenkripsi = enkripsi_viginere(pesan_viginere, kunci_viginere);
    cout << "Pesan terenkripsi: " << pesan_terenkripsi << endl;

    string pesan_terdekripsi = dekripsi_viginere(pesan_terenkripsi, kunci_viginere);
    cout << "Pesan terdekripsi: " << pesan_terdekripsi << endl;
}
