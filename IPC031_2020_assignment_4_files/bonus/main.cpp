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
    Bonus: Show month calendar
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

int find_sunday(int year, Month month)
{
    // we go to easter sunday
    int sunday = easter_day(year);                              // this will be the 'current sunday' in the future
    Month e_month = easter_month(year);                         // this will be the 'current month' in the future
    while (static_cast<int>(month) < static_cast<int>(e_month)) // the current month is earlier than the easter month
    {
        // if we can subtract 7 from the current sunday
        if (sunday > 7)
        {
            sunday -= 7;
        }
        // else we need to change the month
        else
        {
            e_month = static_cast<Month>(e_month - 1);
            sunday = sunday - 7 + number_of_days_in_month(year, e_month);
        }
    }
    while (static_cast<int>(month) > static_cast<int>(e_month)) // the current month is later than easter month
    {
        // if we can add 7 to the current sunday
        if (number_of_days_in_month(year, e_month) - sunday > 7)
        {
            sunday += 7;
        }
        // else we need to change the month
        else
        {
            sunday = sunday + 7 - number_of_days_in_month(year, e_month);
            e_month = static_cast<Month>(e_month + 1);
        }
    }
    // now we got 'a' sunday of the month, but we want the first sunday and return it
    while (sunday > 7)
    {
        sunday -= 7;
    }
    return sunday;
}

string day_string(int day)
{
    // if an int has 2 digits, we need to handle both of them separately
    if (day >= 10)
    {
        string output_string = "";
        output_string += static_cast<char>(day / 10) + 48;
        output_string += static_cast<char>(day % 10) + 48;
        return output_string + "  ";
    }
    // if not, we can just convert one digit to char
    else
    {
        string output_string = "";
        output_string += static_cast<char>(day) + 48;
        return output_string + "   ";
    }
}

void show_month(int year, Month month)
{
    // we set the current day of the month to 1 (first day) and conmpute the first sunday and month length
    int current_day = 1;
    const int first_sunday = find_sunday(year, month);
    const int month_length = number_of_days_in_month(year, month);
    // this is going to be the string we will fill and print to the console
    string output_string = "";
    cout << "Mo  Tu  We  Th  Fr  Sa  Su  " << endl;
    // we make the first line/week (1 until sunday)
    for (int i = 1; i <= first_sunday; i++)
    {
        current_day = i;
        char output_char = static_cast<char>(current_day);
        output_char += 48;
        output_string += output_char;
        output_string += "   ";
    }
    // and fill this up with spaces in the front to get it on the right place
    while (output_string.length() < 28)
    {
        output_string = " " + output_string;
    }
    cout << output_string << endl;

    // and we print the rest of the week.
    while (current_day < month_length)
    {
        string output_string = "";
        // a week has 7 days
        for (int week_counter = 1; week_counter <= 7; week_counter++)
        {
            // we dont want to print too many days
            if (current_day <= month_length)
            {
                output_string += day_string(current_day);
                current_day++;
            }
        }
        cout << output_string << endl;
    }
}

void show_months()
{
    while (true)
    {
        // we let the user input a month and a year
        int year;
        string month_string;
        Month month;
        cout << "Please input a year and a month number" << endl;
        cin >> year;
        cin >> month_string;
        // and convert the month to the month enum (we keep the year)
        if (month_string == "January")
            month = January;
        else if (month_string == "February")
            month = February;
        else if (month_string == "March")
            month = March;
        else if (month_string == "April")
            month = April;
        else if (month_string == "May")
            month = May;
        else if (month_string == "June")
            month = June;
        else if (month_string == "July")
            month = July;
        else if (month_string == "August")
            month = August;
        else if (month_string == "September")
            month = September;
        else if (month_string == "October")
            month = October;
        else if (month_string == "November")
            month = November;
        else
            month = December;
        // and we call show month
        show_month(year, month);
    }
}

int main()
{
    show_months();
    return 0;
}
