#include "System.hpp"
#include "Emulator.hpp"

typedef int Mint;

void RaiseError(Errors error) {
  std::cout << warnings[error];
}

Corrector::Corrector() {
  converter["run"]  = "r";
  converter["add"]  = "a";
  converter["aadd"] = "aa";
  converter["del"]  = "d";
  converter["send"] = "s";
  converter["exit"] = "e";
}

std::queue<Data> fictive;

void Corrector::IsCorrectType(std::string& command) {
  if (converter.find(command) == converter.end()) {
    bool find_flag = false;
    for (const auto& elem : list_of_commands) {
      if (elem == command) {
        find_flag = true;
      }
    }
    if (!find_flag) {
      command = "error";
      return;
    }
  } else {
    command = converter[command];
  }
}

void Session::StartSession() {
  root.next     = &root;
  root.previous = &root;
  id[0]         = &root;
  std::string type;
  Corrector checker;
  while (true) {
    std::cout << "> ";
    std::cin >> type;
    checker.IsCorrectType(type);
    if (type == "error") {
      RaiseError(Errors::UnknownCommand);
      std::string line;
      std::getline(std::cin, line);
      continue;
    }
    if (type == "a") {
      short int n;
      std::cin >> n;
      CreateAgent(n, TypesAgents::Simple);
    } else if (type == "aa") {
      short int n;
      std::cin >> n;
      CreateAgent(n, TypesAgents::Auto);
    } else if (type == "r") {
      Run();
      std::cout << fictive;
    } else if (type == "s") {
      short int from, to;
      std::string command;
      std::string line;
      std::getline(std::cin, line);
      std::istringstream iss(line);
      iss >> from >> to;
      std::getline(iss, command);
      if (!command.empty() && command[0] == ' ')
        command.erase(0, 1);
      if (id.find(from) == id.end()) {
        RaiseError(Errors::UnknownAgent);
        continue;
      }
      if (from == to) {
        RaiseError(Errors::SelfMessage);
        continue;
      }
      id[from]->AddMesage(command, to);
    } else if (type == "d") {
      Run();
      short int number;
      std::cin >> number;
      DeleteAgent(number);
    } else if (type == "e") {
      break;
    }
  }
  std::cout << "\nGoodbye!\n";
}

void Session::HelpCicle(Agent* agent, Data data) {
  if (data.data_type == DataType::kToken) {
    if (data.to == agent->GetId()) {
      if (!agent->submits.empty()) {
        SendMessageFrom(agent);
      }
      SendTokenFrom(agent);
    }
    return;
  }

  while (agent->next->SendGet(data) != Log::MessageFromMe) {
    agent = agent->next;
  }
}

Log Session::SendMessageFrom(Agent* agent) {
  HelpCicle(agent, agent->GetMessage());
  return Log::SuccesfulSendMessage;
}

Log Session::SendTokenFrom(Agent* agent) {
  if (agent->next->GetId() == 0) {
    return Log::FullCicle;
  }
  HelpCicle(agent->next, Token(agent->GetId(), agent->next->GetId()));
  return Log::SuccesdulSendToken;
}

Log Session::SendFrom(Agent* agent) {
  if (agent->submits.empty()) {
    SendTokenFrom(agent);
    return Log::SuccesdulSendToken;
  } else {
    SendMessageFrom(agent);
    SendTokenFrom(agent);
    return Log::SuccesfulSendMessage;
  }
}

void Session::Run() {
  bool final = false;

  while (!final) {
    final = true;

    while (root.next->Checker()) {
      SendFrom(&root);
      final = false;
    }

    while (!root.submits.empty()) {
      SendMessageFrom(&root);
      final = false;
    }
  }
}

void Session::CreateAgent(short int number, TypesAgents type) {
  if (id.find(number) != id.end()) {
    RaiseError(Errors::ExistAgent);
  }
  root.CreateAgent(number, type);
  id[number] = root.next;
}

void Session::DeleteAgent(short int number) {
  if (id.find(number) == id.end()) {
    RaiseError(Errors::UnknownAgent);
  } else if (number == 0) {
    RaiseError(Errors::DeleteMainAgent);
  } else {
    id[number]->Delete();
    id.erase(number);
  }
}

Session::~Session() {
  for (const auto& [key, agent_ptr] : id) {
    if (key != 0) {
      delete agent_ptr;
    }
  }
}
