#include "ladder.h"
#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <vector>
#include <sstream>

using namespace std;

void error(string firstToken, string secondToken, string errorMessage) {
    cerr << "Error: " << errorMessage << "  " << firstToken << secondToken << endl;
}

void load_words(set<string>& dictionary, const string& filename) {
    ifstream inFile(filename);  // Open the file.
    if (!inFile) {
        cerr << "Cannot open file: " << filename << endl;
        exit(1);
    }
    string currentLine;
    // Read each line from the file.
    while (getline(inFile, currentLine)) {
        // Use a string stream to extract words from the line.
        istringstream lineStream(currentLine);
        string token;
        while (lineStream >> token) {
            dictionary.insert(token);
        }
    }
    inFile.close();
}

bool edit_distance_within(const string& strA, const string& strB, int maxAllowed) {
    int lenA = strA.length(), lenB = strB.length();
    if (abs(lenA - lenB) > 1)
        return false;
    
    int posA = 0;
    int posB = 0;
    int differences = 0;
    while (posA < lenA && posB < lenB) {
        if (strA[posA] != strB[posB]) {
            if (++differences > maxAllowed)
                return false;
            if (lenA > lenB)
                posA++;
            else if (lenA < lenB)
                posB++;
            else {
                posA++;
                posB++;
            }
        } else {
            posA++;
            posB++;
        }
    }
    return differences + (lenA - posA) + (lenB - posB) <= maxAllowed;
}

bool is_adjacent(const string& firstWord, const string& secondWord) {
    if (edit_distance_within(firstWord, secondWord, 1)) {
        return true;
    } else {
        return false;
    }
}

vector<string> generate_word_ladder(const string& startWord, const string& targetWord, const set<string>& dictionary) {
    if (startWord == targetWord)
        return {};
    
    queue<vector<string>> ladderQueue;
    set<string> seenWords;
    ladderQueue.push({startWord});
    seenWords.insert(startWord);

    while (!ladderQueue.empty()) {
        vector<string> currentLadder = ladderQueue.front();
        ladderQueue.pop();
        string lastWord = currentLadder.back();

        for (const string& candidate : dictionary) {
            if (is_adjacent(lastWord, candidate) && !seenWords.count(candidate)) {
                vector<string> nextLadder = currentLadder;
                nextLadder.push_back(candidate);
                if (candidate == targetWord)
                    return nextLadder;
                ladderQueue.push(nextLadder);
                seenWords.insert(candidate);
            }
        }
    }
    return {};
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    size_t pos = 0;
    while (pos < ladder.size()) {
        cout << ladder[pos] << " ";
        ++pos;
    }
    cout << endl;
}
