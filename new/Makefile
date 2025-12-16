CXX = g++
CXXFLAGS = -std=c++20 -fsanitize=address
LDFLAGS = -fsanitize=address
TARGET = new
SRCS = ./Server/Data.cpp \
       ./Server/Emulator.cpp \
       ./Server/Agent.cpp \
       ./Server/System.cpp \
       ./Simulator.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
