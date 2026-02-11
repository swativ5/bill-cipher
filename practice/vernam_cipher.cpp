#include <bits/stdc++.h>
using namespace std;

vector<int> encryption(string plain, string key)    {
    vector<int> cipher;
    int keylength = key.length();
    int keyidx = 0;

    for (char c : plain)    {
        int p = c;
        int k = key[keyidx % keylength];

        cipher.push_back(p ^ k);
        keyidx++;
    }
    return cipher;
}

string decryption(vector<int> cipher, string key)   {
    string decrypt = "";
    int keylength = key.length();
    int keyidx = 0;

    for (int n : cipher)    {
        int k = key[keyidx % keylength];
        decrypt += (char) (n ^ k);
        keyidx++;
    }
    return decrypt;
}

int main () {
    int t;
    cout << "Enter number of test cases: ";
    cin >> t;
    cin.ignore();

    while (t--) {
        string plain, key, decrypt;
        vector<int> cipher;
        cout << "Enter your plaintext: ";
        getline(cin, plain);
        cout << "Enter your key: ";
        getline(cin, key);
        cipher = encryption(plain, key);
        cout << "Encrypted word: ";
        for (int n : cipher) cout << n << " ";
        cout << "\n";
        decrypt = decryption(cipher, key);
        cout << "Decrypted word: " << decrypt << "\n";
    }
}