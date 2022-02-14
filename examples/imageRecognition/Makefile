NAME = imageRecognition

CPPFILES = main.cpp

OBJFILES = main.o

all: $(NAME)

$(NAME): $(CPPFILES) $(HPPFILES)
	@clang++ -c $(CPPFILES) -std=c++11 -O1 `Magick++-config --cppflags --cxxflags --ldflags --libs`
	@clang++ $(OBJFILES) -l42neurons  -o $(NAME) `Magick++-config --cppflags --cxxflags --ldflags --libs`
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
