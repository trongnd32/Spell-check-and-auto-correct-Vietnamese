#ifndef _A2U_CPP
#define _A2U_CPP

#include "lib.h"
#include "ConstVar.h"
#include "GeneralFunc.h"

using namespace std;

//-------------------------------------------------

void splitWord(string input, string& inputFirstConsonant, string& inputVowel, string& inputLastConsonant) {
	inputFirstConsonant = "";
	inputVowel = "";
	inputLastConsonant = "";

	int n = input.length();
	int state = 0;
	// state = 0: fill inputFirstConsonant, state = 1: fill inputVowel, state = 2: inputLastConsonant

	for (int i = 0; i < n; i++) {
		if (state == 0) {
			if (isVowelChar(input[i]) == false) {
				inputFirstConsonant += input[i];
			}
			else {
				state = 1;
				inputVowel += input[i];
			}
		}
		else if (state == 1) {
			if (isVowelChar(input[i]) == true) {
				inputVowel += input[i];
			}
			else {
				state = 2;
				inputLastConsonant += input[i];
			}
		}
		else {
			inputLastConsonant += input[i];
		}
	}

	if (inputFirstConsonant.compare("g") == 0 && inputVowel[0] == 'i') {
		inputFirstConsonant += 'i';
		inputVowel = inputVowel.substr(1);
	}
	if (inputFirstConsonant.compare("q") == 0 && inputVowel[0] == 'u') {
		inputFirstConsonant += 'u';
		inputVowel = inputVowel.substr(1);
	}

	if (inputVowel.compare("uow") == 0) {
		if (inputLastConsonant.length() > 1) {
			inputVowel = "uwow";
		}
		else if (inputLastConsonant.length() == 1 && isTone(*(--inputLastConsonant.end())) == false) {
			inputVowel = "uwow";
		}
	}
}

wstring svowel2wsvowel(string inputVowel) {
	return mapOfWsvowel[inputVowel];
}

wstring s2ws(string str) {
	wstring str2(str.length(), L' ');
	copy(str.begin(), str.end(), str2.begin());
	return str2;
}

wchar_t addTone(wstring wstr) {
	return mapOfWcharSingleVowel[wstr];
}

void addVowelTone(wstring& outputVowel, string inputTone, int hasLastConsonant) {
	if (inputTone.length() == 0) return;

	int n = outputVowel.length();
	wstring wsinputTone = s2ws(inputTone);


	//if (n <= 0) return;

	if (n == 1) {
		wstring vowelWithTone = outputVowel + wsinputTone;
		outputVowel[0] = addTone(vowelWithTone);
		return;
	}

	//wcout << outputVowel << L' '; cerr << inputTone << endl;

	int flag = 1;
	// flag = 0, tone in last wchar, flag = 1, tone in left last wchar
	if (outputVowel.compare(L"oa") == 0 || outputVowel.compare(L"oe") == 0 || outputVowel.compare(L"uy") == 0 || outputVowel.compare(L"uê") == 0 || outputVowel.compare(L"uơ") == 0) {
		flag = 0;
	}
	else {
		if (hasLastConsonant == 1) {
			flag = 0;
		}
		else flag = 1;
	}

	if (flag == 0) {
		wstring wchr = L"";
		wchr += outputVowel[n - 1];
		wstring vowelWithTone = wchr + wsinputTone;
		outputVowel[n - 1] = addTone(vowelWithTone);
		return;
	}

	if (flag == 1) {
		wstring wchr = L"";
		wchr += outputVowel[n - 2];
		wstring vowelWithTone = wchr + wsinputTone;
		outputVowel[n - 2] = addTone(vowelWithTone);
	}
}

wstring A2UGi(string inputFirstConsonant, string inputVowel, string inputLastConsonant) {
	string inputTone = "";
	if (inputLastConsonant.length() > 0 && isTone(*(--inputLastConsonant.end())) == true) {
		inputTone = *(--inputLastConsonant.end());
		inputLastConsonant.pop_back();
	}

	if (inputVowel.length() == 0) {
		if (inputTone.compare("s") == 0) return (L"gí" + s2ws(inputLastConsonant));
		if (inputTone.compare("f") == 0) return (L"gì" + s2ws(inputLastConsonant));
		if (inputTone.compare("r") == 0) return (L"gỉ" + s2ws(inputLastConsonant));
		if (inputTone.compare("x") == 0) return (L"gĩ" + s2ws(inputLastConsonant));
		if (inputTone.compare("j") == 0) return (L"gị" + s2ws(inputLastConsonant));
	}
	else {

		wstring outputFirstConsonant = L"";
		wstring outputVowel = L"";
		wstring outputLastConsonant = L"";
		outputLastConsonant = s2ws(inputLastConsonant);
		outputFirstConsonant = s2ws(inputFirstConsonant);
		outputVowel = svowel2wsvowel(inputVowel);

		int hasLastConsonant = 0;
		if (outputLastConsonant.length() > 0) hasLastConsonant = 1;

		addVowelTone(outputVowel, inputTone, hasLastConsonant);
		//cerr << input << endl;

		wstring output = L"";
		output += outputFirstConsonant + outputVowel + outputLastConsonant;
		return output;
	}
}

wstring A2UQu(string inputFirstConsonant, string inputVowel, string inputLastConsonant) {
	int n = inputVowel.length();
	if (inputVowel.compare("i") == 0) inputVowel = "y";

	string inputTone = "";
	wstring outputFirstConsonant = L"";
	wstring outputVowel = L"";
	wstring outputLastConsonant = L"";
	outputVowel = svowel2wsvowel(inputVowel);

	//cerr << inputFirstConsonant << " " << inputVowel << " " << inputLastConsonant << endl;
	outputFirstConsonant = s2ws(inputFirstConsonant);


	if (inputLastConsonant.length() > 0 && isTone(*(--inputLastConsonant.end())) == true) {
		inputTone = *(--inputLastConsonant.end());
		inputLastConsonant.pop_back();
	}


	outputLastConsonant = s2ws(inputLastConsonant);

	int hasLastConsonant = 0;
	if (outputLastConsonant.length() > 0) hasLastConsonant = 1;

	addVowelTone(outputVowel, inputTone, hasLastConsonant);
	//cerr << input << endl;

	wstring output = L"";
	output += outputFirstConsonant + outputVowel + outputLastConsonant;
	return output;
}

wstring A2U(string input) {
	string inputFirstConsonant, inputVowel, inputLastConsonant;
	string inputTone = "";
	splitWord(input, inputFirstConsonant, inputVowel, inputLastConsonant);

	if (inputFirstConsonant.compare("gi") == 0) return A2UGi(inputFirstConsonant, inputVowel, inputLastConsonant);
	if (inputFirstConsonant.compare("qu") == 0) return A2UQu(inputFirstConsonant, inputVowel, inputLastConsonant);

	wstring outputFirstConsonant = L"";
	wstring outputVowel = L"";
	wstring outputLastConsonant = L"";
	outputVowel = svowel2wsvowel(inputVowel);

	//cerr << inputFirstConsonant << " " << inputVowel << " " << inputLastConsonant << endl;

	if (inputFirstConsonant.compare("dd") == 0) {
		outputFirstConsonant = L"đ";
	}
	else outputFirstConsonant = s2ws(inputFirstConsonant);


	if (inputLastConsonant.length() > 0 && isTone(*(--inputLastConsonant.end())) == true) {
		inputTone = *(--inputLastConsonant.end());
		inputLastConsonant.pop_back();
	}


	outputLastConsonant = s2ws(inputLastConsonant);

	int hasLastConsonant = 0;
	if (outputLastConsonant.length() > 0) hasLastConsonant = 1;

	addVowelTone(outputVowel, inputTone, hasLastConsonant);
	//cerr << input << endl;

	wstring output = L"";
	output += outputFirstConsonant + outputVowel + outputLastConsonant;
	return output;
}
#endif // !_A2U_CPP


