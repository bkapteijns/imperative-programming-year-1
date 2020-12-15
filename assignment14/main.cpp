#define NDEBUG

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

typedef string Time;
typedef int Minutes;
typedef int Seconds;
typedef int Amount;
typedef string InputText;
typedef int Size;
typedef int Counter;

Counter runtime = 0;

struct Length
{
    int minutes; // #minutes (0..)
    int seconds; // #seconds (0..59)
};

struct Track
{
    string artist;  // name of artist
    string cd;      // cd title
    int year;       // year of appearance (if known)
    int track;      // track number
    string title;   // track title
    string tags;    // tags
    Length time;    // playing time
    string country; // main countr(y/ies) of artist
};

struct TrackDisplay
{
    bool showArtist;  // if true, show name of artist
    bool showAlbum;   // if true, show cd title
    bool showYear;    // if true, show year of appearance
    bool showTrack;   // if true, show track number
    bool showTitle;   // if true, show track title
    bool showTags;    // if true, show tags
    bool showLength;  // if true, show playing time
    bool showCountry; // if true, show countr(y/ies) of artist
};

struct Slice
{
    int from;
    int length;
};

int size(vector<Track> &data)
{
    return static_cast<int>(data.size());
}

/* For testing purposes, you can use the below defined, very small, music database.
   This is also convenient if you have not yet implemented reading the database file.
*/
vector<Track>
    testDB = {
        {"Adele", "19", 2008, 1, "Daydreamer", "pop,debut album", {3, 40}, "England"},
        {"Adele", "19", 2008, 10, "My same", "pop,debut album", {3, 15}, "England"},
        {"Adele", "19", 2008, 11, "Tired", "pop,debut album", {4, 18}, "England"},
        {"Adele", "19", 2008, 12, "Hometown glory", "pop,debut album", {4, 31}, "England"},
        {"Adele", "19", 2008, 2, "Best for last", "pop,debut album", {4, 18}, "England"},
        {"Adele", "19", 2008, 3, "Chasing pavements", "pop,debut album", {3, 30}, "England"},
        {"Adele", "19", 2008, 4, "Cold shoulder", "pop,debut album", {3, 11}, "England"},
        {"Adele", "19", 2008, 5, "Crazy for you", "pop,debut album", {3, 28}, "England"},
        {"Adele", "19", 2008, 6, "Melt my heart to stone", "pop,debut album", {3, 23}, "England"},
        {"Adele", "19", 2008, 7, "First love", "pop,debut album", {3, 10}, "England"},
        {"Adele", "19", 2008, 8, "Right as rain", "pop,debut album", {3, 17}, "England"},
        {"Adele", "19", 2008, 9, "Make you feel my love", "pop,debut album", {3, 32}, "England"},
        {"Adele", "21", 2011, 1, "Rolling in the deep", "pop", {3, 49}, "England"},
        {"Adele", "21", 2011, 10, "Lovesong", "pop", {5, 16}, "England"},
        {"Adele", "21", 2011, 11, "Someone like you", "pop", {4, 47}, "England"},
        {"Adele", "21", 2011, 2, "Rumour has it", "pop", {3, 43}, "England"},
        {"Adele", "21", 2011, 3, "Turning tables", "pop", {4, 10}, "England"},
        {"Adele", "21", 2011, 4, "Don't you remember", "pop", {4, 3}, "England"},
        {"Adele", "21", 2011, 5, "Set fire to the rain", "pop", {4, 1}, "England"},
        {"Adele", "21", 2011, 6, "He won't go", "pop", {4, 37}, "England"},
        {"Adele", "21", 2011, 7, "Take it all", "pop", {3, 48}, "England"},
        {"Adele", "21", 2011, 8, "I'll be waiting", "pop", {4, 1}, "England"},
        {"Adele", "21", 2011, 9, "One and only", "pop", {5, 48}, "England"},
        {"All them witches", "Dying surfer meets his maker", 2015, 1, "Call me star", "alternative,rock", {3, 54}, "U.S.A."},
        {"All them witches", "Dying surfer meets his maker", 2015, 2, "El centro", "alternative,rock,instrumental", {8, 25}, "U.S.A."},
        {"All them witches", "Dying surfer meets his maker", 2015, 3, "Dirt preachers", "alternative,rock", {3, 44}, "U.S.A."},
        {"All them witches", "Dying surfer meets his maker", 2015, 4, "This is where it falls apart", "alternative,rock", {7, 2}, "U.S.A."},
        {"All them witches", "Dying surfer meets his maker", 2015, 5, "Mellowing", "alternative,instrumental", {3, 11}, "U.S.A."},
        {"All them witches", "Dying surfer meets his maker", 2015, 6, "Open passageways", "alternative,rock", {3, 14}, "U.S.A."},
        {"All them witches", "Dying surfer meets his maker", 2015, 7, "Instrumental 2 (welcome to the caveman future)", "alternative,rock,instrumental", {2, 33}, "U.S.A."},
        {"All them witches", "Dying surfer meets his maker", 2015, 8, "Talisman", "alternative,rock", {6, 7}, "U.S.A."},
        {"All them witches", "Dying surfer meets his maker", 2015, 9, "Blood and sand / milk and endless waters", "alternative,rock", {7, 20}, "U.S.A."},
        {"The decemberists", "The tain", 2005, 1, "The tain (parts i-iv)", "progressive,experimental,folk,rock", {18, 35}, "U.S.A."},
        {"Colin Stetson and Sarah Neufeld", "Never were the way she was", 2015, 1, "The sun roars into view", "jazz,instrumental,experimental", {7, 37}, "U.S.A.,Canada"},
        {"Colin Stetson and Sarah Neufeld", "Never were the way she was", 2015, 2, "Won't be a thing to become", "jazz,instrumental,experimental", {3, 24}, "U.S.A.,Canada"},
        {"Colin Stetson and Sarah Neufeld", "Never were the way she was", 2015, 3, "In the vespers", "jazz,instrumental,experimental", {6, 2}, "U.S.A.,Canada"},
        {"Colin Stetson and Sarah Neufeld", "Never were the way she was", 2015, 4, "And still they move", "jazz,instrumental,experimental", {2, 56}, "U.S.A.,Canada"},
        {"Colin Stetson and Sarah Neufeld", "Never were the way she was", 2015, 5, "With the dark hug of time", "jazz,instrumental,experimental", {6, 34}, "U.S.A.,Canada"},
        {"Colin Stetson and Sarah Neufeld", "Never were the way she was", 2015, 6, "The rest of us", "jazz,instrumental,experimental", {6, 30}, "U.S.A.,Canada"},
        {"Colin Stetson and Sarah Neufeld", "Never were the way she was", 2015, 7, "Never were the way she was", "jazz,instrumental,experimental", {8, 12}, "U.S.A.,Canada"},
        {"Colin Stetson and Sarah Neufeld", "Never were the way she was", 2015, 8, "Flight", "jazz,instrumental,experimental", {1, 38}, "U.S.A.,Canada"}};

bool match(string sub, string source)
{ // Precondition:
    assert(true);
    /*  Postcondition:
    Result is true only if sub is a literal (case sensitive) sub string of source.
*/
    return source.find(sub) != string::npos;
}

ostream &operator<<(ostream &out, const Length length)
{ // Precondition:
    assert(true);
    /*  Postcondition:
    the value of length is shown via out in the format: minutes, ':', seconds (two digits)
*/
    if (length.seconds < 10)
    {
        out << length.minutes << ":0" << length.seconds;
    }
    else
    {
        out << length.minutes << ":" << length.seconds;
    }
    return out;
}

istream &operator>>(istream &in, Length &length)
{ // Precondition:
    assert(true);
    /*  Postcondition:
    the value of length has been read from in: first minutes, then ':', then seconds
*/
    Time m, s;
    Minutes minutes;
    Seconds seconds;

    getline(in, m, ':');
    getline(in, s);

    minutes = stoi(m);
    seconds = stoi(s);

    length.minutes = minutes;
    length.seconds = seconds;

    return in;
}

Length operator+(const Length &a, const Length &b)
{ // Precondition:
    assert(0 <= a.minutes && 0 <= a.seconds && a.seconds < 60 && 0 <= b.minutes && 0 <= b.seconds && b.seconds < 60);
    /*  Postcondition:
    Result is the sum of a and b.
*/
    Seconds seconds = a.seconds + b.seconds;
    Minutes minutes = a.minutes + b.minutes;
    Length time;
    if (seconds > 60)
    {
        seconds -= 60;
        minutes += 1;
    }
    time.minutes = minutes;
    time.seconds = seconds;
    return time;
}

void show_track(Track track, TrackDisplay lt)
{ // Precondition:
    assert(true);
    /*  Postcondition:
    only the members of track are shown for which the corresponding member in lt is true.
*/
    if (lt.showArtist)
    {
        cout << "Artist: " << track.artist << endl;
    }
    if (lt.showAlbum)
    {
        cout << "Album: " << track.cd << endl;
    }
    if (lt.showYear)
    {
        cout << "Year of publication: " << track.year << endl;
    }
    if (lt.showTrack)
    {
        cout << "Track id: " << track.track << endl;
    }
    if (lt.showTitle)
    {
        cout << "Track name: " << track.title << endl;
    }
    if (lt.showTags)
    {
        cout << "Track tags: " << track.tags << endl;
    }
    if (lt.showLength)
    {
        cout << "Track length: " << track.time << endl;
    }
    if (lt.showCountry)
    {
        cout << "Track country: " << track.country << endl;
    }
    cout << endl;
}

int match_tracks(vector<Track> &tracks, string track, bool display)
{ // preconditions:
    assert(true);
    // postconditions: We will have printed matching tracks if display is true and returned the number of matching tracks

    Amount num_tracks = 0;

    for (int i = 0; i < tracks.size(); i++)
    {
        if (match(track, tracks[i].title))
        {
            num_tracks++;
            if (display)
            {
                // According to cirrus, we don't have to print tags. But the assignment says so.
                show_track(tracks[i], {true, true, true, true, true, true, true, true});
            }
        }
    }
    return num_tracks;
}

bool contains(string sub, vector<string> source)
{ // preconditions:
    assert(true);
    // postconditions: we will have returned true if sub is in source, else false
    for (int i = 0; i < source.size(); i++)
    {
        if (sub == source[i])
        {
            return true;
        }
    }
    return false;
}

int match_artists(vector<Track> &tracks, string artist, bool display)
{ // preconditions:
    assert(true);
    // postconditions: we will have printed matching artists if display is true and returned the number of artists

    Amount num_artists = 0;
    vector<string> counted = {};

    for (int i = 0; i < tracks.size(); i++)
    {
        if (match(artist, tracks[i].artist) && !contains(tracks[i].artist, counted))
        {
            num_artists++;
            counted.push_back(tracks[i].artist);
            if (display)
            {
                show_track(tracks[i], {true, false, false, false, false, false, false, false});
            }
        }
    }
    return num_artists;
}

bool contains_1(string sub[2], vector<vector<string>> source)
{ // preconditions:
    assert(true);
    // postconditions: we will have returned true if sub is in source, else false
    for (int i = 0; i < source.size(); i++)
    {
        if (sub[0] == source[i][0] && sub[1] == source[i][1])
        {
            return true;
        }
    }
    return false;
}

int match_cds(vector<Track> &tracks, string artist, bool display)
{ // preconditions:
    assert(true);
    // postconditions: we will have printed cds of matching artists if display is true and returned the number of cds

    Amount num_albums = 0;
    vector<vector<string>> counted;

    for (int i = 0; i < tracks.size(); i++)
    {
        string album[2] = {tracks[i].artist, tracks[i].cd};
        if (match(artist, tracks[i].artist) && !contains_1(album, counted))
        {
            num_albums++;
            counted.push_back({tracks[i].artist, tracks[i].cd});
            if (display)
            {
                show_track(tracks[i], {true, true, false, false, false, false, false, false});
            }
        }
    }
    return num_albums;
}

int number_of_cds(vector<Track> &tracks)
{ // preconditions:
    assert(true);
    // postconditions: we will have returned the amount of cds

    Amount num_albums = 0;
    vector<vector<string>> counted;

    for (int i = 0; i < tracks.size(); i++)
    {
        string album[2] = {tracks[i].artist, tracks[i].cd};
        if (!contains_1(album, counted))
        {
            num_albums++;
            counted.push_back({tracks[i].artist, tracks[i].cd});
        }
    }
    return num_albums;
}

int match_year(vector<Track> &tracks, string _year, bool display)
{ // preconditions:
    assert(true);
    // postconditions: We will have printed artist and cd title for a year

    Amount num_albums = 0;
    int year = stoi(_year);
    vector<vector<string>> counted;

    for (int i = 0; i < tracks.size(); i++)
    {
        string album[2] = {tracks[i].artist, tracks[i].cd};
        if (year == tracks[i].year && !contains_1(album, counted))
        {
            num_albums++;
            counted.push_back({tracks[i].artist, tracks[i].cd});
            if (display)
            {
                show_track(tracks[i], {true, true, false, false, false, false, false, false});
            }
        }
    }
    return num_albums;
}

istream &operator>>(istream &in, Track &track)
{ // Precondition:
    assert(true);
    /*  Postcondition:
    the content of the first 8 lines from in have been read and are stored in the corresponding members of track.
    The following (empty) line from in has also been read.
*/
    string temp;
    char c;
    getline(in, track.artist);
    if (in.fail())
        return in;
    getline(in, track.cd);
    in >> track.year;
    in.get(c);
    in >> track.track;
    in.get(c);
    getline(in, track.title);
    getline(in, track.tags);
    in >> track.time;
    getline(in, track.country);
    getline(in, temp);
}

// These are the operators for the mandatory assignment
bool operator<(Track a, Track b)
{ // preconditions:
    assert(true);
    // postconditions: we will have compared track a to b and given true if a is the smaller one according to the assignment description, false otherwise

    runtime++;
    if (a.artist < b.artist)
    {
        return true;
    }
    else if (a.artist > b.artist)
    {
        return false;
    }
    else if (a.cd < b.cd)
    {
        return true;
    }
    else if (a.cd > b.cd)
    {
        return false;
    }
    else if (a.year < b.year)
    {
        return true;
    }
    else if (a.year > b.year)
    {
        return false;
    }
    else if (a.track < b.track)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator==(Track a, Track b)
{ // preconditions:
    assert(true);
    // postconditions: we will have compared track a to b and given true if a is equal to b according to the assignment description, false otherwise

    runtime++;
    if (a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track == b.track)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/*
// This is the operator for bonus part 1
bool operator<(Track a, Track b)
{ // preconditions:
    assert(true);
    // postconditions: we will have compared track a to b and given true if a is the smaller one according to the assignment description, false otherwise

    runtime++;

    int a_time = a.time.minutes * 60 + a.time.seconds;
    int b_time = b.time.minutes * 60 + b.time.seconds;
    if (a_time < b_time)
    {
        return true;
    }
    else if (a_time > b_time)
    {
        return false;
    }
    if (a.artist < b.artist)
    {
        return true;
    }
    else if (a.artist > b.artist)
    {
        return false;
    }
    if (a.title < b.title)
    {
        return true;
    }
    else if (a.title > b.title)
    {
        return false;
    }
    if (a.cd < b.cd)
    {
        return true;
    }
    else if (a.cd > b.cd)
    {
        return false;
    }
    return false;
}
bool operator==(Track a, Track b)
{ // preconditions:
    assert(true);
    // postconditions: we will have compared track a to b and given true if a is equal to b according to the assignment description, false otherwise

    runtime++;

    int a_time = a.time.minutes * 60 + a.time.seconds;
    int b_time = b.time.minutes * 60 + b.time.seconds;
    if (a_time == b_time && a.artist == b.artist && a.title == b.title && a.cd == b.cd)
    {
        return true;
    }
    return false;
}

string toLower(string text)
{
    string lower = "";
    for (int i = 0; i < text.length(); i++)
    {
        int letter = static_cast<int>(text[i]);
        if (letter <= 90 && letter >= 65)
        {
            letter += 32;
        }
        lower.push_back(static_cast<char>(letter));
    }
    return lower;
}
// This is the operator for bonus part 2
bool operator<(Track a, Track b)
{ // preconditions:
    assert(true);
    // postconditions: we will have compared track a to b and given true if a is the smaller one according to the assignment description, false otherwise

    runtime++;
    if (toLower(a.title) < toLower(b.title))
    {
        return true;
    }
    else if (toLower(a.title) > toLower(b.title))
    {
        return false;
    }
    if (toLower(a.artist) < toLower(b.artist))
    {
        return true;
    }
    else if (toLower(a.artist) > toLower(b.artist))
    {
        return false;
    }
    if (toLower(a.cd) < toLower(b.cd))
    {
        return true;
    }
    else if (toLower(a.cd) > toLower(b.cd))
    {
        return false;
    }
    return false;
}

bool operator==(Track a, Track b)
{ // preconditions:
    assert(true);
    // postconditions: we will have compared track a to b and given true if a is equal to b according to the assignment description, false otherwise

    runtime++;
    if (toLower(a.title) == toLower(b.title) && toLower(a.artist) == toLower(b.artist) && toLower(a.cd) == toLower(b.cd))
    {
        return true;
    }
    return false;
}
*/
Slice mkSlice(int from, int length)
{ // preconditions:
    assert(0 <= from && 0 <= length);
    //postconditions: we will have made slice form from to length
    Slice s = {from, length};
    return s;
}

bool valid_slice(vector<Track> &data, Slice s)
{ // preconditions:
    assert(true);
    // postconditions: we will have returned if the slice is valid
    return 0 <= s.from && 0 <= s.length && size(data) >= s.from + s.length;
}

bool is_sorted(vector<Track> &data, Slice s)
{ // preconditions:
    assert(valid_slice(data, s));
    // postconditions: result is true if data[first (s)]≤ data[first (s)+1] ... and ...data[last (s)-1]≤data[last (s)]
    for (int i = s.from; i <= s.length + s.from - 1; i++)
    {
        if (data[i + 1] < data[i])
        {
            return false; // counterexample found
        }
    }
    return true;
}

void swap(vector<Track> &data, int from, int to)
{ // preconditions:
    assert(from >= 0 && to >= 0);
    // postconditions: we will have swapped the data from from to to and back.
    const Track TEMP = data[from];
    data[from] = data[to];
    data[to] = TEMP;
}

void insert(vector<Track> &data, Slice s)
{ // preconditions:
    assert(s.length > 0 && is_sorted(data, mkSlice(s.from, s.length - 1)));
    // postconditions: data[last (s)] is moved in data[first (s)] ... data[last (s)] and is_sorted (data, s)
    int i = s.from + s.length - 1;
    while (i >= s.from && data[i + 1] < data[i])
    {
        swap(data, i--, i + 1);
    }
}

void insertion_sort(vector<Track> &data)
{ // preconditions:
    assert(true);
    // postconditions: data has been sorted in increasing order
    Size sorted = 1;
    while (sorted < size(data))
    {
        insert(data, mkSlice(0, sorted++));
    }
}

int max_value_at(vector<Track> &data, Slice s)
{ // preconditions
    assert(valid_slice(data, s) && s.length > 0);
    // postconditions: we will have returned the max element from data in slice s
    int max = s.from;
    for (int i = s.from + 1; i < s.from + s.length; i++)
    {
        if (data[max] < data[i])
        {
            max = i;
        }
    }
    return max;
}

void selection_sort(vector<Track> &data)
{ // precondition:
    assert(true);
    // postconditions: data has been sorted in increasing order
    for (int unsorted = size(data); unsorted >= 1; unsorted--)
    {
        int max = max_value_at(data, mkSlice(0, unsorted));
        swap(data, max, unsorted - 1);
    }
}

bool bubble(vector<Track> &data, Slice unsorted)
{ // preconditions:
    assert(valid_slice(data, unsorted));
    //postconditions: immediate pairs in data with slice have been swapped if left element is larger than
    // right element, and result is true only if this is done at least once
    bool any_swaps = false;
    for (int i = unsorted.from; i < unsorted.from + unsorted.length - 1; i++)
    {
        if (data[i + 1] < data[i])
        {
            swap(data, i, i + 1);
            any_swaps = true;
        }
    }
    return any_swaps;
}

void bubble_sort(vector<Track> &data)
{ // preconditions:
    assert(true);
    // postconditions: data has been sorted in increasing order
    int unsorted = size(data);
    while (unsorted > 0)
    {
        if (!bubble(data, {0, unsorted}))
        {
            return;
        }
        unsorted--;
    }
}

bool is_heap(vector<Track> &data, Slice s)
{ // preconditions:
    assert(valid_slice(data, s));
    // postconditions: return true if data is heap structure, else false
    for (int i = s.from; i < s.from + s.length; i++)
    {
        if (2 * (i + 1) - 1 < (s.from + s.length) && !((data[2 * (i + 1) - 1] < data[i]) || (data[2 * (i + 1) - 1] == data[i])))
        {
            return false;
        }
        else if (2 * (i + 1) < (s.from + s.length) && !((data[2 * (i + 1)] < data[i]) || (data[2 * (i + 1)] == data[i])))
        {
            return false;
        }
    }
    return true;
}

void push_up(vector<Track> &data, int element)
{ // preconditions:
    assert(0 <= element && element < size(data) && is_heap(data, {0, element - 1}));
    // postconditions slice 0 to element of data is heap
    int index = element;
    while (index > 0 && data[(index - 1) / 2] < data[index])
    {
        swap(data, index, (index - 1) / 2);
        index = (index - 1) / 2;
    }
}

void build_heap(vector<Track> &data)
{ // preconditions:
    assert(true);
    // postconditions: data has been put into heap structure
    for (int i = 1; i < size(data); i++)
    {
        push_up(data, i);
    }
}

void push_down(vector<Track> &data, int unsorted)
{ // preconditions:
    assert(is_heap(data, {1, unsorted}));
    //postconditions: slice, {0,unsorted+1} of data is a heap structure
    int i = 0;
    while ((2 * (i + 1) - 1 <= unsorted && data[i] < data[2 * (i + 1) - 1]) || (2 * (i + 1) <= unsorted && data[i] < data[2 * (i + 1)]))
    {
        int j = 2 * (i + 1) - 1;
        if (j <= unsorted)
        {
            if (j + 1 <= unsorted && data[j] < data[j + 1])
            {
                j++;
            }
            swap(data, i, j);
            i = j;
        }
        else
        {
            return;
        }
    }
}

void pick_heap(vector<Track> &data)
{ // postconditions:
    assert(is_heap(data, {0, size(data)}));
    // postconditions: data has been sorted in increasing order
    int unsorted = size(data) - 1;
    while (unsorted > 0)
    {
        swap(data, 0, unsorted--);
        push_down(data, unsorted);
    }
}

void heap_sort(vector<Track> &data)
{ // preconditions:
    assert(true);
    // postconditions: data has been sorted in increasing order
    build_heap(data);
    pick_heap(data); // build heap is called during the assertion
}
/*
//mandatory part 1
void dnf(vector<Track> &data, int first, int last, int &red, int &blue)
{ // preconditions:
    assert(true);
    // postconditions: we will have correctly places all values
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track PIVOT = data[first + (last - first) / 2];
    while (red < white - 1)
    {
        const int NEXT = white - 1;
        if (data[NEXT] < PIVOT)
        {
            red++;
            swap(data, red, NEXT);
        }
        else if (data[NEXT] == PIVOT)
        {
            white--;
        }
        else
        {
            white--;
            blue--;
            swap(data, NEXT, blue);
        }
    }
    if (blue == last + 1)
        blue = last;
    if (red == first - 1)
        red = first;
}
*/
// mandatory part 2
void dnf(vector<Track> &data, int first, int last, int &red, int &blue)
{ // preconditions:
    assert(true);
    // postconditions: we will have correctly places all values
    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const Track PIVOT = data[first + (last - first) / 2];
    while (blue > white + 1)
    {
        const int NEXT = white + 1;
        if (data[NEXT] < PIVOT)
        {
            red++;
            white++;
            swap(data, red, NEXT);
        }
        else if (data[NEXT] == PIVOT)
        {
            white++;
        }
        else
        {
            blue--;
            swap(data, NEXT, blue);
        }
    }
    if (blue == last + 1)
        blue = last;
    if (red == first - 1)
        red = first;
}

// mandatory part 1 and 2
void quicksort(vector<Track> &data, int first, int last)
{ // preconditions;
    assert(0 <= first && last < data.size());
    // postconditions: we will have sorted the tracks from first to last
    if (first >= last)
        return;

    int red, blue;
    dnf(data, first, last, red, blue);

    quicksort(data, first, red);
    quicksort(data, blue, last);
}

void sort(vector<Track> &_tracks)
{ // preconditions
    assert(true);
    // postconditions: we will have sorted tracks
    vector<Track> tracks;
    for (int i = 0; i < size(_tracks); i++)
    {
        tracks.push_back(_tracks[i]);
    }
    cout << "Sorting by quicksort: " << endl;
    quicksort(tracks, 0, size(tracks) - 1);
    cout << "The runtime is: " << runtime << endl
         << endl;
    runtime = 0;
    /*for (int i = 0; i < size(_tracks); i++)
    {
        tracks[i] = _tracks[i];
    }
    cout << "Sorting by selection: " << endl;
    selection_sort(tracks);
    cout << "The runtime is: " << runtime << endl
         << endl;
    runtime = 0;
    for (int i = 0; i < size(_tracks); i++)
    {
        tracks[i] = _tracks[i];
    }
    cout << "Sorting by bubble: " << endl;
    bubble_sort(tracks);
    cout << "The runtime is: " << runtime << endl
         << endl;
    runtime = 0;
    for (int i = 0; i < size(_tracks); i++)
    {
        tracks[i] = _tracks[i];
    }
    cout << "Sorting by heap: " << endl;
    heap_sort(tracks);
    cout << "The runtime is: " << runtime << endl
         << endl;
    runtime = 0;*/
}

void output_runtime(int runtime)
{
    while (runtime > 100000)
    {
        cout << "*";
        runtime -= 100000;
    }
    if (runtime > 0)
    {
        cout << ".";
    }
    cout << endl;
}

void test_runtime(vector<Track> &tracks, string algorithm)
{
    cout << algorithm << endl;
    Size len = 100;
    while (len <= 6700)
    {
        runtime = 0;
        vector<Track> data;
        for (Size i = 0; i < len; i++)
        {
            data.push_back(tracks[i]);
        }
        if (algorithm == "Insertion")
            insertion_sort(data);
        else if (algorithm == "Selection")
            selection_sort(data);
        else if (algorithm == "Bubble")
            bubble_sort(data);
        else if (algorithm == "Quicksort")
            quicksort(data, 0, size(data) - 1);
        else
            heap_sort(data);
        output_runtime(runtime);
        len += 100;
    }
}

int main()
{ // Precondition:
    assert(true);
    /*  Postcondition:
    the music database "Tracks.txt" has been read (if present and correctly formatted).
    The assignment queries have been executed and their result has been shown on screen.
    In case of the bonus assignment, the user has been able to query the database and has
    seen the results of these queries.
*/
    vector<Track> trackList;
    ifstream data_set;
    data_set.open("Tracks.txt");
    while (!data_set.fail())
    {
        Track new_track;
        data_set >> new_track;
        if (new_track.artist != "")
        {
            trackList.push_back(new_track);
        }
    }
    /*
    test_runtime(trackList, "Insertion");
    test_runtime(trackList, "Selection");
    test_runtime(trackList, "Bubble");
    test_runtime(trackList, "Heap");
    */
    sort(trackList);

    while (true)
    {
    }

    return 0;
}

/*
Mandatory part 3

void sort (vector<El>& v, int n)
{
    // if (n<=1) return; This is the base case
    if (n > 1) 
    {
        const int POS = largest (v, 0, n-1);
        swap (v, POS, n-1);
        sort (v, n-1); 
    }
}
int largest (vector<El>& v, int low, int up)
{
    if (low >= up) return low; // if (c(x)) return d(x);
    const int POS = largest (v, low+1, up); // B r = recursive(f(x))
    if (v[low] > v[POS]) return low;
    else return POS; // return m(x,r)
}

These function become:

void sort(vector<El>& v, int n)
{
    while(n>1)
    {
        const int POS = largest (v, 0, n-1);
        swap(v, POS, n-1);
        n-=1;
    }
}
int largest (vector<El>& v, int low, int up)
{
    vector<vector<El>> stack;
    int _low = low;
    while(low < up){
        stack.push_back(v);
        // this is to kick out the first element of v
        vector<El> temp;
        for (int i=size(v)-1; i>=0; i--)
        {
            temp.push_back(v[i]);
        }
        temp.pop_back();
        v={};
        for (int i=size(temp)-1; i>=0; i--)
        {
            v.push_back(temp[i]);
        }
        low++;
    }
    low = _low;
    int r = low;
    while(size(stack) > 0)
    {
        v = stack[size(stack)-1];
        stack.pop_back();
        if (v[low] > v[r]) r = low;
        else r = r;
        low += 1; // we dont keep track of low in the stack, so we edit it over here
    }
    return r;
}

*/
