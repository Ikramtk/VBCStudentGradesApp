CXX = g++
CXXFLAGS = -std=c++17 -O2

SRC = main.cpp Student.cpp FileIO.cpp FileGenerator.cpp Timer.cpp ExceptionHelper.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = StudentGradesApp

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

clean:
	rm -f $(OBJ) $(TARGET)