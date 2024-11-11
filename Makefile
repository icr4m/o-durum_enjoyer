NAME = minishell

SRCS_BUILT = $(addprefix srcs/built_in/, cd.c env.c echo.c export.c exit.c init_env.c pwd.c unset.c)
SRCS_EXEC = $(addprefix srcs/exec/, exec_command.c exec_utils.c exit_status.c exec.c ft_fork.c pipe_exec.c handle_append.c handle_heredoc.c redirection.c)
SRCS_GC = $(addprefix srcs/garbage_collector/, gc_destroy.c gc_init.c gc_malloc.c gc_utils.c)
SRCS_SIG = $(addprefix srcs/signal/, signal_handler.c signal_utils.c)
SRCS_TOKEN = $(addprefix srcs/token/, token.c token_list.c token_utils.c token_utils2.c debug_token.c)
SRCS_PARSING = $(addprefix srcs/parser/, parser.c parser_utils.c)
SRCS_UTILS = $(addprefix srcs/utils/, exit.c read_line.c utils.c init_minishell.c prompt_utils.c expand_var.c expand_var_utils.c expand_var_utils2.c)
SRCS_SYNTAX = $(addprefix srcs/syntax/, syntax_checker.c syntax_checker_utils.c)
MAIN = $(addprefix srcs/, main.c)

OBJ_UTILS 			= $(SRCS_UTILS:.c=.o)
OBJ_BUILT = $(SRCS_BUILT:.c=.o)
OBJ_EXEC = $(SRCS_EXEC:.c=.o)
OBJ_GC 			= $(SRCS_GC:.c=.o)
OBJ_SIG 		= $(SRCS_SIG:.c=.o)
OBJ_TOKEN 		= $(SRCS_TOKEN:.c=.o)
OBJ_PARSING		= $(SRCS_PARSING:.c=.o)
OBJ_SYNTAX = $(SRCS_SYNTAX:.c=.o)
OBJ_MAIN		= $(MAIN:.c=.o)

ALL_OBJS		+=	$(OBJ_UTILS)
ALL_OBJS		+=	$(OBJ_BUILT)
ALL_OBJS 		+=  $(OBJ_EXEC)
ALL_OBJS		+=	$(OBJ_GC)
ALL_OBJS		+=	$(OBJ_SIG)
ALL_OBJS		+=  $(OBJ_TOKEN)
ALL_OBJS		+= $(OBJ_PARSING)
ALL_OBJS		+= $(OBJ_SYNTAX)
ALL_OBJS		+=	$(OBJ_MAIN)

ALL_SRCS +=	$(SRCS_UTILS)
ALL_SRCS += $(SRCS_BUILT)
ALL_SRCS += $(SRCS_EXEC)
ALL_SRCS +=	$(SRCS_GC)
ALL_SRCS +=	$(SRCS_SIG)
ALL_SRCS += $(SRCS_TOKEN)
ALL_SRCS += $(SRCS_PARSING)
ALL_SRCS += $(SRCS_SYNTAX)
ALL_SRCS +=	$(MAIN)

INCS = $(addprefix includes/, lexing.h built_in.h  exec.h ft_signal.h garbage_collector.h minishell.h struct.h utils.h)
INCS_LIBFT = $(addprefix libft/includes/, ft_printf.h get_next_line_bonus.h libft.h)

ALL_INCS += $(INCS)
ALL_INCS += $(INCS_LIBFT)

CCFLAGS = -Wall -Wextra -Werror 

MAKE_FLAGS		+=	--no-print-directory
MAKE_FLAGS		+=	-C

INCLUDES_OPT = -Iincludes -I$(LIBFT_PATH)/includes

LIBFT_PATH = ./libft

# Regular Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White

# Bold
BBlack='\033[1;30m'       # Black
BRed='\033[1;31m'         # Red
BGreen='\033[1;32m'       # Green
BYellow='\033[1;33m'      # Yellow
BBlue='\033[1;34m'        # Blue
BPurple='\033[1;35m'      # Purple
BCyan='\033[1;36m'        # Cyan
BWhite='\033[1;37m'       # White

# High Intensity
IBlack='\033[0;90m'       # Black
IRed='\033[0;91m'         # Red
IGreen='\033[0;92m'       # Green
IYellow='\033[0;93m'      # Yellow
IBlue='\033[0;94m'        # Blue
IPurple='\033[0;95m'      # Purple
ICyan='\033[0;96m'        # Cyan
IWhite='\033[0;97m'       # White

NO_COLOR = "\033[0m"

# Rules
all: $(LIBFT_PATH)/libft.a $(NAME)

$(NAME): $(ALL_OBJS)
	@cc $(CFLAGS) $^ $(LIBFT_PATH)/libft.a -lreadline -o $(NAME)
	@echo $(BBlue)$(GRAS)"making minishell 🆗" $(NO_COLOR)

$(LIBFT_PATH)/libft.a:
	@make $(MAKE_FLAGS) $(LIBFT_PATH)

.c.o:
	@cc $(CCFLAGS) $(INCLUDES_OPT) -c $< -o ${<:.c=.o}

norm:
	-@norminette -R CheckForbiddenSourceHeader $(ALL_SRCS)
	-@norminette -R CheckDefine $(INCS)

val: all
	valgrind --leak-check=full --show-leak-kinds=definite --track-fds=yes --trace-children=yes --errors-for-leak-kinds=none --suppressions=/home/ijaber/Documents/Cursus/MINISHELL/.supp.supp -q ./minishell

clean:
	@rm -rf $(ALL_OBJS)
	@make $(MAKE_FLAGS) $(LIBFT_PATH) fclean
	@echo $(BBlue)$(GRAS)"deleting minishell 🚮"$(NO_COLOR)

fclean: clean
	@rm -f $(NAME)
		
re: fclean all