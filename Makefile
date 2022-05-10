CC = gcc
CFLAGS = -Wall -Wextra -Werror

INC = mlx
LIB = -Lmlx -lmlx -lm
FRW = -framework OpenGL -framework Appkit

OBJ = prueba.o

NAME = prueba

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIB) $(FRW) -o $(NAME)
