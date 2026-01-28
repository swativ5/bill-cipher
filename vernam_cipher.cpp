#include <bits/stdc++.h>
using namespace std;

class VernamCipher  {
    public:
    vector<int> encryption(string plaintext, string key)    {
        vector<int> ciphertext;
        int keylen = key.length();
        int keyindex = 0;

        for (char c: plaintext) {
            int x = static_cast<int>(c);
            char k = key[keyindex % keylen];
            int kx = static_cast<int>(k);

            if ((x >= 97 && x <= 122) || (x >= 65 && x <= 90)) {
                ciphertext.push_back(x ^ kx);
                keyindex++;
            } else {
                ciphertext.push_back(x);
            }
        }
        return ciphertext;
    }

    string decryption(vector<int> ciphertext, string key)   {
        string plaintext = "";
        int keylen = key.length();
        int keyindex = 0;

        for (int x: ciphertext) {
            if ((x >= 32 && x <= 126) && !((x >= 65 && x <= 90) || (x >= 97 && x <= 122))) {
                plaintext += (char)x;
            } else {
                char k = key[keyindex % keylen];
                int kx = static_cast<int>(k);
                plaintext += (char)(x ^ kx);
                keyindex++;
            }
        }

        return plaintext;
    }
};

int main()  {
    VernamCipher cipher;
    
    int n;
    cout << "Enter number of cases: ";
    cin >> n;
    cin.ignore();
    
    while (n--)
    {
        string plaintext, key;
        cout << "Enter Plaintext: ";
        getline(cin, plaintext);
        cout << "Enter Key: ";
        getline(cin, key);
        
        vector<int> ciphertext = cipher.encryption(plaintext, key);
        cout << "Ciphertext: ";
        for (int num : ciphertext)    {
            cout << num << " ";
        }
        cout << "\n";

        string decrypted = cipher.decryption(ciphertext, key);
        cout << "Decrypted Text: " << decrypted << "\n\n";
    }
}