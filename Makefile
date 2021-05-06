NAME = a.out
SRC = vector.cpp
OBJ = $(SRC:.cpp=.o)
CFLAGS = -Wall -Wextra -Werror -std=c++98

.PHONY: all clean fclean re

all: $(NAME)
$(NAME): $(OBJ)
	clang++ $(OBJ) $(CFLAGS) -o $(NAME) && ./a.out
%.o: %.cpp
	clang++ $(CFLAGS) -c $<
clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
re: fclean all
