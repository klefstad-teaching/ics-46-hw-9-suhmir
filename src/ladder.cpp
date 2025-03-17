#include "ladder.h"
#include <algorithm>
#include <iterator>

// Report an error using cerr with the provided tokens and message.
void report_error(const string& token1, const string& token2, const string& message) {
    cerr << "Error: " << message << ": " << token1 << token2 << endl;
}

// Load words from a file into a set (dictionary) using STL algorithms.
void load_dictionary(set<string>& dictionary, const string& filename) {
    ifstream inputStream(filename);
    if (!inputStream) {
        cerr << "Cannot open file: " << filename << endl;
        exit(1);
    }
    // Use istream_iterator to insert words directly into the set.
    dictionary.insert(istream_iterator<string>(inputStream),
                      istream_iterator<string>());
    inputStream.close();
}

// Check if two strings are within a specified edit distance using iterators.
bool within_edit_distance(const string& s1, const string& s2, int maxEdits) {
    auto it1 = s1.begin(), it2 = s2.begin();
    int differences = 0;
    while (it1 != s1.end() && it2 != s2.end()) {
        if (*it1 != *it2) {
            if (++differences > maxEdits)
                return false;
            if (s1.size() > s2.size())
                ++it1;
            else if (s1.size() < s2.size())
                ++it2;
            else {
                ++it1;
                ++it2;
            }
        } else {
            ++it1;
            ++it2;
        }
    }
    differences += distance(it1, s1.end()) + distance(it2, s2.end());
    return differences <= maxEdits;
}

// Determine if two words are adjacent (differ by at most one edit).
bool is_adjacent(const string& firstWord, const string& secondWord) {
    return within_edit_distance(firstWord, secondWord, 1);
}

// Generate a word ladder from startWord to targetWord using BFS.
// This version uses a vector of vectors as a queue alternative.
vector<string> generate_word_ladder(const string& startWord, const string& targetWord, const set<string>& dictionary) {
    if (startWord == targetWord)
        return {};
    
    vector<vector<string>> ladders;  // Each element is a word ladder (path)
    ladders.push_back({startWord});
    set<string> visited;
    visited.insert(startWord);

    size_t index = 0; // Instead of a queue, we iterate over our vector.
    while (index < ladders.size()) {
        vector<string> currentLadder = ladders[index];
        string lastWord = currentLadder.back();

        for (const string& candidate : dictionary) {
            if (is_adjacent(lastWord, candidate) && visited.find(candidate) == visited.end()) {
                vector<string> newLadder = currentLadder;
                newLadder.push_back(candidate);
                if (candidate == targetWord)
                    return newLadder;
                ladders.push_back(newLadder);
                visited.insert(candidate);
            }
        }
        ++index;
    }
    return {};
}

// Print the generated word ladder using ostream_iterator for a clean output.
void print_word_ladder(const vector<string>& ladderSequence) {
    if (ladderSequence.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    if (ladderSequence.size() > 1) {
        // Copy all but the last element with a space delimiter.
        copy(ladderSequence.begin(), ladderSequence.end() - 1, ostream_iterator<string>(cout, " "));
    }
    // Print the last word (without an extra space).
    cout << ladderSequence.back() << endl;
}

#define my_assert(expr) { cout << #expr << ((expr) ? " passed" : " failed") << endl; }

// Verify the word ladder implementation with various test cases.
void verify_word_ladder() {
    set<string> dictionary;

    load_dictionary(dictionary, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", dictionary).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", dictionary).size() == 6);
    my_assert(generate_word_ladder("code", "data", dictionary).size() == 6);
    my_assert(generate_word_ladder("work", "play", dictionary).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", dictionary).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", dictionary).size() == 4);
}
