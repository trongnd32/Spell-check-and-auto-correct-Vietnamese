#ifndef _READFILE_CPP
#define _READFILE_CPP

#include "lib.h"
#include "ConstVar.h"
#include "GeneralFunc.h"


int readSen(int pos, wstring input, vector<IWs>& sylls, vector <wstring>& token) {

	wchar_t inputChar;

	wstring syllable = L"";
	int flag = 1;
	int count = 0;

	int N = input.length();

	int i = pos;

	for(i = pos; i < N; i++) {
		inputChar = input[i];

		if (isLetter(inputChar) == true) {
			syllable += Upper2Lower(inputChar);
			flag = 0;
		}
		else {
			if (flag == 0) {
				sylls.push_back(IWs(count, syllable));
				token.push_back(syllable);
				count++;
			}
			count++;
			wstring tmp = L"";
			tmp += inputChar;
			token.push_back(tmp);

			syllable = L"";
			flag = 1;

			if (isEndOfSen(inputChar) == true) {
				break;
			}
		}
	}
	if (syllable.length() > 0) {
		sylls.push_back(IWs(count, syllable));
		token.push_back(syllable);
	}
	return i;
}

#endif

