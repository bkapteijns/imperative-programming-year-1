#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

struct Product
{
  int price;
  string name;
};

bool good_wishlist(vector<Product> wishList)
{
  for (int i = 0; i < wishList.size(); i++)
  {
    if (wishList[i].price < 0)
      return false;
  }
  return true;
}

int sum(vector<Product> &list, int j)
{ // preconditions:
  assert(true);
  // postconditions we will have returned the sum of all elements of list from j and on
  int result = 0;
  if (j >= list.size())
    return result;
  for (int i = j; i < list.size(); i++)
  {
    result += list[i].price;
  }
  return result;
}

Product minimum(vector<Product> &list, int j)
{ // preconditions:
  assert(j < list.size());
  // postconditions: we will have returned the minimum element of list form j and on
  Product min = list[j];
  for (int i = j + 1; i < list.size(); i++)
  {
    if (list[i].price < min.price)
    {
      min = list[i];
    }
  }
  return min;
}

void improve(vector<Product> &current, vector<Product> &best)
{ // preconditions
  assert(true);
  // postconditions: best has become current only if sum(current,0) > sum(best, 0)
  if (sum(current, 0) > sum(best, 0))
  {
    best = {};
    for (int i = 0; i < current.size(); i++)
    {
      best.push_back(current[i]);
    }
  }
}

int gifts(vector<Product> &current, vector<Product> &best, vector<Product> &m, int c, int target)
{ // preconditions:
  assert(c >= 0 && c <= m.size() && good_wishlist(m));
  // postconditions: result is the best combination of products from the wishlist

  // BASE CASES
  if (target == 0)
  {
    improve(current, best);
    return 1;
  }
  if (target < 0)
    return 0;
  if (c == m.size())
  {
    improve(current, best);
    return 0;
  }
  if (sum(current, 0) + sum(m, c) <= sum(best, 0))
    return 0;

  // RECURSIVE CASES
  if (target > 0 && c < m.size())
  {
    current.push_back(m[c]);
    int with_c = gifts(current, best, m, c + 1, target - m[c].price);
    current.pop_back();
    int without_c = gifts(current, best, m, c + 1, target);
    return with_c + without_c;
  }
}

int main()
{
  vector<Product> store = {};
  char c;
  ifstream infile;
  infile.open("giftstore.txt");
  while (!infile.fail())
  {
    int price;
    string name;
    infile >> price;
    infile.get(c);
    getline(infile, name);
    if (name != "")
      store.push_back({price, name});
  }
  infile.clear();
  infile.close();

  while (true)
  {
    vector<string> wishList = {};
    int budget = 0;
    cout << "Give a name: Andrew, Belle, Chris, Desiree, Edward, Fabienne" << endl;
    string child;
    string budget_string;
    cin >> child;
    if (child == "Andrew" || child == "Belle" || child == "Chris" || child == "Desiree" || child == "Edward" || child == "Fabienne")
    {
      string filename = child + ".txt";
      infile.open(filename);
      infile >> budget;
      while (!infile.fail())
      {
        string item;
        getline(infile, item);
        if (item != "")
        {
          wishList.push_back(item);
        }
      }

      vector<Product> current = {};
      vector<Product> best = {};
      vector<Product> m = {};

      for (int i = 0; i < wishList.size(); i++)
      {
        for (int j = 0; j < store.size(); j++)
        {
          if (wishList[i] == store[j].name)
          {
            m.push_back(store[j]);
          }
        }
      }

      gifts(current, best, m, 0, budget);

      cout << "Dear " << child << ", wazzup my homie. I got " << best.size() << " presents for your budget:" << endl
           << endl;
      for (int i = 0; i < best.size(); i++)
      {
        cout << best[i].name << " worth " << best[i].price << " cents" << endl;
      }
      cout << endl
           << "But I heard you have been naughty this year, so you get squat@!" << endl;
    }
    else if (child == "stop")
    {
      return 0;
    }
    else
    {
      cout << "Stop or give a good name!!!1!1!1!" << endl;
    }
    infile.clear();
    infile.close();
  }

  return 0;
}
