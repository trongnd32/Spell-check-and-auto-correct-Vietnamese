#ifndef _NEARLYSYLL_CPP
#define _NEARLYSYLL_CPP

#include "lib.h"
#include "ConstVar.h"
#include "GeneralFunc.h"
#include "U2A.h"
#include "A2U.h"

#define MAXEDFIRSTCONSONANT 1
#define MAXEDVOWEL 1
#define MAXEDLASTCONSONANT 1
#define INFED 100

int ED[15][15];

int edit_distance(string A, string B) {
	int n = A.length(), m = B.length();
	//int ED[n + 1][m + 1];
	for (int i = 0; i <= n; i++) memset(ED[i], 0, sizeof(ED[i])); // set everything to 0
	for (int j = 0; j <= m; j++) ED[0][j] = j;
	for (int i = 0; i <= n; i++) ED[i][0] = i;
	int diff;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			ED[i][j] = ED[i - 1][j] + 1;
			ED[i][j] = (ED[i][j] < ED[i][j - 1] + 1 ? ED[i][j] : ED[i][j - 1] + 1);
			diff = (A[i - 1] == B[j - 1] ? 0 : 1); // arrays in C are indexed from 0
			if (A[i - 1] != B[j - 1]) {
				if (canReplace(A[i - 1], B[j - 1])) diff = 1;
				else diff = INFED;
			}
			ED[i][j] = (ED[i][j] < ED[i - 1][j - 1] + diff ? ED[i][j] : ED[i - 1][j - 1] + diff);
		}
	}
	return ED[n][m];
}

vector < pair <int, char> > findDeleteChars(string inputVowel, string destVowel) {
	vector <pair <int, char> > deletedChar;
	int n = inputVowel.length();
	int m = destVowel.length();

	//tracing
	vector <II> path;
	while (n && m) {
		if (ED[n][m] == ED[n - 1][m] + 1) {
			path.push_back(II(-1, n));
			n--;
			continue;
		}
		if (ED[n][m] == ED[n][m - 1] + 1) {
			path.push_back(II(1, n));
			m--;
			continue;
		}
		if (ED[n][m] == ED[n - 1][m - 1] + 1) {
			path.push_back(II(0, n));
			n--;
			m--;
			continue;
		}
		if (inputVowel[n - 1] == destVowel[m - 1]) {
			n--;
			m--;
			continue;
		}
	}

	// get deleted char
	int k = path.size();
	for (int i = 0; i < k; i++) {
		if (path[i].first == -1) {
			deletedChar.push_back(IC(path[i].second - 1, inputVowel[path[i].second - 1]));
		}
	}
	return deletedChar;
}

vector <string> genNearlyFirstConsonant(string inputFirstConsonant) {
	vector <string> res;
	//int n = *(&firstConsonant + 1) - firstConsonant;
	int n = firstConsonant.size();

	if (inputFirstConsonant.length() > 1) {
		int m = inputFirstConsonant.length();
		for (int i = 1; i < m; i++) {
			string tmp = inputFirstConsonant;
			swap(tmp[i], tmp[i - 1]);
			res.push_back(tmp);
		}
	}

	for (int i = 0; i < n; i++) {
		if (edit_distance(inputFirstConsonant, firstConsonant[i]) <= MAXEDFIRSTCONSONANT) res.push_back(firstConsonant[i]);
	}
	return res;
}

vector <string> genNearlyVowel(string inputVowel) {
	vector <string> res;
	//int n = *(&vowel + 1) - vowel;
	int n = vowel.size();

	for (int i = 0; i < n; i++) {
		int edvowel = edit_distance(inputVowel, vowel[i]);

		if (edvowel <= MAXEDVOWEL) res.push_back(standardVowel[vowel[i]]);
		if (edvowel <= MAXEDVOWEL + 1) {
			vector < pair <int, char> > deletedChar = findDeleteChars(inputVowel, vowel[i]);
			int m = deletedChar.size();

			for (int k = 0; k < m; k++) {
				if (isTone(deletedChar[k].second) && deletedChar[k].first != 0) {
					string str = standardVowel[vowel[i]] + deletedChar[k].second;
					res.push_back(str);
				}
				else {
					if (edvowel <= MAXEDVOWEL) {
						int repToneSize = toneNearBy[deletedChar[k].second - 'a'].size();
						for (int o = 0; o < repToneSize; o++) {
							string str = standardVowel[vowel[i]] + toneNearBy[deletedChar[k].second - 'a'][o];
							res.push_back(str);
						}
					}
				}
			}
			freeVector(deletedChar);
		}
	}
	return res;
}

vector <string> genNearlyLastConsonant(string inputLastConsonant) {
	vector <string> res;
	//int n = *(&lastConsonant + 1) - lastConsonant;
	int n = lastConsonant.size();

	if (inputLastConsonant.length() > 1) {
		int m = inputLastConsonant.length();
		for (int i = 1; i < m; i++) {
			string tmp = inputLastConsonant;
			swap(tmp[i], tmp[i - 1]);
			res.push_back(tmp);
		}
	}

	for (int i = 0; i < n; i++) {
		int edlast = edit_distance(inputLastConsonant, lastConsonant[i]);
		if (edlast <= MAXEDLASTCONSONANT) res.push_back(lastConsonant[i]);

		if (edlast <= MAXEDLASTCONSONANT + 1) {
			vector < pair <int, char> > deletedChar = findDeleteChars(inputLastConsonant, lastConsonant[i]);
			int m = deletedChar.size();

			for (int k = 0; k < m; k++) {
				if (isTone(deletedChar[k].second)) {
					string str = lastConsonant[i] + deletedChar[k].second;
					res.push_back(str);
				}
				else {
					if (edlast <= MAXEDLASTCONSONANT) {
						int repToneSize = toneNearBy[deletedChar[k].second - 'a'].size();
						for (int o = 0; o < repToneSize; o++) {
							string str = lastConsonant[i] + toneNearBy[deletedChar[k].second - 'a'][o];
							res.push_back(str);
						}
					}
				}
			}
			freeVector(deletedChar);
		}
	}
	return res;
}

bool checkGiConsonant(string gfconsonant, string gvowel, string glconsonant) {
	if (gvowel.length() == 0) {
		string newGlconsonant = glconsonant;
		string toneChar = "";

		char lastCharInLastConsonant = '0';
		if (glconsonant.length() > 0) lastCharInLastConsonant = *(--glconsonant.end());
		if (isTone(lastCharInLastConsonant) == true) {
			newGlconsonant.pop_back();
			toneChar = lastCharInLastConsonant;
		}
		int idxLastConsonant = mapOfLastConsonant[newGlconsonant];
		int idxTone = mapOfTone[toneChar];

		if (GiConsonant[newGlconsonant] && combineToneLastConsonant[idxTone][idxLastConsonant]) return true;
		else return false;
	}

	if (gvowel.length() == 1 && isTone(gvowel[0])) {
		string toneChar = "";
		toneChar += gvowel[0];
		gvowel = "";

		int idxLastConsonant = mapOfLastConsonant[glconsonant];
		int idxTone = mapOfTone[toneChar];

		if (GiConsonant[glconsonant] && combineToneLastConsonant[idxTone][idxLastConsonant]) return true;
		else return false;
	}
	else {
		char lastCharInVowel = '0';
		if (gvowel.length() > 0) lastCharInVowel = *(--gvowel.end());

		char lastCharInLastConsonant = '0';
		if (glconsonant.length() > 0) lastCharInLastConsonant = *(--glconsonant.end());

		string newGvowel = gvowel;
		string newGlconsonant = glconsonant;
		string toneChar = "";

		if (isTone(lastCharInVowel)) {
			newGvowel.pop_back();
			toneChar = lastCharInVowel;
		}
		if (isTone(lastCharInLastConsonant)) {
			newGlconsonant.pop_back();
			toneChar = lastCharInLastConsonant;
		}
		if (newGvowel.compare("uow") == 0 && newGlconsonant.length() > 0) newGvowel = "uwow";

		int idxVowel = mapOfVowel[newGvowel];
		int idxLastConsonant = mapOfLastConsonant[newGlconsonant];
		int idxTone = mapOfTone[toneChar];

		if (GiVowel[idxVowel] == 0) return false;
		if (combineVowelLastConsonant[idxVowel][idxLastConsonant] == 0) return false;
		if (combineToneLastConsonant[idxTone][idxLastConsonant] == 0) return false;

		return true;
	}
}

bool checkQuConsonant(string gfconsonant, string gvowel, string glconsonant) {
	char lastCharInVowel = '0';
	if (gvowel.length() > 0) lastCharInVowel = *(--gvowel.end());

	char lastCharInLastConsonant = '0';
	if (glconsonant.length() > 0) lastCharInLastConsonant = *(--glconsonant.end());

	string newGvowel = gvowel;
	string newGlconsonant = glconsonant;
	string toneChar = "";

	if (isTone(lastCharInVowel)) {
		newGvowel.pop_back();
		toneChar = lastCharInVowel;
	}
	if (isTone(lastCharInLastConsonant)) {
		newGlconsonant.pop_back();
		toneChar = lastCharInLastConsonant;
	}
	if (newGvowel.compare("uow") == 0 && newGlconsonant.length() > 0) newGvowel = "uwow";

	int idxVowel = mapOfVowel[newGvowel];
	int idxLastConsonant = mapOfLastConsonant[newGlconsonant];
	int idxTone = mapOfTone[toneChar];

	if (quConsonant[idxVowel][idxLastConsonant] == 0) return false;
	if (combineToneLastConsonant[idxTone][idxLastConsonant] == 0) return false;

	return true;
}

bool checkValidNearlyWord(string gfconsonant, string gvowel, string glconsonant) {
	if (gfconsonant.compare("gi") == 0) {
		return checkGiConsonant(gfconsonant, gvowel, glconsonant);
	}
	if (gfconsonant.compare("qu") == 0) {
		return checkQuConsonant(gfconsonant, gvowel, glconsonant);
	}

	char lastCharInVowel = '0';
	if (gvowel.length() > 0) lastCharInVowel = *(--gvowel.end());

	/*for (string::iterator i = gvowel.begin(); i != gvowel.end(); i++) {
		if (isTone(*i) == true && i != gvowel.begin()) {
			lastCharInVowel = *i;
			gvowel.erase(i);
			break;
		}
	}*/

	char lastCharInLastConsonant = '0';
	/*for (string::iterator i = glconsonant.begin(); i != glconsonant.end(); i++) {
		if (isTone(*i) == true) {
			if (lastCharInLastConsonant != '0') {
				lastCharInLastConsonant = *i;
				glconsonant.erase(i);
			}
			else lastCharInVowel = *i;
		}
	}*/
	if (glconsonant.length() > 0) lastCharInLastConsonant = *(--glconsonant.end());

	if (isTone(lastCharInVowel) && isTone(lastCharInLastConsonant)) return false;

	string newGvowel = gvowel;
	string newGlconsonant = glconsonant;
	string toneChar = "";

	if (isTone(lastCharInVowel)) {
		newGvowel.pop_back();
		toneChar = lastCharInVowel;
	}
	if (isTone(lastCharInLastConsonant)) {
		newGlconsonant.pop_back();
		toneChar = lastCharInLastConsonant;
	}
	if (newGvowel.compare("uow") == 0 && newGlconsonant.length() > 0) newGvowel = "uwow";

	int idxFirstConsonant = mapOfFirstConsonant[gfconsonant];
	int idxVowel = mapOfVowel[newGvowel];
	int idxLastConsonant = mapOfLastConsonant[newGlconsonant];
	int idxTone = mapOfTone[toneChar];

	if (combineFirstConsonantVowel[idxFirstConsonant][idxVowel] == 0) return false;
	if (combineVowelLastConsonant[idxVowel][idxLastConsonant] == 0) return false;
	if (combineToneLastConsonant[idxTone][idxLastConsonant] == 0) return false;

	return true;
}

string wordNormalize(string gfConsonant, string gvowel, string glConsonant) {
	string res = "";

	//cerr << gfConsonant << " - " << gvowel << " - " << glConsonant << endl;

	if (gvowel.length() > 0) {
		char tone = *(--gvowel.end());
		if (isTone(tone) == true) {
			gvowel.pop_back();
			glConsonant += tone;
		}
	}
	res = gfConsonant + gvowel + glConsonant;
	return res;
}

string moveToneToEnd(string str) {
	string tmp = "";
	string res = "";
	for (string::iterator i = str.begin(); i != str.end(); i++) {
		if (isTone(*i) == true) {
			tmp += *i;
			str.erase(i);
			break;
		}
	}
	res = str + tmp;
	return res;
}

set <string> nearTmp(string inputFirstConsonant, string inputVowel, string inputLastConsonant, int genNearF, int genNearV, int genNearL) {
	set <string> res;

	string inputTone = "";
	string inputVowel2 = inputVowel;
	vector <string> validFirstConsonant = {};
	vector <string> validVowel = {};
	vector <string> validVowel2 = {};
	vector <string> validLastConsonant = {};

	for (string::iterator i = inputVowel2.begin(); i != inputVowel2.end(); i++) {
		if (i != inputVowel2.begin() && isTone(*i) == true) {
			char tmp = *i;
			inputVowel2.erase(i);
			inputTone += tmp;
			break;
		}
	}

	if (genNearF != 0)
		validFirstConsonant = genNearlyFirstConsonant(inputFirstConsonant);

	if (genNearV != 0) {
		validVowel = genNearlyVowel(inputVowel);
		if (inputVowel.compare(inputVowel2) != 0) validVowel2 = genNearlyVowel(inputVowel2);
	}

	if (genNearL != 0)
		validLastConsonant = genNearlyLastConsonant(inputLastConsonant);

	inputLastConsonant = moveToneToEnd(inputLastConsonant);

	// Ghep cac thanh phan
	int len1 = validFirstConsonant.size();
	int len2 = validVowel.size();
	int len22 = validVowel2.size();
	int len3 = validLastConsonant.size();

	string inputLastWithoutTone = inputLastConsonant;
	for (string::iterator i = inputLastWithoutTone.begin(); i != inputLastWithoutTone.end(); i++) {
		if (isTone(*i) == true) {
			inputLastWithoutTone.erase(i);
			break;
		}
	}

	string inputVowelWithoutTone = inputVowel;
	for (string::iterator i = inputVowelWithoutTone.begin(); i != inputVowelWithoutTone.end(); i++) {
		if (isTone(*i) == true) {
			inputVowelWithoutTone.erase(i);
			break;
		}
	}

	string inputVowelWithoutTone2 = inputVowel2;
	for (string::iterator i = inputVowelWithoutTone2.begin(); i != inputVowelWithoutTone2.end(); i++) {
		if (isTone(*i) == true) {
			inputVowelWithoutTone2.erase(i);
			break;
		}
	}

	int isLast = isLastConsonant(inputLastWithoutTone);
	int isFirst = isFirstConsonant(inputFirstConsonant);
	int isV = isVowel(inputVowelWithoutTone);
	int isV2 = isVowel(inputVowelWithoutTone2);

	if (isLast && isV2)
		for (int i = 0; i < len1; i++) {
			string LastConsonantTmp = inputLastConsonant + inputTone;
			if (checkValidNearlyWord(validFirstConsonant[i], inputVowel2, LastConsonantTmp)) {
				res.insert(wordNormalize(validFirstConsonant[i], inputVowel2, LastConsonantTmp));
			}
		}

	if (isLast && isFirst)
		for (int i = 0; i < len2; i++) {
			if (checkValidNearlyWord(inputFirstConsonant, validVowel[i], inputLastConsonant)) {
				res.insert(wordNormalize(inputFirstConsonant, validVowel[i], inputLastConsonant));
			}
		}

	if (isLast && isFirst)
		for (int i = 0; i < len22; i++) {
			string LastConsonantTmp = inputLastConsonant + inputTone;
			if (checkValidNearlyWord(inputFirstConsonant, validVowel2[i], LastConsonantTmp)) {
				res.insert(wordNormalize(inputFirstConsonant, validVowel2[i], LastConsonantTmp));
			}
		}

	if (isV && isFirst)
		for (int i = 0; i < len3; i++) {
			if (checkValidNearlyWord(inputFirstConsonant, inputVowel, validLastConsonant[i])) {
				res.insert(wordNormalize(inputFirstConsonant, inputVowel, validLastConsonant[i]));
			}
		}

	freeVector(validFirstConsonant);
	freeVector(validVowel);
	freeVector(validVowel2);
	freeVector(validLastConsonant);
	return res;
}

set <string> nearlyGenerator(int firstPos, int lastPos, string input) {
	set <string> nearlySet;
	int n = input.length();

	string inputFirstConsonant = input.substr(0, firstPos);
	string inputVowel = "";
	string inputLastConsonant = input.substr(lastPos);

	if (firstPos < lastPos) inputVowel = input.substr(firstPos, lastPos - firstPos);

	set <string> tmp = nearTmp(inputFirstConsonant, inputVowel, inputLastConsonant, 1, 1, 1);
	nearlySet.insert(tmp.begin(), tmp.end());
	freeSet(tmp);
	//tmp.clear();


	// ---------------------------------------
	string inputNew = "";

	// swap first position
	if (firstPos > 0 && firstPos < lastPos) {
		inputNew = input.substr(0, firstPos - 1) + input[firstPos] + input[firstPos - 1] + input.substr(firstPos + 1);

		inputFirstConsonant = inputNew.substr(0, firstPos);
		inputVowel = inputNew.substr(firstPos, lastPos - firstPos);
		inputLastConsonant = inputNew.substr(lastPos);

		tmp = nearTmp(inputFirstConsonant, inputVowel, inputLastConsonant, 0, 1, 1);
		nearlySet.insert(tmp.begin(), tmp.end());
		freeSet(tmp);
		//tmp.clear();
	}

	// swap last position
	if (lastPos < n - 1 && firstPos < lastPos) {
		inputNew = input.substr(0, lastPos - 1) + input[lastPos] + input[lastPos - 1] + input.substr(lastPos + 1);

		inputFirstConsonant = inputNew.substr(0, firstPos);
		inputVowel = inputNew.substr(firstPos, lastPos - firstPos);
		inputLastConsonant = inputNew.substr(lastPos);

		tmp = nearTmp(inputFirstConsonant, inputVowel, inputLastConsonant, 1, 1, 0);
		nearlySet.insert(tmp.begin(), tmp.end());
		freeSet(tmp);
		//tmp.clear();
	}

	// swap both position
	if (lastPos < n - 1 && firstPos > 0 && firstPos < lastPos - 1 && firstPos < lastPos) {
		inputNew = input.substr(0, firstPos - 1) + input[firstPos] + input[firstPos - 1] + input.substr(firstPos + 1, lastPos - 1) + input[lastPos] + input[lastPos - 1] + input.substr(lastPos + 1);

		inputFirstConsonant = inputNew.substr(0, firstPos);
		inputVowel = inputNew.substr(firstPos, lastPos - firstPos);
		inputLastConsonant = inputNew.substr(lastPos);

		string inputTone = "";

		for (string::iterator i = inputVowel.begin(); i != inputVowel.end(); i++) {
			if (i != inputVowel.begin() && isTone(*i) == true) {
				char tmp = *i;
				inputVowel.erase(i);
				inputTone += tmp;
				break;
			}
		}

		for (string::iterator i = inputLastConsonant.begin(); i != inputLastConsonant.end(); i++) {
			if (i != inputLastConsonant.begin() && isTone(*i) == true) {
				char tmp = *i;
				inputLastConsonant.erase(i);
				inputTone += tmp;
				break;
			}
		}

		if (inputTone.length() >= 2) {
			if (isFirstConsonant(inputFirstConsonant) && isVowel(inputVowel) && isLastConsonant(inputLastConsonant)) {
				nearlySet.insert(wordNormalize(inputFirstConsonant, inputVowel, inputLastConsonant + inputTone));
			}
		}
	}
	return nearlySet;
}

set <string> nearSyll(string input) {
	set <string> nearlySet;

	int n = input.length();

	int firstConsonantPosition = 0;
	for (int i = 0; i < min(n, 4); i++) {
		firstConsonantPosition = i + 1;
		if (isVowelChar(input[i])) break;
	}

	int lastConsonantPosition = n;
	for (int i = n - 1; i >= max(0, n - 3); i--) {
		lastConsonantPosition = i;
		if (isVowelChar(input[i])) {
			break;
		}
	}

	for (int i = 0; i <= firstConsonantPosition; i++) {
		for (int j = max(i, lastConsonantPosition); j <= n; j++) {
			set <string> tmpS = nearlyGenerator(i, j, input);
			if (!tmpS.empty()) {
				nearlySet.insert(tmpS.begin(), tmpS.end());
				tmpS.clear();
			}
		}
	}

	set <string> tmpSet;

	// Trường hợp phụ âm đầu dd
	int countD = 0;
	string inpSplit1 = "";
	string inpSplit2 = "";
	for(auto i: input){
		if (i == 'd') {
			countD++;
			inpSplit1 += 'd';
		}
		else {
			inpSplit2 += i;
		}
	}
	if (countD >= 2) {
		string input2 = inpSplit1 + inpSplit2;
		for (int i = countD; i <= n; i++) {
			set <string> tmpS = nearlyGenerator(countD, i, input2);
			if (!tmpS.empty()) {
				nearlySet.insert(tmpS.begin(), tmpS.end());
				
				tmpS.erase(tmpS.begin(), tmpS.end());
				//tmpS.clear();
			}
		}

		//Thêm dấu cho từ ban đầu
		int haveTone = 0;
		for (auto j : input2.substr(1)) {
			if (isTone(j) == true) {
				haveTone = 1;
				break;
			}
		}
		if (haveTone == 0) {
			string fC = "";
			string V = "";
			string lC = "";
			splitWord(input2, fC, V, lC);
			if (checkValidNearlyWord(fC, V, lC + "s") == true) {
				nearlySet.insert(input2 + "s");
			}
			if (checkValidNearlyWord(fC, V, lC + "f") == true) {
				nearlySet.insert(input2 + "f");
			}
			if (checkValidNearlyWord(fC, V, lC + "r") == true) {
				nearlySet.insert(input2 + "r");
			}
			if (checkValidNearlyWord(fC, V, lC + "x") == true) {
				nearlySet.insert(input2 + "x");
			}
			if (checkValidNearlyWord(fC, V, lC + "j") == true) {
				nearlySet.insert(input2 + "j");
			}
		}
	}


	//Lỗi phát âm
	for (auto i : nearlySet) {
		string fC = "";
		string v = "";
		string lC = "";
		string t = "";
		splitWord(i, fC, v, lC);
		if (lC.length() > 0 && isTone(*(--lC.end())) == true) {
			t = *(--lC.end());
			lC.pop_back();
		}
		
		// Sai ở phụ âm đầu
		if (fC.length() > 0) {
			int fCId = 0;
			for (auto j : phoneticErr) {
				if (j.second > 0 && fC.compare(j.first) == 0) {
					fCId = j.second;
					break;
				}
			}

			if(fCId != 0) for (auto j : phoneticErr) {
				if (fCId == j.second && fC.compare(j.first) != 0) {
					if (checkValidNearlyWord(j.first, v, lC + t) == true) {
						tmpSet.insert(j.first + v + lC + t);
					}
				}
			}
		}

		//Sai ở nguyên âm
		if (v.length() > 0) {
			int vId = 0;
			for (auto j : phoneticErr) {
				if (v.compare(j.first) == 0) {
					vId = j.second;
					break;
				}
			}

			if (vId != 0) for (auto j : phoneticErr) {
				if (vId == j.second && v.compare(j.first) != 0) {
					if (checkValidNearlyWord(fC, j.first, lC + t) == true) {
						tmpSet.insert(fC + j.first + lC + t);
					}
				}
			}
		}

		//Sai ở phụ âm cuối
		if (lC.length() > 0) {
			int lCId = 0;
			for (auto j : phoneticErr) {
				if (j.second < 0 && lC.compare(j.first) == 0) {
					lCId = j.second;
					break;
				}
			}

			if (lCId != 0) for (auto j : phoneticErr) {
				if (lCId == j.second && lC.compare(j.first) != 0) {
					if (checkValidNearlyWord(fC, v, j.first + t) == true) {
						tmpSet.insert(fC + v + j.first + t);
					}
				}
			}
		}

		//Sai ở dấu thanh
		if (t.length() > 0) {
			if (t.compare("r") == 0) {
				if (checkValidNearlyWord(fC, v, lC + "x") == true) {
					tmpSet.insert(fC + v + lC + "x");
				}

				if (checkValidNearlyWord(fC, v, lC + "j") == true) {
					tmpSet.insert(fC + v + lC + "j");
				}
			}

			if (t.compare("x") == 0) {
				if (checkValidNearlyWord(fC, v, lC + "r") == true) {
					tmpSet.insert(fC + v + lC + "r");
				}

				if (checkValidNearlyWord(fC, v, lC + "s") == true) {
					tmpSet.insert(fC + v + lC + "s");
				}
			}
		}
	}
	nearlySet.insert(tmpSet.begin(), tmpSet.end());
	
	tmpSet.erase(tmpSet.begin(), tmpSet.end());

	// Thêm dấu cho âm tiết k có dấu
	/*tmpSet.clear();
	for (auto i : nearlySet) {
		if (edit_distance(input, i) <= 2) {
			int haveTone = 0;
			for (auto j : i.substr(1)) {
				if (isTone(j) == true) {
					haveTone = 1;
					break;
				}
			}

			if (haveTone == 0) {
				string fC = "";
				string V = "";
				string lC = "";
				splitWord(i, fC, V, lC);
				if (checkValidNearlyWord(fC, V, lC + "s") == true) {
					tmpSet.insert(i + "s");
				}
				if (checkValidNearlyWord(fC, V, lC + "f") == true) {
					tmpSet.insert(i + "f");
				}
				if (checkValidNearlyWord(fC, V, lC + "r") == true) {
					tmpSet.insert(i + "r");
				}
				if (checkValidNearlyWord(fC, V, lC + "x") == true) {
					tmpSet.insert(i + "x");
				}
				if (checkValidNearlyWord(fC, V, lC + "j") == true) {
					tmpSet.insert(i + "j");
				}
			}

		}
	}
	nearlySet.insert(tmpSet.begin(), tmpSet.end());*/

	// Thêm dấu cho từ ban đầu
	int haveTone = 0;
	for (auto j : input.substr(1)) {
		if (isTone(j) == true) {
			haveTone = 1;
			break;
		}
	}
	if (haveTone == 0) {
		string fC = "";
		string V = "";
		string lC = "";
		splitWord(input, fC, V, lC);
		V = standardVowel[V];
		if (checkValidNearlyWord(fC, V, lC + "s") == true) {
			nearlySet.insert(fC + V + lC + "s");
		}
		if (checkValidNearlyWord(fC, V, lC + "f") == true) {
			nearlySet.insert(fC + V + lC + "f");
		}
		if (checkValidNearlyWord(fC, V, lC + "r") == true) {
			nearlySet.insert(fC + V + lC + "r");
		}
		if (checkValidNearlyWord(fC, V, lC + "x") == true) {
			nearlySet.insert(fC + V + lC + "x");
		}
		if (checkValidNearlyWord(fC, V, lC + "j") == true) {
			nearlySet.insert(fC + V + lC + "j");
		}
	}

	// return
	return nearlySet;
}

vector <wstring> nearWSyll(wstring input) {
	string syll = U2A(input);
	set <string> tmp = nearSyll(syll);
	vector <wstring> ret;

	typedef pair<double, int> DI;
	typedef pair<double, wstring> DWs;
	typedef pair<DI, DWs> DIDWs;

	set <DIDWs, greater<> > tmp2;

	for (auto i : tmp) {
		wstring wi = A2U(i);

		string word1 = wstring_to_utf8(wi);

		string query = "SELECT Pbkn, frequency, Alpha FROM unidb where word1 = \"" + word1 + "\"";
		const char* q = query.c_str();
		int qstate = mysql_query(conn, q);
		if (!qstate)
		{
			MYSQL_RES* res = mysql_store_result(conn);
			int rowNum = mysql_num_rows(res);

			if (rowNum == 0) {
				tmp2.insert(DIDWs(DI(0, 0), DWs(0, wi)));
			}
			else {
				MYSQL_ROW row = mysql_fetch_row(res);
				tmp2.insert( DIDWs(DI(stod(row[0]),stoi(row[1])), DWs(stod(row[2]), wi)) );
			}

		}
		//ret.push_back(A2U(i));
	}
	
	int count = 0;
	for (set <DIDWs>::iterator it = tmp2.begin(); it != tmp2.end(); it++) {
		ret.push_back((*it).second.second);
		count++;
		if (count > 15) break;
	}

	tmp.erase(tmp.begin(), tmp.end());
	tmp2.erase(tmp2.begin(), tmp2.end());

	return ret;
}

//int wmain() {
//
//	_setmode(_fileno(stdout), _O_WTEXT);
//	_setmode(_fileno(stdin), _O_WTEXT);
//	locale loc(locale(), new codecvt_utf8<wchar_t>);
//
//	wstring input;
//
//	wifstream fin(L"inpTest.txt");
//	fin.imbue(loc);
//	getline(fin, input);
//	//wstring input = L"ngả";
//
//	vector <wstring> rs = nearWSyll(input);
//	for (auto i : rs) {
//		wcout << i << endl;
//	}
//}

#endif
