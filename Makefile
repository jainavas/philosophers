LIB = ar rcs
RM = rm -f

CC = cc

CCFLAGS = -Wall -Wextra -Werror -g3

SRC_DIR = src

SRC = philo.c\
	philo2.c\
	philo3.c\
	ft_atoi.c\
	intoverunderflow.c\

OBJ = $(SRC:.c=.o)

INCLUDE = philo.h

NAME = philo

all: fork $(NAME)

%.o: %.c
	@$(CC) $(CCFLAGS) -I/usr/include -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CCFLAGS) $(OBJ) -o $(NAME)
	@echo "        ||>>    philo compiled!!    <<||"

clean:
	@$(RM) $(OBJ)

fclean:
	@$(RM) $(NAME) $(OBJ)

re: fclean all

fork:
	@echo "		 ████  ██  ████"
	@echo "		 ██  ██  ██░░██"
	@echo "		 ██  ██  ██░░██"
	@echo "		 ██  ██  ██░░██"
	@echo "		 ██        ░░██"
	@echo "		 ██        ░░██"
	@echo "		   ██    ░░██  "
	@echo "		     ██░░██    "
	@echo "		     ██░░██    "
	@echo "		     ██░░██    "
	@echo "		     ██░░██    "
	@echo "		     ██░░██    "
	@echo "		     ██░░██    "
	@echo "		   ██    ░░██  "
	@echo "		   ██    ░░██  "
	@echo "		   ██    ░░██  "
	@echo "		   ██  ░░░░██  "
	@echo "		     ██████    "

.PHONY: all clean fclean re