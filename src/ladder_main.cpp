#include "ladder.h"
#include <iostream>
#include <set>
#include <vector>
#include <string>

int main() {
    std::string startWord, endWord;
    std::cout << "Enter start word: ";
    std::cin >> startWord;
    std::cout << "Enter end word: ";
    std::cin >> endWord;

    if (startWord == endWord) {
        error(startWord, endWord, "Start and end words must be different");
        return 1;
    }

    std::set<std::string> dictionary;
    load_words(dictionary, "words.txt");

    std::vector<std::string> wordLadder = generate_word_ladder(startWord, endWord, dictionary);

    if (wordLadder.empty()) {
        std::cout << "No ladder found from " << startWord << " to " << endWord << ".\n";
    } else {
        print_word_ladder(wordLadder);
    }

    return 0;
}
