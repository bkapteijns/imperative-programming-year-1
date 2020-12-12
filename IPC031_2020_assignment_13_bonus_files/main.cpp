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

Coords go_north(Coords location, vector<vector<char>> field, bool flamingo = true)
{ // preconditions:
  assert(good_location(location, field));
  // postconditions: we will have moved the flamingo north on the field
  while (location.y > 0 &&
         field[location.y - 1][location.x] != 'p' && field[location.y - 1][location.x] != 'P' &&
         field[location.y - 1][location.x] != 'f' && field[location.y - 1][location.x] != 'F' &&
         ((flamingo && field[location.y][location.x] != 'x') || !flamingo))
  {
    location.y -= 1;
  }
  if (location.y <= 0 && (field[location.y][location.x] != 'x' || !flamingo))
  {
    return {-1, -1};
  }
  return location;
}
Coords go_east(Coords location, vector<vector<char>> field, bool flamingo = true)
{ // preconditions:
  assert(good_location(location, field));
  // postconditions: we will have moved the flamingo east on the field
  while (location.x < field[0].size() - 1 &&
         field[location.y][location.x + 1] != 'p' && field[location.y][location.x + 1] != 'P' &&
         field[location.y][location.x + 1] != 'f' && field[location.y][location.x + 1] != 'F' &&
         ((field[location.y][location.x] != 'x' && flamingo) || !flamingo))
  {
    location.x += 1;
  }
  if (location.x >= field[0].size() - 1 && (field[location.y][location.x] != 'x' || !flamingo))
  {
    return {-1, -1};
  }
  return location;
}
Coords go_south(Coords location, vector<vector<char>> field, bool flamingo = true)
{ // preconditions:
  assert(good_location(location, field));
  // postconditions: we will have moved the flamingo south on the field
  while (location.y < field.size() - 1 &&
         field[location.y + 1][location.x] != 'p' && field[location.y + 1][location.x] != 'P' &&
         field[location.y + 1][location.x] != 'f' && field[location.y + 1][location.x] != 'F' &&
         ((field[location.y][location.x] != 'x' && flamingo) || !flamingo))
  {
    location.y += 1;
  }
  if (location.y >= field.size() - 1 && (field[location.y][location.x] != 'x' || !flamingo))
  {
    return {-1, -1};
  }
  return location;
}
Coords go_west(Coords location, vector<vector<char>> field, bool flamingo = true)
{ // preconditions:
  assert(good_location(location, field));
  // postconditions: we will have moved the flamingo west on the field
  while (location.x > 0 &&
         field[location.y][location.x - 1] != 'p' && field[location.y][location.x - 1] != 'P' &&
         field[location.y][location.x - 1] != 'f' && field[location.y][location.x - 1] != 'F' &&
         ((field[location.y][location.x] != 'x' && flamingo) || !flamingo))
  {
    location.x -= 1;
  }
  if (location.x <= 0 && (field[location.y][location.x] != 'x' || !flamingo))
  {
    return {-1, -1};
  }
  return location;
}

Coords find_flamingo(vector<vector<char>> field)
{ // preconditions
  assert(true);
  // postconditions: returns the location of the flamingo
  for (int i = 0; i < field.size(); i++)
  {
    for (int j = 0; j < field[0].size(); j++)
    {
      if (field[i][j] == 'f' || field[i][j] == 'F')
        return {j, i};
    }
  }
}

vector<Coords> find_penguins(vector<vector<char>> field)
{ // preconditions
  assert(true);
  // postconditions: returns the locations of the penguins
  vector<Coords> locations = {};
  for (int i = 0; i < field.size(); i++)
  {
    for (int j = 0; j < field[0].size(); j++)
    {
      if (field[i][j] == 'p' || field[i][j] == 'P')
        locations.push_back({j, i});
    }
  }
  return locations;
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
  // postconditions: we will have moved the flamingo
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

vector<vector<char>> move_penguin(vector<vector<char>> field, Coords old, Coords next)
{ // preconditions
  assert(good_location(old, field) && good_location(next, field));
  // we will have moved the penguin
  if (field[next.y][next.x] == 'x')
  {
    field[old.y][old.x] = '.';
    field[next.y][next.x] = 'P';
  }
  else
  {
    field[old.y][old.x] = '.';
    field[next.y][next.x] = 'p';
  }
  return field;
}

bool puzzle_present(vector<Candidate> c, vector<vector<char>> newp)
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

void remove_penguin(vector<Candidate> &c, int i, Coords penguin)
{ // preconditions:
  assert(good_location(penguin, c[i].candidate));
  // postconditions: we will have modified candidate to contain a new puzzle (where the penguin is gone)
  vector<vector<char>> newp = c[i].candidate;
  if (newp[penguin.y][penguin.x] == 'P')
    newp[penguin.y][penguin.x] = 'x';
  else
    newp[penguin.y][penguin.x] = '.';
  if (!puzzle_present(c, newp))
    c.push_back({newp, i});
}

void tries(vector<Candidate> &c, int i, Coords old, Coords next, bool flamingo = true)
{ // preconditions
  assert(true);
  // postconditions: we will have modified candidate to contain new puzzle
  vector<vector<char>> p = c[i].candidate;
  vector<vector<char>> newp;
  if (flamingo)
    newp = move_flamingo(p, old, next);
  else
    newp = move_penguin(p, old, next);
  Candidate newc = {newp, i};
  if (!puzzle_present(c, newp))
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
    vector<Coords> penguins = find_penguins(p);
    for (int j = 0; j < penguins.size(); j++)
    {
      if (good_location(go_north(penguins[j], p, false), p))
      {
        tries(c, i, penguins[j], go_north(penguins[j], p, false), false);
      }
      else
      {
        remove_penguin(c, i, penguins[j]);
      }
      if (good_location(go_east(penguins[j], p, false), p))
      {
        tries(c, i, penguins[j], go_east(penguins[j], p, false), false);
      }
      else
      {
        remove_penguin(c, i, penguins[j]);
      }
      if (good_location(go_south(penguins[j], p, false), p))
      {
        tries(c, i, penguins[j], go_south(penguins[j], p, false), false);
      }
      else
      {
        remove_penguin(c, i, penguins[j]);
      }
      if (good_location(go_west(penguins[j], p, false), p))
      {
        tries(c, i, penguins[j], go_west(penguins[j], p, false), false);
      }
      else
      {
        remove_penguin(c, i, penguins[j]);
      }
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

vector<vector<char>> remove_recursive_penguin(vector<vector<char>> ice, Coords location)
{ // preconditions
  assert(good_location(location, ice));
  // postconditions: we will have returned the ice, but without the penguin
  if (ice[location.y][location.x] == 'P')
    ice[location.y][location.x] = 'x';
  else
    ice[location.y][location.x] = '.';
  return ice;
}

int recursive(vector<vector<vector<char>>> &current_path, int depth_bound)
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
  if (current_path.size() - 1 >= depth_bound)
  {
    return -1;
  }

  // RESCURSIVE CASE
  Coords location = find_flamingo(current_path[current_path.size() - 1]);
  if (good_location(go_north(location, current_path[current_path.size() - 1]), current_path[current_path.size() - 1]))
  {
    vector<vector<char>> new_field = move_flamingo(current_path[current_path.size() - 1], location, go_north(location, current_path[current_path.size() - 1]));
    Coords old_location = location;
    current_path.push_back(new_field);
    location = go_north(location, current_path[current_path.size() - 1]);
    recursive(current_path, depth_bound);
    current_path.pop_back();
    location = old_location;
  }
  if (good_location(go_east(location, current_path[current_path.size() - 1]), current_path[current_path.size() - 1]))
  {
    vector<vector<char>> new_field = move_flamingo(current_path[current_path.size() - 1], location, go_east(location, current_path[current_path.size() - 1]));
    Coords old_location = location;
    current_path.push_back(new_field);
    location = go_east(location, current_path[current_path.size() - 1]);
    recursive(current_path, depth_bound);
    current_path.pop_back();
    location = old_location;
  }
  if (good_location(go_south(location, current_path[current_path.size() - 1]), current_path[current_path.size() - 1]))
  {
    vector<vector<char>> new_field = move_flamingo(current_path[current_path.size() - 1], location, go_south(location, current_path[current_path.size() - 1]));
    Coords old_location = location;
    current_path.push_back(new_field);
    location = go_south(location, current_path[current_path.size() - 1]);
    recursive(current_path, depth_bound);
    current_path.pop_back();
    location = old_location;
  }
  if (good_location(go_west(location, current_path[current_path.size() - 1]), current_path[current_path.size() - 1]))
  {
    vector<vector<char>> new_field = move_flamingo(current_path[current_path.size() - 1], location, go_west(location, current_path[current_path.size() - 1]));
    Coords old_location = location;
    current_path.push_back(new_field);
    location = go_west(location, current_path[current_path.size() - 1]);
    recursive(current_path, depth_bound);
    current_path.pop_back();
    location = old_location;
  }

  vector<Coords> penguins = find_penguins(current_path[current_path.size() - 1]);
  for (int j = 0; j < penguins.size(); j++)
  {
    if (good_location(go_north(penguins[j], current_path[current_path.size() - 1], false), current_path[current_path.size() - 1]))
    {
      vector<vector<char>> new_path = move_penguin(current_path[current_path.size() - 1], penguins[j], go_north(penguins[j], current_path[current_path.size() - 1], false));
      current_path.push_back(new_path);
    }
    else
    {
      vector<vector<char>> new_path = remove_recursive_penguin(current_path[current_path.size() - 1], penguins[j]);
      current_path.push_back(new_path);
    }
    recursive(current_path, depth_bound);
    current_path.pop_back();

    if (good_location(go_east(penguins[j], current_path[current_path.size() - 1], false), current_path[current_path.size() - 1]))
    {
      vector<vector<char>> new_path = move_penguin(current_path[current_path.size() - 1], penguins[j], go_east(penguins[j], current_path[current_path.size() - 1], false));
      current_path.push_back(new_path);
    }
    else
    {
      vector<vector<char>> new_path = remove_recursive_penguin(current_path[current_path.size() - 1], penguins[j]);
      current_path.push_back(new_path);
    }
    recursive(current_path, depth_bound);
    current_path.pop_back();

    if (good_location(go_south(penguins[j], current_path[current_path.size() - 1], false), current_path[current_path.size() - 1]))
    {
      vector<vector<char>> new_path = move_penguin(current_path[current_path.size() - 1], penguins[j], go_south(penguins[j], current_path[current_path.size() - 1], false));
      current_path.push_back(new_path);
    }
    else
    {
      vector<vector<char>> new_path = remove_recursive_penguin(current_path[current_path.size() - 1], penguins[j]);
      current_path.push_back(new_path);
    }
    recursive(current_path, depth_bound);
    current_path.pop_back();

    if (good_location(go_west(penguins[j], current_path[current_path.size() - 1], false), current_path[current_path.size() - 1]))
    {
      vector<vector<char>> new_path = move_penguin(current_path[current_path.size() - 1], penguins[j], go_west(penguins[j], current_path[current_path.size() - 1], false));
      current_path.push_back(new_path);
    }
    else
    {
      vector<vector<char>> new_path = remove_recursive_penguin(current_path[current_path.size() - 1], penguins[j]);
      current_path.push_back(new_path);
    }
    recursive(current_path, depth_bound);
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
    cout << "Enter a filename or \"stop\" (6+ steps takes a long time)." << endl;
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

    // Part 2
    solve(field);
    /*
    // Part 3
    best_path = {};
    vector<vector<vector<char>>> field_vector = {field};
    recursive(field_vector, 8);
    show_recursive_path(best_path);
    */
  }

  return 0;
}