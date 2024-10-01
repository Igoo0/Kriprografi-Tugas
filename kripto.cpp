#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
#include <cstdint>
#include <array>
#include <vector>
#include <bitset>

using namespace std;

constexpr size_t CHACHA20_KEY_SIZE = 32;
constexpr size_t CHACHA20_NONCE_SIZE = 12;
constexpr size_t CHACHA20_BLOCK_SIZE = 64;

//-----------------------
// Fungsi untuk menginisialisasi S-Box
void initializeSBox(vector<int> &S, const string &key)
{
    int keyLength = key.length();
    for (int i = 0; i < 256; i++)
    {
        S[i] = i;
    }

    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        j = (j + S[i] + key[i % keyLength]) % 256;
        swap(S[i], S[j]);
    }
}

// Fungsi untuk melakukan enkripsi dan dekripsi
string rc4(const string &key, const string &plaintext)
{
    vector<int> S(256);
    initializeSBox(S, key);

    int i = 0, j = 0;
    string ciphertext;
    for (char c : plaintext)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        int k = S[(S[i] + S[j]) % 256];
        ciphertext += c ^ k; // Operasi XOR
    }
    return ciphertext;
}

// Fungsi untuk menampilkan hasil dalam format heksadesimal
void printHex(const string &data)
{
    for (unsigned char c : data)
    {
        printf("%02X ", c);
    }
    cout << endl;
}
//-----------------------

class ChaCha20
{
public:
    ChaCha20(const uint8_t key[CHACHA20_KEY_SIZE], const uint8_t nonce[CHACHA20_NONCE_SIZE])
    {
        // Set the initial state
        memcpy(initialState.data(), key, CHACHA20_KEY_SIZE);
        memcpy(initialState.data() + 4, nonce, CHACHA20_NONCE_SIZE);
        initialState[12] = 0; // Block counter
        initialState[13] = 0; // Block counter

        // Constant values for ChaCha20
        initialState[0] = 0x61707865; // "expa"
        initialState[1] = 0x3320646e; // "nd 3"
        initialState[2] = 0x79622d32; // "2-by"
        initialState[3] = 0x6b206574; // "te k"
    }

    void encrypt(const uint8_t *plaintext, size_t plaintext_len, uint8_t *ciphertext)
    {
        for (size_t i = 0; i < plaintext_len; i += CHACHA20_BLOCK_SIZE)
        {
            // Generate keystream block
            uint32_t block[16];
            memcpy(block, initialState.data(), sizeof(block)); // Copy initial state to block
            block[12] += 1;                                    // Increment block counter
            chacha20_block(block);

            // Encrypt block
            for (size_t j = 0; j < CHACHA20_BLOCK_SIZE && (i + j) < plaintext_len; ++j)
            {
                ciphertext[i + j] = plaintext[i + j] ^ ((uint8_t *)block)[j];
            }
        }
    }

private:
    array<uint32_t, 16> initialState{};

    void chacha20_block(uint32_t *block)
    {
        for (size_t i = 0; i < 20; i += 2)
        {
            quarter_round(block[0], block[4], block[8], block[12]);
            quarter_round(block[1], block[5], block[9], block[13]);
            quarter_round(block[2], block[6], block[10], block[14]);
            quarter_round(block[3], block[7], block[11], block[15]);

            quarter_round(block[0], block[5], block[10], block[15]);
            quarter_round(block[1], block[6], block[11], block[12]);
            quarter_round(block[2], block[7], block[8], block[13]);
            quarter_round(block[3], block[4], block[9], block[14]);
        }

        for (size_t i = 0; i < 16; ++i)
        {
            block[i] += initialState[i];
        }
    }

    void quarter_round(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d)
    {
        a += b;
        d ^= a;
        d = rotate_left(d, 16);
        c += d;
        b ^= c;
        b = rotate_left(b, 12);
        a += b;
        d ^= a;
        d = rotate_left(d, 8);
        c += d;
        b ^= c;
        b = rotate_left(b, 7);
    }

    uint32_t rotate_left(uint32_t value, size_t amount)
    {
        return (value << amount) | (value >> (32 - amount));
    }
};

int chacha()
{
    // Key (32 bytes for ChaCha20)
    uint8_t key[CHACHA20_KEY_SIZE];
    for (size_t i = 0; i < CHACHA20_KEY_SIZE; ++i)
    {
        key[i] = static_cast<uint8_t>(i); // Example key (should be random)
    }

    // Nonce (12 bytes for ChaCha20)
    uint8_t nonce[CHACHA20_NONCE_SIZE] = {0}; // Example nonce (should be random)

    // Input plaintext from the user
    string input;
    cout << "Enter text to encrypt: ";
    getline(cin, input);
    size_t plaintext_len = input.length();

    // Buffer for ciphertext and decrypted text
    vector<uint8_t> ciphertext(plaintext_len);
    vector<uint8_t> decryptedtext(plaintext_len + 1); // +1 for null terminator

    // Create ChaCha20 instance
    ChaCha20 chacha20(key, nonce);

    // Encrypt the message
    chacha20.encrypt(reinterpret_cast<const uint8_t *>(input.c_str()), plaintext_len, ciphertext.data());

    // Output ciphertext
    cout << "Ciphertext: ";
    for (size_t i = 0; i < plaintext_len; i++)
    {
        printf("%02x ", ciphertext[i]);
    }
    cout << endl;

    // Decrypt the message (encryption and decryption are the same)
    chacha20.encrypt(ciphertext.data(), plaintext_len, decryptedtext.data());
    decryptedtext[plaintext_len] = '\0'; // Null-terminate

    // Output decrypted text
    cout << "Decrypted text: " << decryptedtext.data() << endl;
    

    return 0;
}

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
    return enkripsi_caesar(ciphertext, -kunci); // Dekripsi adalah kebalikan dari enkripsi
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
    string plaintext = "";
    int keyIndex = 0;
    for (int i = 0; i < chipertext.length(); i++)
    {
        if (isalpha(chipertext[i]))
        {
            char offset = isupper(chipertext[i]) ? 'A' : 'a';
            plaintext += (chipertext[i] - offset - (toupper(kunci[keyIndex]) - 'A') + 26) % 26 + offset;
            keyIndex = (keyIndex + 1) % kunci.length();
        }
        else
        {
            plaintext += chipertext[i];
        }
    }
    return plaintext;
}

// Deklarasi fungsi
void caesar();
void viginere();
void rc4();

int main()
{
    int i = 0;
    while (i == 0)
    {
        
        int pilih;
        cout << "=================================\n";
        cout << "| PROGRAM ENKRIPSI DAN DEKRIPSI |\n";
        cout << "=================================\n";
        cout << "| 1. Caesar Chiper              |\n";
        cout << "| 2. Vigenere Chiper            |\n";
        cout << "| 3. Chacha20                   |\n";
        cout << "| 4. RC4                        |\n";
        cout << "| 5. Mix Caesar Viginere        |\n";
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
            chacha();
            i = 0;
        }
            break;

        case 4:
        {
            rc4();
            i = 0;
        }
            break;

        case 5:
        {
            
        }

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
void viginere()
{
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

void rc4()
{
    string key, plaintext;

    // Input kunci dan plaintext
    cout << "Masukkan kunci: ";
    getline(cin, key);
    cout << "Masukkan plaintext: ";
    getline(cin, plaintext);

    // Enkripsi
    string ciphertext = rc4(key, plaintext);
    cout << "Hasil enkripsi (dalam heksadesimal): ";
    printHex(ciphertext);

    // Dekripsi (dapat menggunakan fungsi yang sama)
    string decrypted = rc4(key, ciphertext);
    cout << "Hasil dekripsi: " << decrypted << endl;
}
