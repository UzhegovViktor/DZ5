#include "Agent.hpp"
#include "Data.hpp"
#include "System.hpp"

Agent::Agent(TypesAgents type, short int id) : self_id(id), SelfType(type) {}

void Agent::AddMesage(const std::string& message, short int to) {
	submits.push({});
	short int size = static_cast<short int>(message.size());
	short int temp_size = 0;
	for (short int i = 0; i < size; i += 22) {
		temp_size = std::min(22, size - i);
		char* temp = new char[temp_size];
		for (short int j = 0; j < temp_size; j++) {
			temp[j] = message[i + j];
		}
		bool flag = true;
		if (i + 22 >= size) { flag = false; };
		submits.front().push(Message(self_id, to, temp, temp_size, flag));
	};
};

void Agent::Delete() {
	Agent* prev = previous;
	Agent* nex = next;
	nex->previous = prev;
	prev->next = nex;
	delete this;
}

Log Agent::SendGet(Data data) {
	if (data.data_type == DataType::kMessage) {
		if (data.from == self_id) {
			return Log::MessageFromMe;
		} else if (data.to == self_id || data.to == -1) {
			data.to = self_id;
			if (data.message[0] == '1') {
				get[data.from].push(data);
			} else {
				get[data.from].push(data);
				std::cout << get[data.from];
				if (SelfType == TypesAgents::Auto) {
					submits.push({});
				}
				while (get[data.from].size() != 0) {
					get[data.from].pop();
					continue;
				};
			}
			return Log::MessageToMe;
		} else {
			return Log::NotFromNotTo;
		}
	} else {
		return Log::GetToken;
	}
}

bool Agent::Checker() {
	if (self_id == 0) {
		return false;
	}
	if (submits.size() > 0) {
		return true;
	} else {
		return next->Checker();
	}
}

Data Agent::GetMessage() {
	Data temp = submits.front().front();
	submits.front().pop();
	if (submits.front().size() == 0) {
		submits.pop();
	}
	return temp;
}

SimpleAgent::SimpleAgent(short int id) : Agent(TypesAgents::Simple, id) {}

AutoAgent::AutoAgent(short int id) : Agent(TypesAgents::Auto, id) {}

Log AutoAgent::SendGet(Data data) {
	if (data.data_type == DataType::kMessage) {
		if (data.from == self_id) {
			return Log::MessageFromMe;
		}
		if (data.to == self_id || data.to == -1) {
			data.to = self_id;
			if (data.message[0] == '1') {
				get[data.from].push(data);
			} else {
				get[data.from].push(data);
				std::cout << get[data.from];
				std::string full_message(get[data.from].size() * 22 + 1, '#');
				int full_numeric = 0;
				while (get[data.from].size() > 0) {
					Data part_of = get[data.from].front();
					for (int i = 1; i < 24; ++i) {
						if (part_of.message[i] == '\0') {
							break;
						} else {
							full_message[full_numeric] = part_of.message[i];
							full_numeric++;
						}
					}
					get[data.from].pop();
				}
				std::string reverse_string(full_numeric, '#');
				int reverse_numeric = 0;
				int from = full_message.rfind(' ', full_numeric);
				from = (from == -1) ? 0 : from;
				int to = full_numeric;
				while (from != -1) {
					from = from == 0 ? -1 : from;
					for (int i = from + 1; i < to; ++i) {
						reverse_string[reverse_numeric] = full_message[i];
						reverse_numeric++;
					}
					if (from != -1) {
						reverse_string[reverse_numeric] = ' ';
						reverse_numeric++;
						to = from;
						from = full_message.rfind(' ', from - 1);
						if (from == -1) {
							from = (to == -1) ? from : 0;
						}
					} else {
						from = -1;
					}
				}
				AddMesage(reverse_string, data.from);
			}
			return Log::MessageToMe;
		} else {
			return Log::NotFromNotTo;
		}
	}
	return Log::GetToken;
}

MainAgent::MainAgent() : Agent(TypesAgents::Main, 0) {}

void MainAgent::CreateAgent(short int number, TypesAgents type) {
	Agent* new_agent;
	if (type == TypesAgents::Simple) new_agent = new SimpleAgent(number);
	else new_agent = new AutoAgent(number);
	Agent* temp = next;
	next = new_agent;
	new_agent->previous = this;
	new_agent->next = temp;
	temp->previous = new_agent;
}