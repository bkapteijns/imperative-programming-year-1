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

/* For testing purposes, you can use the below defined, very small, music database.
   This is also convenient if you have not yet implemented reading the database file.
*/
vector<Track> testDB = {{"Adele", "19", 2008, 1, "Daydreamer", "pop,debut album", {3, 40}, "England"}, {"Adele", "19", 2008, 10, "My same", "pop,debut album", {3, 15}, "England"}, {"Adele", "19", 2008, 11, "Tired", "pop,debut album", {4, 18}, "England"}, {"Adele", "19", 2008, 12, "Hometown glory", "pop,debut album", {4, 31}, "England"}, {"Adele", "19", 2008, 2, "Best for last", "pop,debut album", {4, 18}, "England"}, {"Adele", "19", 2008, 3, "Chasing pavements", "pop,debut album", {3, 30}, "England"}, {"Adele", "19", 2008, 4, "Cold shoulder", "pop,debut album", {3, 11}, "England"}, {"Adele", "19", 2008, 5, "Crazy for you", "pop,debut album", {3, 28}, "England"}, {"Adele", "19", 2008, 6, "Melt my heart to stone", "pop,debut album", {3, 23}, "England"}, {"Adele", "19", 2008, 7, "First love", "pop,debut album", {3, 10}, "England"}, {"Adele", "19", 2008, 8, "Right as rain", "pop,debut album", {3, 17}, "England"}, {"Adele", "19", 2008, 9, "Make you feel my love", "pop,debut album", {3, 32}, "England"}, {"Adele", "21", 2011, 1, "Rolling in the deep", "pop", {3, 49}, "England"}, {"Adele", "21", 2011, 10, "Lovesong", "pop", {5, 16}, "England"}, {"Adele", "21", 2011, 11, "Someone like you", "pop", {4, 47}, "England"}, {"Adele", "21", 2011, 2, "Rumour has it", "pop", {3, 43}, "England"}, {"Adele", "21", 2011, 3, "Turning tables", "pop", {4, 10}, "England"}, {"Adele", "21", 2011, 4, "Don't you remember", "pop", {4, 3}, "England"}, {"Adele", "21", 2011, 5, "Set fire to the rain", "pop", {4, 1}, "England"}, {"Adele", "21", 2011, 6, "He won't go", "pop", {4, 37}, "England"}, {"Adele", "21", 2011, 7, "Take it all", "pop", {3, 48}, "England"}, {"Adele", "21", 2011, 8, "I'll be waiting", "pop", {4, 1}, "England"}, {"Adele", "21", 2011, 9, "One and only", "pop", {5, 48}, "England"}, {"All them witches", "Dying surfer meets his maker", 2015, 1, "Call me star", "alternative,rock", {3, 54}, "U.S.A."}, {"All them witches", "Dying surfer meets his maker", 2015, 2, "El centro", "alternative,rock,instrumental", {8, 25}, "U.S.A."}, {"All them witches", "Dying surfer meets his maker", 2015, 3, "Dirt preachers", "alternative,rock", {3, 44}, "U.S.A."}, {"All them witches", "Dying surfer meets his maker", 2015, 4, "This is where it falls apart", "alternative,rock", {7, 2}, "U.S.A."}, {"All them witches", "Dying surfer meets his maker", 2015, 5, "Mellowing", "alternative,instrumental", {3, 11}, "U.S.A."}, {"All them witches", "Dying surfer meets his maker", 2015, 6, "Open passageways", "alternative,rock", {3, 14}, "U.S.A."}, {"All them witches", "Dying surfer meets his maker", 2015, 7, "Instrumental 2 (welcome to the caveman future)", "alternative,rock,instrumental", {2, 33}, "U.S.A."}, {"All them witches", "Dying surfer meets his maker", 2015, 8, "Talisman", "alternative,rock", {6, 7}, "U.S.A."}, {"All them witches", "Dying surfer meets his maker", 2015, 9, "Blood and sand / milk and endless waters", "alternative,rock", {7, 20}, "U.S.A."}, {"The decemberists", "The tain", 2005, 1, "The tain (parts i-iv)", "progressive,experimental,folk,rock", {18, 35}, "U.S.A."}, {"Colin Stetson and Sarah Neufeld", "Never were the way she was", 2015, 1, "The sun roars into view", "jazz,instrumental,experimental", {7, 37}, "U.S.A.,Canada"}, {"Colin Stetson and Sarah Neufeld", "Never were the way she was", 2015, 2, "Won't be a thing to become", "jazz,instrumental,experimental", {3, 24}, "U.S.A.,Canada"}, {"Colin Stetson and Sarah Neufeld", "Never were the way she was", 2015, 3, "In the vespers", "jazz,instrumental,experimental", {6, 2}, "U.S.A.,Canada"}, {"Colin Stetson and Sarah Neufeld", "Never were the way she was", 2015, 4, "And still they move", "jazz,instrumental,experimental", {2, 56}, "U.S.A.,Canada"}, {"Colin Stetson and Sarah Neufeld", "Never were the way she was", 2015, 5, "With the dark hug of time", "jazz,instrumental,experimental", {6, 34}, "U.S.A.,Canada"}, {"Colin Stetson and Sarah Neufeld", "Never were the way she was", 2015, 6, "The rest of us", "jazz,instrumental,experimental", {6, 30}, "U.S.A.,Canada"}, {"Colin Stetson and Sarah Neufeld", "Never were the way she was", 2015, 7, "Never were the way she was", "jazz,instrumental,experimental", {8, 12}, "U.S.A.,Canada"}, {"Colin Stetson and Sarah Neufeld", "Never were the way she was", 2015, 8, "Flight", "jazz,instrumental,experimental", {1, 38}, "U.S.A.,Canada"}};

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

    InputText input;
    char c;
    while (true)
    {
        cout << "Give your command:" << endl;
        cin >> input;
        if (input == "track")
        {
            cin.get(c);
            getline(cin, input);
            cout << "Number of tracks: " << match_tracks(trackList, input, true) << endl;
        }
        else if (input == "artist")
        {
            cin.get(c);
            getline(cin, input);
            cout << "Number of artists: " << match_artists(trackList, input, true) << endl;
        }
        else if (input == "cds")
        {
            cin.get(c);
            getline(cin, input);
            cout << "Number of cds from artists: " << match_cds(trackList, input, true) << endl;
        }
        else if (input == "#cds")
        {
            getline(cin, input);
            cout << "Total number of cds: " << number_of_cds(trackList) << endl;
        }
        else if (input == "year")
        {
            cin.get(c);
            getline(cin, input);
            cout << "Number of tracks in year: " << match_year(trackList, input, true) << endl;
        }
        else if (input == "stop")
        {
            return 0;
        }
    }

    while (true)
    {
    }

    return 0;
}
