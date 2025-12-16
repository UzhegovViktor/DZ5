#pragma once

#include <vector>
#include <map>
#include <string>
#include <queue>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <stack>
#include <algorithm>

extern std::ostringstream buffer;

extern short int size_of_message;

enum class Log {
    MessageFromMe,
    MessageToMe,
    NotFromNotTo,
    GetToken,
    HaventMessage,
    SuccesfulSendMessage,
    SuccesdulSendToken,
    FullCicle,
    ExistAgent,
    SuccesfullCreateAgent
};

enum class Errors {
    UnknownCommand,
    ExistAgent,
    UnknownAgent,
    DeleteMainAgent,
    SelfMessage,
    FromAuto
};

extern std::map<Errors, std::string> warnings;

enum class TypesAgents {
	Simple,
	Auto,
	Main
};

enum class DataType {
  kToken,
  kMessage
};