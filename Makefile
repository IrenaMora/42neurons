NAME = 42neurons.a

CPPFILES = */*.cpp

HPPFILES = */*.hpp

OBJFILES = *.o

all: $(NAME)

$(NAME): $(CPPFILES) $(HPPFILES)
	@printf "Compiling object files... "
	@clang++ -c $(CPPFILES) -Ibase -Iconnection -Iexceptions -Iinterfaces -Inetwork -Ineurons -std=c++11 -O1
	@printf "Done!\n"
	@printf "Creating library... "
	@ar rcs $(NAME) $(OBJFILES)
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
