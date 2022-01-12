NAME = simpleNetwork

CPPFILES = main.cpp

OBJFILES = main.o

all: $(NAME)

$(NAME): $(CPPFILES) $(HPPFILES)
	@printf "Compiling 42neurons library\n"
	@$(MAKE) -C ../../
	@clang++ -c $(CPPFILES) -std=c++11 -O1
	@clang++ $(OBJFILES) ../../42neurons.a -o $(NAME)
	@printf "Done!\n"

clean:
	@printf "Removing files... "
	@rm -rf $(OBJFILES)
	@printf "Done!\n"

fclean: clean
	@rm -rf $(NAME)

re: fclean all

run:
	@./$(NAME)
