#pragma once
void RingLift(int selection, int & raised, int * t1, int * t2, int * t3);	//функция поднятия кольца
void PutRingDown(int selection, int & raised, int * t1, int * t2, int * t3);	//
void CheckForReading(int & raised, int * t);
void CheckForWriting(int & raised, int * t);
bool ArraySearch(int * t, int value, int & index);