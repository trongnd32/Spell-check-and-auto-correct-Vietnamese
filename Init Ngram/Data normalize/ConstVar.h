#ifndef _CONSTVAR_H
#define _CONSTVAR_H

#include "lib.h"


// mysql
extern wifstream fin;

// index wchar and combine them
extern map <string, int> mapOfVowel;

extern map <string, int> mapOfLastConsonant;

extern map <string, int> mapOfTone;

extern map <string, int> mapOfFirstConsonant;

extern int combineVowelLastConsonant[54][10];

extern int combineToneLastConsonant[7][10];

extern int combineFirstConsonantVowel[29][54];

//----

extern map <string, string> standardVowel;

// cvt A2U
extern map <string, wstring> mapOfWsvowel;

extern map <wstring, wchar_t> mapOfWcharSingleVowel;

//----

// cvt U2A
extern map <wchar_t, string> cvtU2A;

// other const

extern char consonantChar[15];
extern char vowelChar[7];
extern char lastConsonantChar[5];
extern char tone[5];
extern vector <string> firstConsonant;
extern vector <string> lastConsonant;
extern vector <string> vowel;

extern vector <char> toneNearBy[26];

extern vector <char> replaceChar[26];

//---

extern vector <wchar_t> uniList;

extern vector <wchar_t> uniUpperList;

extern wchar_t sentencesEndSymbols[3];

extern vector <pair <string, int> > phoneticErr;

extern int quConsonant[54][10];
extern int GiVowel[54];
extern map <string, int> GiConsonant;

#endif
