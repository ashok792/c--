#include <iostream>
#include <fstream>  //Lets your program read from and write to files.
#include <string>  //Provides the std::string type
#include <vector>  //grow or shrink in size automatically

struct Question {
    std::string text;
    std::string opts[4];   // A, B, C, D
    char correct;          // 'A'..'D'
};

int main() {
    std::ifstream in("questions.txt");
    if (!in) {
        std::cout << "questions.txt not found \n";
        return 1;
    }

    std::vector<Question> qs;
    std::string line;

    while (true) {
        Question q;
        // Read question line (skip empty lines)
        while (std::getline(in, line) && line.empty()) { /* skip */ }
        if (!in) break;               // no more questions
        q.text = line;                // question prompt

        // Read four option lines: A) .. D)
        for (int i = 0; i < 4; ++i) {
            if (!std::getline(in, line)) { std::cout << "Bad file format.\n"; return 2; }
            // Remove leading "X) " if present (basic)
            if (line.size() >= 3 && line[1] == ')' && line[2] == ' ') {
                q.opts[i] = line.substr(3);
            } else {
                q.opts[i] = line; // fall back if no prefix
            }
        }

        // Read ANSWER line like "ANSWER: B"
        if (!std::getline(in, line)) { std::cout << "Bad file format.\n"; return 2; }
        // Pick last non-space character and make uppercase (basic)
        char ans = 'A';
        for (int i = (int)line.size() - 1; i >= 0; --i) {
            if (!std::isspace(static_cast<unsigned char>(line[i]))) {
                ans = std::toupper(static_cast<unsigned char>(line[i]));
                break;
            }
        }
        if (ans < 'A' || ans > 'D') { std::cout << "Invalid answer in file.\n"; return 2; }
        q.correct = ans;

        qs.push_back(q);

        // Optional: consume one blank line between questions if present
        std::getline(in, line);
    }

    if (qs.empty()) {
        std::cout << "No questions found.\n";
        return 0;
    }

    std::cout << "Loaded " << qs.size() << " questions.\n\n";

    int correctCount = 0;
    int qno = 1;

    for (const auto& q : qs) {
        std::cout << "Q" << qno++ << ": " << q.text << "\n";
        std::cout << "  A) " << q.opts[0] << "\n";
        std::cout << "  B) " << q.opts[1] << "\n";
        std::cout << "  C) " << q.opts[2] << "\n";
        std::cout << "  D) " << q.opts[3] << "\n";

        char choice;
        while (true) {
            std::cout << "Your answer (A-D): ";
            std::string input;
            std::getline(std::cin, input);
            if (!input.empty()) {
                choice = std::toupper(static_cast<unsigned char>(input[0]));
                if (choice >= 'A' && choice <= 'D') break;
            }
            std::cout << "Please enter A, B, C, or D.\n";
        }

        if (choice == q.correct) {
            std::cout << "Correct!\n";
            ++correctCount;
        } else {
            std::cout << "Wrong. Correct answer: " << q.correct << "\n\n";
        }
    }

    std::cout << "Score: " << correctCount << " / " << (int)qs.size() << "\n";
    // Simple percentage (no <iomanip>)
    int percent = (correctCount * 100) / (int)qs.size();
    std::cout << "Percentage: " << percent << "%\n";
    return 0;
}
