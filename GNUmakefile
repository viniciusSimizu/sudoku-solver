SRCDIR=./src
INCDIR=./include
BINDIR=./bin
OBJDIR=$(BINDIR)/objs

SOURCE_FILES=$(shell find $(SRCDIR) -name '*.cpp' -type f)
OBJECT_FILES=$(SOURCE_FILES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CXX=g++
CPPFLAGS=-I$(INCDIR)

ENTRY=main

.PHONY: $(OBJDIR) test build_test

all: $(BINDIR)/$(ENTRY)

$(BINDIR)/$(ENTRY): $(OBJECT_FILES)
	$(CXX) -o $@ $(CPPFLAGS) $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(OBJDIR)
	$(CXX) -c -o $@ $(CPPFLAGS) $<

$(SRCDIR)/%.cpp: $(INCDIR)/%.hpp

$(OBJDIR):
	mkdir -p $@

TESTDIR=./test
TEST_BINDIR=$(BINDIR)/$(TESTDIR)
TEST_FILES=$(wildcard $(TESTDIR)/*_test.cpp)
TEST_OBJS=$(TEST_FILES:$(TESTDIR)/%.cpp=$(TEST_BINDIR)/%.o)
TEST_FLAGS=-I$(TESTDIR) $(CPPFLAGS)

test:
	@mkdir -p $(TEST_BINDIR)
	$(MAKE) build_test

build_test: $(TEST_OBJS)

$(TEST_BINDIR)/%.o: $(TESTDIR)/%.cpp $(SOURCE_FILES)
	$(CXX) -o $@ $(TEST_FLAGS) $^

clean:
	@rm -rf $(BINDIR)
