NAME      := philo
CC        := cc
FLAGS     := -Wall -Wextra -Werror #-fsanitize=thread -g
SRCS      :=    clock.c  create_info.c \
				create_mutex.c create_table.c \
				destroyer.c thread_fnc.c\
                          
OBJS      := $(SRCS:.c=.o)

.c.o:
			@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
			@$(CC) $(FLAGS) $(OBJS) main.c -o $(NAME) 
			@echo "$(NAME) created[0m ✔️"

all:		${NAME}

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "Deleting $(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "Deleting $(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re