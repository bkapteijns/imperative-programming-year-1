#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

struct Coords
{
  int x;
  int y;
};
struct Candidate
{
  vector<vector<char>> candidate;
  int parent_candidate;
};

vector<vector<vector<char>>> best_path = {};

bool good_location(Coords location, vector<vector<char>> field)
{ // preconditions:
  assert(true);
  // postconditions: we will have returned whether the location is a good location
  return (location.x >= 0 && location.y >= 0 && location.y < field.size() && location.x < field[0].size());
}

Coords go_north(Coords location, vector<vector<char>> field)
{ // preconditions:
  assert(good_location(location, field));
  // postconditions: we will have moved the flamingo north on the field
  while (location.y > 0 && field[location.y - 1][location.x] != 'r' && field[location.y][location.x] != 'x')
  {
    location.y -= 1;
  }
  if (location.y <= 0 && field[location.y][location.x] != 'x')
  {
    return {-1, -1};
  }
  return location;
}
Coords go_east(Coords location, vector<vector<char>> field)
{ // preconditions:
  assert(good_location(location, field));
  // postconditions: we will have moved the flamingo east on the field
  while (location.x < field[0].size() - 1 && field[location.y][location.x + 1] != 'r' && field[location.y][location.x] != 'x')
  {
    location.x += 1;
  }
  if (location.x >= field[0].size() - 1 && field[location.y][location.x] != 'x')
  {
    return {-1, -1};
  }
  return location;
}
Coords go_south(Coords location, vector<vector<char>> field)
{ // preconditions:
  assert(good_location(location, field));
  // postconditions: we will have moved the flamingo south on the field
  while (location.y < field.size() - 1 && field[location.y + 1][location.x] != 'r' && field[location.y][location.x] != 'x')
  {
    location.y += 1;
  }
  if (location.y >= field.size() - 1 && field[location.y][location.x] != 'x')
  {
    return {-1, -1};
  }
  return location;
}
Coords go_west(Coords location, vector<vector<char>> field)
{ // preconditions:
  assert(good_location(location, field));
  // postconditions: we will have moved the flamingo west on the field
  while (location.x > 0 && field[location.y][location.x - 1] != 'r' && field[location.y][location.x] != 'x')
  {
    location.x -= 1;
  }
  if (location.x <= 0 && field[location.y][location.x] != 'x')
  {
    return {-1, -1};
  }
  return location;
}

Coords find_flamingo(vector<vector<char>> field)
{
  for (int i = 0; i < field.size(); i++)
  {
    for (int j = 0; j < field[0].size(); j++)
    {
      if (field[i][j] == 'f' || field[i][j] == 'F')
        return {j, i};
    }
  }
}

bool puzzle_ready(vector<vector<char>> field)
{ // preconditions
  assert(true);
  // postconditions: returns true if puzzle is done
  bool done = false;
  for (int i = 0; i < field.size(); i++)
  {
    for (int j = 0; j < field[0].size(); j++)
    {
      if (field[i][j] == 'F')
        done = true;
    }
  }
  return done;
}

vector<vector<char>> move_flamingo(vector<vector<char>> field, Coords old, Coords next)
{ // preconditions
  assert(good_location(old, field) && good_location(next, field));
  if (field[next.y][next.x] == 'x')
  {
    field[old.y][old.x] = '.';
    field[next.y][next.x] = 'F';
  }
  else
  {
    field[old.y][old.x] = '.';
    field[next.y][next.x] = 'f';
  }
  return field;
}

bool puzzle_present(vector<Candidate> c, int i, vector<vector<char>> newp)
{ // preconditions
  assert(true);
  // postconditions: checks if we already have the new puzzle in the candidates
  for (int i = 0; i < c.size(); i++)
  {
    if (c[i].candidate == newp)
      return true;
  }
  return false;
}

void show_candidate(vector<vector<char>> ice)
{ // preconditions
  assert(true);
  // postconditions: we will have printed a current flamingo ice
  for (int i = 0; i < ice.size(); i++)
  {
    for (int j = 0; j < ice[0].size(); j++)
    {
      cout << ice[i][j];
    }
    cout << endl;
  }
  cout << endl;
}

void show_path(vector<Candidate> c, int i)
{ // preconditions:
  assert(i >= 0);
  // postconditions: we will have printed the path of the solutions
  while (i >= 0)
  {
    show_candidate(c[i].candidate);
    i = c[i].parent_candidate;
  }
}

void tries(vector<Candidate> &c, int i, Coords old, Coords next)
{ // preconditions
  assert(true);
  // postconditions: we will have modified candidate to contain new puzzle
  vector<vector<char>> p = c[i].candidate;
  vector<vector<char>> newp = move_flamingo(p, old, next);
  Candidate newc = {newp, i};
  if (!puzzle_present(c, i, newp))
    c.push_back(newc);
}

void solve(vector<vector<char>> start)
{ // preconditions
  assert(true);
  //postcondition: we will have solved a flamingo challenge
  int i = 0;
  vector<Candidate> c = {{start, -1}};
  while (i < c.size() && !puzzle_ready(c[i].candidate))
  {
    vector<vector<char>> p = c[i].candidate;
    Coords location = find_flamingo(p);
    if (good_location(go_north(location, p), p))
    {
      tries(c, i, location, go_north(location, p));
    }
    if (good_location(go_east(location, p), p))
    {
      tries(c, i, location, go_east(location, p));
    }
    if (good_location(go_south(location, p), p))
    {
      tries(c, i, location, go_south(location, p));
    }
    if (good_location(go_west(location, p), p))
    {
      tries(c, i, location, go_west(location, p));
    }
    i++;
  }
  if (i < c.size())
  {
    show_path(c, i);
  }
}

void show_recursive_path(vector<vector<vector<char>>> path)
{ // preconditions:
  assert(true);
  // postconditions: we will have printed the path
  for (int i = 0; i < path.size(); i++)
  {
    show_candidate(path[i]);
  }
}

int recursive(vector<vector<vector<char>>> &current_path, Coords location, int depth_bound)
{ // preconditions:
  assert(true);
  // postconditions: we will have solved a flamingo challenge

  // BASE CASE
  if (puzzle_ready(current_path[current_path.size() - 1]))
  {
    if (current_path.size() < best_path.size() || best_path.size() == 0)
    {
      best_path = current_path;
      return current_path.size();
    }
  }
  if (current_path.size() >= best_path.size() && best_path.size() != 0)
  {
    return -1;
  }
  if (current_path.size() >= depth_bound)
  {
    return -1;
  }

  // RESCURSIVE CASE
  if (good_location(go_north(location, current_path[current_path.size() - 1]), current_path[current_path.size() - 1]))
  {
    vector<vector<char>> new_field = move_flamingo(current_path[current_path.size() - 1], location, go_north(location, current_path[current_path.size() - 1]));
    current_path.push_back(new_field);
    recursive(current_path, go_north(location, current_path[current_path.size() - 1]), depth_bound);
    current_path.pop_back();
  }
  if (good_location(go_east(location, current_path[current_path.size() - 1]), current_path[current_path.size() - 1]))
  {
    vector<vector<char>> new_path = move_flamingo(current_path[current_path.size() - 1], location, go_east(location, current_path[current_path.size() - 1]));
    current_path.push_back(new_path);
    recursive(current_path, go_east(location, current_path[current_path.size() - 1]), depth_bound);
    current_path.pop_back();
  }
  if (good_location(go_south(location, current_path[current_path.size() - 1]), current_path[current_path.size() - 1]))
  {
    vector<vector<char>> new_path = move_flamingo(current_path[current_path.size() - 1], location, go_south(location, current_path[current_path.size() - 1]));
    current_path.push_back(new_path);
    recursive(current_path, go_south(location, current_path[current_path.size() - 1]), depth_bound);
    current_path.pop_back();
  }
  if (good_location(go_west(location, current_path[current_path.size() - 1]), current_path[current_path.size() - 1]))
  {
    vector<vector<char>> new_path = move_flamingo(current_path[current_path.size() - 1], location, go_west(location, current_path[current_path.size() - 1]));
    current_path.push_back(new_path);
    recursive(current_path, go_west(location, current_path[current_path.size() - 1]), depth_bound);
    current_path.pop_back();
  }
  return 1;
}

int main()
{
  ifstream field_file;
  string filename;
  char c;
  while (true)
  {
    vector<vector<char>> field = {{}};
    cout << "Enter a filename or \"stop\"." << endl;
    cin >> filename;

    if (filename == "stop")
    {
      return 0;
    }

    field_file.open(filename);

    while (!field_file.fail())
    {
      field_file.get(c);
      if (c == '\n')
      {
        field.push_back({});
      }
      else
      {
        field[field.size() - 1].push_back(c);
      }
    }

    if (field[field.size() - 1].size() == 0)
    {
      field.pop_back();
      field.pop_back();
    }

    field_file.clear();
    field_file.close();

    /*
    // Part 2
    solve(field);
    */

    // Part 3
    best_path = {};
    vector<vector<vector<char>>> field_vector = {field};
    recursive(field_vector, find_flamingo(field), 15);
    show_recursive_path(best_path);
  }

  return 0;
}