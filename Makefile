NAME = 42neurons

CPPFILES = *.cpp

HPPFILES = *.hpp

OBJFILES = *.o

all: $(NAME)

$(NAME): $(CPPFILES) $(HPPFILES)
	@clang++ -c $(CPPFILES) -I. -std=c++98
	@clang++ $(OBJFILES) -o $(NAME) -std=c++98

clean:
	@rm -rf $(OBJFILES)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

run:
	@./$(NAME)

test: all
	@./$(NAME)
