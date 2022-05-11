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

OBJ = mandel.o events.o

NAME = mandel

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIB) $(FRW) -o $(NAME)
