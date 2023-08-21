#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

int countMatches(const string a[], int n, string target);
int detectMatch(const string a[], int n, string target);
bool detectSequence(const string a[], int n, string target, int& begin, int& end);
int detectMin(const string a[], int n);
int moveToBack(string a[], int n, int pos);
int moveToFront(string a[], int n, int pos);
int detectDifference(const string a1[], int n1, const string a2[], int n2);
int deleteDups(string a[], int n);
bool contains(const string a1[], int n1, const string a2[], int n2);
int meld(const string a1[], int n1, const string a2[], int n2, string result[], int max);
int separate(string a[], int n, string separator);
//dont worry about checking if n is too big for the array
int main()
{
	string h[7] = { "isaac", "paul", "danny", "june", "", "amy", "danny" };
	assert(countMatches(h, 7, "danny") == 2);
	assert(countMatches(h, 7, "") == 1);
	assert(countMatches(h, 7, "fumi") == 0);
	assert(countMatches(h, 0, "danny") == 0);
	assert(detectMatch(h, 7, "danny") == 2);
	assert(detectMatch(h, 2, "danny") == -1);
	int bg;
	int en;
	assert(detectSequence(h, 7, "amy", bg, en) && bg == 5 && en == 5);

	string g[4] = { "isaac", "paul", "amy", "danny" };
	assert(detectMin(g, 4) == 2);
	assert(detectDifference(h, 4, g, 4) == 2);
	assert(contains(h, 7, g, 4));
	assert(moveToBack(g, 4, 1) == 1 && g[1] == "amy" && g[3] == "paul");

	string r[4] = { "paul", "amy", "danny", "isaac" };
	assert(moveToFront(r, 4, 2) == 2 && r[0] == "danny" && r[2] == "amy");

	string e[5] = { "paul", "paul", "paul", "danny", "danny" };
	assert(deleteDups(e, 5) == 2 && e[1] == "danny");

	string u[4] = { "george", "george", "naomi", "paul" };
	string v[4] = { "amy", "danny", "george", "isaac" };
	string w[10];
	assert(meld(u, 4, v, 4, w, 10) == 8 && w[5] == "isaac");

	assert(separate(h, 7, "isaac") == 4);

	cout << "All tests succeeded" << endl;
}

//countMatches works good!
int countMatches(const string a[], int n, string target)
{
	if (n < 0)
	{
		return -1;
	}

	int strCounter = 0;

	for (int i = 0; i < n; ++i)
	{
		if (a[i] == target)
		{
			strCounter++;
		}
	}
	return strCounter;
}

//detectMatch works good!
int detectMatch(const string a[], int n, string target)
{
	if (n < 0)
	{
		return -1;
	}

	for (int i = 0; i < n; ++i)
	{
		if (a[i] == target)
			return i;
	}
	return -1;
}

//detectSequence works good!
bool detectSequence(const string a[], int n, string target, int& begin, int& end)
{
	begin = 0;
	end = 0;
	if (n < 0)
		return false;
	//makes sure target is in the array
	int targetCounter = 0;
	for (int i = 0; i < n; ++i)
	{
		if (a[i] == target)
		{
			targetCounter++;
		}
	}
	if (targetCounter == 0)
		return false;

	for (int i = 0; i < n; ++i)
	{
		if (a[i] == target)
		{
			begin = i;
			for (int j = i; j < n; ++j)
			{
				if (a[j + 1] != target)
				{
					end = j;
					return true;
				}
			}
		}
	}
	return false;
}

//detectMin works good!
int detectMin(const string a[], int n)
{
	if (n <= 0)
		return -1;

	int smallString = 0;
	string smallest = a[0];
	for (int i = 0; i < n; ++i)
	{
		if (a[i] < smallest)
		{
			smallString = i;
			smallest = a[i];
		}
	}
	return smallString;
}

//moveToBack works good!
int moveToBack(string a[], int n, int pos)
{
	if (pos >= n)
	{
		return -1;
	}
	if (n < 0)
	{
		return -1;
	}

	string tempHold = a[pos];
	for (int i = pos; i < n - 1; ++i)
	{
		a[i] = a[i + 1];
	}
	a[n - 1] = tempHold;
	return pos;
}

//moveToFront works good!
int moveToFront(string a[], int n, int pos)
{
	if (pos >= n)
	{
		return -1;
	}
	if (n < 0)
	{
		return -1;
	}

	string tempHold = a[pos];
	for (int i = pos; i > 0; --i)
	{
		a[i] = a[i - 1];
	}
	a[0] = tempHold;
	return pos;
}

//detectDifference works good!
int detectDifference(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
		return -1;

	for (int i = 0; i < n1 && i < n2; ++i)
	{
		if (a1[i] != a2[i])
			return i;
	}
	if (n1 < n2)
	{
		return n1;
	}
	if (n1 > n2)
	{
		return n2;
	}
	return -1;
}

//deleteDups works good!
int deleteDups(string a[], int n)
{
	if (n < 0)
	{
		return -1;
	}

	int consecutiveCount = 0;
	for (int i = 0; i < n; ++i)
	{
		while (i < n && a[i] == (a[i + 1]))
		{
			++i;
		}
		a[consecutiveCount] = a[i];
		consecutiveCount++;
	}
	return consecutiveCount;
}

//contains works good!
bool contains(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 == 0 && n2 == 0)
		return true;
	if (n1 <= 0 || n2 < 0)
		return false;
	if (n2 == 0)
		return true;
	int i = 0;
	int j = 0;
	while (i < n2 && j < n1)
	{
		if (a2[i] == a1[j])
		{
			++i;
		}
		++j;
	}
	if (i == n2)
	{
		return true;
	}
	return false;
}

//meld works good!
int meld(const string a1[], int n1, const string a2[], int n2, string result[], int max)
{
	if (n1 < 0 || n2 < 0)
		return -1;

	for (int i = 0; i < n1 - 1; ++i)
	{
		if (a1[i] > a1[i + 1])
		{
			return -1;
		}
	}
	for (int j = 0; j < n2 - 1; ++j)// had to be last index minus 1
	{
		if (a2[j] > a2[j + 1])
		{
			return -1;
		}
	}
	if (n1 + n2 > max)
	{
		return -1;
	}
	int k = 0;
	int g = 0;
	int r = 0;
	//if statements for each of the possible scenarios
	while (k < n1 && g < n2)
	{
		if (a1[k] < a2[g])
		{
			result[r] = a1[k];
			++r;
			++k;
		}
		if (a1[k] > a2[g])
		{
			result[r] = a2[g];
			++r;
			++g;
		}
		if (a1[k] == a2[g])//had to account for the indexes being equal
		{
			result[r] = a2[g];
			++r;
			result[r] = a1[k];
			++r;
			++g;
			++k;
		}
	}
	//for when either n1 or n2 is smaller than the other
	while (k == n1 && g < n2)
	{
		result[r] = a2[g];
		++r;
		++g;
	}
	while (g == n2 && k < n1)
	{
		result[r] = a1[k];
		++r;
		++k;
	}
	return n1 + n2;
}

//separate works good!
int separate(string a[], int n, string separator)
{
	if (n < 0)
	{
		return -1;
	}

	string strHold;
	for (int i = 0; i < n; i++)
	{
		for (int k = i + 1; k < n; k++)
		{
			if (a[i] > a[k])
			{
				strHold = a[i];
				a[i] = a[k];
				a[k] = strHold;
			}
		}
	}
	for (int j = 0; j < n; ++j)
	{
		if (a[j] >= separator)
		{
			return j;
		}
	}
	return n;
}