cssim: main.cpp Market.cpp NamedObject.cpp NameContainer.cpp CommandList.cpp Project.cpp EmployeesCommand.cpp InterviewCommand.cpp HireCommand.cpp ProjectCommand.cpp WaitCommand.cpp StatusCommand.cpp PeopleCommand.cpp QuitCommand.cpp CommandFunctor.cpp Language.cpp Company.cpp Person.cpp MasterState.cpp Trait.cpp Platform.cpp
	g++ -g main.cpp Market.cpp NamedObject.cpp NameContainer.cpp CommandList.cpp Language.cpp Project.cpp HireCommand.cpp EmployeesCommand.cpp InterviewCommand.cpp ProjectCommand.cpp WaitCommand.cpp StatusCommand.cpp PeopleCommand.cpp QuitCommand.cpp CommandFunctor.cpp Company.cpp Person.cpp MasterState.cpp Trait.cpp Platform.cpp -o cssim -lform -lmenu -lncurses
