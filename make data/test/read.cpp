//#include <cstring>
//#include <iostream>
//#include <fcntl.h> //_O_WTEXT
//#include <io.h>  
//#include <string>
//#include <vector>
//#include <locale>
//#include <codecvt> //possible C++11?
//#include <fstream>
//
//using namespace  std;
//typedef pair <int, wstring> IWs;
//
//vector <wstring> token;
//vector <IWs> sylls;
//wifstream fin(L"input.txt");
//
//const vector <wchar_t> uniList = {
//	L'a', L'á', L'à', L'ả', L'ã', L'ạ', L'ă', L'ắ', L'ằ', L'ẳ', L'ẵ', L'ặ', L'â', L'ấ', L'ầ', L'ẩ', L'ẫ', L'ậ',
//	L'b', L'c', L'd', L'đ', L'e', L'é', L'è', L'ẻ', L'ẽ', L'ẹ', L'ê', L'ế', L'ề', L'ể', L'ễ', L'ệ', L'f', L'g',
//	L'h', L'i', L'í', L'ì', L'ỉ', L'ĩ', L'ị', L'j', L'k', L'l', L'm', L'n', L'o', L'ó', L'ò', L'ỏ', L'õ', L'ọ',
//	L'ô', L'ố', L'ồ', L'ổ', L'ỗ', L'ộ', L'ơ', L'ớ', L'ờ', L'ở', L'ỡ', L'ợ', L'p', L'q', L'r', L's', L't', L'u',
//	L'ú', L'ù', L'ủ', L'ũ', L'ụ', L'ư', L'ứ', L'ừ', L'ử', L'ữ', L'ự', L'v', L'w', L'x', L'y', L'ý', L'ỳ', L'ỷ',
//	L'ỹ', L'ỵ', L'z',
//	L'A', L'Á', L'À', L'Ả', L'Ã', L'Ạ', L'Ă', L'Ắ', L'Ằ', L'Ẳ', L'Ẵ', L'Ặ', L'Â', L'Ấ', L'Ầ',
//	L'Ẩ', L'Ẫ', L'Ậ', L'B', L'C', L'D', L'Đ', L'E', L'É', L'È', L'Ẻ', L'Ẽ', L'Ẹ', L'Ê', L'Ế', L'Ề', L'Ể', L'Ễ',
//	L'Ệ', L'F', L'G', L'H', L'I', L'Í', L'Ì', L'Ỉ', L'Ĩ', L'Ị', L'J', L'K', L'L', L'M', L'N', L'O', L'Ó', L'Ò',
//	L'Ỏ', L'Õ', L'Ọ', L'Ô', L'Ố', L'Ồ', L'Ổ', L'Ỗ', L'Ộ', L'Ơ', L'Ớ', L'Ờ', L'Ở', L'Ỡ', L'Ợ', L'P', L'Q', L'R',
//	L'S', L'T', L'U', L'Ú', L'Ù', L'Ủ', L'Ũ', L'Ụ', L'Ư', L'Ứ', L'Ừ', L'Ử', L'Ữ', L'Ự', L'V', L'W', L'X', L'Y',
//	L'Ý', L'Ỳ', L'Ỷ', L'Ỹ', L'Ỵ', L'Z'
//};
//
//wchar_t sentencesEndSymbols[] = {
//	L'.', L'?', L'!'
//};
//
//bool isLetter(wchar_t wchr) {
//	int n = uniList.size();
//	bool rt = false;
//	for (int i = 0; i < n; i++) {
//		if (wchr == uniList[i]) {
//			return true;
//		}
//	}
//	return rt;
//}
//
//bool isEndOfSen(wchar_t wchr) {
//	int n = *(&sentencesEndSymbols + 1) - sentencesEndSymbols;
//	for (int i = 0; i < n; i++) {
//		if (wchr == sentencesEndSymbols[i]) {
//			return true;
//		}
//	}
//	return false;
//}
//
//void print(vector <IWs> vs) {
//	for (auto const& v : vs) {
//		wcout << v.first << L' ' << v.second << endl;
//	}
//}
//
//
//void ReadFile() {
//	wchar_t inputChar;
//
//	wstring syllable = L"";
//	int flag = 1;
//	int count = 0;
//
//	while (fin.peek() != WEOF) {
//		fin.get(inputChar);
//
//		wcout << inputChar << ' ';
//
//		if (isLetter(inputChar) == true) {
//			syllable += inputChar;
//			flag = 0;
//		}
//		else {
//			if (flag == 0) {
//				sylls.push_back(IWs(count, syllable));
//				token.push_back(syllable);
//			}
//			count++;
//
//			wstring tmp = L"";
//			tmp += inputChar;
//			token.push_back(tmp);
//
//			syllable = L"";
//			flag = 1;
//
//			if (isEndOfSen(inputChar) == true) {
//
//				// reset
//				syllable = L"";
//				flag = 1;
//				count = 0;
//				sylls.clear();
//				token.clear();
//				break;
//			}
//		}
//	}
//	cerr << "efsf: " << syllable.length() << endl;
//	if (syllable.length() > 0) {
//		sylls.push_back(IWs(count, syllable));
//		token.push_back(syllable);
//
//		print(sylls);
//	}
//	print(sylls);
//}
//
//
//int wmain() {
//
//	//read and write utf8
//	_setmode(_fileno(stdout), _O_WTEXT);
//	_setmode(_fileno(stdin), _O_WTEXT);
//	locale loc(locale(), new codecvt_utf8<wchar_t>);
//
//	//read file
//	if (!fin) wcout << "Khong tim thay input.txt\n";
//	else fin.imbue(loc);
//
//	while (fin.peek() != WEOF) ReadFile();
//
//	
//
//}
//
//int main() {
//
//	_setmode(_fileno(stdout), _O_WTEXT);
//	_setmode(_fileno(stdin), _O_WTEXT);
//
//	locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8
//
//	wifstream fin(L"input.txt");
//	if (!fin) wcout << "Khong tim thay input.txt\n";
//	else fin.imbue(loc);
//
//	wstring input;
//
//	while (fin.peek() != WEOF) {
//		getline(fin, input);
//
//		int n = input.length();
//
//		wstring syllable = L"";
//		int flag = 1;
//		int count = 0;
//
//		for (int i = 0; i < n; i++) {
//			if (isLetter(input[i]) == true) {
//				syllable += input[i];
//				flag = 0;
//			}
//			else {
//				if (flag == 0) {
//					sylls.push_back(IWs(count, syllable));
//					token.push_back(syllable);
//				}
//				count++;
//
//				wstring tmp = L"";
//				tmp += input[i];
//				token.push_back(tmp);
//
//				syllable = L"";
//				flag = 1;
//
//				if (isEndOfSen(input[i]) == true) {
//					// process
//					print(sylls);
//					wcout << endl << endl;
//					// reset
//					syllable = L"";
//					flag = 1;
//					count = 0;
//					sylls.clear();
//					token.clear();
//				}
//			}
//		}
//		if (syllable.length() > 0) {
//			sylls.push_back(IWs(count, syllable));
//			token.push_back(syllable);
//
//			// process
//			print(sylls);
//		}
//	}
//
//}