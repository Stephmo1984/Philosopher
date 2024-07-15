
NAME = philo

SRCS =	philo_utils.c \
		philo_init.c \
		philo_mandatory_OK.c \
		philo_parsing_01.c \
		philo_parsing_02.c \
		philo_utils.c 


OBJS = ${SRCS:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

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