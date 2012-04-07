cssim: linenoise.c linenoise.h main.cpp Company.cpp Person.cpp MasterState.cpp Trait.cpp AmbitionTrait.cpp GreedTrait.cpp InitiativeTrait.cpp CreativityTrait.cpp
	g++ -g linenoise.c main.cpp Company.cpp Person.cpp MasterState.cpp AmbitionTrait.cpp Trait.cpp GreedTrait.cpp InitiativeTrait.cpp CreativityTrait.cpp -o cssim
