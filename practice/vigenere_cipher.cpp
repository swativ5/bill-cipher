#include <bits/stdc++.h>
using namespace std;

int mod (int a, int b)  {
    return ((a % b) + b) % b;
}

// assume plaintext and key have upper case alphabets only
string encrypt(string plaintext, string key)    {
    int keylength = key.size();
    string cipher = "";
    int keyindex = 0;

    for (char c: plaintext) {
        int kx = key[keyindex % keylength];
        int px = c;

        if (px >= 65 && px <= (65 + 25))    {
            cipher += (char) (mod(px - 65 + (kx - 65), 26) + 65);
            keyindex++;
        }   else    {
            cipher += c;
        }
    }
    return cipher;
}

string decrypt(string cipher, string key)   {
    int keylength = key.size();
    string decrypted = "";
    int keyindex = 0;

    for (char c: cipher) {
        int kx = key[keyindex % keylength];
        int px = c;

        if (px >= 65 && px <= (65 + 25))    {
            decrypted += (char) (mod(px - 65 - (kx - 65), 26) + 65);
            keyindex++;
        }   else    {
            decrypted += c;
        }
    }
    return decrypted;
}

int main()  {
    int t;
    cout << "Enter number of cases: ";
    cin >> t;
    cin.ignore();

    cout << "\n";
    while (t--) {
        string plain, cipher, decrypted, key;
        cout << "Enter your word: ";
        getline(cin, plain);
        cout << "Enter your shift value: ";
        getline(cin, key);
        cout << "\n";
        cipher = encrypt(plain, key);
        cout << "Encrypted word: " << cipher << "\n";
        decrypted = decrypt(cipher, key);
        cout << "Decrypted word: " << decrypted << "\n\n";
    }
}