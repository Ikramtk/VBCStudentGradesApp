# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -O2

# Output executable
TARGET = app

# Source files
SRCS = main.cpp Student.cpp FileIO.cpp FileGenerator.cpp ExceptionHelper.cpp
# Header-only files (Timer.h does NOT need to be compiled)
HDRS = Student.h FileIO.h FileGenerator.h ExceptionHelper.h Timer.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)