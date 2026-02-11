#include <bits/stdc++.h>
using namespace std;

int mod(int a, int b)   {
    return ((a % b) + b) % b;
}

string encrypt(string plain, int shift) {
    string cipher;
    for (char c: plain) {
        int x = c;
        if (x >= 97 && x <= (97 + 25))    {
            cipher += (char)(mod(x - 97 + shift, 26) + 97);
        }   else if (x >= 65 && x <= (65 + 25))   {
            cipher += (char)(mod(x - 65 + shift, 26) + 65);
        }   else if (x >= 48 && x <= (48 + 9))   {
            cipher += (char) (mod(x - 48 + shift, 10) + 48);
        }   else    {
            cipher += c;
        }
    }
    return cipher;
}

string decrypt(string cipher, int shift)    {
    string decrypted = "";
    for (char c: cipher)    {
        int x = c;
        if (x >= 97 && x <= (97 + 25))  {
            decrypted += (char)(mod(x - 97 - shift, 26) + 97);
        }   else if (x >= 65 && x <= (65 + 25)) {
            decrypted += (char)(mod(x - 65 - shift, 26) + 65);
        }   else if (x >= 48 && x <= (48 + 9))  {
            decrypted += (char)(mod(x - 48 - shift, 10) + 48);
        }   else    {
            decrypted += c;
        }
    }
    return decrypted;
}

vector<string> cryptanalysis(string cipher) {
    vector<string> possibilities;
    for (int i = 1; i <= 26; i++)    {
        possibilities.push_back(decrypt(cipher, i));
    }
    return possibilities;
}

int main()  {
    int t;
    cout << "Enter number of cases: ";
    cin >> t;
    cout << "\n";
    while (t--) {
        string plain, cipher, decrypted; int shift;
        cout << "Enter your word: ";
        cin.ignore();
        getline(cin, plain);
        cout << "Enter your shift value: ";
        cin >> shift;
        cout << "\n";
        cipher = encrypt(plain, shift);
        cout << "Encrypted word: " << cipher << "\n";
        decrypted = decrypt(cipher, shift);
        cout << "Decrypted word: " << decrypted << "\n\n";
    }

    cout << "Cryptanalysis time :3" << "\n";
    string cipher;
    cout << "Enter your word: ";
    cin.ignore();
    getline(cin, cipher);
    vector<string> possibilities = cryptanalysis(cipher);
    int shift = 0, n = 0;
    while (shift < possibilities.size())    {
        cout << "Word: " << possibilities[shift]  << "\n" << "Enter 1 if its the correct decrypted word, else 0: ";
        cin >> n;
        if (n == 1) {
            cout << "\n" << "Decrypted word is: " << possibilities[shift];
            break;
        }
        shift++;
    }
}