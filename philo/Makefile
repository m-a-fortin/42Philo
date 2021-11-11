NAME 		=	philo

INC_PATH	=	includes/
OBJS_PATH 	=	objs/
SRCS_PATH 	=	srcs/
UTILS_PATH 	=	srcs/utils
CC 			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -rf

INC_FILES 	=	philo.h

SRCS_FILES	=	main.c ph_parsing.c ph_error.c ph_exec.c ph_activity.c ph_exec_utils.c

UTILS_FILES =	ft_atoi.c ft_putendl_fd.c ft_putstr_fd.c ft_strncmp.c ft_putchar_fd.c\
				ft_putnbr_fd.c ft_putnbr_ulong.c ft_strlen.c

SRCS 		=	$(addprefix $(SRCS_PATH), $(SRCS_FILES))

OBJS_FILES	= 	$(SRCS_FILES:.c=.o) $(UTILS_FILES:.c=.o)

INCLUDES	=	$(addprefix $(INC_PATH), $(INC_FILES))
OBJS 		=	$(addprefix $(OBJS_PATH), $(OBJS_FILES))

VPATH		=	$(SRCS_PATH) $(UTILS_PATH)

$(OBJS_PATH)%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all:	CFLAGS += -O2
all:	$(NAME)

$(NAME):	$(OBJS_PATH) $(OBJS)
	@echo "\n\033[96m Compiling PHILO \033[0m\n"
	$(CC) $(OBJS) -o $(NAME)
	@echo "\\n\033[32;1m PHILOSOPHERS IS READY \033[0m \\n"

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)
	@echo "\033[34;1m Created Object Directory \033[0m"

debug:	CFLAGS += -g
debug:	$(NAME)

clean:
	@$(RM) $(OBJS_FILES) $(OBJS_PATH) 
	@echo "\033[34;1m CLEAN DONE \033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[34;1m FCLEAN DONE \033[0m"

re: fclean all

.PHONY: all clean fclean re