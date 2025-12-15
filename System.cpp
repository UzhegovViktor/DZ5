#include "System.hpp"
#include "Data.hpp"

std::map<Errors, std::string> warnings = {
    {Errors::ExistAgent, "# This agent is exist\n"},
    {Errors::UnknownCommand, "# Unknown command, sorry...\n"},
    {Errors::UnknownAgent, "# This agent is doesn't exist\n"},
    {Errors::DeleteMainAgent, "# You can't delete MainAgent\n"},
    {Errors::SelfMessage, "# You can't send message for self\n"},
};

short int size_of_message = 22;