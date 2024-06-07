NAME = philo.a

SRCS = thread_exemple_1.c

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -pthread

RM = rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} 

clean: 
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re


