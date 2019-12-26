#ifndef _GENERALFUNC_H
#define _GENERALFUNC_H

#include "lib.h"

bool isVowelChar(char chr);
bool isVowel(string str);
bool isTone(char chr);
bool isConsonantChar(char chr);
bool isFirstConsonant(string str);
bool isLastConsonantChar(char chr);
bool isLastConsonant(string str);
bool canReplace(char chr1, char chr2);

bool isLetter(wchar_t wchr);
bool isEndOfSen(wchar_t wchr);

wchar_t Upper2Lower(wchar_t wchr);

void freeVector(vector <string>& a);
void freeVector(vector <II>& a);
void freeVector(vector <pair <int, char> >& a);
void freeVector(vector <IWs>& a);
void freeVector(vector <wstring>& a);
void freeSet(set <string>& a);

string wstring_to_utf8(const wstring& str);

#endif // !_GENERALFUNC_H
