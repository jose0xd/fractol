CC = gcc
CFLAGS = -Wall -Wextra -Werror

OS = $(shell uname)
ifeq ($(OS), Linux)
	INC = mlx_Linux
	LIB = -Lmlx_Linux -lmlx_Linux -lm
	FRW = -lXext -lX11
else
	INC = mlx
	LIB = -Lmlx -lmlx -lm
	FRW = -framework OpenGL -framework Appkit
endif

OBJ = main.o events.o fractals.o utils.o

NAME = fractol

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIB) $(FRW) -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean
	$(MAKE)

.PHONY: clean fclean re
