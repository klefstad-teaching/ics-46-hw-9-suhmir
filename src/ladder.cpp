#include "ladder.h"

// Function to report an error message.
// Combines two tokens with a descriptive message and outputs to standard error.
void report_error(string token1, string token2, string message) {
    cerr << "Error: " << message << ":  " << token1 << token2 << endl;
}

// Function to load words from a file into a set (dictionary).
// The set ensures each word is unique.
void load_word_set(set<string> &dictionary, const string& filename) {
    ifstream inputFile(filename);
    // Check if the file was successfully opened.
    if (!inputFile) {
        cerr << "Cannot open file: " << filename << endl;
        exit(1); // Exit the program if the file cannot be opened.
    }
    string currentWord;
    // Read words one by one and insert them into the dictionary.
    while (inputFile >> currentWord) {
        dictionary.insert(currentWord);
    }
    inputFile.close(); // Always close the file when done.
}

// Function to check if two strings are within a given edit distance.
// This version is optimized for an edit distance of 1 (or more, based on maxDiff).
bool within_edit_distance(const string& s1, const string& s2, int maxDiff) {
    int len1 = s1.length(), len2 = s2.length();
    // If the length difference is more than 1, they can't be within the edit distance.
    if (abs(len1 - len2) > 1)
        return false;

    int idx1 = 0;       // Index for s1
    int idx2 = 0;       // Index for s2
    int diffCount = 0;  // Counter for differences found

    // Traverse both strings until we reach the end of one.
    while (idx1 < len1 && idx2 < len2) {
        // If characters don't match, we have a potential edit.
        if (s1[idx1] != s2[idx2]) {
            // Increase the difference count and check if we exceeded the allowed differences.
            if (++diffCount > maxDiff)
                return false;
            // Depending on which string is longer, increment the index of the longer string.
            if (len1 > len2)
                idx1++;
            else if (len1 < len2)
                idx2++;
            else {
                // If both strings are equal in length, increment both indices.
                idx1++;
                idx2++;
            }
        } else {
            // Characters match, simply move to the next ones.
            idx1++;
            idx2++;
        }
    }
    // Add any remaining characters (if one string was longer) to the difference count.
    return diffCount + (len1 - idx1) + (len2 - idx2) <= maxDiff;
}

// Helper function to check if two words are adjacent (i.e., differ by at most one edit).
bool are_adjacent(const string& firstWord, const string& secondWord) {
    return within_edit_distance(firstWord, secondWord, 1);
}

// Function to build a word ladder from startWord to targetWord using a dictionary of words.
// A word ladder is a sequence where each adjacent pair of words differs by one letter.
vector<string> build_word_ladder(const string& startWord, const string& targetWord, const set<string>& dictionary) {
    // If the start and target words are the same, no ladder is needed.
    if (startWord == targetWord) {
        return {}; // Return an empty vector.
    } else {
        // Queue to hold the ladders (each ladder is a vector of strings).
        queue<vector<string>> ladderQueue;
        // Set to track words that have been seen to avoid cycles.
        set<string> seenWords;

        // Start the ladder with the initial word.
        ladderQueue.push({startWord});
        seenWords.insert(startWord);

        // Perform a breadth-first search (BFS) for the word ladder.
        while (!ladderQueue.empty()) {
            // Get the current ladder (path) from the front of the queue.
            vector<string> currentLadder = ladderQueue.front();
            ladderQueue.pop();
            // Get the last word in the current ladder.
            string lastWord = currentLadder.back();

            // Iterate through all words in the dictionary.
            for (const string& candidate : dictionary) {
                // Check if the candidate word is adjacent to the last word and hasn't been visited.
                if (are_adjacent(lastWord, candidate) && !seenWords.count(candidate)) {
                    // Create a new ladder by appending the candidate word.
                    vector<string> nextLadder = currentLadder;
                    nextLadder.push_back(candidate);
                    // If the candidate is the target word, we've found our ladder.
                    if (candidate == targetWord)
                        return nextLadder;
                    // Otherwise, add the new ladder to the queue and mark the word as seen.
                    ladderQueue.push(nextLadder);
                    seenWords.insert(candidate);
                }
            }
        }
        // If no ladder is found, return an empty vector.
        return {};
    }
}

// Function to display the found word ladder.
// Prints the words in sequence separated by spaces.
void display_word_ladder(const vector<string>& ladderSequence) {
    // If the ladder is empty, indicate that no ladder was found.
    if (ladderSequence.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    // Use a while loop to iterate through the ladder sequence.
    size_t pos = 0;
    while (pos < ladderSequence.size()) {
        cout << ladderSequence[pos];
        // Only print a space if this isn't the last word.
        if (pos < ladderSequence.size() - 1)
            cout << " ";
        ++pos;
    }
    cout << endl;
}

// Macro for simple assertion testing.
// Prints whether an expression passed or failed.
#define my_assert(expr) { cout << #expr << ((expr) ? " passed" : " failed") << endl; }

// Function to test the word ladder generation with several assertions.
void test_word_ladder() {
    set<string> dictionary;

    // Load words from "words.txt" into the dictionary.
    load_word_set(dictionary, "words.txt");

    // Test cases: assert that the word ladder generated has the expected size.
    my_assert(build_word_ladder("cat", "dog", dictionary).size() == 4);
    my_assert(build_word_ladder("marty", "curls", dictionary).size() == 6);
    my_assert(build_word_ladder("code", "data", dictionary).size() == 6);
    my_assert(build_word_ladder("work", "play", dictionary).size() == 6);
    my_assert(build_word_ladder("sleep", "awake", dictionary).size() == 8);
    my_assert(build_word_ladder("car", "cheat", dictionary).size() == 4);
}
