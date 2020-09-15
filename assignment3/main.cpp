#include <iostream>
#include <cmath>

using namespace std;

// Mario Patroza - s1028653 - Computing science
// Bram Kapteijns - s1052111 - Computing science

/* Desktop testing

* Inclusion algorithm

epsilon = 0.1

  v = 0:
v = 0 => a = 0 and b = 1
a * a == v => sqrt(v) = a = 0

  v = 1:
v = 1 => a = 0 and b = 1
b * b == v => sqrt(v) = b = 1

  v = 0.3:
v = 0.3 => a = 0 and b = 1
x = (a + b)/2 = 0.5
|x * x - v| = .05 < 0.1
sqrt(v) = x = 0.5

  v = 4:
v = 4 => a = 0 and b = 4
x = (a + b)/2 = 2
|x * x - v| = 0 < 0.1
sqrt(v) = x = 2

  v = 50:
v = 50 => a = 0 and b = 50
x = (a + b)/2 = 25
|x * x - v| = 575 > 0.1 and 25*25 > v
b = 25
x = (a + b)/2 = 12.5
|x * x - v| = 106.25 > 0.1 and 12.5 * 12.5 > v
b = 12.5
x = (a + b)/2 = 6.25
|x * x - v| = 10.9... > 0.1 and 6.25 * 6.25 < v
a = 6.25
x = (a + b)/2 = 9.375
|x * x - v| = 37.9... > 0.1 and 9.375*9.375 > v
b = 9.375
x = (a + b)/2 = 7.8125
|x * x - v| = 11.0... > 0.1 and 7.8125*7.8125 > v
b = 7.8125
x = (a + b)/2 = 7.03125
|x * x - v| = 0.56 > 0.1 and 7.03125*7.03125 < v
a = 7.03125
x = (a + b)/2 = 7.421875
|x * x - v| = 5.1... > 0.1 and 7.421875 > v
b = 7.421875
x = (a + b)/2 = 7.2265625
|x * x - v| = 2.2 > 0.1 and 7.2... * 7.2... > v
b = 7.2...
x = (a + b)/2 = 7.12890625
|x * x - v| = 0.8 > 0.1 and 7.1... * 7.1... > v
b = 7.1...
x = (a + b)/2 = 7.080078125
|x * x - v| = 0.13 > 0.1 and 7.08... * 7.08... > v
b = 7.08...
x = (a + b)/2 = 7.056640625
|x * x - v| = 0.22 > 0.1 and 7.05... * 7.05... < v
a = 7.05...
x = (a + b)/2 = 7.06787109375
|x * x - v| = 0.05 < 0.1
sqrt(v) = x = 7.067871090375


* Newton-Raphson

  v = 0
v = 0 => x = 1
|x * x - v| = 1 > 0.1
x = x - 1/2 = 0.5
|x * x - v| = 0.25 > 0.1
x = x - 1/4 = 0.25
|x * x - v| = 0.0625 < 0.1
sqrt(v) = x = 0.0625
  v = 1
v = 1 => x = 1
|x * x - 1| = 0 < 0.1
sqrt(v) = x - 1
  v = 0.95
v = 0.95 => x = 1
|x * x - v| = 0.05 < 0.1
sqrt(v) = x = 1
  v = 4
v = 4 => x = 4
|x * x - v| = 12 > 0.1
x = x - 3/2 = 2.5
|x * x - v| = 2.25 > 0.1
x = x - 0.2125 = 2.2875
|x * x - v| = 1.2... > 0.1
x = x - 0.26... = 2.018...
|x * x - v| = 0.07... < 0.1
sqrt(v) = x = 2.018...
  v = 11
v = 11 => x = 11
|x * x - v| = 110 > 0.1
x = x - 5 = 6
|x * x - v| = 25 > 0.1
x = x - 25/11 = 3+8/11
|x * x - v| = 2.89... > 0.1
x = 3.3...
|x * x - v| = 0.15... > 0.1
x = 3.316...
|x * x - v| = 0.0005... < 0.1
sqrt(v) = x = 3.316...
*/

void inclusion(double v, double e)
{
  // assign the needed variables
  int n = 1;
  double a = 0;
  double b = max(1.0, v);
  double x = (a + b) / 2;

  // check if either a or b is the square root of v
  if (a * a == v)
  {
    cout << "Inclusion square root of " << v << " is " << a << " (a)" << endl;
  }
  else if (b * b == v)
  {
    cout << "Inclusion square root of " << v << " is " << b << " (b)" << endl;
  }

  // loop until x is close enough to the square root of v
  while (abs(x * x - v) > e)
  {
    // do the algorithm
    if (x * x > v)
    {
      b = x;
    }
    else
    {
      a = x;
    }
    x = (a + b) / 2;
    // increase n by one
    n++;
  }

  cout << "Inclusion square root of " << v << " is " << x << " for epsilon " << e << " (loop amount: " << n << ")" << endl;

  return;
}

void newton_raphson(double v, double e)
{
  // assign the needed vars
  int n = 1;
  double x = max(1.0, v);

  // loop until the x is close enough to the square root of v
  while (abs(x * x - v) > e)
  {
    // do the algorithm
    x = x - (x * x - v) / (2 * x);
    n++;
  }

  cout << "Newton_raphson square root of " << v << " is " << x << " for epsilon " << e << " (loop amount: " << n << ")" << endl;

  return;
}

int main()
{
  // Store the value 'v' and the epsilon
  double value;
  double epsilon;

  // Make sure the program does not quit after only one number
  while (true)
  {
    cout << "First give the number of which you want to compute the square root" << endl;
    cout << "Then give the desired epsilon value" << endl;
    cin >> value >> epsilon;
    cout << "This is the value: " << value << endl;
    cout << "And this is the epsilon: " << epsilon << endl;
    // do the inclusion and newton_raphson algorithm
    inclusion(value, epsilon);
    newton_raphson(value, epsilon);
    cout << endl;
  }

  return 0;
}
