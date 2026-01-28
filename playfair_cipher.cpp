#include <bits/stdc++.h>
using namespace std;

class PlayfairCipher  {
    public:

    pair<vector<vector<char>>, unordered_map<char, pair<int, int>>> create_playfair_mat(string key)    {
        vector<vector<char>> playfairmat(5, vector<char>(5, 'x'));
        unordered_set<char> visited;
        unordered_map<char, pair<int, int>> cache;
        int i = 0, j = 0;
        for (char c: key) {
            c = tolower(c);
            if (c < 'a' || c > 'z') {
                continue;
            }
            if (c == 'i' || c == 'j')   {
                if (visited.count('i')) {
                    continue;
                }
                c = 'i';
            } else if (visited.count(c)) {
                continue;
            }
            
            if (j > 4) {
                j = 0;
                i++;
            }
            
            playfairmat[i][j] = c;
            cache[c] = {i, j};
            
            if (c == 'i') {
                cache['j'] = {i, j};
                visited.insert('i');
                visited.insert('j');
            } else {
                visited.insert(c);
            }
            
            j++;
        }
        for (int cc = 97; cc <= 122; cc++) {
            char c = (char) cc;
            
            if (c == 'j' && visited.count('i')) {
                continue;
            }
            if (c == 'i' && visited.count('i')) {
                continue;
            }
            if (visited.count(c)) {
                continue;
            }
            
            if (j > 4) {
                j = 0;
                i++;
            }
            
            playfairmat[i][j] = c;
            cache[c] = {i, j};
            
            if (c == 'i') {
                cache['j'] = {i, j};
                visited.insert('i');
                visited.insert('j');
            } else {
                visited.insert(c);
            }
            
            j++;
        }
        return {playfairmat, cache};
    }

    pair<string, vector<vector<char>>> encryption(string plaintext, string key)    {
        // prepare plaintext
        string filtered_plaintext = "";
        for (char c: plaintext) {
            c = tolower(c);
            if (c < 'a' || c > 'z') {
                continue;
            }
            if (c == 'j') {
                c = 'i';
            }
            filtered_plaintext += c;
        }
        plaintext = filtered_plaintext;
        pair<vector<vector<char>>, unordered_map<char, pair<int, int>>> playfair_data = create_playfair_mat(key);    

        vector<vector<char>> playfairmat = playfair_data.first;
        unordered_map<char, pair<int, int>> cache = playfair_data.second;
        
        cout << "Playfair Matrix:\n";
        for (auto line: playfairmat)    {
            for (auto c: line)   {
                cout << c << " ";
            }
            cout << "\n";
        }

        vector<pair<char, char>> digrams;
        for (int idx = 0; idx < plaintext.size(); idx++) {
            char first = plaintext[idx];
            char second;
            if (idx == plaintext.size() - 1) {
                second = 'x';
            } else {
                second = plaintext[idx + 1];
            }
            if (first == second)   {
                digrams.push_back({first, 'x'});
            } else {
                digrams.push_back({first, second});
                idx++;
            }
        }

        cout << "Digrams:\n";
        for (auto p: digrams) {
            cout << p.first << p.second << " ";
        }
        cout << "\n";

        vector<pair<char, char>> encrypted_diagrams;
        for (auto p: digrams) {
            pair<int, int> pair1 = cache[p.first];
            pair<int, int> pair2 = cache[p.second];

            if (pair1.first == pair2.first)    {
                // same row
                int direction = (pair1.second < pair2.second) ? 1 : -1;
                if (pair1.second == 4 && pair2.second == 0) {
                    direction = 1;
                }
                encrypted_diagrams.push_back({playfairmat[pair1.first][(pair1.second + direction + 5) % 5], playfairmat[pair2.first][(pair2.second + direction + 5) % 5]});
            } else if (pair1.second == pair2.second) {
                // same column
                int direction = (pair1.first < pair2.first) ? 1 : -1;
                if (pair1.first == 4 && pair2.first == 0) {
                    direction = -1;
                }
                encrypted_diagrams.push_back({playfairmat[(pair1.first + direction + 5) % 5][pair1.second], playfairmat[(pair2.first + direction + 5) % 5][pair2.second]});
            } else {
                // rectangle swap
                encrypted_diagrams.push_back({playfairmat[pair1.first][pair2.second], playfairmat[pair2.first][pair1.second]});
            }
        }
        string ciphertext = "";
        for (auto p: encrypted_diagrams) {
            ciphertext += p.first;
            ciphertext += p.second;
            ciphertext += " ";
        }
        return {ciphertext, playfairmat};
    }

    string decryption(string ciphertext, vector<vector<char>> playfairmat, unordered_map<char, pair<int, int>> cache)    {
        // remove spaces and prepare ciphertext
        string filtered_ciphertext = "";
        for (char c: ciphertext) {
            c = tolower(c);
            if (c >= 'a' && c <= 'z') {
                filtered_ciphertext += c;
            }
        }
        
        // split into digrams
        vector<pair<char, char>> digrams;
        for (int idx = 0; idx < filtered_ciphertext.size(); idx += 2) {
            if (idx + 1 < filtered_ciphertext.size()) {
                digrams.push_back({filtered_ciphertext[idx], filtered_ciphertext[idx + 1]});
            }
        }
        
        cout << "Encrypted Digrams:\n";
        for (auto p: digrams) {
            cout << p.first << p.second << " ";
        }
        cout << "\n";
        
        // decrypt each digram
        vector<pair<char, char>> decrypted_diagrams;
        for (auto p: digrams) {
            pair<int, int> pair1 = cache[p.first];
            pair<int, int> pair2 = cache[p.second];

            if (pair1.first == pair2.first)    {
                // same row - move left (opposite of encryption)
                int direction = (pair1.second < pair2.second) ? 1 : -1;
                if (pair1.second == 0 && pair2.second == 4) {
                    direction = 1;
                }
                decrypted_diagrams.push_back({playfairmat[pair1.first][(pair1.second + direction + 5) % 5], playfairmat[pair2.first][(pair2.second + direction + 5) % 5]});
            } else if (pair1.second == pair2.second) {
                // same column - move up (opposite of encryption)
                int direction = (pair1.first < pair2.first) ? -1 : 1;
                if (pair1.first == 0 && pair2.first == 4) {
                    direction = -1;
                }
                decrypted_diagrams.push_back({playfairmat[(pair1.first + direction + 5) % 5][pair1.second], playfairmat[(pair2.first + direction + 5) % 5][pair2.second]});
            } else {
                // rectangle swap - same as encryption
                decrypted_diagrams.push_back({playfairmat[pair1.first][pair2.second], playfairmat[pair2.first][pair1.second]});
            }
        }
        
        string plaintext = "";
        for (auto p: decrypted_diagrams) {
            plaintext += p.first;
            plaintext += p.second;
            plaintext += " ";
        }
        return plaintext;
    }
};

int main()  {
    PlayfairCipher cipher;

    int n;
    cout << "Enter number of cases: ";
    cin >> n;
    cout << "\n";
    while (n)
    {
        string plaintext, key;
        cout << "Enter Plaintext: ";
        cin.ignore();
        getline(cin, plaintext);
        cout << "Enter Key: ";
        getline(cin, key);
        
        // Encryption
        pair<string, vector<vector<char>>> result = cipher.encryption(plaintext, key);
        string ciphertext = result.first;
        vector<vector<char>> playfairmat = result.second;
        cout << "Ciphertext: " << ciphertext << "\n\n";
        
        // Decryption
        pair<vector<vector<char>>, unordered_map<char, pair<int, int>>> playfair_data = cipher.create_playfair_mat(key);
        unordered_map<char, pair<int, int>> cache = playfair_data.second;
        string decrypted = cipher.decryption(ciphertext, playfairmat, cache);
        cout << "Decrypted Text: " << decrypted << "\n\n";
        
        n--;
    }
    
}