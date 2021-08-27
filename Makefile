NAME= convert

#************************PARSING************************#
PARSING= libparsing.a
PARSING_PATH= Parsing


#************************Server************************#
SRC_SERVER_PATH= Server
HDR_SERVER_PATH= Server/headers
OBJ_PATH_SERVER= objectsServer

SRC_NAME_SERVER= serverMain.cpp\
				Server.class.cpp\
				server.cpp\
				getWord.cpp\
				ft_split.cpp\
				manipulation.cpp\


HDR_SERVER_NAME= Server.class.hpp\
				server.hpp\
				# parse.hpp\

OBJ_NAME_SERVER= $(SRC_NAME_SERVER:.cpp=.o)
OBJ_SERVER= $(addprefix $(OBJ_PATH_SERVER)/,$(OBJ_NAME_SERVER))
HDR_SERVER= $(addprefix $(HDR_SERVER_PATH)/,$(HDR_SERVER_NAME))

H_SERVER_FLAG= -I $(HDR_SERVER_PATH)

#************************Client************************#
SRC_CLIENT_PATH= Client
HDR_CLIENT_PATH= Client/headers
OBJ_PATH_CLIENT= objectsClient

SRC_NAME_CLIENT= client.cpp\

HDR_CLIENT_NAME= 

OBJ_NAME_CLIENT= $(SRC_NAME_CLIENT:.cpp=.o)
OBJ_CLIENT= $(addprefix $(OBJ_PATH_CLIENT)/,$(OBJ_NAME_CLIENT))
HDR_CLIENT= $(addprefix $(HDR_CLIENT_PATH)/,$(HDR_CLIENT_NAME))

H_CLIENT_FLAG= -I $(HDR_CLIENT_PATH)

#******************************************************#

# FLAGS= -Wall -Wextra -Werror
LPARSING_FLAG= -L$(PARSING_PATH) Parsing/libparsing.a

COMP= clang++

all: parsing server client

server : $(PARSING_PATH)/$(PARSING) $(OBJ_SERVER)
	@$(COMP) $(H_SERVER_FLAG) $(OBJ_SERVER) $(LPARSING_FLAG) -o $@
	@echo "Compilation of Server:  \033[1;32mOK\033[m"

client : $(PARSING_PATH)/$(PARSING) $(OBJ_CLIENT)
	@$(COMP) $(H_CLIENT_FLAG) $(OBJ_CLIENT) $(LPARSING_FLAG) -o $@
	@echo "Compilation of Client:  \033[1;32mOK\033[m"

parsing:
	@make -sC $(PARSING_PATH)

$(OBJ_PATH_SERVER)/%.o:  $(SRC_SERVER_PATH)/%.cpp $(HDR_SERVER)
	@mkdir -p $(OBJ_PATH_SERVER) 
	@$(COMP) -g $(FLAGS) $(H_SERVER_FLAG) -o $@ -c $<

$(OBJ_PATH_CLIENT)/%.o:  $(SRC_CLIENT_PATH)/%.cpp $(HDR_CLIENT)
	@mkdir -p $(OBJ_PATH_CLIENT) 
	@$(COMP) -g $(FLAGS) $(H_CLIENT_FLAG) -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH_SERVER) $(OBJ_PATH_CLIENT)
	@make clean -C $(PARSING_PATH)
	@echo "\033[1;33m>> all objects files are deleted.\033[0m" 


fclean: clean
	@rm -rf server client
	@make fclean -C $(PARSING_PATH)
	@echo "\033[0;31m>> Server and client are deleted.\033[0m" 

re : fclean all