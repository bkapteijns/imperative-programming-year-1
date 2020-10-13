#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

int find_word_index(string words[], int length, string word)
{ //preconditions
  assert(length > 0);
  //postconditions: we will have returned the index the word belongs
  for (int i = 0; i < length; i++)
  {
    if (words[i] == word)
    {
      return i;
    }
    else if (words[i] == "")
    {
      return i;
    }
  }
}

bool enter(string fileName, ifstream &infile)
{ //preconditions
  assert(!infile.is_open());
  //postconditions: we will have opened the infile
  infile.open(fileName);
  return infile.is_open();
}

void content(ifstream &infile, string fileName)
{ //preconditions:
  assert(infile.is_open());
  //postconditions: we will have printed all words
  typedef string InputWord;

  InputWord word;

  while (true)
  {
    infile >> word;
    if (infile.fail())
    {
      cout << endl;

      infile.clear();
      infile.close();
      infile.open(fileName);
      return;
    }
    cout << word << ' ';
  }
}

int count_total_words(ifstream &infile, string fileName)
{ //preconditions:
  assert(infile.is_open());
  //postconditions: we will have returned the amount of words
  typedef int Counter;
  typedef string InputWord;

  Counter wordAmount;
  InputWord word;

  while (true)
  {
    infile >> word;
    if (infile.fail())
    {
      infile.clear();
      infile.close();
      infile.open(fileName);
      return wordAmount;
    }
    wordAmount++;
  }
}

void array_of_words(string words[], int length, ifstream &infile)
{ // preconditions
  assert(infile.is_open());
  // postconditions: we will have created an array of all the words
  typedef string Word;

  Word input;

  infile >> input;
  for (int i = 0; i < length; i++)
  {
    words[i] = input;
    infile >> input;
  }
  return;
}

void count(string fileName, ifstream &infile)
{ //preconditions
  assert(infile.is_open());
  //postconditions: we will have printed the frequency of a certain word combo
  //the total words and the percentage of that word combo
  typedef int Counter;
  typedef string Word;
  typedef bool Correct;
  typedef char InputChar;

  const Counter wordAmount = count_total_words(infile, fileName);
  Word allWords[wordAmount];
  array_of_words(allWords, wordAmount, infile);
  Word inputWords[10];
  Counter inputIndex = 0;
  Counter countAmount = 0;
  Correct wordInWords = false;
  InputChar c;

  while (!cin.fail())
  {
    cin.get(c);
    if (c == ' ')
    {
      inputIndex++;
    }
    else
    {
      inputWords[inputIndex] = inputWords[inputIndex] + c;
    }
  }

  for (int i = 0; i < wordAmount; i++)
  {
    if (allWords[i] == inputWords[0])
    {
      wordInWords = true;
      for (int j = 0; j < inputIndex; j++)
      {
        if (!(allWords[i + j] == inputWords[j]))
        {
          wordInWords = false;
        }
      }
      if (wordInWords)
      {
        countAmount++;
        wordInWords = false;
      }
    }
  }

  cout << countAmount << '\t' << wordAmount << '\t' << countAmount * 1.0 / wordAmount << endl;

  return;
}

int main()
{
  typedef ifstream InputFile;
  typedef string InputText;
  typedef char InputChar;
  typedef bool Finish;

  Finish stop;
  InputFile infile;
  InputText input;
  InputText fileName;
  InputText inputExtra;
  InputChar c;

  while (true)
  {
    cin >> input;
    if (input == "enter")
    {
      cin.get(c);
      getline(cin, fileName);
      infile.clear();
      infile.close();
      if (!enter(fileName, infile))
      {
        cout << "An error has occurred trying to open the file.";
        return 0;
      }
      cout << "A file has successfully been loaded." << endl;
    }
    else if (input == "content")
    {
      content(infile, fileName);
    }
    else if (input == "count")
    {
      count(fileName, infile);
    }
    else if (input == "where")
    {
      //where(inputExtra, infile);
    }
    else if (input == "context")
    {
      //context(inputExtra, infile);
    }
    else
    {
      return 1;
    }
  }
}