#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
#include <cstdint>
#include <array>
#include <vector>
#include <bitset>

using namespace std;



// Fungsi Caesar
string enkripsi_caesar(string plaintext, int kunci)
{
    string ciphertext = "";
    for (char c : plaintext)
    {
        if (isalpha(c))
        {
            char base = isupper(c) ? 'A' : 'a';
            ciphertext += char((c - base + kunci) % 26 + base);
        }
        else
        {
            ciphertext += c;
        }
    }
    return ciphertext;
}

string dekripsi_caesar(string ciphertext, int kunci)
{
    string plaintext = "";
    for (char c : ciphertext)
    {
        if (isalpha(c))
        {
            char base = isupper(c) ? 'A' : 'a';
            plaintext += char((c - base - kunci + 26) % 26 + base);
        }
        else
        {
            plaintext += c;
        }
    }
    return plaintext;// Dekripsi adalah kebalikan dari enkripsi
}

// Fungsi Vigenere
string enkripsi_viginere(string plaintext, string kunci)
{
    string enkripsi = "";
    int keyIndex = 0;
    for (int i = 0; i < plaintext.length(); i++)
    {
        if (isalpha(plaintext[i]))
        {
            char offset = isupper(plaintext[i]) ? 'A' : 'a';
            enkripsi += (plaintext[i] - offset + (toupper(kunci[keyIndex]) - 'A')) % 26 + offset;
            keyIndex = (keyIndex + 1) % kunci.length();
        }
        else
        {
            enkripsi += plaintext[i];
        }
    }
    return enkripsi;
}

string dekripsi_viginere(string chipertext, string kunci)
{
    string dekripsi = "";
    int keyIndex = 0;
    for (int i = 0; i < chipertext.length(); i++)
    {
        if (isalpha(chipertext[i]))
        {
            char offset = isupper(chipertext[i]) ? 'A' : 'a';
            dekripsi += (chipertext[i] - offset - (toupper(kunci[keyIndex]) - 'A') + 26) % 26 + offset;
            keyIndex = (keyIndex + 1) % kunci.length();
        }
        else
        {
            dekripsi += chipertext[i];
        }
    }
    return dekripsi;
}


// Fungsi untuk menghapus spasi 
string hilangkanSpasi(string teks)
{
    string hasil = "";
    for (char karakter : teks)
    {
        if (karakter != ' ') // Abaikan karakter spasi
        {
            hasil += karakter;
        }
    }
    return hasil;
}

// Stream Cipher (XOR-based)
string cipherStream(string teks, string kunci)
{
    teks = hilangkanSpasi(teks); // Hapus spasi
    string hasil = "";
    for (int i = 0; i < teks.size(); i++)
    {
        hasil += teks[i] ^ kunci[i % kunci.size()];
    }
    return hasil;
}

// Dekripsi Stream Cipher (XOR-based)
string dekripsiStream(string cipherText, string kunci)
{
    return cipherStream(cipherText, kunci); // XOR adalah operasi yang simetris
}

// Block Cipher (XOR-based)
string cipherBlok(string teks, string kunci)
{
    teks = hilangkanSpasi(teks); // Hapus spasi
    int ukuranBlok = 4;
    string hasil = "";
    for (int i = 0; i < teks.size(); i += ukuranBlok)
    {
        string blok = teks.substr(i, ukuranBlok);
        for (int j = 0; j < blok.size(); j++)
        {
            blok[j] ^= kunci[j % kunci.size()];
        }
        hasil += blok;
    }
    return hasil;
}

// Dekripsi Block Cipher (XOR-based)
string dekripsiBlok(string cipherText, string kunci)
{
    return cipherBlok(cipherText, kunci); // XOR adalah operasi yang simetris
}


// Deklarasi fungsi
void caesar();
void viginere();
void block_cipher();
void stream_cipher();
void mix_caesar_viginere_stream_block();

int main()
{
    int i = 0;
    while (i == 0)
    {
        
        int pilih;
        cout << "=================================\n";
        cout << "| PROGRAM ENKRIPSI DAN DEKRIPSI |\n";
        cout << "=================================\n";
        cout << "| 1. Caesar Cipher              |\n";
        cout << "| 2. Vigenere Cipher            |\n";
        cout << "| 3. Stream Ciphher             |\n";
        cout << "| 4. Block Chipher              |\n";
        cout << "| 5. Mix                        |\n";
        cout << "| 0. Exit                       |\n";
        cout << "=================================\n";
        cout << "Silahkan pilih menu : ";
        cin >> pilih;
        cin.ignore(); // Bersihkan buffer sebelum getline

        switch (pilih)
        {
        case 1:
        {
            caesar();
            i = 0;
        }
            break;

        case 2:
        {
            viginere();
            i = 0;
        }
            break;

        case 3:
        {
            stream_cipher();
            i = 0;
        }
            break;

        case 4:
        {
            block_cipher();
            i = 0;
        }
            break;

        case 5:
        {
            mix_caesar_viginere_stream_block();
            i = 0;
        }
            break;

        case 0:
        {
            cout << "\nExit..\n" ;
            i = 1;
        }
            break;

        default:{
            cout << "\nPilihan tidak valid!\n" << endl;
            i=0;}
            break;
        }
    }
}

// Fungsi untuk Caesar Cipher
void caesar()
{
    string pesan;
    int kunci;
    string Hasil;
    int pilih;
    cout << "1. Enkripsi \n2. Dekripsi \n";
    cout << "Silahkan pilih menu : ";
    cin >> pilih;

    cout << "Masukkan pesan: ";
    cin.ignore();
    getline(cin, pesan);

    cout << "Masukkan kunci (biangan bulat): ";
    cin >> kunci;

    switch (pilih)
        {
        case 1:
        {
            Hasil = enkripsi_caesar(pesan,kunci);  
        }
            break;

        case 2:
        {
            Hasil = dekripsi_caesar(pesan,kunci);  
        }
            break;
        }
     cout << "Hasil : " << Hasil << endl << endl ;
}

// Fungsi untuk Vigenere Cipher1

void viginere()
{
    string pesan;
    string kunci;
    string Hasil;
    int pilih;
    cout << "1. Enkripsi \n2. Dekripsi \n";
    cout << "Silahkan pilih menu : ";
    cin >> pilih;

    cout << "Masukkan pesan: ";
    cin.ignore();
    getline(cin, pesan);

    cout << "Masukkan kunci (kata): ";
    getline(cin, kunci);

    switch (pilih)
        {
        case 1:
        {
            Hasil = enkripsi_viginere(pesan,kunci);  
        }
            break;

        case 2:
        {
            Hasil = dekripsi_viginere(pesan,kunci);  
        }
            break;
        }
     cout << "Hasil : " << Hasil << endl << endl ;
}

void block_cipher()
{
    int pilih;
    string pesan , kunci ,Hasil;
    cout << "1. Enkripsi \n2. Dekripsi \n";
    cout << "Silahkan pilih menu : ";
    cin >> pilih;

    cout << "Masukkan pesan: ";
    cin.ignore();
    getline(cin, pesan);
    cout << "Masukkan kunci (jumlah char sama): ";
    getline(cin, kunci);

    switch (pilih)
        {
        case 1:
        {
            Hasil = cipherBlok(pesan,kunci);  
        }
            break;

        case 2:
        {
            Hasil = dekripsiBlok(pesan,kunci);  
        }
            break;
        }
     cout << "Hasil : " << Hasil << endl << endl ;
}

void stream_cipher()
{
    int pilih;
    string pesan , kunci ,Hasil;
    cout << "1. Enkripsi \n2. Dekripsi \n";
    cout << "Silahkan pilih menu : ";
    cin >> pilih;

    cout << "Masukkan pesan: ";
    cin.ignore();
    getline(cin, pesan);
    cout << "Masukkan kunci (jumlah char sama): ";
    getline(cin, kunci);

    switch (pilih)
        {
        case 1:
        {
            Hasil = cipherStream(pesan,kunci);  
        }
            break;

        case 2:
        {
            Hasil = dekripsiStream(pesan,kunci);  
        }
            break;
        }
     cout << "Hasil : " << Hasil << endl << endl ;
}

// Fungsi Mix Caesar dan Vigenere
// Fungsi Mix dari Caesar, Vigenere, Stream, dan Block Cipher
void mix_caesar_viginere_stream_block()
{
    string pesan, kunci_vigenere, kunci_stream, kunci_block;
    int kunci_caesar, pilih;

    cout << "1. Enkripsi \n2. Dekripsi \n";
    cout << "Silahkan pilih menu : ";
    cin >> pilih;
    cin.ignore();

    cout << "Masukkan pesan: ";
    getline(cin, pesan);

    // Input kunci untuk keempat metode
    cout << "Masukkan kunci Vigenere (kata): ";
    getline(cin, kunci_vigenere);

    cout << "Masukkan kunci Caesar (bilangan bulat): ";
    cin >> kunci_caesar;
    cin.ignore(); // Bersihkan buffer setelah input bilangan bulat

    cout << "Masukkan kunci Stream Cipher (jumlah karakter sama): ";
    getline(cin, kunci_stream);

    cout << "Masukkan kunci Block Cipher (jumlah karakter sama): ";
    getline(cin, kunci_block);

    string hasil;
    
    switch (pilih)
    {
    case 1: // Enkripsi
    {
        // Langkah pertama: Enkripsi menggunakan Caesar
        string enkripsi_caesar_hasil = enkripsi_caesar(pesan, kunci_caesar);

        // Langkah kedua: Enkripsi menggunakan Vigenere
        string enkripsi_vigenere_hasil = enkripsi_viginere(enkripsi_caesar_hasil, kunci_vigenere);

        // Langkah ketiga: Enkripsi menggunakan Stream Cipher
        string enkripsi_stream_hasil = cipherStream(enkripsi_vigenere_hasil, kunci_stream);

        // Langkah keempat: Enkripsi menggunakan Block Cipher
        hasil = cipherBlok(enkripsi_stream_hasil, kunci_block);

        cout << "Pesan terenkripsi dengan campuran: " << hasil << endl;
        break;
    }
    case 2: // Dekripsi
    {
        // Langkah pertama: Dekripsi menggunakan Block Cipher
        string dekripsi_block_hasil = dekripsiBlok(pesan, kunci_block);

        // Langkah kedua: Dekripsi menggunakan Stream Cipher
        string dekripsi_stream_hasil = dekripsiStream(dekripsi_block_hasil, kunci_stream);

        // Langkah ketiga: Dekripsi menggunakan Vigenere
        string dekripsi_vigenere_hasil = dekripsi_viginere(dekripsi_stream_hasil, kunci_vigenere);

        // Langkah keempat: Dekripsi menggunakan Caesar
        hasil = dekripsi_caesar(dekripsi_vigenere_hasil, kunci_caesar);

        cout << "Pesan terdekripsi dengan campuran: " << hasil << endl;
        break;
    }
    default:
        cout << "Pilihan tidak valid!" << endl;
        break;
    }
}

