#include "lib.h"
#include "A2U.h"
#include "U2A.h"
#include "ConstVar.h"
#include "CorrectSen.h"
#include "GeneralFunc.h"
#include "MysqlConn.h"
#include "NearSyll.h"
#include "ReadFile.h"
#include "NormalizeSyll.h"

wstring autoCorrect(wstring inpText)
{

	MysqlConn();

	vector <wstring> tokens;
	vector <IWs> sylls;
	vector <IWs> sylls2;

	wstring res = L"";

	//int N = inpText.length();
	int pos = -1;

	int N = inpText.length();

	while (1) {
		pos = readSen(pos + 1, inpText, sylls, tokens);

		sylls2 = correctSen(sylls);

		int j = 0;
		int n = tokens.size();
		int m = sylls2.size();

		/*for (auto token : tokens) {
			res += token;
		}*/

		for (int i = 0; i < n; i++) {
			if (j < m && sylls2[j].first == i) {
				res += sylls2[j].second;
				j++;
			}
			else res += tokens[i];
		}

		//reset
		freeVector(sylls);
		freeVector(tokens);
		freeVector(sylls2);

		if (pos >= N - 1) break;
	}

	return res;
}
