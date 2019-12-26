#ifndef _GENERALFUNC_CPP
#define _GENERALFUNC_CPP

#include "ConstVar.h"


bool isVowelChar(char chr) {
	int n = *(&vowelChar + 1) - vowelChar;
	for (int i = 0; i < n; i++) {
		if (chr == vowelChar[i]) return true;
	}
	return false;
}

bool isVowel(string str) {
	int n = vowel.size();
	for (int i = 0; i < n; i++) {
if (str.compare(vowel[i]) == 0) return true;
	}
	return false;
}

bool isTone(char chr) {
	int n = *(&tone + 1) - tone;
	for (int i = 0; i < n; i++) {
		if (chr == tone[i]) return true;
	}
	return false;
}

bool isConsonantChar(char chr) {
	int n = *(&consonantChar + 1) - consonantChar;
	for (int i = 0; i < n; i++) {
		if (chr == consonantChar[i]) return true;
	}
	return false;
}

bool isFirstConsonant(string str) {
	//int n = *(&firstConsonant + 1) - firstConsonant;
	int n = firstConsonant.size();
	for (int i = 0; i < n; i++) {
		if (str.compare(firstConsonant[i]) == 0) return true;
	}
	return false;
}

bool isLastConsonantChar(char chr) {
	int n = *(&lastConsonantChar + 1) - lastConsonantChar;

	for (int i = 0; i < n; i++) {
		if (chr == lastConsonantChar[i]) return true;
	}
	return false;
}

bool isLastConsonant(string str) {
	//int n = *(&lastConsonant + 1) - lastConsonant;
	int n = lastConsonant.size();
	for (int i = 0; i < n; i++) {
		if (str.compare(lastConsonant[i]) == 0) return true;
	}
	return false;
}

bool canReplace(char chr1, char chr2) {
	int n = replaceChar[chr1 - 'a'].size();
	for (int i = 0; i < n; i++) {
		if (chr2 == replaceChar[chr1 - 'a'][i]) return true;
	}
	return false;
}

bool isLetter(wchar_t wchr) {
	int n = uniList.size();
	bool rt = false;
	for (int i = 0; i < n; i++) {
		if (wchr == uniList[i]) {
			return true;
		}
	}
	return rt;
}

bool isEndOfSen(wchar_t wchr) {
	int n = *(&sentencesEndSymbols + 1) - sentencesEndSymbols;
	for (int i = 0; i < n; i++) {
		if (wchr == sentencesEndSymbols[i]) {
			return true;
		}
	}
	return false;
}

wchar_t Upper2Lower(wchar_t wchr) {
	wchar_t res = wchr;
	int n = uniUpperList.size();
	for (int i = 0; i < n; i++) {
		if (wchr == uniUpperList[i]) {
			res = uniList[i];
			break;
		}
	}
	return res;
}

string wstring_to_utf8(const wstring& str) {
	wstring_convert<codecvt_utf8<wchar_t>> myconv;
	return myconv.to_bytes(str);
}

void freeVector(vector <string>& a) {
	a.clear();
	a.shrink_to_fit();
}

void freeVector(vector <II>& a) {
	a.clear();
	a.shrink_to_fit();
}

void freeVector(vector <pair <int, char> > &a) {
	a.clear();
	a.shrink_to_fit();
}

void freeVector(vector <IWs>& a) {
	a.clear();
	a.shrink_to_fit();
}

void freeVector(vector <wstring>& a) {
	a.clear();
	a.shrink_to_fit();
}

void freeSet(set <string>& a) {
	a.erase(a.begin(), a.end());
};

#endif // !GENERALFUNC_CPP
