#include "ladder.h"
#include <algorithm>

bool edit_distance_within(const string& str1, const string& str2, int maxDistance) {
    int len1 = str1.size(), len2 = str2.size();
    if (abs(len1 - len2) > maxDistance) return false;

    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));
    for (int i = 0; i <= len1; ++i) dp[i][0] = i;
    for (int j = 0; j <= len2; ++j) dp[0][j] = j;

    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min(min(dp[i - 1][j - 1], dp[i][j - 1]), dp[i - 1][j]);
            }
        }
    }

    return dp[len1][len2] <= maxDistance;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& startWord, const string& endWord, const set<string>& dictionary) {
    queue<vector<string>> ladderQueue;
    set<string> visitedWords;

    ladderQueue.push({startWord});
    visitedWords.insert(startWord);

    while (!ladderQueue.empty()) {
        vector<string> currentLadder = ladderQueue.front();
        ladderQueue.pop();

        string currentWord = currentLadder.back();
        for (const string& candidate : dictionary) {
            if (is_adjacent(currentWord, candidate) && !visitedWords.count(candidate)) {
                vector<string> newLadder = currentLadder;
                newLadder.push_back(candidate);

                if (candidate == endWord) {
                    return newLadder;
                }

                ladderQueue.push(newLadder);
                visitedWords.insert(candidate);
            }
        }
    }

    return {};
}

void load_words(set<string>& dictionary, const string& fileName) {
    ifstream inputFile(fileName);
    string word;
    while (inputFile >> word) {
        dictionary.insert(word);
    }
    inputFile.close();
}

void print_word_ladder(const vector<string>& ladder) {
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i + 1 < ladder.size()) cout << " -> ";
    }
    cout << "\n";
}

void error(string startWord, string endWord, string message) {
    cerr << "Error: " << message << " [" << startWord << ", " << endWord << "]\n";
}
