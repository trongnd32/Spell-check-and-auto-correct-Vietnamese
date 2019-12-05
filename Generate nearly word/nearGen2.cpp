#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <ctime>
#include <iostream>
#include <algorithm>

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
const string vowel[75] = { "a", "aw", "aa", "e", "ee", "i", "o", "oo", "ow", "u", "w", "uw", "y", "ai", "ao", "au", "ay", "aau", "aua", "aay", "aya", "eo", "eeu",
					"eue", "ia", "iu", "iee", "oa", "oaw", "oe", "oi", "ooo", "oio", "ooi", "oiw", "owi", "ua", "uaa", "ui", "uee", "uoo", "uow", "uy", "uwa", "wa",
					"uaw", "uiw", "uwi", "wi", "uwow", "uow", "wow", "wu", "uwu", "uuw", "yee", "oai", "oay", "uaay", "uaya", "uooi", "uoio", "ieeu", "ieue",
					"uyee", "uouw", "uowu", "uwowu", "uoiw", "uowi", "uwowi", "uya", "yeeu", "yeue", "uyu" };
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

map <string, string> standardVowel = {
  {"a", "a"},
  {"aw", "aw"},
  {"aa", "aa"},
  {"e", "e"},
  {"ee", "ee"},
  {"i", "i"},
  {"o", "o"},
  {"oo", "oo"},
  {"ow", "ow"},
  {"u", "u"},
  {"uw", "uw"}, {"w", "uw"},
  {"y", "y"},
  {"ai", "ai"},
  {"ao", "ao"},
  {"au", "au"},
  {"ay", "ay"},
  {"aau", "aau"}, {"aua", "aau"},
  {"aay", "aay"}, {"aya", "aay"},
  {"eo", "eo"},
  {"eeu", "eeu"}, {"eue", "eeu"},
  {"ia", "ia"},
  {"iu", "iu"},
  {"iee", "iee"},
  {"oa", "oa"},
  {"oaw", "oaw"},
  {"oe", "oe"},
  {"oi", "oi"},
  {"ooo", "ooo"},
  {"ooi", "ooi"}, {"oio", "ooi"},
  {"owi", "owi"}, {"oiw", "owi"},
  {"ua", "ua"},
  {"uaa", "uaa"},
  {"ui", "ui"},
  {"uee", "uee"},
  {"uoo", "uoo"},
  {"uow", "uow"},
  {"uy", "uy"},
  {"uwa", "uwa"}, {"wa", "uwa"}, {"uaw", "uwa"},
  {"uwi", "uwi"}, {"uiw", "uwi"}, {"wi", "uwi"},
  {"uwow", "uwow"}, {"wow", "uwow"},
  {"uwu", "uwu"}, {"wu", "uwu"}, {"uuw", "uwu"},
  {"yee", "yee"},
  {"oai", "oai"},
  {"oay", "oay"},
  {"uaay", "uaay"}, {"uaya", "uaay"},
  {"uooi", "uooi"}, {"uoio", "uooi"},
  {"ieeu", "ieeu"}, {"ieue", "ieeu"},
  {"uyee", "uyeen"},
  {"uwowu", "uwowu"}, {"uouw", "uwowu"}, {"uowu", "uwowu"}, 
  {"uwowi", "uwowi"}, {"uoiw", "uwowi"}, {"uowi", "uwowi"}, 
  {"uya", "uya"},
  {"yeeu", "yeeu"}, {"yeue", "yeeu"},
  {"uyu", "uyu"}
};

map <string, int> mapOfFirstConsonant = {
	{"b", 1},
	{"c", 2},
	{"d", 3},
	{"dd", 4},
	{"g", 5},
	{"h", 6},
	{"k", 7},
	{"l", 8},
	{"m", 9},
	{"n", 10},
	{"q", 11},
	{"r", 12},
	{"s", 13},
	{"t", 14},
	{"v", 15},
	{"x", 16},
	{"ch", 17},
	{"gh", 18},
	{"gi", 19},
	{"kh", 20},
	{"ng", 21},
	{"nh", 22},
	{"ph", 23},
	{"qu", 24},
	{"th", 25},
	{"tr", 26},
	{"ngh", 27},
	{"", 28}
};

map <string, int> mapOfVowel = {
  {"a", 1},
  {"aw", 2},
  {"aa", 3},
  {"e", 4},
  {"ee", 5},
  {"i", 6},
  {"o", 7},
  {"oo", 8},
  {"ow", 9},
  {"u", 10},
  {"uw", 11},
  {"y", 12},
  {"ai", 13},
  {"ao", 14},
  {"au", 15},
  {"ay", 16},
  {"aau", 17},
  {"aay", 18},
  {"eo", 19},
  {"eeu", 20},
  {"ia", 21},
  {"iu", 22},
  {"iee", 23},
  {"oa", 24},
  {"oaw", 25},
  {"oe", 26},
  {"oi", 27},
  {"ooo", 28},
  {"ooi", 29},
  {"owi", 30},
  {"ua", 31},
  {"uaa", 32},
  {"ui", 33},
  {"uee", 34},
  {"uoo", 35},
  {"uow", 36},
  {"uy", 37},
  {"uwa", 38},
  {"uwi", 39},
  {"uwow", 40},
  {"uwu", 41},
  {"yee", 42},
  {"oai", 43},
  {"oay", 44},
  {"uaay", 45},
  {"uooi", 46},
  {"ieeu", 47},
  {"uyee", 48},
  {"uwowu", 49},
  {"uwowi", 50},
  {"uya", 51},
  {"yeeu", 52},
  {"uyu", 53}
};

map <string, int> mapOfLastConsonant = {
  {"c", 1},
  {"p", 2},
  {"t", 3},
  {"m", 4},
  {"n", 5},
  {"ch", 6},
  {"ng", 7},
  {"nh", 8},
  {"", 9}
};

map <string, int> mapOfTone = {
  {"s", 1},
  {"f", 2},
  {"r", 3},
  {"x", 4},
  {"j", 5},
  {"", 6}
};

int combineVowelLastConsonant[54][10] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {0, 1, 1, 1, 1, 1, 0, 1, 0, 0},
  {0, 1, 1, 1, 1, 1, 0, 1, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
  {0, 1, 1, 1, 1, 1, 1, 0, 1, 1},
  {0, 0, 1, 1, 1, 1, 1, 0, 1, 1},
  {0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
  {0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
  {0, 1, 1, 1, 1, 1, 0, 0, 0, 1},
  {0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
  {0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 1, 1, 1, 1, 1, 0, 1, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {0, 1, 1, 1, 1, 1, 0, 1, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 1, 0, 1, 1, 1, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 1, 1, 1, 0, 0, 1, 1},
  {0, 0, 0, 1, 1, 1, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 1, 1, 0, 0, 1, 0, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 1, 1, 1, 1, 1, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
};

int combineToneLastConsonant[7][10] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 1, 1, 0, 1, 1, 1},
  {0, 0, 0, 0, 1, 1, 0, 1, 1, 1},
  {0, 0, 0, 0, 1, 1, 0, 1, 1, 1},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 1, 1, 0, 1, 1, 1}
};

int combineFirstConsonantVowel[29][54] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1}
};

int ED[15][15];

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

    if (edvowel <= MAXEDVOWEL) res.push_back(standardVowel[vowel[i]]);
    if (edvowel <= MAXEDVOWEL + 1) {
      vector < pair <int, char> > deletedChar = findDeleteChars(inputVowel, vowel[i]);
      int m = deletedChar.size();

      for(int k = 0; k < m; k++) {
        if (isTone(deletedChar[k].second) && deletedChar[k].first != 0) {
          string str = standardVowel[vowel[i]] + deletedChar[k].second;
          res.push_back(str);
        } else {
          if(edvowel <= MAXEDVOWEL) {
            int repToneSize = toneNearBy[deletedChar[k].second - 'a'].size();
            for (int o = 0; o < repToneSize; o++) {
              string str = standardVowel[vowel[i]] + toneNearBy[deletedChar[k].second - 'a'][o];
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
  char lastCharInVowel = '0';
	if (gvowel.length() > 0) lastCharInVowel = *(--gvowel.end());
	char lastCharInLastConsonant = '0';
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

string wordNormalize(string gfConsonant, string gvowel, string glConsonant){
  string res = "";

  if(gvowel.length() > 0) {
    char tone = *(--gvowel.end());
    if(isTone(tone) == true) {
      gvowel.pop_back();
      glConsonant += tone;
    }
  }
  res = gfConsonant + gvowel + glConsonant;
  return res;
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
          nearlySet.insert(wordNormalize(validFirstConsonant[i], validVowel[j], validLastConsonant[k]));
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
            nearlySet.insert(wordNormalize(inputFirstConsonant, validVowel[i], validLastConsonant[j]));
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
            nearlySet.insert(wordNormalize(validFirstConsonant[i], validVowel[j], inputLastConsonant));
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
          nearlySet.insert(wordNormalize(inputFirstConsonant, validVowel[i], inputLastConsonant));
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