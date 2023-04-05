NAME = philo

SRCS = philo.c philo_do.c philo_utils.c philo_utils2.c philo_error.c
OBJS = philo.o philo_do.o philo_utils.o philo_utils2.o philo_error.o

CC = cc -Wall -Wextra -Werror -g -fsanitize=address

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) -o $@ $^

.c.o :
	$(CC) -c -o $@ $<

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

