#pragma once
#include "System.hpp"

class Data {
public:
  const DataType data_type;
  char message[24];
  short int from = -1;
  short int to = -1;
  friend std::ostream& operator<<(std::ostream& os, Data& get);
  friend std::ostream& operator<<(std::ostream& os, std::queue<Data> msg);
protected:
  explicit Data(DataType dt, short int from, short int to);
};

class Token : public Data {
public:
  Token(short int from, short int to);
};

class Message : public Data {
public:
  Message(short int from, short int to, const char* message, size_t size, bool flag);
};