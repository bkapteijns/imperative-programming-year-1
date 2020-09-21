#include <iostream>

using namespace std;

enum Month
{
    January = 1,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};

/*  The function easter_base uses the Meeus/Jones/Butcher formula to compute
    the number that is used to determine on which month (easter_month below)
    and day (easter_day below) Easter is in the given year.
*/
int easter_base(int year)
{
    const int A = year % 19;
    const int B = year / 100;
    const int C = year % 100;
    const int D = B / 4;
    const int E = B % 4;
    const int F = (B + 8) / 25;
    const int G = (B - F + 1) / 3;
    const int H = (19 * A + B - D - G + 15) % 30;
    const int I = C / 4;
    const int K = C % 4;
    const int L = (32 + 2 * E + 2 * I - H - K) % 7;
    const int M = (A + 11 * H + 22 * L) / 451;
    return H + L - 7 * M + 114;
}

/*  The result of easter_year is the day number of the month in which Easter occurs in
    the given year.
*/
int easter_day(int year)
{
    return (easter_base(year) % 31) + 1;
}

/*  The result of easter_month is the month in which Easter occurs in the given year.
*/
Month easter_month(int year)
{
    return static_cast<Month>(easter_base(year) / 31);
}

/********************************************************************
    Assignment part 1: Leap years
********************************************************************/
bool is_leap_year(int year)
{
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
    {
        return true;
    }
    return false;
}

int number_of_days_in_month(int year, Month month)
{
    if (month == January || month == March || month == May || month == July || month == August || month == October || month == December)
    {
        return 31;
    }
    else if (month == February)
    {
        if (is_leap_year(year))
        {
            return 29;
        }
        return 28;
    }
    else
    {
        return 30;
    }
}

/********************************************************************
    Assignment part 2: Holy days based on Easter
********************************************************************/
void print_holy_day(int day, Month month, int year, int days_ahead, string holy_day)
{
    // if we need to go back in time (so the days ahead are negative)
    while (days_ahead < 0)
    {
        // if the days to go back are larger than the number of days in the current month, we can subtract a month to the current date (without affecting the day)
        if (abs(days_ahead) > number_of_days_in_month(year, month))
        {
            month = static_cast<Month>(month - 1);
            days_ahead += number_of_days_in_month(year, month);
        }
        // else if the days to go back are larger than the current day, we need to subtract a month from the current date and edit the day
        else if (abs(days_ahead) > day)
        {
            month = static_cast<Month>(month - 1);
            day = number_of_days_in_month(year, month) + day + days_ahead;
            days_ahead = 0;
        }
        // otherwise we can just subtract the amount of days to go back from the current day of the month
        else
        {
            day += days_ahead;
            days_ahead = 0;
        }
    }
    // if we need to go ahead in time (so the days ahead are positive)
    while (days_ahead > 0)
    {
        // if the days ahead are larger than the amount of days in the current month, we can just go to the next month
        if (days_ahead > number_of_days_in_month(year, month))
        {
            days_ahead -= number_of_days_in_month(year, month);
            month = static_cast<Month>(month + 1);
        }
        // if the amount of days ahead is larger than the current amount of days, we will need to go to the next month and change the day accordingly
        else if (days_ahead + day > number_of_days_in_month(year, month))
        {
            day = day + days_ahead - number_of_days_in_month(year, month);
            month = static_cast<Month>(month + 1);
            days_ahead = 0;
        }
        // otherwise, we can just add the amount of days ahead to the day
        else
        {
            day += days_ahead;
            days_ahead = 0;
        }
    }
    // output the current holy day and the date in a beautiful way.
    cout << "The holy day " << holy_day << " is on " << day << "-" << month << '-' << year << endl;
}

void show_holy_days()
{
    // let the user input a year and calculate easter day and month
    cout << "Input a year: ";
    int year = 0;
    cin >> year;
    const int e_day = easter_day(year);
    const Month e_month = easter_month(year);

    // input all different holy days to the function
    print_holy_day(e_day, e_month, year, -49, "Carnival");
    print_holy_day(e_day, e_month, year, -2, "Good Friday");
    print_holy_day(e_day, e_month, year, 0, "Easter");
    print_holy_day(e_day, e_month, year, 39, "Ascension Day");
    print_holy_day(e_day, e_month, year, 49, "Whitsuntide");
}

int main()
{
    // Prevent the program from quitting
    while (true)
    {
        show_holy_days();
    }
    return 0;
}
