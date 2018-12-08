# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktlili <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/10 23:32:37 by ktlili            #+#    #+#              #
#    Updated: 2018/10/06 19:30:38 by ktlili           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRC_PATH = ./src
PARSER_PATH = $(SRC_PATH)/parsing
BUILTIN_PATH = $(SRC_PATH)/builtins
ENV_PATH = $(SRC_PATH)/env
TOOLS_PATH = $(SRC_PATH)/tools
OBJ_PATH = ./obj

SRC_BUILTIN = builtins.c \
			  changedir.c 

SRC_NAME =	main.c \
			testing.c \
			eval_line.c \
			exec.c \
			spawn_bin.c \
			expand_tokens.c 

SRC_PARSER = build_tree.c \
			 tree_tools.c \
		  	 eval.c \
			 syntax.c

SRC_ENV = 	env1.c \
			env_util.c \
			ft_env.c 

SRC_TOOL =  util.c \
			util2.c \
			clean_path.c 


OBJ_NAME = 	$(SRC_NAME:.c=.o) $(SRC_PARSER:.c=.o) $(SRC_ENV:.c=.o)  \
			$(SRC_TOOL:.c=.o) $(SRC_BUILTIN:.c=.o)

LIB = ./lib/libft.a

INCLUDES = -I ./includes

FLAGS = -ggdb -Wall -Wextra -Werror

SRC =	$(addprefix $(SRC_PATH)/,$(SRC_NAME)) $(addprefix $(BUILTINS_PATH)/,$(SRC_BUILTINS)) \
		$(addprefix $(PARSER_PATH)/,$(SRC_PARSER)) $(addprefix $(ENV_PATH)/,$(SRC_ENV)) \
		$(addprefix $(TOOLS_PATH)/,$(SRC_TOOLS))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

COLOR		= \033[01;34m
NO_COLOR	= \033[00m
OP_COLOR	= \033[1;31m
DONE 		= $(NO_COLOR)[\033[1;32mOK$(NO_COLOR)]

all:	$(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C ./lib/
	@clang $(OBJ) $(INCLUDES) $(LIB) -o $@
	@printf "$(DONE) $(OP_COLOR)$(NAME)$(NO_COLOR)\n"

$(OBJ_PATH)/%.o: $(PARSER_PATH)/%.c 
	@mkdir -p $(OBJ_PATH)
	@clang  $(FLAGS) $(INCLUDES) -o $@ -c $<
	@printf "$(DONE)$(OP_COLOR)$<$(NO_COLOR)                \r"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c 
	@mkdir -p $(OBJ_PATH)
	@clang $(FLAGS) $(INCLUDES) -o $@ -c $< -I.
	@printf "$(DONE)$(OP_COLOR)$<$(NO_COLOR)                \r"

$(OBJ_PATH)/%.o: $(ENV_PATH)/%.c 
	@mkdir -p $(OBJ_PATH)
	@clang $(FLAGS) $(INCLUDES) -o $@ -c $< -I.
	@printf "$(DONE)$(OP_COLOR)$<$(NO_COLOR)                 \r"

$(OBJ_PATH)/%.o: $(BUILTIN_PATH)/%.c 
	@mkdir -p $(OBJ_PATH)
	@clang $(FLAGS) $(INCLUDES) -o $@ -c $< -I.
	@printf "$(DONE)$(OP_COLOR)$<$(NO_COLOR)                 \r"

$(OBJ_PATH)/%.o: $(TOOLS_PATH)/%.c 
	@mkdir -p $(OBJ_PATH)
	@clang $(FLAGS) $(INCLUDES) -o $@ -c $< -I.
	@printf "$(DONE)$(OP_COLOR)$<$(NO_COLOR)                 \r"

sclean:
	@/bin/rm -rf $(OBJ_PATH) $(NAME)

clean:
	$(MAKE) -C ./lib/ clean
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	$(MAKE) -C ./lib/ fclean
	@/bin/rm -f $(NAME)

clear:
	@clear

re: fclean all

fre: clear sclean all

exe: fre
	./$(NAME)

save:
	@git add *
	@git commit -m  "make save"
	@git push
	@echo "$(DONE)"