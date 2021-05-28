NAME = containers
SRC = ./test/test.cpp ./test/vector.cpp ./test/list.cpp ./test/stack.cpp ./test/queue.cpp
OBJ = $(SRC:.cpp=.o)
CFLAGS = -Wall -Wextra -Werror  -std=c++98

.PHONY: all clean fclean re

all: $(NAME)
$(NAME): $(OBJ)
	clang++ $(OBJ) $(CFLAGS) -o $(NAME) && ./$(NAME)
%.o: %.cpp
	clang++ $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
re: fclean all
