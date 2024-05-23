#include <string>
#include <map>

using std::string, std::map;

class Utils
{
public:
    static int promptSel();
    static int promptSel(map<int, string> promptMap);

    static string promptInput();
    static string promptInput(string promptText);

    static void printErr(string errText);
};