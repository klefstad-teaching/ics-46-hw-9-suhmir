#include "ladder.h"
#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <vector>
using namespace std;

// Report an error by outputting a message with two tokens.
void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << "  " << word1 << word2 << endl;
}

// Load words from a file into a set. The set 'word_list' serves as the dictionary.
void load_words(set<string> &word_list, const string& file_name) {
    ifstream file(file_name);  // Open the file.
    if (!file) {
        // If the file can't be opened, output an error and exit.
        cerr << "Cannot open file: " << file_name << endl;
        exit(1);
    }
    string word;
    // Read words from the file and insert them into the set.
    while (file >> word) {
        word_list.insert(word);
    }
    file.close(); // Close the file when done.
}

// Check if two strings are within a specified edit distance.
// This is used to determine if one word can transform into another with at most 'd' edits.
bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.length(), len2 = str2.length();
    // If the difference in lengths is greater than 1, the edit distance cannot be within d.
    if (abs(len1 - len2) > 1)
        return false;
    
    int i = 0;
    int j = 0;
    int diff = 0;
    // Traverse both strings simultaneously.
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            // Increment the difference count if characters differ.
            if (++diff > d)
                return false;
            // Adjust indices based on the relative lengths of the strings.
            if (len1 > len2)
                i++;
            else if (len1 < len2)
                j++;
            else {
                i++;
                j++;
            }
        } else {
            // If characters match, move to the next characters.
            i++;
            j++;
        }
    }
    // Account for any remaining characters in the longer string.
    return diff + (len1 - i) + (len2 - j) <= d;
}

// Determine if two words are adjacent (i.e., can be transformed into one another with at most one edit).
bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

// Generate a word ladder from 'begin_word' to 'end_word' using the dictionary.
// A word ladder is a sequence of words where each pair of adjacent words differ by one letter.
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    // If the starting and ending words are the same, return an empty vector.
    if (begin_word == end_word)
        return {};
    
    // Use a queue for breadth-first search (BFS). Each element in the queue is a vector representing a word ladder.
    queue<vector<string>> l_queue;
    // Keep track of visited words to avoid cycles.
    set<string> visited;
    l_queue.push({begin_word});
    visited.insert(begin_word);

    // Process the queue until it is empty.
    while (!l_queue.empty()) {
        vector<string> ladder = l_queue.front();
        l_queue.pop();
        // Get the last word in the current ladder.
        string last = ladder.back();

        // Try every word in the dictionary as a candidate for the next step.
        for (const string& word : word_list) {
            // If the candidate is adjacent and hasn't been visited:
            if (is_adjacent(last, word) && !visited.count(word)) {
                // Create a new ladder by appending the candidate word.
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                // If we've reached the end word, return the ladder.
                if (word == end_word)
                    return new_ladder;
                // Otherwise, push the new ladder onto the queue for further exploration.
                l_queue.push(new_ladder);
                // Mark the word as visited.
                visited.insert(word);
            }
        }
    }
    // Return an empty vector if no ladder is found.
    return {};
}

// Print the word ladder. If no ladder exists, output an appropriate message.
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    // Print each word in the ladder separated by a space.
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i < ladder.size() - 1)
            cout << " ";
    }
    cout << endl;
}
