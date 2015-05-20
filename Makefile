CXX := g++
CXXFLAGS := -g

OBJ := jaycommand.o jaylexer.o jayparse.o jaytools.o main.o

jayrun: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(OBJ) jayrun
