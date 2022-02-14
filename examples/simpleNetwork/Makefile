.PHONY: all clean fclean re
export CXX CPPFLAGS MAKEFLAGS LDFLAGS INCLUDES
MKDIR_P 	:= mkdir -p
SRC_DIR		:= .
OUT_DIR 	:= build
CXX 		:= clang++ -std=c++17 -O1
CPPFLAGS 	:= -c -MMD -Wall -Wextra -Werror -fPIC -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=2 -Wno-unknown-pragmas  # -Wno-unused-result
LDFLAGS 	:= -MMD -Wall -Wextra -Werror # -Wno-unused-result
DFLAGS 		:= '-O0 -g3'
ASFLAGS 	:= -fsanitize=address
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
OBJ 		:= main.o

OBJ 		:= $(addprefix $(OUT_DIR)/,$(OBJ))
D_FILES 	= $(OBJ:.o=.d)
NAME 		= simpleNetwork
INCLUDES 	= -I$(PWD)/include -I$(PWD)/src
LIB_INCLUDES = -L$(PWD)/../..
UNAME 		= $(shell uname)

ifeq ($(UNAME), Linux)
	CFLAGS += -D LINUX=1
endif

all: directories $(NAME)

directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}
$(NAME): $(OBJ)
	$(CXX) $(LDFLAGS) $(OBJ) $(INCLUDES) $(LIB_INCLUDES) -l42neurons -o $(NAME)
$(OUT_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) -c $(INCLUDES) $< -o $@
debug :
	@make CPPFLAGS+=$(DFLAGS) LDFLAGS+=$(DFLAGS)
debugas :
	@make debug CPPFLAGS+=$(ASFLAGS) LDFLAGS+=$(ASFLAGS)
debugh :
	@make debugas CPPFLAGS+=$(HFLAGS) LDFLAGS+=$(HFLAGS)
clean:
	rm -rf $(OUT_DIR)
fclean: clean
	rm -f $(NAME)
re%: fclean
	make $(patsubst re%, %, $@)
re: fclean all

-include $(D_FILES)