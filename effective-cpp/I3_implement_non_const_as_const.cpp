#include <iostream>

using namespace std;

class textBlock
{
public:
  textBlock(const string &val): text(val) {}

  const string& getText(void) const
  {
    return text;
  }

  char& operator[](const size_t position)
  {
    const char &temp = static_cast<const textBlock &>(*this)[position];
    return const_cast<char &>(temp);
  }

  const char& operator[](const size_t position) const
  {
    //do bounds and error checking
    return text[position];
  }

private:
  string text;
};

int main()
{

  textBlock obj("Hello World");
  const textBlock cObj("Const World");

  cout << obj[0] << endl;
  cout << obj.getText() << endl;
  obj[0] = 'J';
  cout << obj.getText() << endl;

  return 0;
}
