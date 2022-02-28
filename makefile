CC = gcc

AR = ar rc
CFLAGS = -Wall -Wextra -Werror

SRCS = pipex.c dependencies/utils.c dependencies/utils_plus.c ./dependencies/ft_strdup.c  ./dependencies/ft_strjoin.c ./dependencies/ft_split.c \
				./dependencies/ft_strlen.c ./dependencies/ft_strncmp.c ./dependencies/ft_substr.c

OBJS = $(SRCS:.c=.o)


B_SRCS =  bonus.c dependencies/utils.c dependencies/utils_plus.c limiter.c ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c ./dependencies/ft_strdup.c  ./dependencies/ft_strjoin.c ./dependencies/ft_split.c \
				dependencies/ft_strlen.c dependencies/ft_strncmp.c dependencies/ft_substr.c

B_OBJS = $(B_SRCS:.c=.o)

NAME = dependencies/mandatory.a
BONUS = dependencies/bonus.a

all : $(NAME)

bonus : $(BONUS)

$(NAME) : $(OBJS)
	rm -rf $(BONUS)
	$(AR) $(NAME) $(OBJS)
	$(CC) $(CFLAGS) $(NAME)  -o pipex

$(BONUS) :   $(B_OBJS)
	rm -rf $(NAME)
	$(AR) $(BONUS) $(B_OBJS)
	$(CC) $(CFLAGS) $(BONUS)  -o pipex

clean :
	rm -rf $(OBJS) $(B_OBJS)

fclean : clean
	rm -f $(NAME) $(BONUS)

re : fclean all

.PHONY : all clean fclean re