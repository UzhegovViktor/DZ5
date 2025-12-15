#pragma once

#include "System.hpp"
#include "Agent.hpp"

class Corrector {
public:
  Corrector();
  void IsCorrectType(std::string& command);

private:
  std::map<std::string, std::string> converter;
  std::vector<std::string> list_of_commands{
    "r", "a", "aa", "d", "s", "e"
  };
};

class Session {
public:
  Session() = default;
  ~Session();

  void StartSession();

private:
  MainAgent root;
  std::map<short int, Agent*> id;
  std::queue<std::string> history;

  void Run();

  void HelpCicle(Agent* agent, Data data);
  void Terminate();

  Log SendMessageFrom(Agent* agent);
  Log SendTokenFrom(Agent* agent);
  Log SendFrom(Agent* agent);

  void CreateAgent(short int number, TypesAgents type);
  void DeleteAgent(short int number);

};
