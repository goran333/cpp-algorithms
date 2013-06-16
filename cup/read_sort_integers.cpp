#include <iostream> 
#include <vector>
#include <algorithm>

using namespace std;

int main() 
{
  cout << "enter max nos -->\n";
  int max = 0;
  cin >> max;

  int number;
  vector<int> numbers;
  for(int i = 0; i < max; ++i)
    {
      cin >> number;
      numbers.push_back(number);
    }
  sort(numbers.begin(), numbers.end());

  cout << "sorted list ...\n";

  for(size_t i = 0; i < numbers.size(); ++i)
    cout << numbers[i] << "\n";
}
