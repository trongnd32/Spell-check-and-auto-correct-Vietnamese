#include <bits/stdc++.h>
#define MAXEDFIRSTCONSONANT 1
#define MAXEDVOWEL 2
#define MAXEDLASTCONSONANT 1
#define INFED 100

#define __DEBUG__

using namespace std;
typedef pair <int,int> II;
typedef pair <int, char> IC;

string input;
// vector <string> nearlySet;
set <string> nearlySet;

const char consonantChar[15] = {'b','c','d','g','h','k','l','m','n','q','r','s','t','v','x'};
const char vowelChar[] = {'a','e','w','u','y','i','o'};
const char lastConsonantChar[5] = {'c','p','t','m','n'};
const char tone[5] = {'s','f','r','x','j'};
string firstConsonant[28] = {"b","c","d","dd","g","h","k","l","m","n","q","r","s","t","v","x","ch","gh","gi","kh","ng","nh","ph","qu","th","tr","ngh",""};
string lastConsonant[9] = {"c","p","t","m","n","ch","ng","nh",""};
string vowel[74] = {"a", "aw", "aa", "e", "ee", "i", "o", "oo", "ow", "u", "w", "uw", "y", "ai", "ao", "au", "ay", "aau", "aua", "aay", "aya", "eo", "eeu", 
                    "eue", "ia", "iu", "iee", "oa", "oaw", "oe", "oi", "oio", "ooi", "oiw", "owi", "ua", "uaa", "ui", "uee", "uoo", "uow", "uy", "uwa", "wa",
                    "uaw", "uiw", "uwi", "wi", "uwow", "uow", "wow", "wu", "uwu", "uuw", "yee", "oai", "oay", "uaay", "uaya", "uooi", "uoio", "ieeu", "ieue", 
                    "uyee", "uouw", "uowu", "uwowu", "uoiw", "uowi", "uwowi", "uya", "yeeu", "yeue", "uyu"};
vector <char> toneNearBy[26] = {
  {'s'},              //a
  {},                 //b
  {'x','f'},          //c
  {'f','s','x','r'},  //d
  {'r','s'},          //e
  {'r'},              //f
  {'f'},              //g
  {'j'},              //h
  {'j'},              //i
  {},                 //j
  {'j'},              //k
  {},
  {'j'},
  {'j'},
  {},
  {},
  {},
  {'f'},
  {'x'},
  {'r','f'},
  {'j'},
  {'f'},
  {'s'},
  {'s'},
  {},
  {'s','x'}
};

vector <char> replaceChar[26] = {
  {'q','w','s','z'}, //a
  {'v','g','h','n'}, //b
  {'x','d','f','v','g'}, //c
  {'s','e','r','f','c','x'}, //d
  {'w','r','d','s'}, //e
  {'d','r','t','g','v','c'}, //f
  {'f','t','y','h','b','v','c'}, //g
  {'g','y','u','j','n','b','v'}, //h
  {'u','o','k','j'}, //i
  {'h','u','i','k','m','n','b'}, //j
  {'j','i','o','l','m','n'}, //k
  {'k','o','p','m'}, //l
  {'n','j','k','l'}, //m
  {'b','h','j','m'}, //n
  {'i','p','l','k'}, //o
  {'o','l'}, //p
  {'w','a'}, //q
  {'e','t','f','d'}, //r
  {'a','w','e','d','x','z'}, //s
  {'r','y','g','f'}, //t
  {'y','i','j','h'}, //u
  {'c','f','g','h','b'}, //v
  {'q','e','s','a'}, //w
  {'z','s','d','f','c'}, //x
  {'t','u','h','g'}, //y
  {'a','s','d','x'} //z
};

map <string, int> mapOfVowel = {
  {"a", 0},
  {"aw", 1},
  {"aa", 2},
  {"e", 3},
  {"ee", 4},
  {"i", 5},
  {"o", 6},
  {"oo", 7},
  {"ow", 8},
  {"u", 9},
  {"w", 10}, {"uw", 10},
  {"y", 11},
  {"ai", 12},
  {"ao", 13},
  {"au", 14},
  {"ay", 15},
  {"aau", 16}, {"aua", 16},
  {"aay", 17}, {"aya", 17},
  {"eo", 18},
  {"eeu", 19}, {"eue", 19},
  {"ia", 20},
  {"iu", 21},
  {"iee", 22},
  {"oa", 23},
  {"oaw", 24},
  {"oe", 25},
  {"oi", 26},
  //{"oo", 27},
  {"oio", 28}, {"ooi", 28},
  {"oiw", 29}, {"owi", 29},
  {"ua", 30},
  {"uaa", 31},
  {"ui", 32},
  {"uee", 33},
  {"uoo", 34},
  {"uow", 35},
  {"uy", 36},
  {"uwa", 37}, {"wa", 37}, {"uaw", 37},
  {"uiw", 38}, {"uwi", 38}, {"wi", 38},
  {"uwow", 39}, {"wow", 39},
  {"wu", 40}, {"uwu", 40}, {"uuw", 40},
  {"yee", 41},
  {"oai", 42},
  {"oay", 43},
  {"uaay", 44}, {"uaya", 44},
  {"uooi", 45}, {"uoio", 45},
  {"ieeu", 46}, {"ieue", 46},
  {"uyee", 47},
  {"uouw", 48}, {"uowu", 48}, {"uwowu", 48},
  {"uoiw", 49}, {"uowi", 49}, {"uwowi", 49},
  {"uya", 50},
  {"yeeu", 51}, {"yeue", 51},
  {"uyu", 52}
};

map <string, int> mapOfLastConsonant = {
  {"c", 0},
  {"p", 1},
  {"t", 2},
  {"m", 3},
  {"n", 4},
  {"ch", 5},
  {"ng", 6},
  {"nh", 7},
  {"", 8}
};

map <string, int> mapOfTone = {
  {"s", 0},
  {"f", 1},
  {"r", 2},
  {"x", 3},
  {"j", 4},
  {"", 5}
};

int combineVowelLastConsonant[53][9] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 0, 1, 0, 0},
  {1, 1, 1, 1, 1, 0, 1, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 0, 1},
  {1, 1, 1, 1, 1, 1, 0, 1, 1},
  {0, 1, 1, 1, 1, 1, 0, 1, 1},
  {1, 1, 1, 1, 1, 0, 1, 0, 1},
  {1, 1, 1, 1, 1, 0, 1, 0, 1},
  {1, 1, 1, 1, 1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 0, 1, 0, 1},
  {1, 1, 1, 1, 1, 0, 1, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 0, 1, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 0, 1, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 1, 1, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 1, 1, 1, 0, 0, 1, 1},
  {0, 0, 1, 1, 1, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 1, 1, 0, 0, 1, 0, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1}
};

int combineToneLastConsonant[6][9] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 1, 1, 0, 1, 1, 1},
  {0, 0, 0, 1, 1, 0, 1, 1, 1},
  {0, 0, 0, 1, 1, 0, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 1, 1, 0, 1, 1, 1}
};

int ED[10][10];

//---------------------------------------------

bool isConsonantChar(char chr){
  int n = *(&consonantChar + 1) - consonantChar;
  for(int i = 0; i < n; i++) {
    if(chr == consonantChar[i]) return true;
  }
  return false;
}

bool isVowelChar(char chr) {
  int n = *(&vowelChar + 1) - vowelChar;
  for (int i = 0; i < n; i++){
    if (chr == vowelChar[i]) return true;
  }
  return false;
}

bool isLastConsonantChar(char chr){
  int n = *(&lastConsonantChar + 1) - lastConsonantChar;
  for(int i = 0; i < n; i++) {
    if(chr == lastConsonantChar[i]) return true;
  }
  return false;
}

bool isFirstConsonant(string str) {
  int n = *(&firstConsonant + 1) - firstConsonant;
  for(int i = 0; i < n; i++) {
    if(str.compare(firstConsonant[i]) == 0) return true;
  }
  return false;
}

bool isLastConsonant(string str) {
  int n = *(&lastConsonant + 1) - lastConsonant;
  for(int i = 0; i < n;i++) {
    if(str.compare(lastConsonant[i]) == 0) return true;
  }
  return false;
}

bool isTone(char chr) {
  int n = *(&tone + 1) - tone;
  for (int i = 0; i < n; i++) {
    if (chr == tone[i]) return true;
  }
  return false;
}

bool canReplace(char chr1, char chr2){
  int n = replaceChar[chr1 - 'a'].size();
  for (int i = 0; i < n; i++) {
    if(chr2 == replaceChar[chr1 - 'a'][i]) return true;
  }
  return false;
}

//-------------------------------------------------
int edit_distance(string A, string B) {
  int n = A.length(), m = B.length();
  //int ED[n + 1][m + 1];
  for (int i = 0; i <= n; i++) memset(ED[i], 0, sizeof(ED[i])); // set everything to 0
  for (int j = 0; j <= m; j++) ED[0][j] = j;
  for (int i = 0; i <= n; i++) ED[i][0] = i;
  int diff;
  for (int i = 1; i <= n; i++){
    for (int j = 1; j <= m; j++){
      ED[i][j] = ED[i - 1][j] + 1;
      ED[i][j] = (ED[i][j] < ED[i][j - 1] + 1 ? ED[i][j] : ED[i][j - 1] + 1);
      diff = (A[i - 1] == B[j - 1] ? 0 : 1); // arrays in C are indexed from 0
      if (A[i - 1] != B[j - 1]){
        if(canReplace(A[i - 1], B[j - 1])) diff = 1;
        else diff = INFED; 
      }
      ED[i][j] = (ED[i][j] < ED[i - 1][j - 1] + diff ? ED[i][j] : ED[i - 1][j - 1] + diff);
    }
  }
  return ED[n][m];
}

vector < pair <int,char> > findDeleteChars(string inputVowel, string destVowel){
  vector <pair <int,char> > deletedChar;
  int n = inputVowel.length();
  int m = destVowel.length();

  //tracing
  vector <II> path;
  while(n && m) {
        if(ED[n][m] == ED[n-1][m] + 1) {
            path.push_back(II(-1, n));
            n--;
            continue;
        }
        if (ED[n][m] == ED[n][m-1] + 1) {
            path.push_back(II(1, n));
            m--;
            continue;
        }
        if (ED[n][m] == ED[n-1][m-1] + 1) {
            path.push_back(II(0, n));
            n--;
            m--;
            continue;
        }
        if(inputVowel[n-1] == destVowel[m-1]){
            n--;
            m--;
            continue;
        }
    }
    
    // get deleted char
    int k = path.size();
    for(int i = 0; i < k; i++) {
      if(path[i].first == -1) {
        deletedChar.push_back(IC(path[i].second - 1, inputVowel[path[i].second - 1]));
      }
    }
  return deletedChar;
}

vector <string> genNearlyFirstConsonant(string inputFirstConsonant) {
  vector <string> res;
  int n = *(&firstConsonant + 1) - firstConsonant;
  for (int i = 0; i < n; i++){
    if(edit_distance(inputFirstConsonant, firstConsonant[i]) <= MAXEDFIRSTCONSONANT) res.push_back(firstConsonant[i]);
  }
  return res;
}

vector <string> genNearlyVowel(string inputVowel){
  vector <string> res;
  int n = *(&vowel + 1) - vowel;
  for(int i = 0; i < n; i++) {
    int edvowel = edit_distance(inputVowel, vowel[i]);

    if (edvowel <= MAXEDVOWEL) res.push_back(vowel[i]);
    if (edvowel <= MAXEDVOWEL + 1) {
      vector < pair <int, char> > deletedChar = findDeleteChars(inputVowel, vowel[i]);
      int m = deletedChar.size();

      for(int k = 0; k < m; k++) {
        if (isTone(deletedChar[k].second) && deletedChar[k].first != 0) {
          string str = vowel[i] + deletedChar[k].second;
          res.push_back(str);
        } else {
          if(edvowel <= MAXEDVOWEL) {
            int repToneSize = toneNearBy[deletedChar[k].second - 'a'].size();
            for (int o = 0; o < repToneSize; o++) {
              string str = vowel[i] + toneNearBy[deletedChar[k].second - 'a'][o];
              res.push_back(str);
            }
          }
        }
      }
    }
  }
  return res;
}

vector <string> genNearlyLastConsonant(string inputLastConsonant) {
  vector <string> res;
  int n = *(&lastConsonant + 1) - lastConsonant;
  for(int i = 0; i < n; i++) {
    int edlast = edit_distance(inputLastConsonant, lastConsonant[i]);
    if (edlast <= MAXEDLASTCONSONANT) res.push_back(lastConsonant[i]);

    if (edlast <= MAXEDLASTCONSONANT + 1) {
      vector < pair <int, char> > deletedChar = findDeleteChars(inputLastConsonant, lastConsonant[i]);
      int m = deletedChar.size();

      for(int k = 0; k < m; k++) {
        if (isTone(deletedChar[k].second)) {
          string str = lastConsonant[i] + deletedChar[k].second;
          res.push_back(str);
        } else {
          if(edlast <= MAXEDLASTCONSONANT) {
            int repToneSize = toneNearBy[deletedChar[k].second - 'a'].size();
            for (int o = 0; o < repToneSize; o++) {
              string str = lastConsonant[i] + toneNearBy[deletedChar[k].second - 'a'][o];
              res.push_back(str);
            }
          }
        }
      }
    }
  }
  return res;
}

bool checkValidNearlyWord(string gfconsonant, string gvowel, string glconsonant) {
  char lastCharInVowel = *(--gvowel.end());
  char lastCharInLastConsonant = *(--glconsonant.end());
  if (isTone(lastCharInVowel) && isTone(lastCharInLastConsonant)) return false;
  string newGvowel = gvowel;
  string newGlconsonant = glconsonant;
  string toneChar = "";
  if (isTone(lastCharInVowel)) {
    newGvowel.pop_back();
    toneChar = lastCharInVowel;
  }
  if(isTone(lastCharInLastConsonant)) {
    newGlconsonant.pop_back();
    toneChar = lastCharInLastConsonant;
  }
  if(newGvowel.compare("uow") == 0 && newGlconsonant.length() > 0) newGvowel = "uwow";
  int idxVowel = mapOfVowel[newGvowel];
  int idxLastConsonant = mapOfLastConsonant[newGlconsonant];
  int idxTone = mapOfTone[toneChar];

  if (combineVowelLastConsonant[idxVowel][idxLastConsonant] == 0) return false;
  if (combineToneLastConsonant[idxTone][idxLastConsonant] == 0) return false;
  return true;
}

void nearlyGenerator(int firstPos, int lastPos){

  int n = input.length();

  string inputFirstConsonant = input.substr(0, firstPos);
  string inputVowel = input.substr(firstPos, lastPos - firstPos);
  string inputLastConsonant = input.substr(lastPos);

  vector <string> validFirstConsonant = genNearlyFirstConsonant(inputFirstConsonant);
  vector <string> validVowel = genNearlyVowel(inputVowel);
  vector <string> validLastConsonant = genNearlyLastConsonant(inputLastConsonant);

  // Ghep cac thanh phan
  int len1 = validFirstConsonant.size();
  int len2 = validVowel.size();
  int len3 = validLastConsonant.size();
  
  for(int i = 0; i < len1; i++) {
    for(int j = 0; j < len2; j++){
      for(int k = 0; k < len3; k++){
        if(checkValidNearlyWord(validFirstConsonant[i], validVowel[j], validLastConsonant[k])) {
          string str = validFirstConsonant[i] + validVowel[j] + validLastConsonant[k];
          // nearlySet.push_back(str);
          nearlySet.insert(str);
        }
      }
    }
  }
  
  // ---------------------------------------
  string inputNew = "";

  // swap first position
  if (firstPos > 0){
    inputNew = input.substr(0, firstPos - 1) + input[firstPos] + input[firstPos - 1] + input.substr(firstPos + 1);

    inputFirstConsonant = input.substr(0, firstPos);
    inputVowel = input.substr(firstPos, lastPos - firstPos);
    inputLastConsonant = input.substr(lastPos);

    if (isFirstConsonant(inputFirstConsonant)) {
      validVowel.clear();
      validLastConsonant.clear();
      validVowel = genNearlyVowel(inputVowel);
      validLastConsonant = genNearlyLastConsonant(inputLastConsonant);

      // Ghep cac thanh phan
      int len1 = validVowel.size();
      int len2 = validLastConsonant.size();

      for(int i = 0; i < len1; i++) {
        for(int j = 0; j < len2; j++) {
          if(checkValidNearlyWord(inputFirstConsonant, validVowel[i], validLastConsonant[j])) {
            string str = inputFirstConsonant + validVowel[i] + validLastConsonant[j];
            // nearlySet.push_back(str);
            nearlySet.insert(str);
          }
        }
      }
    }
  }

  // swap last position
  if (lastPos < n - 1) {
    inputNew = input.substr(0, lastPos - 1) + input[lastPos] + input[lastPos - 1] + input.substr(lastPos + 1);

    inputFirstConsonant = input.substr(0, firstPos);
    inputVowel = input.substr(firstPos, lastPos - firstPos);
    inputLastConsonant = input.substr(lastPos);

    if (isLastConsonant(inputLastConsonant)) {
      validFirstConsonant.clear();
      validVowel.clear();
      validFirstConsonant = genNearlyFirstConsonant(inputFirstConsonant);
      validVowel = genNearlyVowel(inputVowel);

      // Ghep cac thanh phan
      int len1 = validFirstConsonant.size();
      int len2 = validVowel.size();

      for(int i = 0; i < len1; i++) {
        for(int j = 0; j < len2; j++) {
          if(checkValidNearlyWord(validFirstConsonant[i], validVowel[j], inputLastConsonant)) {
            string str = validFirstConsonant[i] + validVowel[j] + inputLastConsonant;
            // nearlySet.push_back(str);
            nearlySet.insert(str);
          }
        }
      }
    }
  }

  // swap both position
  if (lastPos < n - 1 && firstPos > 0 && firstPos < lastPos - 1) {
    inputNew = input.substr(0, firstPos - 1) + input[firstPos] + input[firstPos - 1] + input.substr(firstPos + 1, lastPos - 1) + input[lastPos] + input[lastPos - 1] + input.substr(lastPos + 1);

    inputFirstConsonant = input.substr(0, firstPos);
    inputVowel = input.substr(firstPos, lastPos - firstPos);
    inputLastConsonant = input.substr(lastPos);

    if (isLastConsonant(inputLastConsonant) && isFirstConsonant(inputFirstConsonant)) {
      validVowel.clear();
      validVowel = genNearlyVowel(inputVowel);

      // Ghep cac thanh phan
      int len1 = validVowel.size();
      for(int i = 0; i < len1; i++) {
        if(checkValidNearlyWord(inputFirstConsonant, validVowel[i], inputLastConsonant)) {
          string str = inputFirstConsonant + validVowel[i] + inputLastConsonant;
          // nearlySet.push_back(str);
          nearlySet.insert(str);
        }
      }
    }
  }
}

int main(){
  #ifdef __DEBUG__
  clock_t start = clock();
  #endif

  ios::sync_with_stdio(false);
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);

  cin>>input;
  int n = input.length();

  int firstConsonantPosition = 0;
  for(int i = 0; i < min(n, 4); i++) {
    firstConsonantPosition = i + 1;
    if (isVowelChar(input[i])) break;
  }
  
  int lastConsonantPosition = n;
  for(int i = n - 1; i >= max(0, n - 3); i--) {
    lastConsonantPosition = i;
    if (isVowelChar(input[i])) {
      break;
    }
  }

  for(int i = 0; i <= firstConsonantPosition; i++) {
    for(int j = max(i + 1, lastConsonantPosition); j <= n; j++) {
      nearlyGenerator(i, j);
    }
  }

  #ifdef __DEBUG__
  int m = nearlySet.size();
  for(set<string>::iterator it=nearlySet.begin(); it!=nearlySet.end(); ++it) {
    cout<<*it<<" \n";
  }
  // for(int i = 0; i < m;i++) {
  //   cout<<nearlySet[i]<<" \n";
  // }
  #endif

  #ifdef __DEBUG__
  cout<<((double)(clock() - start)/CLOCKS_PER_SEC);
  #endif
  return 0;
}