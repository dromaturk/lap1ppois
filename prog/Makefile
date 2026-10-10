CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
LDFLAGS  := -lUnitTest++

SET_SRC  := set.cpp smain.cpp
TTT_SRC  := ttt.cpp tmain.cpp

SET_BIN  := set_app
TTT_BIN  := ttt_app

.PHONY: all clean run-set run-ttt

all: $(SET_BIN) $(TTT_BIN)

$(SET_BIN): $(SET_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(TTT_BIN): $(TTT_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

run-set: $(SET_BIN)
	./$(SET_BIN)

run-ttt: $(TTT_BIN)
	./$(TTT_BIN)

clean:
	rm -f $(SET_BIN) $(TTT_BIN)
