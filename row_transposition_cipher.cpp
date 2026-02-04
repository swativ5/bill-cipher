#include <bits/stdc++.h>
using namespace std;

class RowCipher  {
    public:
    string encryption(string plaintext, string key)    {
        vector<int> keyorder;
        for (char c: key)   {
            if (c == ' ')   {
                continue;
            }
            keyorder.push_back(c - '0');
        }

        int m = keyorder.size();
        int n = ceil(plaintext.size() / m);
        n++;
    
        vector<vector<char>> grid(m, vector<char>(n, ' '));
        int idx = 0;
        for (int col = 0; col < n; col++)   {
            for (int row = 0; row < m; row++)   {
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
        for (int rowi = 0; rowi < m; rowi++)    {
            int row = keyorder[rowi] - 1;
            for (int col = 0; col < n; col++)   {
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

        int m = keyorder.size();
        int n = ciphertext.size() / m;

        vector<vector<char>> grid(m, vector<char>(n, ' '));
        
        int idx = 0;
        for (int rowi = 0; rowi < m; rowi++)    {
            int row = keyorder[rowi] - 1;
            for (int col = 0; col < n; col++)   {
                grid[row][col] = ciphertext[idx++];
            }
        }
        
        string decrypted = "";
        for (int col = 0; col < n; col++)   {
            for (int row = 0; row < m; row++)   {
                decrypted += grid[row][col];
            }
        }
        return decrypted;
    }
};

int main()  {
    RowCipher cipher;
    
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