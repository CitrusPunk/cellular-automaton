#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

char** createArr2d(int size)
{
	char** arr2d = 0;
	arr2d = new char*[size];

	for (int x = 0;x < size; x++)
	{
		arr2d[x] = new char[size];
		for (int y = 0; y < size; y++)
			arr2d[x][y] = '-';
	}
	return arr2d;
}

char** createRand2d(int size, int cells)
{
	char** arr2d = 0;
	arr2d = new char*[size];

	for (int x = 0;x < size; x++)
	{
		arr2d[x] = new char[size];
		for (int y = 0; y < size; y++)
			arr2d[x][y] = '-';
	}

	int x,y;
	while(cells)
	{
		x = rand() % size;
		y = rand() % size;

		if(arr2d[x][y] == '-')
		{
			arr2d[x][y] = 'X';
			cells--;
		}
	}

	return arr2d;
}

void printArr(char** arr, int size)
{
	cout << endl;
	for (int y = 0; y < size; ++y)
	{
		for (int x = 0; x < size; ++x)
			cout << arr[x][y] << " ";
		cout << endl;
	}
	cout << endl;
}

void setCells(char** arr)
{
	cout << "Which cells are alive?" << endl;
	cout << "\t-1 -1 to quit" << endl;
	while(1)
	{
		int x = -1,y = -1;
		cout << "[x] [y]: ";
		cin >> x >> y;

		if(x < 0 && y < 0)
			break;
		else
			arr[x][y] = 'X';
	}
}

int getNeighbours(char** arr, int x, int y, int size)
{
	int neighbours = 0;

	//top
	if(y > 0)
	{
		if(arr[x][y-1]== 'X')	neighbours++;
		if(x > 0 && arr[x-1][y-1] == 'X')	neighbours++;
		if(x < size-2 && arr[x+1][y-1] == 'X')	neighbours++;
	}

	//bottom
	if(y < size-2)
	{
		if(arr[x][y+1] == 'X')	neighbours++;
		if(x > 0 && arr[x-1][y+1] == 'X')	neighbours++;
		if(x < size-2 && arr[x+1][y+1] == 'X')	neighbours++;
	}

	//inline
	if(x > 0 && arr[x-1][y] == 'X') neighbours++;
	if(x < size-2 && arr[x+1][y] == 'X') neighbours++;

	return neighbours;
}

char** calculateNext(char** last,int size)
{
	char** next = 0;
	next = new char*[size];

	for (int x = 0;x < size; x++)
	{
		next[x] = new char[size];
		for (int y = 0; y < size; y++)
		{
			int counted = getNeighbours(last,x,y,size);
			//test living cells
			if(last[x][y] == 'X')
			{
				if(counted < 2 || counted > 3) 
					next[x][y] = '-';
				else 
					next[x][y] = 'X';
			}
			else if(counted == 3)
				next[x][y] = 'X';
			else 
				next[x][y] = '-';
		}
	}
	return next;
}

int main()
{
	srand(time(NULL));
	int size;
	
	//get array size
	cout << "Width = Height = ";
	cin >> size;
	char **arr = createArr2d(size);

	cout << "Initialze Methods:" << endl;
	cout << "[1] user input" << endl;
	cout << "[2] random cells" << endl;

	//get initializing mode & initialize	
	int initMode = 2;
	cin >> initMode;
	switch(initMode){
		case 1: 
				setCells(arr);
				break;
		case 2:
				arr = createRand2d(size,(size*size)/2);
				break;
	}

	//show start generation and pause
	printArr(arr,size);
	cout << "\n...[ENTER] to start Conway" << endl;
	cin.get();
	cin.get();

	for(int counter = 0;1; counter++)
	{
		cout << counter << ". Generation:" << endl;
		printArr(arr,size);
		arr = calculateNext(arr, size);

		cout << "...[ENTER] to get next generation" << endl;
		cout << "...[Q] + [ENTER] to quit program" << endl;
		if(cin.get() == 'q')
			break;
	}
}