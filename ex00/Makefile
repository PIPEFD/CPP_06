NAME =  Scalarcoverter

SRC_DIR = src/
INC = inc/



SRC_FILES = main.cpp \
			ScalarConverter.cpp

SRC         =   $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ_DIR		=	objs/
OBJS_FILES	=	$(SRC_FILES:%.cpp=$(OBJ_DIR)%.o)


CXX			=  c++
FLAGS		= -std=c++98 -Wall -Wextra -Werror -g3
RM			= rm -rf

DEF_COLOR 	= \033[0;39m
GRAY 		= \033[0;90m
RED 		= \033[0;31m
GREEN 		= \033[0;92m
YELLOW 		= \033[0;93m
BLUE 		= \033[0;94m
MAGENTA 	= \033[0;95m
CYAN 		= \033[0;96m
WHITE 		= \033[0;97m
CLEAR 		= \033[0m

all:		$(NAME)

$(NAME): $(OBJS_FILES)
	@$(CXX) -o $(NAME) $(FLAGS) $(OBJS_FILES)
	@echo "$(GREEN)SCALARCONVERTER COMPILED SUCCESSFULLY!$(CLEAR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)COMPILING $<...$(CLEAR)"
	@$(CXX) $(FLAGS) -I$(INC) -c $< -o $@

sanitize:
	$(eval FLAGS = -fsanitize=address -g3)

sani: sanitize all
clean:
	@echo "$(YELLOW)FILES REMOVED!$(DEF_COLOR)"
	@if [ -d $(OBJ_DIR) ]; then rm -rf $(OBJ_DIR); fi

fclean: clean
	@if [ -f $(NAME) ]; then rm -rf $(NAME); fi
	@echo "$(RED)$(NAME) REMOVED!$(DEF_COLOR)"

re: fclean all

.PHONY: all clean fclean re