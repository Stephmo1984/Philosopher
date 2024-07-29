NAME =	philo

NAME_FULL =	philo_full

SRCS =	philo_death.c \
		philo_diner.c \
		philo_get_set.c \
		philo_init.c \
		philo_main.c \
		philo_parsing_01.c \
		philo_parsing_02.c \
		philo_time.c 

SRCS_MAND =	 philo_utils.c

SRCS_FULL =	philo_utils_full.c

OBJ = ${SRCS:.c=.o}

OBJ_MAND = ${SRCS_MAND:.c=.o}

OBJ_FULL = ${SRCS_FULL:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

all: ${NAME}

full: ${NAME_FULL}

%.o: %.c
	$(CC) -Wall -Wextra -Werror -g -pthread -c $< -o $@
	
$(NAME): $(OBJ) $(OBJ_MAND)
	$(CC) $(OBJ) $(OBJ_MAND) -o $(NAME)

$(NAME_FULL): $(OBJ_FULL) $(OBJ)
	$(CC) $(OBJ_FULL) $(OBJ) -o $(NAME_FULL)

clean: 
	@${MAKE}
	@${RM} ${OBJ} ${OBJ_FULL} $(OBJ_MAND)

fclean: clean
	@${RM} ${NAME} ${NAME_FULL} $(OBJ_MAND)

re: fclean all

.PHONY: all clean fclean re full