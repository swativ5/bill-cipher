#include <bits/stdc++.h>
using namespace std;

class ColumnCipher  {
    public:
    string encryption(string plaintext, string key)    {
        vector<int> keyorder;
        for (char c: key)   {
            if (c == ' ')   {
                continue;
            }
            keyorder.push_back(c - '0');
        }

        int n = keyorder.size();
        int m = ceil(plaintext.size() / n);
        m++;

        vector<vector<char>> grid(m, vector<char>(n, ' '));
        int idx = 0;
        for (int row = 0; row < m; row++)   {
            for (int col = 0; col < n; col++)   {
                if (idx < plaintext.size()) {
                    grid[row][col] = plaintext[idx++];
                }
            }
        }

        for (vector<char> r: grid)  {
            for (char c: r) {
                cout << c << " ";
            }
            cout << "\n";
        }
        
        string ciphertext = "";
        for (int keyval = 0; keyval < n; keyval++)    {
            int col = keyorder[keyval] - 1;
            for (int row = 0; row < m; row++)   {
                ciphertext += grid[row][col];
            }
        }
        return ciphertext;
    }

    string decryption(string ciphertext, string key)   {
        vector<int> keyorder;
        for (char c: key)   {
            if (c == ' ')   {
                continue;
            }
            keyorder.push_back(c - '0');
        }

        int n = keyorder.size();
        int m = ciphertext.size() / n;
        
        vector<vector<char>> grid(m, vector<char>(n, ' '));
        
        int idx = 0;
        for (int keyval = 0; keyval < n; keyval++)    {
            int col = keyorder[keyval] - 1;
            for (int row = 0; row < m; row++)   {
                grid[row][col] = ciphertext[idx++];
            }
        }
        
        string plaintext = "";
        for (int row = 0; row < m; row++)   {
            for (int col = 0; col < n; col++)   {
                plaintext += grid[row][col];
            }
        }
        return plaintext;
    }
};

int main()  {
    ColumnCipher cipher;
    
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
        
        string ciphertext = cipher.encryption(plaintext, key);
        cout << "Ciphertext: " << ciphertext << "\n";

        string decrypted = cipher.decryption(ciphertext, key);
        cout << "Decrypted Text: " << decrypted << "\n\n";
    }
}