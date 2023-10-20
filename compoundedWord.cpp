
#include <bits/stdc++.h>
using namespace std;

class TrieNode {
public:
  char data;
  bool isTerminalNode;
  TrieNode *children[26];

  TrieNode(char ch) {
    data = ch;
    isTerminalNode = false;
    for (int i = 0; i < 26; i++) {
      children[i] = nullptr;
    }
  }
};

void insertWord(TrieNode *root, const string &word) {
  TrieNode *current = root;
  for (char c : word) {
    int index = c - 'a';
    if (!current->children[index]) {
      current->children[index] = new TrieNode(c);
    }
    current = current->children[index];
  }
  current->isTerminalNode = true;
}


bool searchLongestCompoundWord(TrieNode *root, const string &word, int index, int count) {
  TrieNode *current = root;
  for (int i = index; i < word.length(); i++) {
    int letterIndex = word[i] - 'a';
    if (!current->children[letterIndex]) {
      return false;
    }
    current = current->children[letterIndex];
    if (current->isTerminalNode) {
      if (i == word.length() - 1) {
        return count >= 1; // Compound word requires at least one complete word before it
      }
      if (searchLongestCompoundWord(root, word, i + 1, count + 1)) {
        return true;
      }
    }
  }
  return false;
}


string findLongestCompoundWord(const vector<string> &words) {
  TrieNode *root = new TrieNode(' ');
  for (const string &word : words) {
    if (!word.empty()) {
      insertWord(root, word);
    }
  }
  string longestCompoundWord="";
  for (const string &word : words) {
    if (searchLongestCompoundWord(root, word, 0, 0) &&
        word.length() > longestCompoundWord.length()) {
      longestCompoundWord = word;
    }
  }
  return longestCompoundWord;
}

int main() {
  clock_t start, end;
  start = clock();
  ifstream f1;
  f1.open("Input_02.txt", ios::in);

  vector<string> wordList;
  string line;

  while (f1 >> line) {
    wordList.push_back(line);
  }

  string longestCompoundWord = findLongestCompoundWord(wordList);

  if (!longestCompoundWord.empty()) {
    cout << "Longest compounded word: " << longestCompoundWord << endl;
  } else {
    cout << "No compounded word found." << endl;
  }

  remove(wordList.begin(), wordList.end(),longestCompoundWord);
  string longest2CompoundWord = findLongestCompoundWord(wordList);
  cout << "Second longest compounded word is " << longest2CompoundWord << endl;
  end = clock();
  double timetaken = double(end - start) / double(CLOCKS_PER_SEC);
  cout << "Time taken to process the file is " << timetaken << setprecision(4)
       << "sec" << endl;
  return 0;
}
