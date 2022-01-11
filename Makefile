NAME = 42neurons

CPPFILES = main.cpp */*.cpp

HPPFILES = */*.hpp

OBJFILES = *.o

all: $(NAME)

$(NAME): $(CPPFILES) $(HPPFILES)
	@clang++ -c $(CPPFILES) -Ibase -Iconnection -Iexceptions -Iinterfaces -Inetwork -Ineurons -std=c++11 -O1
	@clang++ $(OBJFILES) -o $(NAME) -std=c++11 -O1

clean:
	@rm -rf $(OBJFILES)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

run:
	@./$(NAME)

test: all
	@./$(NAME) && $(MAKE) clean
