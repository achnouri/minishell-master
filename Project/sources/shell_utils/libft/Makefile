CC = cc
CFLAGS = -Wextra -Wall -Werror
AR = ar rcs 
RM = rm -f

SRCS =  ft_bzero.c \
	ft_isalpha.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_isspace.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_strndup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c  \
	ft_strmapi.c \
	ft_strcmp.c  \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c  \
	ft_tolower.c \
	ft_toupper.c \
	ft_atoi.c

SRCB = ft_lstnew_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c

OBJS = $(SRCS:.c=.o)
BOBJS = $(SRCB:.c=.o)

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS) $(BOBJS)
	$(AR) $(NAME) $(OBJS) $(BOBJS)

bonus: $(BOBJS)
	$(AR) $(NAME) $(BOBJS)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BOBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
