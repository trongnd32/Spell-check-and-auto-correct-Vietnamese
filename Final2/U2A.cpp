#ifndef _U2A_CPP
#define U2A_CPP

#include "lib.h"
#include "ConstVar.h"
#include "GeneralFunc.h"

string U2A(wstring wstr) {
	string str = "";
	int n = wstr.length();
	string tone = "";
	for (int i = 0; i < n; i++) {
		string tmp = cvtU2A[wstr[i]];

		if (tmp.length() > 1 && isTone(*(--tmp.end()))) {
			tone = "";
			tone += *(--tmp.end());
			tmp.pop_back();
		}
		str += tmp;
	}
	str += tone;
	return str;
}

#endif

