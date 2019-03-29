#include <iostream>

using namespace std;


static bool showLog = true;

class String
{
private:
	char* 	_char;
	int 	_size;

public:
	// Constructor & Destructor
	String();
	String(const char character);
	String(const char* charArray);
	String(const String& str);
	String(String&& str);
	~String();

	String& operator=(const String& str);
	String& operator+=(const String& str);

	// --- operator plus
	friend String operator+(const String& lstr, const String& rstr);
	// friend String operator+(const String& lstr, const char*   rstr);
	// friend String operator+(const String& lstr, const char    rstr);
	// friend String operator+(const char*   lstr, const String& rstr);
	// friend String operator+(const char    lstr, const String& rstr);

	// --- operator repeat
	// friend String operator+(const String& str, const int   times);
	// friend String operator+(const int   times, const String& str);

	char operator[](const int index) const; //--- copy data
	char& operator[](const int index); 	//--- assign data

	// --- I/O
	friend ostream& operator<< (ostream& out, const String& _string);

	// --- operator compare

	int size() const;
	// --- subString

	// --- capital/small letter convert
	// void upperCase();
	// void upperCase(int index, int length);
	// void lowerCase();
	// void lowerCase(int index, int length);
	// void toggle();
};

/*  
 *  Default Constructor
 */
String::String() : _char(nullptr), _size(0)
{
	if (showLog)
		cout << "Default Constructor." << endl;
}

/*  
 *  Word Constructor
 */
String::String(const char* charArray) :  _char(nullptr), _size(0)
{
	if (showLog)
		cout << "Word Constructor" << endl;

	if (charArray!=nullptr)
	{
	    while (charArray[_size]!='\0')
	        _size++;
		_char = new char[_size];
		for (int i=0; i<_size; ++i)
	        _char[i] = charArray[i];
	}
}

/*  
 *  Copy Constructor
 */
String::String(const String& str) : _size(str._size)
{
	if (showLog)
		cout << "Copy Constructor... " << str << endl;

	_char = new char[_size];
    for (int i=0; i<_size; ++i)
        _char[i] = str[i];
}

/*  
 *  Move Constructor
 *  From: https://docs.microsoft.com/zh-tw/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=vs-2017
 */
String::String(String&& str) : _char(nullptr), _size(0)
{
	if (showLog)
		cout << "Move Constructor" << endl;
	_char = str._char;
	_size = str._size;

	str._char = nullptr;
	str._size = 0;
}

/*  
 *  Destructor
 */
String::~String()
{
	if (showLog)
		cout << "Destructor" << endl;

	delete [] _char; //--- delete, delete[] are different.
}

/*  
 *  Copy Assignment Operator
 */
String& String::operator=(const String& str)
{
	delete [] _char;
	_size = str.size();
	_char = new char[_size];
	for (int i=0; i<_size; ++i)
		_char[i] = str[i];

	return *this;
}

/*  
 *  Copy Constructor
 */
String& String::operator+=(const String& str)
{
	int newSize = _size + str.size();
	char* newChar = new char[newSize];

	for (int i=0; i<_size; ++i)
		newChar[i] = _char[i];

	for (int i=0; i<str.size(); ++i)
		newChar[i+_size] = str[i];
	delete[] _char;

	_char = newChar;
	_size = newSize;

	return *this;
}


String operator+(const String& lstr, const String& rstr)
{
	return String(lstr) += rstr;
}

char String::operator[](const int index) const
{
	if (index>=_size)
		throw "Out of range!";
	return _char[index];
}

char& String::operator[](const int index)
{
	if (index>=_size)
		throw "Out of range!";
	return _char[index];
}

ostream& operator<< (ostream& out, const String& _string)
{
    for (int i=0; i<_string.size(); ++i)
	    out << _string[i];
	return out;
}


int String::size() const
{
	return _size;
}


// --- general function
void showAddress(const String& str)
{
	cout << &str << ": " << str << endl;
}


int main()
{
	// auto* pointer = 
	String s0;
	String s1("Hello ");
	String s2("World I'm Yu.");
	showAddress(s1);
	showAddress(s2);
	cout << "s1: " << s1 << endl;
	cout << "s2: " << s2 << endl;
	s2[3] = 'L';
    s2[6] = 'i';
	cout << "s2': " << s2 << endl;
	cout << "s2'[3]: " << s2[3] << endl;

	String s3 = s1 + s2;
	showAddress(s3);
	showAddress(s0);
	s0 = s1;
	showAddress(s0);
	cout << "s3: " << s3 << endl;
	cout << "length: " << s3.size() << endl;

	return 0;
}
