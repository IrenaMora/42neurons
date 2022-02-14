.PHONY: all clean fclean re
export CXX CPPFLAGS MAKEFLAGS LDFLAGS INCLUDES
MKDIR_P 	:= mkdir -p
SRC_DIR		:= src
OUT_DIR 	:= build
CXX 		:= clang++ -std=c++17 -O1
CPPFLAGS 	:= -c -MMD -Wall -Wextra -Werror -fPIC -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=2 -Wno-unknown-pragmas  # -Wno-unused-result
LDFLAGS 	:= -MMD -Wall -Wextra -Werror # -Wno-unused-result
DFLAGS 		:= '-O0 -g3'
ASFLAGS 	:= -fsanitize=address
SHELL = /bin/zsh

ifeq ($(CXX), g++)
	HFLAGS		= '-pedantic -Wshadow -Wformat=2 -Wfloat-equal\
	-Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align\
	-D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2\
	-fsanitize=undefined -fno-sanitize-recover -fstack-protector\
	-Wno-pointer-arith -Wno-cast-qual -Wimplicit-fallthrough -Wno-shadow'
else
	HFLAGS		= '-pedantic -Wshadow -Wformat=2 -Wfloat-equal\
	-Wshift-overflow -Wcast-qual -Wcast-align\
	-D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2\
	-fsanitize=undefined -fno-sanitize-recover=all -fstack-protector\
	-Wno-pointer-arith -Wno-cast-qual -Wimplicit-fallthrough -Wno-shadow'
endif
MAKEFLAGS	= --no-print-directory
OBJ 		:= NeuronConnection.o\
               NeuronDeep.o\
               NeuronException.o\
               NeuronFunctions.o\
               NeuronIn.o\
               NeuronNetwork.o\
               NeuronOut.o\
               NeuronSimple.o

OBJ 		:= $(addprefix $(OUT_DIR)/,$(OBJ))
D_FILES 	= $(OBJ:.o=.d)
NAME 		= lib42neurons
INCLUDES 	= -I$(PWD)/include -I$(PWD)/src
UNAME 		= $(shell uname)

ifeq ($(UNAME), Linux)
	CFLAGS += -D LINUX=1
endif

all: directories $(NAME).so
ifeq ($(UNAME), Linux)
	sudo cp $(NAME).so /lib/x86_64-linux-gnu/$(NAME).so
endif
	$(shell echo 'export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$$PWD' >> ~/.zshrc)
	. ~/.zshrc

directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}
$(NAME).so: $(OBJ)
	$(CXX) $(LDFLAGS) $(OBJ) $(INCLUDES) -shared -o $(NAME).so
$(OUT_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) -c $(INCLUDES) $< -o $@
static:
	ar rcs $(OBJ) $(NAME).a
debug :
	@make CPPFLAGS+=$(DFLAGS) LDFLAGS+=$(DFLAGS)
debugas :
	@make debug CPPFLAGS+=$(ASFLAGS) LDFLAGS+=$(ASFLAGS)
debugh :
	@make debugas CPPFLAGS+=$(HFLAGS) LDFLAGS+=$(HFLAGS)
clean:
	rm -rf $(OUT_DIR)
fclean: clean
	rm -f $(NAME).a
	rm -f $(NAME).so
re%: fclean
	make $(patsubst re%, %, $@)
re: fclean all

-include $(D_FILES)