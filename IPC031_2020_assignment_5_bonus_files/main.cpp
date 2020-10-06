#include <iostream>
#include <fstream> // for file I/O
#include <cassert> // for assertion checking

using namespace std;

// the good r is: 2809

int seed = 0;
void initialise_pseudo_random(int r)
{
  //  pre-condition:
  assert(r > 0 && r <= 65536);
  /*  post-condition:
    seed has value r.
*/
  seed = r;
}

int next_pseudo_random_number()
{
  //  pre-condition:
  assert(seed > 0 && seed <= 65536);
  /*  post-condition:
    result value > 0 and result value <= 65536 and result value != seed at entry of function
*/
  const int seed75 = seed * 75;
  int next = (seed75 & 65535) - (seed75 >> 16);
  if (next < 0)
    next += 65537;
  seed = next;
  return next;
}

char rotate_char(char a, int r)
{
  //  Pre-condition:
  assert(r > 0 && r <= 65536);
  //  Post-condition: we will have encrypted/changed the char according to the formula given
  if (static_cast<int>(a) < 32)
    return a;
  return static_cast<char>((a - 32 - (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32);
}

bool open_input_and_output_file(ifstream &infile, ofstream &outfile, string &in_name, string &out_name)
{
  //  Pre-condition:
  assert(!infile.is_open() && !outfile.is_open());
  //  Post-condition: we will have opened an infile and an outfile (from user input)
  string infile_name, outfile_name;
  cout << "Input the name of the input file" << endl;
  cin >> infile_name;
  cout << "Input the name of the output file" << endl;
  cin >> outfile_name;
  while (outfile_name == infile_name)
  {
    cout << "Input the name of the output file" << endl;
    cin >> outfile_name;
  }
  in_name = infile_name;
  out_name = outfile_name;
  infile.open(infile_name);
  outfile.open(outfile_name);
  if (!infile.fail() && !outfile.fail())
  {
    return true;
  }
  return false;
}

int find_good_r(ifstream &infile, ofstream &outfile, string inname)
{
  // precondition:
  assert(infile.is_open() && outfile.is_open());
  // postcondition: we have found the value for r, where there are the most spaces (that's probably english)
  char c;
  char d;
  int good_r = 0;
  int max_spaces = 0;
  for (int i = 1; i < 65536; i++)
  {
    int spaces_amount = 0;
    infile.clear();
    infile.close();
    infile.open(inname);
    initialise_pseudo_random(i);
    for (int j = 1; j < 1000; j++)
    {
      infile.get(c);
      if (rotate_char(c, next_pseudo_random_number()) == ' ')
      {
        spaces_amount++;
      }
    }
    if (spaces_amount > max_spaces)
    {
      good_r = i;
      max_spaces = spaces_amount;
    }
  }
  return good_r;
}

void use_OTP(ifstream &infile, ofstream &outfile, string inname)
{
  //  Pre-condition:
  assert(infile.is_open() && outfile.is_open());
  //  Post-condition: decrypt the input file and paste the result in the output file
  const int good_r = find_good_r(infile, outfile, inname);
  infile.clear();
  infile.close();
  infile.open(inname);
  initialise_pseudo_random(good_r);
  char c;
  while (!infile.fail())
  {
    infile.get(c);
    outfile << rotate_char(c, next_pseudo_random_number());
  }
}

int main()
{
  ifstream input_file;
  ofstream output_file;
  string in_name, out_name;
  if (!open_input_and_output_file(input_file, output_file, in_name, out_name))
  {
    cout << "Program aborted." << endl;
    return -1;
  }
  use_OTP(input_file, output_file, in_name);
  input_file.clear();
  output_file.clear();
  input_file.close();
  output_file.close();

  if (!input_file || !output_file)
  {
    cout << "Not all files were closed succesfully. The output might be incorrect." << endl;
    return -1;
  }
  return 0;
}
