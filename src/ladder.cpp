#include "ladder.h"

void display_error(const string& first_word, const string& second_word, const string& message) {
    cerr << "Error: " << message << " [" << first_word << " " << second_word << "]" << endl;
}


void load_word_list(set<string> &word_set, const string& filename) {
    ifstream file_stream(filename);
    if (!file_stream) {
        cerr << "Cannot open file: " << filename << endl;
        exit(1);
    }
    string current_word;
    while (file_stream >> current_word) {
        word_set.insert(current_word);
    }
    file_stream.close();
}

bool is_within_edit_distance(const string& first_str, const string& second_str, int max_distance) {
    int length1 = first_str.length(), length2 = second_str.length();
    if (abs(length1 - length2) > 1) 
        return false; 

    int index1 = 0;
    int index2 = 0;
    int differences = 0;
    while (index1 < length1 && index2 < length2) {
        if (first_str[index1] != second_str[index2]) {
            if (++differences > max_distance) 
                return false;
            if (length1 > length2) 
                index1++;
            else if (length1 < length2) 
                index2++;
            else {
                index1++; 
                index2++; 
            }
        } else {
            index1++; 
            index2++;
        }
    }
    return differences + (length1 - index1) + (length2 - index2) <= max_distance;
}

bool are_adjacent(const string& word_one, const string& word_two) {
    if (is_within_edit_distance(word_one, word_two, 1)) {
        return true;
    } else {
        return false;
    }
}

vector<string> build_word_ladder(const string& start_word, const string& target_word, const set<string>& word_set) {
    if (start_word == target_word) 
        return {}; 
    queue<vector<string>> ladder_queue;
    set<string> seen_words;
    ladder_queue.push({start_word});
    seen_words.insert(start_word);

    while (!ladder_queue.empty()) {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = current_ladder.back();

        for (const string& word : word_set) {
            if (are_adjacent(last_word, word) && !seen_words.count(word)) {
                vector<string> next_ladder = current_ladder;
                next_ladder.push_back(word);
                if (word == target_word) 
                    return next_ladder;
                ladder_queue.push(next_ladder);
                seen_words.insert(word);
            }
        }
    }
    return {};
}

void display_word_ladder(const vector<string>& ladder_sequence) {
    if (ladder_sequence.empty()) {
        cout << "No word ladder found." << endl; 
        return;
    }
    cout << "Word ladder found: ";
    for (const auto& word : ladder_sequence) {
        cout << word << " "; // Always add a space after each word
    }
    cout << "\n";
}


#define assert_check(e) {cout << #e << ((e) ? " passed" : " failed") << endl;}

void test_word_ladder() {

    set<string> word_set;

    load_word_list(word_set, "words.txt");

    assert_check(build_word_ladder("cat", "dog", word_set).size() == 4);
    assert_check(build_word_ladder("marty", "curls", word_set).size() == 6);
    assert_check(build_word_ladder("code", "data", word_set).size() == 6);
    assert_check(build_word_ladder("work", "play", word_set).size() == 6);
    assert_check(build_word_ladder("sleep", "awake", word_set).size() == 8);
    assert_check(build_word_ladder("car", "cheat", word_set).size() == 4);
}