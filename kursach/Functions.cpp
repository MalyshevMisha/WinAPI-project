#include "Header.h"
void RingLift(int selection, int & raised, int * t1, int * t2, int * t3)
{
	switch (selection)
	{
	case(1):
		CheckForReading(raised, t1);
		break;
	case(2):
		CheckForReading(raised, t2);
		break;
	case(3):
		CheckForReading(raised, t3);
		break;
	}
}

void PutRingDown(int selection, int & raised, int * t1, int * t2, int * t3)
{
	switch (selection)
	{
	case(1):
		CheckForWriting(raised, t1);
		break;
	case(2):
		CheckForWriting(raised, t2);
		break;
	case(3):
		CheckForWriting(raised, t3);
		break;
	}
}

void CheckForReading(int & raised, int * t)
{
	for (int i = 0; i < 8; i++)
	{
		if (t[i])
		{
			raised = t[i];
			t[i] = 0;
			i = 8;
		}
	}
}

void CheckForWriting(int & raised, int * t)
{
	for (int i = 7; i >= 0; i--)
	{
		if (t[i] == 0 && i == 7)
		{
			t[i] = raised;
			raised = 0;
			i = -1;
		}
		if (t[i] == 0 && i != 7 && t[i + 1] > raised)
		{
			t[i] = raised;
			raised = 0;
			i = -1;
		}
	}

}

bool ArraySearch(int * t, int value, int & index)
{
	bool endFunc = false;
	for (int i = 0; i < 8; i++)
	{
		if (t[i]==value)
		{
			endFunc = true;
			index = i;
		}
	}
	return endFunc;
}