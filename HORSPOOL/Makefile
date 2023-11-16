# Define the compiler to use
CXX = g++
CXXFLAGS = -Wall -g

# Define the target executable
TARGET = horspool

# Define the source files
SRCS = horspool.cpp horspool_main.cpp

# Define the object files from the source files
OBJS = $(SRCS:.cpp=.o)

# The first rule is the one executed when no parameters are fed into the Makefile
all: $(TARGET)

# Define the rule to link the target with object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Define the rule to compile source files into object files
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Define the rule to clean the project
clean:
	rm -f $(OBJS) $(TARGET)
