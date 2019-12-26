//#include <iostream>
//#include <fcntl.h> //_O_WTEXT
//#include <io.h>    //_setmode()
//#include <string>
//#include <locale>
//#include <codecvt> //possible C++11?
//#include <fstream>
//#include <vector>
//
//#define __FORM1__
////#define __FORM2__
//
//
//using namespace std;
//
////read __form2__
//void splitWstr(wstring wstr, wstring& word1, wstring& word2, wstring &word3, int& fre) {
//	int n = wstr.length();
//	word1 = L"";
//	word2 = L"";
//	word3 = L"";
//	fre = 0;
//	int flag = 0;
//	for (int i = 0; i < n; i++) {
//		if (wstr[i] == L'"') continue;
//		if (wstr[i] == L',') {
//			flag++;
//		}
//		else {
//			if (flag == 0) word1 += wstr[i];
//			if (flag == 1) word2 += wstr[i];
//			if (flag == 2) word3 += wstr[i];
//			if (flag == 3) fre = fre * 10 + wstr[i] - L'0';
//		}
//	}
//}
//
////read __form1__
//void splitWstr2(wstring wstr, wstring& word1, wstring& word2, wstring &word3, int& fre) {
//	int n = wstr.length();
//	word1 = L"";
//	word2 = L"";
//	word3 = L"";
//	fre = 0;
//	int flag = 0;
//	for (int i = 0; i < n; i++) {
//		if (wstr[i] == L'"') continue;
//		if (wstr[i] == L',') {
//			flag++;
//			i++;
//		}
//		else {
//			if (flag == 0) word1 += wstr[i];
//			if (flag == 1) word2 += wstr[i];
//			if (flag == 2) word3 += wstr[i];
//			if (flag == 3) fre = fre * 10 + wstr[i] - L'0';
//		}
//	}
//}
//
//void mertri() {
//	_setmode(_fileno(stdout), _O_WTEXT); //needed for output
//	_setmode(_fileno(stdin), _O_WTEXT); //needed for input
//	// nhớ chuyển font của console sang Consolas (size 16)
//	locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8
//	// lưu file tiếng Việt (UTF-8 without BOM)
//
//	// đọc file tiếng Việt (định dạng UTF-8 without BOM)
//	wifstream fin1(L"./data new/tri1-2-3-4.txt");
//	if (!fin1) {
//		wcout << L"Không thể đọc file tri1.txt\n";
//	}
//	else { fin1.imbue(loc); }
//
//	wifstream fin2(L"./data new/tri5.txt");
//	if (!fin2) {
//		wcout << L"Không thể đọc file tri2.txt\n";
//	}
//	else { fin2.imbue(loc); }
//
//	wofstream fout(L"./data new/tri.txt");
//	fout.imbue(loc);
//
//#ifdef __FORM1__
//	//fout << L"word1, frequency" << endl;
//#endif // __FORM1__
//
//
//	wstring wstr1 = L"";
//	wstring wstr2 = L"";
//
//	wstring word11 = L"";
//	wstring word12 = L"";
//	wstring word13 = L"";
//	wstring word21 = L"";
//	wstring word22 = L"";
//	wstring word23 = L"";
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
//			splitWstr(wstr1, word11, word12, word13, fre1);
//			splitWstr(wstr2, word21, word22, word23, fre2);
//			word1 = word11 + L' ' + word12 + L' ' + word13;
//			word2 = word21 + L' ' + word22 + L' ' + word23;
//		}
//
//		if (read == 1) {
//			getline(fin1, wstr1);
//			splitWstr(wstr1, word11, word12, word13, fre1);
//			word1 = word11 + L' ' + word12 + L' ' + word13;
//		}
//
//		if (read == 2) {
//			getline(fin2, wstr2);
//			splitWstr(wstr2, word21, word22, word23, fre2);
//			word2 = word21 + L' ' + word22 + L' ' + word23;
//		}
//
//		int cmp = word1.compare(word2);
//
//		if (cmp == 0) {
//			#ifdef __FORM1__
//				fout << word11 << L"," << word12 << L"," << word13 << L"," << fre1 + fre2 << endl;
//			#endif // __FORM1__
//
//			#ifdef __FORM2__
//				fout << word1 << L'|' << fre1 + fre2 << endl;
//			#endif // __FORM2__
//
//			word1 = L""; fre1 = 0;
//			word2 = L""; fre2 = 0;
//
//			read = 0;
//		}
//		else if (cmp < 0) {
//			#ifdef __FORM1__
//				fout << word11 << L"," << word12 << L"," << word13 << L"," << fre1 << endl;
//			#endif // __FORM1__
//
//			#ifdef __FORM2__
//				fout << word1 << L'|' << fre1 << endl;
//			#endif // __FORM2__
//
//			word1 = L""; fre1 = 0;
//
//			read = 1;
//		}
//		else if (cmp > 0) {
//			#ifdef __FORM1__
//				fout << word21 << L"," << word22 << L"," << word23 << L"," << fre2 << endl;
//			#endif // __FORM1__
//
//			#ifdef __FORM2__
//				fout << word2 << L'|' << fre2 << endl;
//			#endif // __FORM2__
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
//			splitWstr(wstr2, word21, word22, word23, fre2);
//
//			word2 = word21 + L' ' + word22 + L' ' + word23;
//
//			int cmp = word1.compare(word2);
//			if (cmp == 0) {
//
//				#ifdef __FORM1__
//					fout << word11 << L"," << word12 << L"," << word13 << L"," << fre1 + fre2 << endl;
//				#endif // __FORM1__
//
//				#ifdef __FORM2__
//					fout << word1 << L'|' << fre1 + fre2 << endl;
//				#endif // __FORM2__
//
//				word1 = L""; fre1 = 0;
//				word2 = L""; fre2 = 0;
//
//				read = 0;
//			}
//			else if (cmp < 0) {
//				#ifdef __FORM1__
//					fout << word11 << L"," << word12 << L"," << word13 << L"," << fre1 << endl;
//				#endif // __FORM1__
//
//				#ifdef __FORM2__
//					fout << word1 << L'|' << fre1 << endl;
//				#endif // __FORM2__
//
//				word1 = L""; fre1 = 0;
//
//				read = 1;
//				break;
//			}
//			else if (cmp > 0) {
//				#ifdef __FORM1__
//					fout << word21 << L"," << word22 << L"," << word23 << L"," << fre2 << endl;
//				#endif // __FORM1__
//
//				#ifdef __FORM2__
//					fout << word2 << L'|' << fre2 << endl;
//				#endif // __FORM2__
//
//				word2 = L""; fre2 = 0;
//
//				read = 2;
//			}
//		}
//	}
//
//	#ifdef __FORM1__
//		if (fre1 != 0) fout << word11 << L"," << word12 << L"," << word13 << L"," << fre1 << endl;
//		if (fre2 != 0) fout << word21 << L"," << word22 << L"," << word23 << L"," << fre2 << endl;
//	#endif // __FORM1__
//
//	#ifdef __FORM2__
//		if (fre1 != 0) fout << word1 << L'|' << fre1 << endl;
//		if (fre2 != 0) fout << word2 << L'|' << fre2 << endl;
//	#endif // __FORM2__
//
//
//
//	while (fin1.peek() != WEOF) {
//		getline(fin1, wstr1);
//		splitWstr(wstr1, word11, word12, word13, fre1);
//
//		word1 = word11 + L' ' + word12 + L' ' + word13;
//
//		#ifdef __FORM1__
//			fout << word11 << L"," << word12 << L"," << word13 << L"," << fre1 << endl;
//		#endif // __FORM1__
//
//		#ifdef __FORM2__
//			fout << word1 << L'|' << fre1 << endl;
//		#endif // __FORM2__
//	}
//
//	while (fin2.peek() != WEOF) {
//		getline(fin2, wstr2);
//		splitWstr(wstr2, word21, word22, word23, fre2);
//
//		word2 = word21 + L' ' + word22 + L' ' + word23;
//
//		#ifdef __FORM1__
//			fout << word21 << L"," << word22 << L"," << word23 << L"," << fre2 << endl;
//		#endif // __FORM1__
//
//		#ifdef __FORM2__
//			fout << word2 << L'|' << fre2 << endl;
//		#endif // __FORM2__
//	}
//
//	fin2.close();
//	fin1.close();
//	fout.close();
//}
//
//int wmain(int argc, wchar_t* argv[]) {
//	mertri();
//}