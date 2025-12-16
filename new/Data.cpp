#include "Data.hpp"
#include "System.hpp"
Data::Data(DataType dt, short int from_t, short int to_t) : data_type(dt), from(from_t), to(to_t) {}

Token::Token(short int from_t, short int to_t) : Data(DataType::kToken, from_t, to_t) {}

Message::Message(short int  from_t, short int to_t,
                 const char* submit, size_t size, bool flag) : 
                 Data(DataType::kMessage, from_t, to_t){
  if (flag) { message[0] = '1'; }
  else {message[0] = '0';}
  for (size_t i = 0; i < size; i++) {
    message[i + 1] = submit[i];
  }
  message[size + 1] = '\0';
}

std::ostream& operator<<(std::ostream& os, std::queue<Data> get) {
  os << "# " << get.front().to << " recv from " << get.front().from << ": ";
  while (get.size() != 0) {
    for (int i = 1; i < 24; ++i) {
        if (get.front().message[i] == '\0') break; 
        os << get.front().message[i];
    }
    get.pop();
  }
  os << '\n';
  return os;
}

std::ostream& operator<<(std::ostream& os, Data& get) {
  os << "# " << get.to << " recv from " << get.from << ": ";
  for (int i = 1; i < 24; ++i) {
      if (get.message[i] == '\0') break; 
      os << get.message[i];
  }
  os << '\n';
  return os;
}