CXX = g++
CXXFLAGS = -std=c++20
TARGET = new
SRCS = ./Server/Data.cpp \
       ./Server/Emulator.cpp \
       ./Server/Agent.cpp \
	   ./Server/System.cpp \
       ./Simulator.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
