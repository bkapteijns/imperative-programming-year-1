#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

enum Cell
{
    Dead = 0,
    Live
}; // a cell is either Dead or Live (we use the fact that dead = 0 and live = 1)

const char DEAD = '.';                 // the presentation of a dead cell (both on file and screen)
const char LIVE = '*';                 // the presentation of a live cell (both on file and screen)
const int NO_OF_ROWS = 40;             // the number of rows (height) of the universe (both on file and screen)
const int NO_OF_COLUMNS = 60;          // the number of columns (width) of the universe (both on file and screen)
const int ROWS = NO_OF_ROWS + 2;       // the number of rows in a universe array, including the 'frame' of dead cells
const int COLUMNS = NO_OF_COLUMNS + 2; // the number of columns in a universe array, including the 'frame' of dead cells

const int MAX_FILENAME_LENGTH = 80; // the maximum number of characters for a file name (including termination character)

//  Part 1: setting the scene
bool read_universe_file(ifstream &inputfile, Cell universe[ROWS][COLUMNS])
{
    // pre-condition:
    assert(inputfile.is_open());
    /* post-conditions:
        We will have created an array called universe from the input file
    */
    for (int i = 0; i < COLUMNS; i++)
    {
        universe[0][i] = Dead;
    }

    for (int j = 1; j <= NO_OF_ROWS; j++)
    {
        universe[j][0] = Dead;
        for (int i = 1; i <= NO_OF_COLUMNS; i++)
        {
            if (inputfile.get() == DEAD)
            {
                universe[j][i] = Dead;
            }
            else
            {
                universe[j][i] = Live;
            }
        }
        if (inputfile.get() != '\n')
        {
            return false;
        }
        universe[j][61] = Dead;
    }

    for (int i = 0; i < COLUMNS; i++)
    {
        universe[41][i] = Dead;
    }

    return true;
}

void show_universe(Cell universe[ROWS][COLUMNS])
{
    // pre-conditions
    assert(true);
    /* post-condition
        We will have printed the universe to the console
    */
    for (int j = 0; j < ROWS; j++)
    {
        for (int i = 0; i < COLUMNS; i++)
        {
            if (universe[j][i] == Dead)
            {
                cout << DEAD;
            }
            else
            {
                cout << LIVE;
            }
        }
        cout << endl;
    }
}

//  Part 2: the next generation
void next_generation(Cell now[ROWS][COLUMNS], Cell next[ROWS][COLUMNS])
{
    // pre-condition
    assert(true);
    /* post-conditions
        We will have made a new generation of the universe
    */
    for (int i = 0; i < COLUMNS; i++)
    {
        next[0][i] = Dead;
    }

    for (int j = 1; j <= NO_OF_ROWS; j++)
    {
        next[j][0] = Dead;
        for (int i = 1; i <= NO_OF_COLUMNS; i++)
        {
            int live_count = 0;
            for (int p = -1; p <= 1; p++)
            {
                for (int q = -1; q <= 1; q++)
                {
                    if (!(p == 0 && q == 0))
                    {
                        if (now[j + p][i + q] == Live)
                        {
                            live_count++;
                        }
                    }
                }
            }
            switch (live_count)
            {
            case 2:
                if (now[j][i] == Live)
                {
                    next[j][i] = Live;
                }
                break;
            case 3:
                next[j][i] = Live;
                break;
            default:
                next[j][i] = Dead;
                break;
            }
        }
        next[j][61] = Dead;
    }

    for (int i = 0; i < COLUMNS; i++)
    {
        next[41][i] = Dead;
    }
}

int main()
{
    Cell universe[ROWS][COLUMNS];
    ifstream inputfile;
    char c;
    string filename = "";

    while (!cin.fail() && c != '\n')
    {
        cin.get(c);
        if (c != '\n')
        {
            filename = filename + c;
        }
    }

    inputfile.open(filename);

    read_universe_file(inputfile, universe);

    Cell now_universe[ROWS][COLUMNS];
    for (int j = 0; j < ROWS; j++)
    {
        for (int i = 0; i < COLUMNS; i++)
        {
            now_universe[j][i] = universe[j][i];
        }
    }

    next_generation(now_universe, universe);
    show_universe(universe);
    cin.get();
}
