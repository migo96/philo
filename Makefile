NAME = philo

SRCS = philo.c philo_do.c philo_utils.c
OBJS = philo.o philo_do.o philo_utils.o

CC = cc -Wall -Wextra -Werror

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

