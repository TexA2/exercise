#ifndef GRAF
#define GRAG
#define SIZE 5

int hesh_func(const char*);

struct list{
	int data;
	list* next;

	list(int n): data{n}, next{nullptr}
	{}

	void add(int);
};


struct deque{

	list *head;


	deque(int n)
	{
		head = new list(n);
	}

	void add(int);
	void pop();

};

struct table{
	list* head;

	table(): head{nullptr}
	{}
	
	void add(int);

	table* operator [](const char* str)
	{
		table* temp = this;
		return (temp + hesh_func(str));
	}
};


#endif
