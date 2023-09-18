#include <iostream>
#include <string>
#include <cstring>

using std::cout;
using std::string;

class hangers{
 public:
  hangers(const int n);
  ~hangers();
  hangers(const hangers &cpy_val);
  string* operator[](const int i) const;
  const string& operator=(const string str);
//  const string& operator+=(const string rhs_str);
  // void operator[](const int i);
  operator bool() const;
  int get_n()const {return _len;};
  friend std::ostream& operator <<(std::ostream& s, const hangers h);

 private:
  string** _hangers_list;
  int _len;
};

hangers::hangers(const int n): _hangers_list(new string*[n]), _len(n){};

hangers::~hangers()
{
  delete[] _hangers_list;
}

string* hangers::operator[](const int i) const
{
  int ind = i%_len;
  // cout<<" ind: " << ind;
  return _hangers_list[ind];
}

// void hangers::operator[](const int i, const string& clothes)
// {
//     _hangers_list[i] = new string*(string(clothes));
// }


std::ostream& operator<<(std::ostream& s, const hangers h)
{
  int len = h.get_n();
  for(int i=0; i<len; i++)
  {
    s << i << ": " << h[i] << std::endl;
  }
  return s;
}

hangers::hangers(const hangers &cpy_val)
{
  _len = cpy_val._len;
  _hangers_list = new string*[_len];
  for(int i=0; i<_len; i++)
    {
      // _hangers_list[i] = new string;
      _hangers_list[i] = cpy_val._hangers_list[i];
    }
}

// const string& hangers::operator=(const string str)
// {

//     return new string(str);
// }

hangers::operator bool()const
{
  //iterate and if not empty return 1
  for(int i=0; i<_len; i++)
  {
    if(!_hangers_list[i])
      return false;
  }
  return true;
}

int main()
{
  hangers h(4);
  h[4] = "Coat";
  std::cout << h;
  return 0;
}