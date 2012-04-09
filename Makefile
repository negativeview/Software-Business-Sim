cssim: linenoise.c linenoise.h main.cpp Language.cpp Company.cpp Person.cpp MasterState.cpp Trait.cpp AmbitionTrait.cpp GreedTrait.cpp InitiativeTrait.cpp CreativityTrait.cpp Platform.cpp
	g++ -g linenoise.c main.cpp Language.cpp Company.cpp Person.cpp MasterState.cpp AmbitionTrait.cpp Trait.cpp GreedTrait.cpp InitiativeTrait.cpp CreativityTrait.cpp Platform.cpp -o cssim
