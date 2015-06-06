CXX := g++
CXXFLAGS := -g -Wall

OBJ := jaycommand.o jaylexer.o operators.o jayparse.o jaytools.o main.o

jayrun: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@
	cp jayrun prebuilts/

clean:
	rm -f $(OBJ) jayrun
