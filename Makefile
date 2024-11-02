NAME = pipex
NAME_BONUS = b_pipex
NAME_BONUS2 = pipex_bonus2
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/pipex_utils.c srcs/pipex.c
SRCS_BONUS = srcs/pipex_utils_bonus.c srcs/pipex_bonus.c
SRCS_BONUS2 = srcs/pipex_utils_bonus2.c srcs/pipex_bonus2.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
HEADER = pipex.h
HEADER_BONUS = pipex_bonus.h
HEADER_BONUS2 = pipex_bonus2.h

PRINTF_DIR = includes/ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a
LIBFT_DIR = includes/Libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I $(PRINTF_DIR) -I $(LIBFT_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(PRINTF) $(LIBFT) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -g -c $< -o $@

$(LIBFT): 
	make -C $(LIBFT_DIR) bonus

$(PRINTF): $(LIBFT)
	make -C $(PRINTF_DIR)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_BONUS) $(PRINTF) $(LIBFT) -o $(NAME_BONUS)

%.o: %.c $(HEADER_BONUS)
	$(CC) $(CFLAGS) $(INCLUDES) -g -c $< -o $@

bonus2: $(NAME_BONUS2)

$(NAME_BONUS2): $(OBJS_BONUS2) $(PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_BONUS2) $(PRINTF) $(LIBFT) -o $(NAME_BONUS2)

%.o: %.c $(HEADER_BONUS2)
	$(CC) $(CFLAGS) $(INCLUDES) -g -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)
	rm -f $(OBJS_BONUS2)
	make -C $(PRINTF_DIR) clean
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	rm -f $(NAME_BONUS2)
	make -C $(PRINTF_DIR) fclean
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re