CC      = cc
CFLAGS  =  -Wall -Wextra -Werror

INCLUDES = -Iincludes -Isources/shell_utils/libft

NAME = minishell

SRC_DIR = sources
OBJ_DIR = obj
DEP_DIR = $(OBJ_DIR)/.deps
LIBFT_DIR = sources/shell_utils/libft
LIBFT = $(LIBFT_DIR)/libft.a

READLINE_PREFIX  = $(shell brew --prefix readline 2>/dev/null || echo /usr)
READLINE_COMPILE = -I$(READLINE_PREFIX)/include
READLINE_LINK    = -L$(READLINE_PREFIX)/lib -lreadline

MAIN_SRC = main.c

PARSER_SRCS = \
	sources/parser/shell_initialization.c \
	sources/parser/shell_initialization_utils.c \
	sources/parser/core_tokens/tokens.c \
	sources/parser/core_tokens/tokens_list_manager.c \
	sources/parser/core_tokens/tokens_utils.c \
	sources/parser/core_expansions/expander_env.c \
	sources/parser/core_expansions/expander_helper.c \
	sources/parser/core_expansions/expansion_utils.c \
	sources/parser/core_expansions/expansion_commons.c \
	sources/parser/core_expansions/expander_env_utils.c \
	sources/parser/core_commands/commands.c \
	sources/parser/core_commands/commands_utils1.c \
	sources/parser/core_commands/commands_utils2.c \
	sources/parser/core_commands/commands_utils3.c	\
	sources/parser/core_commands/commands_commons.c \
	sources/parser/core_commands/commands_helper.c \
	sources/parser/core_commands/handle_append.c \
	sources/parser/core_commands/handle_input.c \
	sources/parser/core_commands/handle_pipe.c \
	sources/parser/core_commands/handle_trunc.c \
	sources/parser/core_commands/handle_herdoc_1.c \
	sources/parser/core_commands/handle_herdoc_2.c \
	sources/parser/core_commands/handle_herdoc_3.c \
	sources/parser/core_commands/handle_herdoc_4.c

EXECUTER_SRCS = \
	sources/executer/builtins/cd_builtin_cmd.c \
	sources/executer/builtins/cd_builtin_utils_1.c	\
	sources/executer/builtins/cd_builtin_utils_2.c	\
	sources/executer/builtins/echo_builtin_cmd.c \
	sources/executer/builtins/env_builtin_cmd.c \
	sources/executer/builtins/exit_builtin_cmd.c \
	sources/executer/builtins/exit_builtin_utils.c	 \
	sources/executer/builtins/export_builtin_cmd.c \
	sources/executer/builtins/pwd_builtin_cmd.c \
	sources/executer/builtins/unset_builtin_cmd.c \
	sources/executer/execution/execution.c \
	sources/executer/execution/execute_command.c \
	sources/executer/execution/execution_utils.c \
	sources/executer/execution/execution_utils_1.c \
	sources/executer/execution/execution_utils_2.c \
	sources/executer/redirection/io_file.c \
	sources/executer/redirection/pipe.c

UTILS_SRCS = \
	sources/shell_utils/free.c \
	sources/shell_utils/free_gb_coll.c \
	sources/shell_utils/msg_err.c \
	sources/shell_utils/quotes_utils.c \
	sources/shell_utils/quotes_utils_1.c \
	sources/shell_utils/syntax_validator.c \
	sources/shell_utils/terminate.c \
	sources/shell_utils/utils.c

SRCS = $(MAIN_SRC) $(PARSER_SRCS) $(EXECUTER_SRCS) $(UTILS_SRCS)

OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS = $(patsubst %.c,$(DEP_DIR)/%.d,$(SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(READLINE_LINK)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@mkdir -p $(dir $(DEP_DIR)/$*.d)
	$(CC) $(CFLAGS) $(INCLUDES) $(READLINE_COMPILE) -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re