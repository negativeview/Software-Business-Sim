cssim: linenoise.c linenoise.h main.cpp Project.cpp EmployeesCommand.cpp InterviewCommand.cpp HireCommand.cpp ProjectCommand.cpp WaitCommand.cpp StatusCommand.cpp PeopleCommand.cpp QuitCommand.cpp HelpCommand.cpp CommandFunctor.cpp Language.cpp Company.cpp Person.cpp MasterState.cpp Trait.cpp AmbitionTrait.cpp GreedTrait.cpp InitiativeTrait.cpp CreativityTrait.cpp Platform.cpp
	g++ -g linenoise.c main.cpp Language.cpp Project.cpp HireCommand.cpp EmployeesCommand.cpp InterviewCommand.cpp ProjectCommand.cpp WaitCommand.cpp StatusCommand.cpp PeopleCommand.cpp QuitCommand.cpp HelpCommand.cpp CommandFunctor.cpp Company.cpp Person.cpp MasterState.cpp AmbitionTrait.cpp Trait.cpp GreedTrait.cpp InitiativeTrait.cpp CreativityTrait.cpp Platform.cpp -o cssim -lform -lmenu -lncurses
