#pragma once

#include "System.hpp"
#include "Agent.hpp"

class Session {
public:
  Session();
  ~Session();

  void StartSession();

  friend class Corrector;

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

class Corrector {
public:
  Corrector(Session& session);
  bool IsCorrectType(std::string& command);
  bool LoadAdress(short int from, short int to);

private:
  std::map<std::string, std::string> converter;
  std::vector<std::string> list_of_commands{
    "r", "a", "aa", "d", "s", "e"
  };
  Session& session_;
};
