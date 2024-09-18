NAME = minishell

SRCS = $(addprefix srcs/, )
MAIN = $(addprefix srcs/, main.c)

OBJ =  $(SRCS:.c=.o)
OBJ_MAIN		=	$(MAIN:.c=.o)

ALL_OBJS		+=	$(OBJ)
ALL_OBJS		+=	$(OBJ_MAIN)

ALL_SRCS +=	$(SRCS)
ALL_SRCS +=	$(MAIN)

INCS = $(addprefix includes/, minishell.h struct.h)
INCS_LIBFT = $(addprefix Libft/includes/, ft_printf.h get_next_line_bonus.h libft.h)

ALL_INCS += $(INCS)
ALL_INCS += $(INCS_LIBFT)

CCFLAGS = -Wall -Wextra -Werror -g3

MAKE_FLAGS		+=	--no-print-directory
MAKE_FLAGS		+=	-C

INCLUDES_OPT = -Iincludes -I$(LIBFT_PATH)/includes

LIBFT_PATH = ./libft

# Colors
RED	= "\033[0;31m"
GREEN = "\033[0;32m"
GRAS = "\033[1m"
NO_COLOR = "\033[0m"

# Rules
all: $(LIBFT_PATH)/libft.a $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN)
	@cc $(CFLAGS) $^ $(LIBFT_PATH)/libft.a -o $(NAME)
	@echo $(GREEN)$(GRAS)"making minishell .o files" $(NO_COLOR)

$(LIBFT_PATH)/libft.a:
	@make $(MAKE_FLAGS) $(LIBFT_PATH)

.c.o:
	@cc $(CCFLAGS) $(INCLUDES_OPT) -c $< -o ${<:.c=.o}

norm:
	@norminette -R CheckForbiddenSourceHeader $(ALL_SRCS)
	@norminette -R CheckDefine $(ALL_INCS)

bonus: $(LIBFT_PATH)/libft.a $(BONUS_NAME)

clean:
	@rm -rf $(ALL_OBJS)
	@make $(MAKE_FLAGS) $(LIBFT_PATH) fclean
	@echo $(RED)$(GRAS)"deleting minishell .o files"$(NO_COLOR)

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@echo $(RED)$(GRAS)"deleting minishell"$(NO_COLOR)
		
re: fclean all