#include <bits/stdc++.h>
using namespace std;

pair<vector<vector<char>>, unordered_map<char, pair<int, int>>> createmat(string key) {
    vector<vector<char>> mat(5, vector<char>(5, 'x'));
    int i = 0, j = 0;
    unordered_map<char, pair<int, int>> cache;

    for (char c : key) {
        c = tolower(c);
        if (!isalpha(c)) continue;
        if (c == 'j') c = 'i';       
        if (cache.count(c)) continue;

        mat[i][j] = c;
        cache[c] = {i, j};
        if (j == 4) { j = 0; i++; }
        else        { j++; }
    }

    for (char c = 'a'; c <= 'z'; c++) {
        if (c == 'j') continue;        
        if (cache.count(c)) continue;

        mat[i][j] = c;
        cache[c] = {i, j};
        if (j == 4) { j = 0; i++; }
        else        { j++; }
    }

    return {mat, cache};
}

string preprocess(string s) {
    string out = "";
    for (char c : s) {
        c = tolower(c);
        if (!isalpha(c)) continue;
        if (c == 'j') c = 'i';
        out += c;
    }
    return out;
}

vector<string> gendigrams(string plain) {
    plain = preprocess(plain);          
    vector<string> digrams;

    for (int idx = 0; idx < (int)plain.size(); idx++) {
        char f = plain[idx];
        char s;

        if (idx + 1 >= (int)plain.size()) {
            s = 'x';
        } else {
            s = plain[idx + 1];
        }

        if (f == s) {
            s = 'x';                   
        } else {
            idx++;                     
        }

        digrams.push_back(string(1, f) + string(1, s)); 
    }
    return digrams;
}

vector<string> encryption(string plain, string key) {
    pair<vector<vector<char>>, unordered_map<char, pair<int, int>>> matcache = createmat(key);
    vector<vector<char>> mat = matcache.first;
    unordered_map<char, pair<int, int>> cache = matcache.second;    
    
    vector<string> digrams = gendigrams(plain);

    cout << "Digrams: ";
    for (string s : digrams) cout << s << " ";
    cout << "\n";

    vector<string> encrypteddigrams;
    for (string str : digrams) {
        char f = str[0], s = str[1];
        int r1 = cache[f].first,  r2 = cache[s].first;
        int c1 = cache[f].second, c2 = cache[s].second;

        string edigram;
        if (r1 == r2) {
            edigram = string(1, mat[r1][(c1 + 1) % 5]) + string(1, mat[r2][(c2 + 1) % 5]);
        } else if (c1 == c2) {
            edigram = string(1, mat[(r1 + 1) % 5][c1]) + string(1, mat[(r2 + 1) % 5][c2]);
        } else {
            edigram = string(1, mat[r1][c2]) + string(1, mat[r2][c1]);
        }
        encrypteddigrams.push_back(edigram);
    }
    return encrypteddigrams;
}

vector<string> decryption(vector<string> encrypteddigrams, string key) {  
    pair<vector<vector<char>>, unordered_map<char, pair<int, int>>> matcache = createmat(key);
    vector<vector<char>> mat = matcache.first;
    unordered_map<char, pair<int, int>> cache = matcache.second;
    vector<string> decrypteddigrams;
    for (string str : encrypteddigrams) {
        char f = str[0], s = str[1];
        int r1 = cache[f].first,  r2 = cache[s].first;
        int c1 = cache[f].second, c2 = cache[s].second;

        string ddigram;
        if (r1 == r2) {
            ddigram = string(1, mat[r1][(c1 + 4) % 5]) + string(1, mat[r2][(c2 + 4) % 5]);
        } else if (c1 == c2) {
            ddigram = string(1, mat[(r1 + 4) % 5][c1]) + string(1, mat[(r2 + 4) % 5][c2]);
        } else {
            ddigram = string(1, mat[r1][c2]) + string(1, mat[r2][c1]);
        }
        decrypteddigrams.push_back(ddigram);
    }
    return decrypteddigrams;                            
}

int main() {
    string plain, key;

    cout << "Enter plaintext: ";
    getline(cin, plain);
    cout << "Enter key: ";
    getline(cin, key);                                   

    pair<vector<vector<char>>, unordered_map<char, pair<int, int>>> matcache = createmat(key);
    vector<vector<char>> mat = matcache.first;
    unordered_map<char, pair<int, int>> cache = matcache.second;

    cout << "\nPlayfair Matrix:\n";
    for (auto row : mat) {
        for (char c : row) cout << c << " ";
        cout << "\n";
    }
    cout << "\n";

    vector<string> cipher = encryption(plain, key);
    cout << "\nEncrypted digrams: ";
    for (string s : cipher) cout << s << " ";
    cout << "\n";

    vector<string> decrypted = decryption(cipher, key);  
    cout << "Decrypted digrams: ";
    for (string s : decrypted) cout << s << " ";
    cout << "\n";
}