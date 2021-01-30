# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mescande <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 14:03:19 by mescande          #+#    #+#              #
#    Updated: 2021/01/30 15:25:24 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	Cub3D
EXEC		=	test

CC			?=	clang-9
CFLAGS		?=	-Wall -Werror -Wextra -fPIC -fsanitize=address

LEN_NAME	=	`printf "%s" $(NAME) | wc -c`
DELTA		=	$$(echo "$$(tput cols)-32-$(LEN_NAME)" | bc)

SRC_DIR		=	srcs/
OBJ_DIR		=	objs/
INC_DIR		=	includes/
LIB_LIB		=	libft.a
LIB_DIR		=	libft/
LIB_INC		=	libft/includes/
MLX_INC		=	mlx/
MLX_DIR		=	mlx/
MLX_LIB		=	mlx/libmlx.a

INC_FLAGS	=	-I $(INC_DIR) -I $(LIB_INC) -I $(MLX_INC)
MLX_FLAGS	=	-lft -lmlx -lm -lXext -lX11 -L$(LIB_DIR) -L$(MLX_INC) -L/usr/lib/

SRC_LIST	=	main.c\
				parse/parse.c\
				parse/set_values.c\
				parse/map_verif.c\
				parse/textures.c\
				arguments.c\
				arguments2.c\
				error.c\
				mlx_manage.c\
				loop.c\
				player_manage.c\
				calcul_img.c\
				maths/vector_basics.c\
				maths/general_basics.c\
				show_map.c\
				hooky.c\
				textures.c\
				sprite_manage.c\
				movements.c\
				is_mapchar.c\
				bmp.c


SRC			=	$(addprefix $(SRC_DIR), $(SRC_LIST))
OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_LIST:.c=.o))
DIR			=	$(sort $(dir $(OBJ)))
NB			=	$(words $(SRC_LIST))
INDEX		=	0

SHELL		:=	/bin/bash

all: 
	@$(MAKE) -j -C $(LIB_DIR) $(LIB_LIB)
	@$(MAKE) -C $(MLX_INC)
	@$(MAKE) -j $(NAME)
#	@cp cub3D Cub3D 

$(NAME):		$(OBJ) Makefile $(LIB_DIR)$(LIB_LIB) 
	@$(CC) $(CFLAGS) -MMD $(OBJ) -o $@ $(INC_FLAGS) $(MLX_FLAGS)
	@printf "\r\033[38;5;117m✓ MAKE $(NAME)\033[0m\033[K\n"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c Makefile | $(DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB) - 1))))
	@$(eval COLOR=$(shell list=(160 196 202 208 215 221 227 226 190 154 118 84 46); index=$$(($(PERCENT) * $${#list[@]} / 100)); echo "$${list[$$index]}"))
	@printf "\r\033[38;5;%dm↻ [%s]: %2d%% `printf '█%.0s' {0..$(DONE)}`%*s❙%s\033[0m\033[K" $(COLOR) $(NAME) $(PERCENT) $(TO_DO) "" "$(shell echo "$@" | sed 's/^.*\/\(.*\).[och]$$/\1/')"
	@$(CC) $(CFLAGS) -MMD -c $< -o $@ $(INC_FLAGS) $(MLX_FLAGS)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

$(DIR):
	@mkdir -p $@

$(EXEC): all
	@echo "Starting test :"
	./$(NAME) test/subject.cub

clean:
	@$(MAKE) -C $(LIB_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIB_DIR) fclean
	@rm -rf $(NAME)

re: fclean
	@$(MAKE) -j -C $(MLX_INC) re
	@$(MAKE) all

nolib:
	@echo "Recompiling everything exept libs"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -j $(NAME)

help:
	@echo "all	: compiling everything that changed, linking, not relinking\n"
	@echo "clean	: destroy all objects and linking files from program and libs\n"
	@echo "fclean	: clean and destroy exec files and libs"
	@echo "test	: all and exec with validfile.rt or a file given in argument"
	@echo "re	: fclean all"
	@echo "nolib	: destroy object of programs only (not lib) then compiling again"
	@echo "help	: print this help"

.PHONY: all clean fclean re

-include $(OBJ:.o=.d)
