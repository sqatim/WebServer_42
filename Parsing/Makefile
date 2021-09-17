NAME = libparsing.a

OBJ_PATH= objects

SRC_NAME = parse.cpp\
			set_val_to_attr.cpp\
			tools.cpp\
			check_error.cpp\
			location.cpp\
			webServ.cpp\
			cgi.cpp\



OBJ_NAME = $(SRC_NAME:.cpp=.o)
OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CFLAGS = -Wall -Wextra -Werror
COMP= clang++

all : $(NAME)

$(NAME) : $(OBJ) parse.hpp
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	@echo "Compilation of Parsing:  \033[1;32mOK\033[m"


$(OBJ_PATH)/%.o: %.cpp parse.hpp
	@mkdir -p $(OBJ_PATH) 
	@$(COMP) -g $(FLAGS) -o $@ -c $<

clean :
	@rm -rf $(OBJ_PATH)
	@echo "\033[1;33m>> all objects files are deleted.\033[0m" 

fclean : clean
	@rm -rf $(NAME)
	@echo "\033[0;31m>> $(NAME) is deleted.\033[0m" 


re : fclean all
