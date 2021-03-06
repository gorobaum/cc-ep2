PROG_NAME = ep2
FLAGS = -lpthread

SRC_DIR = src
OBJ_DIR = .temp

CXX = g++
CXXFLAGS = -ansi -Wall -O0 $(FLAGS)

OUTPUT = $(PROG_NAME)

include objs.makefile

$(PROG_NAME): $(OBJ_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(OUTPUT)

$(OBJ_DIR):
	mkdir $@

.temp/%.o: src/%.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@

.temp/%.o: src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

.temp/%.o: src/%.cxx
	$(CXX) -c $(CXXFLAGS) $< -o $@

include deps.makefile

.PHONY: debug
debug: CXXFLAGS += -g
debug: $(PROG_NAME)

.PHONY: clean
clean:
	rm -rf $(OUTPUT)
	rm -rf $(OBJ_DIR)


