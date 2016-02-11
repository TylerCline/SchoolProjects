#include <iostream>

#include <vector>
#include <iterator>
#include <string>

using namespace std;

template<class elemType>
int seqSearch(const vector<elemType> &list, const elemType& item);

int main()
{
	vector<int> intList;
	vector<string> stringList;
	ostream_iterator<int> screen(cout, " ");
	ostream_iterator<string> screen2(cout, " ");

	int position;

	intList.push_back(23);
	intList.push_back(56);
	intList.push_back(45);
	intList.push_back(33);
	intList.push_back(88);
	intList.push_back(12);
	intList.push_back(67);

	cout << "intList: ";
	copy(intList.begin(), intList.end(), screen);
	cout << endl;

	position = seqSearch(intList, 88);

	if (position != -1)
	    cout << "88 found at position " << position << endl;
	else
	    cout << "88 is not in the list" << endl;

	stringList.push_back("Hello");
	stringList.push_back("Sunny");
	stringList.push_back("Fall");
	stringList.push_back("Winter");

	cout << "stringList: ";
	copy(stringList.begin(), stringList.end(), screen2);
	cout << endl;

	string str = "Cloudy";

	position = seqSearch(stringList, str);

	if (position != -1)
	    cout << "Cloudy found at position " << position << endl;
	else
        cout << "Cloudy is not in the list" << endl;

	return 0;
}

template<class elemType>
int seqSearch(const vector<elemType> &list, const elemType& item)
{
  int locate;
  for(int i = 0; i < list.size(); i++)
  {
      if(list[i] == item)
      {
          locate = i;
          return locate;
      }
  }
  return -1;

}
