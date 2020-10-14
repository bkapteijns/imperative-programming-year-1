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

  Counter wordAmount = 0;
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

  for (int i = 0; i < length; i++)
  {
    infile >> input;
    words[i] = input;
  }
  return;
}

void array_of_query(string searchWords[], int length, string input)
{ //preconditions
  assert(length > 0);
  //postconditions: we will have created an array of words from the query
  typedef int Counter;

  Counter j = 0;

  for (int i = 1; i < input.length(); i++)
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

int correspondence_amount(int wordAmount, int inputAmount, string allWords[], string inputWords[])
{ // preconditions:
  assert(wordAmount > 0);
  // postconditions: we will have returned the amount of times a wordsequence is in a text

  typedef int Counter;
  typedef bool Correct;

  Correct corresponds = false;
  Counter correspondences = 0;

  for (int i = 0; i < wordAmount; i++)
  {
    if (allWords[i] == inputWords[0])
    {
      corresponds = true;
      for (int j = 0; j < inputAmount; j++)
      {
        if (i + j > wordAmount)
        {
          corresponds = false;
        }
        if (allWords[i + j] != inputWords[j])
        {
          corresponds = false;
        }
      }
      if (corresponds)
      {
        correspondences++;
      }
    }
  }
  return correspondences;
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
  Counter inputAmount = 0;
  Word input;
  getline(cin, input);
  for (int j = 0; j < input.length(); j++)
  {
    if (input[j] == ' ')
    {
      inputAmount++;
    }
  }
  Word inputWords[inputAmount];
  array_of_query(inputWords, inputAmount, input);

  Counter correspondences = 0;

  correspondences = correspondence_amount(wordAmount, inputAmount, allWords, inputWords);

  cout << correspondences << '\t' << wordAmount << '\t' << correspondences * 1.0 / wordAmount << endl;

  infile.clear();
  infile.close();
  infile.open(fileName);

  return;
}

void where(ifstream &infile, string fileName)
{ //preconditions
  assert(infile.is_open());
  //postconditions: we will have printed the indices and frequency of a word combo
  typedef int Counter;
  typedef string Word;
  typedef bool Correct;
  typedef char InputChar;
  typedef int Index;

  const Counter wordAmount = count_total_words(infile, fileName);
  Word allWords[wordAmount];
  array_of_words(allWords, wordAmount, infile);
  Counter inputAmount = 0;
  Word input;
  getline(cin, input);
  for (int j = 0; j < input.length(); j++)
  {
    if (input[j] == ' ')
    {
      inputAmount++;
    }
  }
  Word inputWords[inputAmount];
  array_of_query(inputWords, inputAmount, input);

  Correct corresponds = false;
  Counter correspondences = 0;

  correspondences = correspondence_amount(wordAmount, inputAmount, allWords, inputWords);

  Index wordPlaces[correspondences];
  Counter placeIndex = 0;

  for (int i = 0; i < wordAmount; i++)
  {
    if (allWords[i] == inputWords[0])
    {
      corresponds = true;
      for (int j = 0; j < inputAmount; j++)
      {
        if (i + j > wordAmount)
        {
          corresponds = false;
        }
        if (allWords[i + j] != inputWords[j])
        {
          corresponds = false;
        }
      }
      if (corresponds)
      {
        wordPlaces[placeIndex++] = i + 1;
      }
    }
  }

  for (int i = 0; i < correspondences; i++)
  {
    cout << wordPlaces[i] << ", ";
  }

  cout << "correspondences: " << correspondences << endl;

  infile.clear();
  infile.close();
  infile.open(fileName);

  return;
}

void context(ifstream &infile, string fileName)
{ //preconditions
  assert(infile.is_open());
  //postconditions: we will have printed the context including the word sequence and frequency of a word sequence
  typedef int Counter;
  typedef string Word;
  typedef bool Correct;
  typedef char InputChar;
  typedef int Index;
  typedef int Length;

  const Counter wordAmount = count_total_words(infile, fileName);
  Word allWords[wordAmount];
  array_of_words(allWords, wordAmount, infile);
  Counter inputAmount = 0;
  Word input;

  Length contextAmount;
  cin >> contextAmount;

  getline(cin, input);
  for (int j = 0; j < input.length(); j++)
  {
    if (input[j] == ' ')
    {
      inputAmount++;
    }
  }
  Word inputWords[inputAmount];
  array_of_query(inputWords, inputAmount, input);

  Correct corresponds = false;
  Counter correspondences = 0;

  correspondences = correspondence_amount(wordAmount, inputAmount, allWords, inputWords);

  Index wordPlaces[correspondences];
  Counter placeIndex = 0;

  for (int i = 0; i < wordAmount; i++)
  {
    if (allWords[i] == inputWords[0])
    {
      corresponds = true;
      for (int j = 0; j < inputAmount; j++)
      {
        if (i + j > wordAmount)
        {
          corresponds = false;
        }
        if (allWords[i + j] != inputWords[j])
        {
          corresponds = false;
        }
      }
      if (corresponds)
      {
        wordPlaces[placeIndex++] = i;
      }
    }
  }

  for (int j = 0; j < correspondences; j++)
  {
    for (int i = 0; i < 2 * contextAmount + inputAmount; i++)
    {
      if (wordPlaces[j] + i - contextAmount >= 0 && wordPlaces[j] + i - contextAmount < wordAmount)
      {
        cout << allWords[wordPlaces[j] + i - contextAmount] << ' ';
      }
    }
    cout << endl;
  }

  cout << correspondences << endl;

  infile.clear();
  infile.close();
  infile.open(fileName);

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
    cout << "Enter your command" << endl;
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
      where(infile, fileName);
    }
    else if (input == "context")
    {
      context(infile, fileName);
    }
    else if (input == "stop")
    {
      return 1;
    }
  }
}