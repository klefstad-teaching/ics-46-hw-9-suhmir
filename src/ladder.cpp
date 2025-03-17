#include "ladder.h"
#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <vector>
using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << "  " << word1 << word2 << endl;
}

void load_words(set<string> &word_list, const string& file_name) {
    ifstream file(file_name);  // Open the file.
    if (!file) {
        cerr << "Cannot open file: " << file_name << endl;
        exit(1);
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.length(), len2 = str2.length();
    if (abs(len1 - len2) > 1)
        return false;
    
    int i = 0;
    int j = 0;
    int diff = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            if (++diff > d)
                return false;
            if (len1 > len2)
                i++;
            else if (len1 < len2)
                j++;
            else {
                i++;
                j++;
            }
        } else {
            i++;
            j++;
        }
    }
    return diff + (len1 - i) + (len2 - j) <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word)
        return {};
    
    queue<vector<string>> l_queue;
    set<string> visited;
    l_queue.push({begin_word});
    visited.insert(begin_word);

    while (!l_queue.empty()) {
        vector<string> ladder = l_queue.front();
        l_queue.pop();
        string last = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last, word) && !visited.count(word)) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word)
                    return new_ladder;
                l_queue.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    return {};
}

// Modified print_word_ladder: prints a space after every word, ensuring a trailing space.
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i] << " ";
    }
    cout << endl;
}
