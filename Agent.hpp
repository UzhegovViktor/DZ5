#pragma once
#include "Data.hpp"
#include "System.hpp"
#include "Agent.hpp"

class Agent {
public:
    Agent(TypesAgents, short int);
    virtual ~Agent() {}
    short int GetId() const { return self_id; }
    TypesAgents GetType() const { return SelfType; }
    void AddMesage(const std::string&, short int);
    virtual Log SendGet(Data);
    Data GetMessage();
    bool Checker();
    void Delete();

    friend class Session;
    friend class MainAgent;

protected:
    std::queue<std::queue<Data>> submits;
    std::unordered_map<short int, std::queue<Data>> get;
    Agent* next;
    Agent* previous;
    short int self_id;
    TypesAgents SelfType;
};

class SimpleAgent : public Agent {
public:
    SimpleAgent(short int);
    using Agent::AddMesage;
    using Agent::SendGet;
    using Agent::GetMessage;
    using Agent::Checker;
    using Agent::Delete;

    friend class Session;
};

class AutoAgent : public Agent {
public:
    AutoAgent(short int);
    Log SendGet(Data);
    using Agent::AddMesage;
    using Agent::GetMessage;
    using Agent::Checker;
    using Agent::Delete;

    friend class Session;

};

class MainAgent : public Agent {
public:
    MainAgent();
    void CreateAgent(short int, TypesAgents);
    using Agent::AddMesage;
    using Agent::SendGet;
    using Agent::GetMessage;
    using Agent::Checker;

    friend class Session;

};