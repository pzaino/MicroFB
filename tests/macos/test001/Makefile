
#CXX = /opt/homebrew/bin/g++-13
CXXFLAGS = -std=c++11 -Wall -Wextra
SFML_DIR = /opt/homebrew/Cellar/sfml/2.6.1
CXXFLAGS += -I$(SFML_DIR)/include
LDFLAGS += -L. -L../../../ux-src/ -L$(SFML_DIR)/lib -lsfml-graphics -lsfml-window -lsfml-system -lMicroFB -lstdc++ -lm -framework Cocoa

# Name of your executable
TARGET = SpriteDisplayApp

# Source files
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: all clean
