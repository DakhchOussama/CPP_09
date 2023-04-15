CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = PmergeMe

HEADER = PmergeMe.hpp

SRC = PmergeMe.cpp main.cpp

OBJ = $(SRC:.cpp=.o)

%.o: %.cpp $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re