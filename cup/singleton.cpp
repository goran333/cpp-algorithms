#include <iostream> 


using namespace std;

template<typename T>
class Singleton
{
public:
  static T* GetInstance()
  {
    if(NULL == _instance)
    {
      cout << "create new one\n";
      _instance = new T;
    }
    else
    {
      cout << "return old instance\n";
    }
    return _instance;
  }

  static T* GetInstance_v2()
  {
    static T t;
    return &t;
  }

private:
  static T* _instance;
  Singleton();
  Singleton(const T&) {}
  T& operator=(const T&) {}
};

template<typename T> T* Singleton<T>::_instance = NULL;

int main()
{
  string *test = Singleton<string>::GetInstance();
  test = Singleton<string>::GetInstance();

  int *test2 = Singleton<int>::GetInstance_v2();
  test2 = Singleton<int>::GetInstance_v2();
}
