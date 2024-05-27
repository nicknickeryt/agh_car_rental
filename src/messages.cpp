#include <string>
#include <iostream>

#include "messages.h"

using std::string, std::cout, std::endl;

string Messages::getMessage(const Message message) { return translateableMessages.at(message); }

void Messages::sendMessage(const Message message) { cout << translateableMessages.at(message) << endl; }