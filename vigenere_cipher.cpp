#include <bits/stdc++.h>
using namespace std;

class VigenereCipher  {
    public:
    string encryption(string plaintext, string key)    {
        string ciphertext = "";
        int keylen = key.length();
        int keyindex = 0;

        for (char c: plaintext) {
            int x = static_cast<int>(c);
            char k = key[keyindex % keylen];
            int kx = static_cast<int>(k);

            if (x >= 97 && x <= 122) {
                ciphertext += (char)((x - 97 + (kx - 97)) % 26 + 97);
                keyindex++;
            }
            else if (x >= 65 && x <= 90) {
                ciphertext += (char)((x - 65 + (kx - 65)) % 26 + 65);
                keyindex++;
            } else {
                ciphertext += c;
            }
        }

        return ciphertext;
    }

    string decryption(string ciphertext, string key)   {
        string plaintext = "";
        int keylen = key.length();
        int keyindex = 0;

        for (char c: ciphertext) {
            int x = static_cast<int>(c);
            char k = key[keyindex % keylen];
            int kx = static_cast<int>(k);

            if (x >= 97 && x <= 122) {
                plaintext += (char)(((x - 97 - (kx - 97)) % 26 + 26) % 26 + 97);
                keyindex++;
            }
            else if (x >= 65 && x <= 90) {
                plaintext += (char)(((x - 65 - (kx - 65)) % 26 + 26) % 26 + 65);
                keyindex++;
            } else {
                plaintext += c;
            }
        }

        return plaintext;
    }
};

int main()  {
    VigenereCipher cipher;

    int n;
    cout << "Enter number of cases: ";
    cin >> n;
    cout << "\n";
    while (n--)
    {
        string plaintext, key;
        cout << "Enter Plaintext: ";
        cin.ignore();
        getline(cin, plaintext);
        cout << "Enter Key: ";
        getline(cin, key);

        string encrypted_text = cipher.encryption(plaintext, key);
        cout << "Encrypted Text: " << encrypted_text << "\n";

        string decrypted_text = cipher.decryption(encrypted_text, key);
        cout << "Decrypted Text: " << decrypted_text << "\n";
        cout << "\n";
    }

    return 0;
}