#include <iostream>

using namespace std;

// convert from int to the result
void to_(int number, int base)
{
  // this will be the result
  string answer = "";

  // loop through the whole number
  while (number > 0)
  {
    // make sure it's converted to a letter-character
    if (number % base > 9)
    {
      // convert the remainder to a character and add it to the result
      answer = static_cast<char>(number % base + 55) + answer;
    }
    // else it can be a number-character
    else
    {
      // convert the remainder to a character and add it to the result
      answer = static_cast<char>(number % base + 48) + answer;
    }
    // make sure we divide the number by the base
    number = number / base;
  }

  // print the answer
  cout << answer << endl;
  return;
}

// calculate the (decimal) value of a number
void convert(string number, int input_type, int output_type)
{
  // this will be the (decimal) value
  int value = 0;

  // loop through all the different 'characters' in the number
  for (int i = 0; i < 4; i++)
  {
    // calculate the (decimal) 'weight' of the position of a character
    int weight = 1;
    for (int j = 3; j > i; j--)
    {
      weight *= input_type;
    }

    // give the character a (decimal) value and add that value to the total value of the number
    if (number[i] == 'A' || number[i] == 'B' || number[i] == 'C' || number[i] == 'D' || number[i] == 'E' || number[i] == 'F')
    {
      value += (static_cast<int>(number[i]) - 55) * weight;
    }
    else
    {
      value += (static_cast<int>(number[i]) - 48) * weight;
    }
  }

  // either print the value (already decimal) or convert from decimal to another type
  switch (output_type)
  {
  case 10:
    cout << value << endl;
    break;
  default:
    to_(value, output_type);
    break;
  }

  return;
}

int main()
{
  // Make sure the program does not stop
  while (true)
  {
    int input_type = 0;
    int output_type = 0;
    string number = "00000";

    // let the user input their values
    while (!(input_type == 2 || input_type == 8 || input_type == 10 || input_type == 16))
    {
      cout << "Choose an input type (either 2, 8, 10 or 16)" << endl;
      cin >> input_type;
    }
    while (!(output_type == 2 || output_type == 8 || output_type == 10 || output_type == 16))
    {
      cout << "Choose an output type (either 2, 8, 10 or 16)" << endl;
      cin >> output_type;
    }
    while (number.length() != 4)
    {
      cout << "Choose a number you want to convert from " << input_type << "-base to " << output_type << "-base" << endl;
      cin >> number;
    }
    convert(number, input_type, output_type);
  }
  return 0;
}