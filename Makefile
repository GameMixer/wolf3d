# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/28 19:09:15 by gderenzi          #+#    #+#              #
#    Updated: 2017/08/10 16:58:59 by gderenzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= wolf3d
CC			= gcc
CFLAGS		= -g -Wall -Werror -Wextra
CFLAGS		+= -I includes/ -I libft/includes -I mlx/ 
LDFLAGS		:= -L libft/ -lft -L mlx/ -lmlx -framework OpenGL -framework AppKit
SRC			= main.c \
			  load.c \
			  init.c \
			  map.c \
			  ray_cast.c \
			  calc.c \
			  draw.c \
			  render.c \
			  sprite.c \
			  display.c \
			  path.c \
			  weapon.c \
			  key_hook.c \
			  movement.c \
			  vector.c \
			  util.c \
			  error.c

OBJ			= $(addprefix $(OBJDIR),$(SRC:.c=.o))

LIBFT		= libft/libft.a
LIBMLX		= mlx/libmlx.a

SRCDIR		= ./src/
INCDIR		= ./includes/
OBJDIR		= ./obj/

all: $(NAME)


$(LIBFT):
	$(MAKE) -C libft 

$(LIBMLX):
	@make -C mlx

$(addprefix $(OBJDIR), %.o): $(addprefix $(SRCDIR), %.c)
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(LIBFT) $(LIBMLX) $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ 

clean:
	$(MAKE) -C libft clean
	make -C mlx clean
	@rm -f $(OBJ)
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all
