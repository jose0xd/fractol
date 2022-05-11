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

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) -C $(INC)
	$(CC) $(OBJ) $(LIB) $(FRW) -o $(NAME)

clean:
	@rm -f $(OBJ)
	$(MAKE) -C $(INC) clean

fclean: clean
	@rm -f $(NAME)

re: fclean
	$(MAKE)

bonus: $(NAME)

.PHONY: clean fclean re
