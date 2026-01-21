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
        // to be implemented
        return "";
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
        pair<string, vector<vector<char>>> result = cipher.encryption(plaintext, key);
        plaintext = result.first;
        cout << "Ciphertext: " << plaintext << "\n\n";
        n--;
    }
    
}