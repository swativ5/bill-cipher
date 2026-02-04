#include <bits/stdc++.h>
using namespace std;

class RailfenceCipher  {
    public:
    string encryption(string plaintext, int key)    {
        int m = key;
        int n = ceil(plaintext.size() / key);
        n++;
        vector<vector<char>> grid(m, vector<char>(n, 'x'));
        int c = 0;
        for (int col = 0; col < n; col++)   {
            for (int row = 0; row < m; row++)   {
                if (c < plaintext.size())   {
                    grid[row][col] = plaintext[c++];
                }
            }
        }
        string ciphertext(m * n, 'x');
        c = 0; 
        for (int row = 0; row < m; row++)   {
            for (int col = 0; col < n; col++)   {
                ciphertext[c++] = grid[row][col];
            }
        }
        return ciphertext;
    }

    string decryption(string ciphertext, int key)   {
        int m = key;
        int n = ceil(ciphertext.size() / key);
        vector<vector<char>> grid(m, vector<char>(n, 'x'));
        int c = 0;
        for (int row = 0; row < m; row++)   {
            for (int col = 0; col < n; col++)   {
                grid[row][col] = ciphertext[c++];
            }
        }
        string decrypted(m * n, 'x');
        c = 0;
        for (int col = 0; col < n; col++)   {
            for (int row = 0; row < m; row++)   {
                decrypted[c++] = grid[row][col];
            }
        }
        return decrypted;
    }
};

int main()  {
    RailfenceCipher cipher;
    
    int n;
    cout << "Enter number of cases: ";
    cin >> n;
    cin.ignore();
    
    while (n--)
    {
        string plaintext; int key;
        cout << "Enter Plaintext: ";
        getline(cin, plaintext);
        cout << "Enter Key: ";
        cin >> key;
        
        string ciphertext = cipher.encryption(plaintext, key);
        cout << "Ciphertext: " << ciphertext << "\n";
        cout << "\n";

        string decrypted = cipher.decryption(ciphertext, key);
        cout << "Decrypted Text: " << decrypted << "\n\n";
    }
}