SRCDIR = src
OBJDIR = obj
BINDIR = bin
BINARY_NAME = evilhangman
OBJECTS = $(shell find . -name "*.cpp" | sed "s/.cpp/.o/" | sed "s/\/$(SRCDIR)\//\/$(OBJDIR)\//")
HEADERS = $(shell find . -name "*.h")

CXX = g++
CPPFLAGS = -std=c++17 -Wall -Wdeprecated -Wextra -pedantic -g
LDFLAGS = -g

.PHONY: all clean

all: $(BINDIR)/$(BINARY_NAME)

clean:
	rm -rf $(BINDIR)
	rm -rf $(OBJDIR)

$(BINDIR)/$(BINARY_NAME): $(OBJECTS) $(BINDIR)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS) $(OBJDIR)
	$(CXX) $(CPPLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

$(BINDIR):
	mkdir $(BINDIR)
