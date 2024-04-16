#include <iostream>

using namespace std;

int simple_hesh(const char*,int);

struct list{

	list* next;
	
	int cost;


	list() : cost{0}
	{
		next = nullptr;
	}

	list(int n):cost{n},next{nullptr}
	{}

	void add(int n)
	{
		list* newList = new list(n);
		list* temp = this;

		while(temp->next != nullptr)
			temp = next;

		temp->next = newList;
	}
};

class Table{
private:
	int len;
	list* ptr;
public:
	Table(int size) : len{size}
	{
	ptr = new list[len];
	}

	void cadd(const char* str, int num)
	{
		int pos = simple_hesh(str,len);
		(ptr+pos)->add(num);
	}

	void print(const char*);
};

void Table::print(const char* str)
{
	int pos = simple_hesh(str, len);
	{
		list* temp = ptr+pos;

		while ( temp != nullptr)
		{
			cout << temp->cost <<" : " << str << endl;
			temp = temp->next;
		}
	}
}

int simple_hesh(const char* str, int len)
{
	int sum = 0;
	int i = 0;
	char c = str[i];

	while (c != '\0')
	{
		sum += int(c);
		c = str[++i];
	}

	return sum%len;
}


int main(){
	Table test(3);

	test.cadd("Name",3);
	test.cadd("Name",6);

	test.print("Name");
	
	test.cadd("Apple", 22);
	test.cadd("Apple", 31);

	test.print("Apple");

	return 0;
}
