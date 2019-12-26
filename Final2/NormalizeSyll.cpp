#include "lib.h"
#include "A2U.h"
#include "U2A.h"


void normalizeSyll(vector <IWs> &sylls) {
	for (auto i : sylls) {
		wstring wsyll = i.second;
		string syll = U2A(wsyll);

		i.second = A2U(syll);

		wcout << i.second << endl;
	}
}