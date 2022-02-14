NAME = imageRecognition

CPPFILES = main.cpp

OBJFILES = main.o
LIB_INCLUDES = -L$(PWD)/../..
all: $(NAME)

$(NAME): $(CPPFILES) $(HPPFILES)
	@clang++ -c $(CPPFILES) -std=c++11 -O1 `Magick++-config --cppflags --cxxflags --ldflags --libs`
	@clang++ $(OBJFILES) $(LIB_INCLUDES) -l42neurons  -o $(NAME) `Magick++-config --cppflags --cxxflags --ldflags --libs`
	unzip images.zip
	@printf "Done!\n"

clean:
	@printf "Removing files... "
	@rm -rf $(OBJFILES)
	@printf "Done!\n"

fclean: clean
	rm -rf images
	rm -rf __MACOSX
	@rm -rf $(NAME)

re: fclean all

run:
	@./$(NAME)
