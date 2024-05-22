#include <string>
#include <map>

using std::string, std::map;
int promptSel();
int promptSel(map<int, string> promptMap);
string promptInput();
string promptInput(string promptText);

void printErr(string errText);