//#include <iostream>
//#include <fcntl.h> //_O_WTEXT
//#include <io.h>    //_setmode()
//#include <string>
//#include <locale>
//#include <codecvt> //possible C++11?
//#include <fstream>
//#include <vector>
//
//using namespace std;
//
//
//void splitWstr(wstring wstr, wstring& word, int& fre) {
//	int n = wstr.length();
//	word = L"";
//	fre = 0;
//	int flag = 0;
//	for (int i = 0; i < n; i++) {
//		if (wstr[i] == L'"') continue;
//		if (wstr[i] == L',') {
//			flag = 1;
//		}
//		else {
//			if (flag == 0) word += wstr[i];
//			else fre = fre * 10 + wstr[i] - L'0';
//		}
//	}
//}
//
//void splitWstr2(wstring wstr, wstring& word, int& fre) {
//	int n = wstr.length();
//	word = L"";
//	fre = 0;
//	int flag = 0;
//	for (int i = 0; i < n; i++) {
//		if (wstr[i] == L'"') continue;
//		if (wstr[i] == L',') {
//			flag = 1;
//			i++;
//		}
//		else {
//			if (flag == 0) word += wstr[i];
//			else fre = fre * 10 + wstr[i] - L'0';
//		}
//	}
//}
//
//void meruni() {
//	_setmode(_fileno(stdout), _O_WTEXT); //needed for output
//	_setmode(_fileno(stdin), _O_WTEXT); //needed for input
//	// nhớ chuyển font của console sang Consolas (size 16)
//	locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8
//	// lưu file tiếng Việt (UTF-8 without BOM)
//
//	// đọc file tiếng Việt (định dạng UTF-8 without BOM)
//	wifstream fin1(L"./data new/uni1-2-3-4.txt");
//	if (!fin1) {
//		wcout << L"Không thể đọc file data1.txt\n";
//	}
//	else { fin1.imbue(loc); }
//
//	wifstream fin2(L"./data new/uni5.txt");
//	if (!fin2) {
//		wcout << L"Không thể đọc file data1.txt\n";
//	}
//	else { fin2.imbue(loc); }
//
//	wofstream fout(L"./data new/uni.txt");
//	fout.imbue(loc);
//
//	//fout << L"word1, frequency" << endl;
//
//	wstring wstr1 = L"";
//	wstring wstr2 = L"";
//
//	wstring word1 = L"";
//	wstring word2 = L"";
//
//	int fre1 = 0;
//	int fre2 = 0;
//
//	int read = 0;
//
//
//	while (fin1.peek() != WEOF) {
//		if (read == 0) {
//			getline(fin1, wstr1);
//			getline(fin2, wstr2);
//			splitWstr(wstr1, word1, fre1);
//			splitWstr(wstr2, word2, fre2);
//		}
//
//		if (read == 1) {
//			getline(fin1, wstr1);
//			splitWstr(wstr1, word1, fre1);
//		}
//
//		if (read == 2) {
//			getline(fin2, wstr2);
//			splitWstr(wstr2, word2, fre2);
//		}
//
//		int cmp = word1.compare(word2);
//
//		if (cmp == 0) {
//			fout << word1 << L"," << fre1 + fre2 << endl;
//			//fout << word1 << L'|' << fre1 + fre2 << endl;
//
//			word1 = L""; fre1 = 0;
//			word2 = L""; fre2 = 0;
//
//			read = 0;
//		}
//		else if (cmp < 0) {
//			fout << word1 << "," << fre1 << endl;
//			//fout << word1 << L'|' << fre1 << endl;
//
//			word1 = L""; fre1 = 0;
//
//			read = 1;
//		}
//		else if (cmp > 0) {
//			fout << word2 << "," << fre2 << endl;
//			//fout << word2 << L'|' << fre2 << endl;
//
//			word2 = L""; fre2 = 0;
//
//			read = 2;
//		}
//
//		if (fre2 == 0 && fin2.peek() == WEOF) break;
//	}
//
//	if (fre1 != 0 && fin1.peek() == WEOF) {
//		while (fin2.peek() != WEOF) {
//			getline(fin2, wstr2);
//			splitWstr(wstr2, word2, fre2);
//
//			int cmp = word1.compare(word2);
//			if (cmp == 0) {
//				fout << word1 << "," << fre1 + fre2 << endl;
//				//fout << word1 << L'|' << fre1 + fre2 << endl;
//
//				word1 = L""; fre1 = 0;
//				word2 = L""; fre2 = 0;
//
//				read = 0;
//			}
//			else if (cmp < 0) {
//				fout << word1 << "," << fre1 << endl;
//				//fout << word1 << L'|' << fre1 << endl;
//
//				word1 = L""; fre1 = 0;
//
//				read = 1;
//				break;
//			}
//			else if (cmp > 0) {
//				fout << word2 << "," << fre2 << endl;
//				//fout << word2 << L'|' << fre2 << endl;
//
//				word2 = L""; fre2 = 0;
//
//				read = 2;
//			}
//		}
//	}
//
//	if (fre1 != 0) fout << word1 << L"," << fre1 << endl;
//	if (fre2 != 0) fout << word2 << L"," << fre2 << endl;
//
//	//if(fre1 != 0) fout << word1 << L'|' << fre1 << endl;
//	//if(fre2 != 0) fout << word2 << L'|' << fre2 << endl;
//
//	while (fin1.peek() != WEOF) {
//		getline(fin1, wstr1);
//		splitWstr(wstr1, word1, fre1);
//		fout << word1 << L"," << fre1 << endl;
//		//fout << word1 << L'|' << fre1 << endl;
//	}
//
//	while (fin2.peek() != WEOF) {
//		getline(fin2, wstr2);
//		splitWstr(wstr2, word2, fre2);
//		fout << word2 << "," << fre2 << endl;
//		//fout << word2 << L'|' << fre2 << endl;
//	}
//
//	fin2.close();
//	fin1.close();
//	fout.close();
//}
//
//int wmain(int argc, wchar_t* argv[]) {
//	meruni();
//}