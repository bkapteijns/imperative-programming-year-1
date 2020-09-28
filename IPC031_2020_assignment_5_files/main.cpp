#include <iostream>
#include <fstream> // for file I/O
#include <cassert> // for assertion checking

using namespace std;

enum Action
{
    Encrypt,
    Decrypt
};

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

char rotate_char(char a, int r, Action action)
{
    //  Pre-condition:
    assert(r > 0 && r <= 65536);
    //  Post-condition: we will have encrypted/changed the char according to the formula given
    if (static_cast<int>(a) < 32)
        return a;
    if (action == Encrypt)
    {
        return static_cast<char>((a - 32 + (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32);
    }
    return static_cast<char>((a - 32 - (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32);
}

void test_rotate_char()
{
    //  Pre-condition:
    assert(true);
    //  Post-condition: we will have tested rotate_char with r = user input
    int r = 0;
    cout << "Input a number 0 - 65535" << endl;
    cin >> r;
    while (r >= 0)
    {
        cout << "Tested for: r = " << r << ":" << endl;
        for (int i = 0; i < 128; i++)
        {
            cout << rotate_char(rotate_char(static_cast<char>(i), r, Encrypt), r, Decrypt);
        }
        cout << endl
             << "Input a number 0 - 65535" << endl;
        cin >> r;
    }
    return;
}

bool open_input_and_output_file(ifstream &infile, ofstream &outfile)
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
    infile.open(infile_name);
    outfile.open(outfile_name);
    if (!infile.fail() && !outfile.fail())
    {
        return true;
    }
    return false;
}

Action get_user_action()
{ // Pre-condition:
    assert(true);
    /*  Post-condition:
    result is the Action that the user has indicated that the program should encrypt / decrypt
*/
    cout << "Do you want to encrypt the file? (y/n): ";
    string answer;
    cin >> answer;
    if (answer == "y")
        return Encrypt;
    else
        return Decrypt;
}

int initial_encryption_value()
{ // Pre-conditie:
    assert(true);
    /*  Post-condition:
    result is a value between 0 and 65355 (both inclusive)
*/
    int initial_value = -1;
    while (initial_value < 0 || initial_value > 65535)
    {
        cout << "Please enter the initial coding value (greater or equal to 0 and less than 65536)" << endl;
        cin >> initial_value;
    }
    return initial_value;
}

void use_OTP(ifstream &infile, ofstream &outfile, Action action, int initial_value)
{
    //  Pre-condition:
    assert(infile.is_open() && outfile.is_open());
    //  Post-condition: all character in the infile have been en-/decoded into the outfile
    initialise_pseudo_random(initial_value);
    char c;
    while (!infile.fail())
    {
        infile.get(c);
        outfile << rotate_char(c, next_pseudo_random_number(), action);
    }
}

int main()
{
    const Action ACTION = get_user_action();
    ifstream input_file;
    ofstream output_file;
    if (!open_input_and_output_file(input_file, output_file))
    {
        cout << "Program aborted." << endl;
        return -1;
    }
    const int INITIAL_VALUE = initial_encryption_value();
    use_OTP(input_file, output_file, ACTION, INITIAL_VALUE);
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
