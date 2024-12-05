# COLORS
MAGENTA = \033[35;1m
YELLOW  = \033[33;1m
GREEN   = \033[32;1m
WHITE   = \033[37;1m
RESET   = \033[0m
GRAY 	= \033[0;90m
BLUE    = \033[34;1m
CYAN    = \033[37;1m
BOLD	= \033[1m
RED		= \033[31;1m

#---------- BASE ----------#

# FILES 
CFILES = \

PARSER_FILES = 

EXECUTER_CFILES = executer.c executer_utils.c last_cmd.c

# DIRECTORIES 
SRC_DIR = src/
PARSER_DIR = src/parser/
BUILT_IN_SRC_DIR = src/built_ins/
EXECUTER_SRC_DIR = src/executer/
OBJ_DIR = objs/

# OBJECTS
OFILES = $(addprefix $(OBJ_DIR), $(CFILES:.c=.o))
PARSER_OFILES = $(addprefix $(OBJ_DIR)parser/, $(PARSER_FILES:.c=.o))
BUILT_IN_OFILES = $(addprefix $(OBJ_DIR)built_ins/, $(BUILT_IN_CFILES:.c=.o))
EXECUTER_OFILES = $(addprefix $(OBJ_DIR)executer/, $(EXECUTER_CFILES:.c=.o))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@ mkdir -p $(OBJ_DIR)
	@ echo "$(BLUE)-Compiling File: $(RESET)$(notdir $<)"
	@ $(CC) $(CFLAGS) -c $< -o $@ -g

$(OBJ_DIR)parser/%.o: $(PARSER_DIR)%.c
	@ mkdir -p $(OBJ_DIR)/parser/
	@ echo "$(BLUE)-Compiling File: $(CYAN)parser/$(RESET)$(notdir $<)"
	@ $(CC) $(CFLAGS) -c $< -o $@ -g

$(OBJ_DIR)executer/%.o: $(EXECUTER_SRC_DIR)%.c
	@ mkdir -p $(OBJ_DIR)/executer/
	@ echo "$(BLUE)-Compiling File: $(CYAN)executer/$(RESET)$(notdir $<)"
	@ $(CC) $(CFLAGS) -c $< -o $@ -g

$(OBJ_DIR)built_ins/%.o: $(BUILT_IN_SRC_DIR)%.c
	@ mkdir -p $(OBJ_DIR)/built_ins/
	@ echo "$(BLUE)-Compiling File: $(CYAN)built_ins/$(RESET)$(notdir $<)"
	@ $(CC) $(CFLAGS) -c $< -o $@ -g


#---------- FLAGS & COMPILATION ----------#

CC = clang
NAME = cub3d
CFLAGS = -Wall -Werror -Wextra

all: libft $(NAME)
$(NAME): compiling $(PARSER_OFILES) $(EXECUTER_OFILES) $(BUILT_IN_OFILES) $(OFILES)
	@ echo
	@ $(CC) $(CFLAGS) $(PARSER_OFILES) $(EXECUTER_OFILES) $(BUILT_IN_OFILES) $(OFILES) include/libft/libft.a -lreadline -o $(NAME)
	@ echo "$(YELLOW)COMPILATION FINISHED!$(RESET)"

debug: all
	@ echo
	@ $(CC) $(CFLAGS) $(PARSER_OFILES) $(EXECUTER_OFILES) $(BUILT_IN_OFILES) $(OFILES) include/libft/libft.a -lreadline -o $(NAME) -g -fsanitize=address
	@ echo "$(RED)DEBUG MODE ACTIVATED!$(RESET)"

libft:
	@ make --silent -C include/libft/ bonus

bonus: all $(BONUS_NAME)
$(BONUS_NAME): $(BONUS_OFILES) $(BONUS_ORDER_OFILES)
	@ $(CC) $(CFLAGS) $(BONUS_OFILES) $(BONUS_ORDER_OFILES) -o $(BONUS_NAME)

#---------- CLEAN ----------#

clean:
	@ echo "$(RED)CLEANING PROJECT ... $(RESET)"
	@ rm -f $(OFILES) $(ORDER_OFILES) $(BONUS_OFILES) $(BONUS_ORDER_OFILES)
	@ make --silent -C "include/libft/" fclean
	@ echo "$(YELLOW)PROJECT CLEANED!\n $(RESET)"

fclean: clean
	@ rm -f $(NAME) $(BONUS_NAME)

re: fclean all

rebug: re debug
	@ ./cub3d

compiling:
	@ echo "$(MAGENTA)COMPILING PROJECT: $(RESET)"

.PHONY: all clean fclean re bonus compiling debug rebug
