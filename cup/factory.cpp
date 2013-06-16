#include <iostream>
#include <vector>

class IPerson
{
public:
  enum PersonType {StudentType, TeacherType};

  virtual ~IPerson() {}
  virtual void WhoAmI() const = 0;
  static IPerson* Create(PersonType type);
};

class Student: public IPerson
{
public:
  virtual void WhoAmI() const {std::cout << "I am a student\n";}
};

class Teacher: public IPerson
{
public:
  virtual void WhoAmI() const {std::cout << "I am a teacher\n";}
};

IPerson* IPerson::Create(PersonType type = StudentType)
{
  switch(type)
  {
    case TeacherType:
      return new Teacher;
    case StudentType:
    default:
      return new Student;
  }
}

int main()
{
  std::vector<IPerson *> Persons;
  
  Persons.push_back(IPerson::Create(IPerson::StudentType));
  Persons.push_back(IPerson::Create(IPerson::StudentType));
  Persons.push_back(IPerson::Create(IPerson::StudentType));
  Persons.push_back(IPerson::Create(IPerson::TeacherType));
  Persons.push_back(IPerson::Create(IPerson::TeacherType));
  Persons.push_back(IPerson::Create(IPerson::TeacherType));

  for(size_t i = 0; i < Persons.size(); ++i)
    {
      Persons.at(i)->WhoAmI();
    }

  for(size_t i = 0; i < Persons.size(); ++i)
    {
      delete Persons.at(i);
    }
}
