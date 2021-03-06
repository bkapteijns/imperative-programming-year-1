#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

// Mario Patroza s1028653
// Bram Kapteijns s1052111

// Dear SA, we did not exactly understand the assignment,
// as we don't have a read_word function in the mandatory assignment.
// But we interpreted is as:
//  Print every word in an input and filter the words on garbage characters
//  And make -- into a space

void fileToString(ifstream &infile, string &input)
{ // preconditions:
  assert(!infile.is_open());
  // postconditions: we will have opened a file and put the contents into a string

  typedef char InputCharacter;
  typedef string InputText;

  InputText fileName;
  InputCharacter c;

  cin.clear();
  cout << "What is the name of the file?" << endl;
  getline(cin, fileName);
  infile.open(fileName);
  infile.get(c);
  while (!infile.fail())
  {
    input = input + c;
    infile.get(c);
  }
}

void inputToString(string &input)
{
  // preconditions:
  assert(input.length() == 0);
  // postconditions: we will have put the console input into the input variable
  typedef char TemporaryCharacter;

  TemporaryCharacter temp;

  cout << "Write your own text here (without enters):" << endl;
  cin.get(temp);
  getline(cin, input);
  input = temp + input;
  return;
}

bool isLetter(char letter)
{ // preconditions:
  assert(true);
  // postconditions: we will have determined if the character is a letter
  typedef int Letter;
  Letter c = static_cast<int>(letter);
  return (c == 39 || c >= 65 && c <= 90 || c >= 97 && c <= 122);
}

int wordAmount(string &input)
{ // preconditions:
  assert(input.length() > 0);
  // postconditions: we will have computed the amount of words in an input
  typedef int Length;
  typedef int Counter;
  Length wordLength = 1;
  for (Counter i = 0; i < input.length(); i++)
  {
    if (input[i] == '-' && input[i + 1] == '-')
    {
      input[i] = ' ';
      input.erase(input.begin() + i + 1);
    }
    if (i >= 1)
    {
      if (input[i] == ' ')
      {
        wordLength++;
      }
    }
  }
  return wordLength;
}

void array_of_query(string searchWords[], int length, string input)
{ //preconditions
  assert(length > 0);
  //postconditions: we will have created an array of words from the query
  typedef int Counter;

  Counter j = 0;

  for (Counter i = 0; i < input.length(); i++)
  {
    if (input[i] == ' ')
    {
      j++;
    }
    else
    {
      searchWords[j] = searchWords[j] + input[i];
    }
  }

  return;
}

void read_word(string word)
{ // preconditions:
  assert(true);
  // postconditions: we will have printed the trimmed word (so with only letters)
  if (word[word.length() - 1] == '\'' && !isLetter(word[word.length() - 2]))
  {
    word.erase(word.begin() + word.length() - 1);
  }
  if (word.length() == 0 || word == "'")
  {
    return;
  }
  while (!isLetter(word[0]))
  {
    word.erase(word.begin());
    if (word.length() == 0)
    {
      return;
    }
  }
  while (!isLetter(word[word.length() - 1]))
  {
    word.erase(word.begin() + word.length() - 1);
    if (word.length() == 0)
    {
      return;
    }
  }

  cout << word << ' ';
  return;
}

void filterInput(string input)
{ //preconditions:
  assert(input.length() > 0);
  //postconditions: we will have printed out the filtered words
  typedef int Amount;
  typedef string Word;
  typedef int Counter;
  Amount amount_of_words = wordAmount(input);
  Word allWords[amount_of_words];
  for (Counter i = 0; i < amount_of_words; i++)
  {
    allWords[i] = "";
  }
  array_of_query(allWords, amount_of_words, input);
  for (Counter i = 0; i < amount_of_words; i++)
  {
    read_word(allWords[i]);
  }
  cout << endl;
}

int main()
{
  typedef char InputCharacter;
  typedef ifstream InputFile;
  typedef string Text;

  InputFile infile;
  InputCharacter c;
  Text input = "";

  while (true)
  {
    cout << "Do you want to open a file? (y / n)" << endl;
    cin.clear();
    cin.get(c);
    if (c == 'y' || c == 'Y')
    {
      fileToString(infile, input);
      infile.clear();
      infile.close();
    }
    else
    {
      inputToString(input);
      filterInput(input);
    }

    input = "";
    cin.clear();
  }
  cin >> input;
  return 1;
}
