//
// Created by poojac on 8/5/19.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using namespace std;
/*
is_palindrome,
test_is_palindrome,
second_max,
test_second_max,
countStringLambda, countStringFreeFun, countStringFunctor,
charFrequency, multisetUsingMyComparator,
*/

unsigned long a;
bool is_palindrome(const std::string & phrase);
void test_is_palindrome();
void test_second_max(std::vector<int> vec);
int testCountStringLambda(const std::vector<string> &vecstr, int n);
class Comparator;
template < class Iterator > // template header
std::pair < Iterator, bool > // function template return type
second_max(Iterator start, Iterator finish);
int testCountStringFreeFun(const std::vector<string> &vecstr, int n);
int testCountStringFunctor(const std::vector<string> &vecstr, int n);
void charFrequency();
void multisetUsingMyComparator();

int CountStringFreeFun(string str) {
	return str.length() == a;
}
int main()
{
	// problem 1 :
	test_is_palindrome();
	cout << "\n";
	// problem 2 :
	std::vector <int> v1{ 1 }; // one element
	test_second_max(v1);
	std::vector <int> v2{ 1, 1 }; // all elements equal
	test_second_max(v2);
	std::vector <int> v3{ 1, 1, 3, 3, 7, 7 }; // at least with two distict elements
	test_second_max(v3);
	cout << "\n";
	// problem 3 :

	std::vector < std::string > vecstr
	{ " count_if " , " Returns " , " the " , " number " , " of " , " elements " , " in " , " the " ,
		" range " , " [ first " , " last ) " , " for " , " which " , " pred " , " is " , " true . "
	};
	cout << testCountStringLambda(vecstr, 5) << endl;
	cout << testCountStringFreeFun(vecstr, 5) << endl;
	cout << testCountStringFunctor(vecstr, 5) << endl;
	cout << " \n ";

	// problem 4 :
	charFrequency();
	cout << "\n";
	// problem 5 :
	multisetUsingMyComparator();
	cout << "\n";
	system("pause");
	return 0;
}
void test_is_palindrome()
{
	std::string str_i = std::string("Was it a car or a cat I saw?");
	std::string str_u = std::string("Was it a car or a cat U saw?");
	cout << "the phrase \"" + str_i + "\" is " + (is_palindrome(str_i) ? "" : "not") + " a palindrome \n";
	cout << "the phrase \"" + str_u + "\" is " + (is_palindrome(str_u) ? "" : "not") + " a palindrome \n";
}
bool is_palindrome(const std::string & phrase)
{
	string temp;
	//1. use std::remove copy if to move only alphabet characters from phrase to temp; note that temp is empty; hence the need for an inserter iterator
	int phraseSize = phrase.size();
	std::insert_iterator<std::string> insert_it(temp, temp.begin());
	std::remove_copy_if(phrase.c_str(), phrase.c_str() + phraseSize, insert_it, [](char c) {return !isalpha(c); });
	//2. use std::transform to convert all characters in temp to uppercase (or lowercase) (see page 22, Smart Pointers + Move Semantics, Moodle)
	std::transform(temp.begin(), temp.end(), temp.begin(), [](char ch) { return toupper(ch); });
	//3. use std::equal to compare the first half of temp with its second half, moving forward in the first half (starting at temp.begin()) and moving
	//backward in the second half (starting at temp.rbegin())
	int center = temp.size() / 2;
	return  std::equal(temp.begin(), temp.begin() + center, temp.rbegin());
	//4. return the outcome of step 3
}

void test_second_max(std::vector<int> vec)
{
	// note : auto in the following statement is deduced as
	// std :: pair < std :: vector < int >:: iterator , bool >
	auto retval = second_max(vec.begin(), vec.end());
	if (retval.second)
	{
		cout << "The second largest element in vec is "
			<< *retval.first << endl;
	}
	else
	{
		if (retval.first == vec.end())
			cout << "List empty, no elements \n ";
		else
			cout << "Container’s elements are all equal to "
			<< *retval.first << endl;
	}
}

int testCountStringLambda(const std::vector<string> & vecstr, int n) {
	int result{ 0 };
	// 1) Create a lambda expression named countStringLambda  (as described on page 4 of A5)
	auto countStringLambda = [n](string str) { return str.length() == n; };
	// 2) Use countStringLambda as the callable argument in the call to the count-if algorithm
	result = count_if(vecstr.begin(), vecstr.end(), countStringLambda);
	return result;

}
// Version 2
// 1) Create a free function named countStringFreeFun (as described on page 4 of A5)
int testCountStringFreeFun(const std::vector<string> & vecstr, int n) {
	int result{ 0 };
	a = n;
	// 2) Use countStringFreeFun as the callable argument in the call to the count-if algorithm
	result = count_if(vecstr.begin(), vecstr.end(), CountStringFreeFun);
	// 3) Let result = what count-if returns.
	return result;
}

int testCountStringFunctor(const std::vector<string> &vecstr, int n) {
	// version 3
	int result{ 0 };
	a = n;
	// 1) Define a class, say StringFunctor, whose objects are functors (as described on page 4 of A5)
	class StringFunctor {
	public:
		bool operator() (const std::string &s1) const
		{
			return s1.length() == a;
		}
	};
	// 2) Create a functor (function object) named countStringFunctor
	StringFunctor countStringFunctor;
	// 3) Use countStringFunctor as the callable argument in the call to the count-if algorithm
	result = count_if(vecstr.begin(), vecstr.end(), countStringFunctor);
	// 4) Let result = what count-if returns.
	return result;
}

void charFrequency() {
	cout << "Enter one or more lines of text.\nTo end input press Ctrl - Z in Windows and Ctrl - D in Linux" << endl;
	std::istream_iterator<char> cin_it(cin);
	std::istream_iterator<char> eos;

	std::map<char, int> index;
	std::for_each(cin_it, eos, [&index]( char c) {index[c]++; });//uses lambda expression

	std::for_each(index.begin(), index.end(), [&](pair<char, int> mypair){ std::cout << mypair.first << " " << mypair.second << '\n';});
}
template<class Iterator>
std::pair<Iterator, bool> second_max(Iterator start, Iterator finish) // function signature
{
	// your code
	//    int smallest_element = *start; //let, first element is the smallest one
	//    int largest_element = *start; //also let, first element is the biggest one
	if (start == finish) {
		return std::make_pair(finish, false);
	}
	else if (std::adjacent_find(start, finish) == finish)
	{
		//   std::cout << "All elements are equal each other" << std::endl;
		return std::make_pair(start, false);
	}
	Iterator largest = start;
	Iterator second = start;
	++start;
	for (; start != finish; ++start) {
		if (*largest < *start) {
			second = largest;
			largest = start;
		}
		else if (*start > *second && *start != *largest) {
			second = start;
		}
	}
	return std::make_pair(second, true);
}
/**
* */
class Comparator
{
public:
	// Returns ( s1 < s2 ) if s1 and s2 have the same length;
	// otherwise, returns ( s1.size() < s2.size() ).
	bool operator() (const std::string &s1, const std::string &s2) const
	{
		if (s1.size() == s2.size()) return s1 < s2;
		else return s1.size() < s2.size();
	}
};

void multisetUsingMyComparator() {
	//std::multiset<std::string> strSet; // an empty set
	std::multiset<std::string, Comparator>  strSet;
	// a set that uses the default std :: less < int > to sort the set elements
	std::vector<std::string> vec{ "C", "BB", "A", "CC", "A", "B", "BB", "A", "D", "CC", "DDD", "AAA" };
	// copy the vector elements to our set .
	// We must use a general ( not front or back ) inserter
	// ( set does not have push_front or push_back members ,
	// so we can ’t use front or back inserter )
	std::copy(vec.begin(), vec.end(), std::inserter(strSet, strSet.begin()));// general inserter
																			 // create an ostream_iterator for writing to cout ,
																			 // using a space " " as a separator
	std::ostream_iterator<std::string> out(cout, " ");
	// output the set elements to cout separating them with a space
	std::copy(strSet.begin(), strSet.end(), out);
}
