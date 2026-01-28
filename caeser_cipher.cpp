#include <bits/stdc++.h>
using namespace std;

class CaeserCipher  {
    public:
    string encryption(string plaintext, int shift, int alphabetsize)    {

        string ciphertext = "";
        for (char c: plaintext) {
            int x = static_cast<int>(c);
            if (x >= 97 && x <= 122) {
                ciphertext += (char)((x - 97 + shift) % 26 + 97);
            }
            else if (x >= 65 && x <= 90) {
                ciphertext += (char)((x - 65 + shift) % 26 + 65);
            } else if (x >= 48 && x <= 57)   {
                ciphertext += (char)((x - 48 + shift) % 10 + 48);
            }   else    {
                ciphertext += c;
            }
        }

        return ciphertext;
    }

    string decrpytion(string ciphertext, int shift, int alphabetsize)   {
        string plaintext = "";
        for (char c: ciphertext) {
            int x = static_cast<int>(c);
            if (x >= 97 && x <= 122) {
                plaintext += (char)(((x - 97 - shift) % 26 + 26) % 26 + 97);
            }
            else if (x >= 65 && x <= 90) {
                plaintext += (char)(((x - 65 - shift) % 26 + 26) % 26 + 65);
            } else if (x >= 48 && x <= 57)   {
                plaintext += (char)(((x - 48 - shift) % 10 + 10) % 10 + 48);
            }   else    {
                plaintext += c;
            }
        }

        return plaintext;
    }

    vector<string> unknown_shift_decrypt(string ciphertext, int alphabetsize) {
        vector<string> possible_plaintexts;
        for (int i = 1; i < alphabetsize; i++)  {
            possible_plaintexts.push_back(decrpytion(ciphertext, i, alphabetsize));
        }
        return possible_plaintexts;
    }
};

int main()  {
    CaeserCipher cipher;

    int choice = 0;
    cout << "Enter 1 for Basic Encryption and Decryption & 2 for Unknown Shift Decryption: ";
    cin >> choice;

    if (choice == 1)    {
        int n;
        cout << "Enter number of cases: ";
        cin >> n;
        cout << "\n";
        string plaintext;
        int shiftsize, alphabetsize;
        while (n)   {
            cout << "Enter the word: ";
            getline(cin, plaintext);
            getline(cin, plaintext);
            cout << "Enter the shift size: ";
            cin >> shiftsize;
            cout << "Enter alphabet size: ";
            cin >> alphabetsize;
            string ciphertext = cipher.encryption(plaintext, shiftsize, alphabetsize);
            cout << "\nEncrypted text: " << ciphertext << "\n";
            cout << "Decrypted text: " << cipher.decrpytion(ciphertext, shiftsize, alphabetsize) << "\n";
            n--;
        }
    }   else    {
        int n;
        cout << "Enter number of cases: ";
        cin >> n;
        cout << "\n";
        string ciphertext;
        int alphabetsize;
        while (n)   {
            cout << "Enter the word: ";
            cin.ignore();
            getline(cin, ciphertext);
            cout << "Enter alphabet size: ";
            cin >> alphabetsize;
            vector<string> possibilites = cipher.unknown_shift_decrypt(ciphertext, alphabetsize);
            for (int i = 0; i < possibilites.size(); i++)   {
                cout << "Enter 1 if its the correct plaintext, else 2: ";
                cout << "Possible word is:" << possibilites[i] << " ";
                int correct = 0;
                cin >> correct;
                if (correct == 1) {
                    cout << "The plaintext is: " << possibilites[i] << "\n";
                    break;
                }
            }
            n--;
        }
    }
    return 0;
}