#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

//  Part 1
// 1.
double naive_power(double x, int n)
{ // preconditions
  assert(n >= 0);
  // postconditions: we will have returned x to the power of n
  if (n == 0)
  {
    return 1;
  }
  else
  {
    return x * naive_power(x, n - 1);
  }
}

// 2.
double efficient_power(double x, int n)
{ // preconditions
  assert(n >= 0);
  // postconditions: we will have returned x to the power of n
  if (n == 0)
  {
    return 1;
  }
  if (n == 1)
  {
    return x;
  }
  else if (n % 2 == 0)
  {
    double a = efficient_power(x, n / 2);
    return a * a;
  }
  else
  {
    return efficient_power(x, n / 2 + 1) * efficient_power(x, n / 2);
  }
}

//  Part 2
// 1.
bool palindrome1(string text, int i, int j)
{ // preconditions
  assert(true);
  // postconditions: we will have returned whether the text from i to j is a palindrome
  if (i > j)
  {
    return true;
  }
  else
  {
    return text[i] == text[j] && palindrome1(text, i + 1, j - 1);
  }
}
// 2.
bool compare_letter(char letter1, char letter2)
{
  int l1 = static_cast<int>(letter1);
  int l2 = static_cast<int>(letter2);
  if (64 < l1 && l1 < 91)
    l1 += 32;
  if (64 < l2 && l2 < 91)
    l2 += 32;
  if (l1 == l2)
    return true;
  else
    return false;
}
bool palindrome2(string text, int i, int j)
{ // preconditions
  assert(true);
  // postconditions: we will have returned whether the text from i to j is a palindrome
  if (i > j)
  {
    return true;
  }
  else
  {
    return compare_letter(text[i], text[j]) && palindrome2(text, i + 1, j - 1);
  }
}
// 3.
bool palindrome3(string text, int i, int j)
{ // preconditions
  assert(true);
  // postconditions: we will have returned whether the text from i to j is a palindrome
  if (i > j)
    return true;
  int letter_i = static_cast<int>(text[i]);
  if (letter_i < 65 || (letter_i > 90 && letter_i < 97) || letter_i > 122)
  {
    return palindrome3(text, i + 1, j);
  }
  int letter_j = static_cast<int>(text[j]);
  if (letter_j < 65 || (letter_j > 90 && letter_j < 97) || letter_j > 122)
  {
    return palindrome3(text, i, j - 1);
  }
  return compare_letter(text[i], text[j]) && palindrome3(text, i + 1, j - 1);
}

//  Part 3
// 1.
bool match_chars(string chars, int i, string source, int j)
{ // preconditions
  assert(true);
  // postconditions: we will have returned whether chars is in source (in order)
  if (i >= chars.length())
    return true;
  if (j >= source.length())
    return false;
  if (chars[i] == source[j])
    return match_chars(chars, i + 1, source, j + 1);
  return match_chars(chars, i, source, j + 1);
}

//  Bonus
bool match_pattern(string pattern, string source)
{ // preconditions
  assert(true);
  // postconditions: we will have returned whether the pattern is found in the source
  // The base step
  if (pattern.length() == 0 && source.length() == 0)
    return true;

  // the wildcart pattern rewriters
  if (pattern[0] == '*' && pattern[1] == '*')
    return match_pattern(pattern.substr(1, pattern.length() - 1), source);
  if (pattern[0] == '*' && pattern[1] == '.')
  {
    pattern[0] = '.';
    pattern[1] = '*';
    return match_pattern(pattern, source);
  }

  // the wildcard rules
  if (pattern[0] == '*')
  {
    if (source.length() > 0)
      return match_pattern(pattern.substr(1, pattern.length() - 1), source) || match_pattern(pattern, source.substr(1, source.length() - 1));
    return match_pattern(pattern.substr(1, pattern.length() - 1), source);
  }
  if (source.length() == 0)
    return false;
  if (pattern[0] == '.')
    return match_pattern(pattern.substr(1, pattern.length() - 1), source.substr(1, source.length() - 1));

  // the normal rules
  if (pattern[0] == source[0])
    return match_pattern(pattern.substr(1, pattern.length() - 1), source.substr(1, source.length() - 1));
  if (pattern[0] != source[0])
    return false;
}

int main()
{
  while (true)
  {
  }

  return 0;
}
