NAME= WebServer

#************************PARSING************************#
PARSING= libparsing.a
PARSING_PATH= Parsing

#************************Server************************#
SRC_SERVER_PATH= Server
HDR_SERVER_PATH= Server/headers
OBJ_PATH_SERVER= objectsServer

SRC_NAME_SERVER= serverMain.cpp\
				Server.class.cpp\
				ft_split.cpp\
				manipulation.cpp\
				Request.class.cpp\
				Response.class.cpp\
				methods.cpp\
				location.cpp\
				location2.cpp\
				tools.cpp\
				get_next_line.cpp\
				get_next_line_utils.cpp\


HDR_SERVER_NAME= Server.class.hpp\
				server.hpp\
				Request.class.hpp\
				get_next_line.hpp\
				# parse.hpp\

OBJ_NAME_SERVER= $(SRC_NAME_SERVER:.cpp=.o)
OBJ_SERVER= $(addprefix $(OBJ_PATH_SERVER)/,$(OBJ_NAME_SERVER))
HDR_SERVER= $(addprefix $(HDR_SERVER_PATH)/,$(HDR_SERVER_NAME))

H_SERVER_FLAG= -I $(HDR_SERVER_PATH)


# FLAGS= -Wall -Wextra -Werror
LPARSING_FLAG= -L$(PARSING_PATH) Parsing/libparsing.a

COMP= clang++

all: Parse $(NAME)

WebServer : $(PARSING_PATH)/$(PARSING) $(OBJ_SERVER)
	@$(COMP) $(H_SERVER_FLAG) $(OBJ_SERVER) $(LPARSING_FLAG) -o $@
	@echo "Compilation of WebServer:  \033[1;32mOK\033[m"

Parse:
	@make -sC $(PARSING_PATH)

$(OBJ_PATH_SERVER)/%.o:  $(SRC_SERVER_PATH)/%.cpp $(HDR_SERVER)
	@mkdir -p $(OBJ_PATH_SERVER) 
	@$(COMP) -g $(FLAGS) $(H_SERVER_FLAG) -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH_SERVER)
	@make clean -C $(PARSING_PATH)
	@echo "\033[1;33m>> all objects files are deleted.\033[0m" 


fclean: clean
	@make fclean -C $(PARSING_PATH)
	@rm -rf $(NAME)
	@echo "\033[0;31m>> $(NAME) is deleted.\033[0m" 

re : fclean all