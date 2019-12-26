#include <iostream>
#include <fcntl.h> //_O_WTEXT
#include <io.h>    //_setmode()
#include <string>
#include <locale>
#include <codecvt> //possible C++11?
#include <fstream>
#include <vector>
#include <set>

#include "A2U.h"
#include "U2A.h"
#include "ConstVar.h"
#include "GeneralFunc.h"

using namespace std;


vector <wchar_t> endSen = { L'.', L'!', L'?', L':', L'-', L'|', L';' };

vector <wchar_t> endSyll = { L' ', L',', L'/', L'\"', L'\'' };

//------------------------------------------------------------

map <wstring, int> unigram;
map <wstring, int> bigram;
map <wstring, int> trigram;
//------------------------------------------------------------

bool isEndSyll(wchar_t wchr) {
	int n = endSyll.size();
	for (int i = 0; i < n; i++) {
		if (wchr == endSyll[i]) return true;
	}
	return false;
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
	if (glconsonant.length() > 0) lastCharInLastConsonant = *(--glconsonant.end());
	/*for (string::iterator i = glconsonant.begin(); i != glconsonant.end(); i++) {
		if (isTone(*i) == true) {
			if (lastCharInLastConsonant != '0') {
				lastCharInLastConsonant = *i;
				glconsonant.erase(i);
			}
			else lastCharInVowel = *i;
		}
	}*/

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

//normalize syllable
wstring normalizeSyll(wstring wstr) {
	wstring res = L"";
	string res1 = U2A(wstr);

	string inputFirstConsonant, inputVowel, inputLastConsonant;
	splitWord(res1, inputFirstConsonant, inputVowel, inputLastConsonant);
	

	if (checkValidNearlyWord(inputFirstConsonant, inputVowel, inputLastConsonant)) {
		res = A2U(res1);
		//wcout << wstr << endl;
	}
	return res;
}

int wmain(int argc, wchar_t* argv[])
{
	_setmode(_fileno(stdout), _O_WTEXT); //needed for output
	_setmode(_fileno(stdin), _O_WTEXT); //needed for input
	// nhớ chuyển font của console sang Consolas (size 16)
	locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8
	// lưu file tiếng Việt (UTF-8 without BOM)
	wstring wstr;

	// đọc file tiếng Việt (định dạng UTF-8 without BOM)
	wifstream fin(L"./data/VNcorpus5.txt");
	//wifstream fin(L"data1.txt");
	if (!fin) {
		wcout << L"Không thể đọc file data1.txt\n";
	}
	else { fin.imbue(loc); }

	//wofstream fout(L"output.txt");
	//fout.imbue(loc);

	int deletedCount = 0;
	int lineCount = 0;
	int wordCount = 0;

	// read from file
	while (fin.peek() != WEOF) {
		//read a line
		getline(fin, wstr);

		int n = wstr.length();
		//wstring wstr2 = L"";
		wstring syllable = L"";
		int flag = 1;
		//flag = 0: the last wchar is not <space>, flag = 1: the last wchar is <space>

		wstring word1 = L"";
		wstring word2 = L"";
		wstring word3 = L"";

		// for log
		lineCount++;
		if (lineCount % 50000 == 0) cerr << "- " << lineCount << ": ";

		for (int i = 0; i < n; i++) {
			if (isLetter(wstr[i]) == false) {
				if (flag == 0) {
					
					wstring syllableNormalized = normalizeSyll(syllable);
					//wstr2 += syllableNormalized;
					//wcout << wstr2 <<  endl;

					if (isEndSyll(wstr[i]) == true || isEndOfSen(wstr[i]) == true) {
						if (syllableNormalized.length() > 0) {
							//for log
							wordCount++;

							//wstr2 += L' ';
							word1 = word2;
							word2 = word3;
							word3 = syllableNormalized;

							// unigram
							unigram[word3]++;

							if (word2.compare(L"") != 0) {
								//bigram
								wstring tmpstr = word2 + L"," + word3;
								bigram[tmpstr]++;
							}
							if (word1.compare(L"") != 0) {
								//trigram
								wstring tmpstr = word1 + L"," + word2 + L"," + word3;
								trigram[tmpstr]++;
							}
						}
						if (isEndOfSen(wstr[i]) == true) {
							word1 = L"";
							word2 = L"";
							word3 = L"";
						}
					}

					flag = 1;
					syllable = L"";
				}
			}
			else {
				syllable += wstr[i];
				flag = 0;
			}
		}
		wstring syllableNormalized = normalizeSyll(syllable);
		if (syllableNormalized.length() > 0) {
			//for log
			wordCount++;

			//wstr2 += L' ';
			word1 = word2;
			word2 = word3;
			word3 = syllableNormalized;

			// unigram
			unigram[word3]++;

			if (word2.compare(L"") != 0) {
				//bigram
				wstring tmpstr = word2 + L"," + word3;
				bigram[tmpstr]++;
			}
			if (word1.compare(L"") != 0) {
				//trigram
				wstring tmpstr = word1 + L"," + word2 + L"," + word3;
				trigram[tmpstr]++;
			}
		}
		//wstr2 += syllableNormalized;

		//calculate how many char deleted
		//deletedCount += wstr.length() - wstr2.length();

		//write $wstr2 to file
		//if(wstr2.length() > 0) fout << wstr2 << endl;

		//for log
		if (lineCount % 50000 == 0) cerr << wordCount << endl;
	}

	//cerr << "Deleted Char: " << deletedCount << endl;
	fin.close();
	//fout.close();

	// test
	/*wcout << L"\nUnigram: \n";
	for (auto const& imap : unigram) {
		wcout << imap.first << ' ' << imap.second << endl;
	}

	wcout << L"\nBigram: \n";
	for (auto const& imap : bigram) {
		wcout << imap.first << ' ' << imap.second << endl;
	}

	wcout << L"\nTrigram: \n";
	for (auto const& imap : trigram) {
		wcout << imap.first << ' ' << imap.second << endl;
	}*/

	//uni
	wofstream uniout(L"uni5.txt");
	uniout.imbue(loc);
	for (auto const& imap : unigram) {
		uniout << imap.first << L',' << imap.second << endl;
	}
	uniout.close();

	//bi
	wofstream biout(L"bi5.txt");
	biout.imbue(loc);
	for (auto const& imap : bigram) {
		biout << imap.first << L',' << imap.second << endl;
	}
	biout.close();

	//tri
	wofstream triout(L"tri5.txt");
	triout.imbue(loc);
	for (auto const& imap : trigram) {
		triout << imap.first << L',' << imap.second << endl;
	}
	triout.close();

	return 0;
}
