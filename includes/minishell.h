/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:07:37 by ecolin            #+#    #+#             */
/*   Updated: 2022/11/20 17:04:31 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "garbage.h"
# include "libft.h"
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>

# ifndef PATH_MAX
#  define PATH_MAX 1024 
# endif

# include <stdio.h>
# include <string.h>

typedef enum e_enum
{
	NO_SEP = 0,
	PIPE = 1,
	REDIRECT_STDIN = 2,
	REDIRECT_STDOUT = 3,
	CAT = 4,
	APPEND = 5,
}	t_enum;

typedef struct s_env
{
	char			*line;
	char			*name;
	char			*value;
	struct s_env	*next;
}			t_env;

typedef struct s_input
{
	char			*input;
	int				type;
	struct s_input	*prev;
	struct s_input	*next;
}				t_input;

typedef struct s_root
{
	t_input			*parse;
	t_input			*heredoc;
	t_env			*env;
	char			**path;
	char			**envp;
	pid_t			pid;
	int				pipefd[2];
	int				exit;
	int				infile;
	int				outfile;
	int				cmd_num;
	struct s_cmd	*cmd_lst;
}				t_root;

typedef struct s_cmd
{
	char			**parse_cmd;
	char			*cmd;
	int				infile;
	int				outfile;
	int				close;
	t_input			*init_input;
	t_input			*cmd_input;
	pid_t			pid;
	struct s_cmd	*next_cmd;
}	t_cmd;

char	*expand(char *arg, t_env *env, int inside);
char	*after(char *arg, t_env *env);
int		env(char **envp);
char	*ft_getenv(char *name, t_env *env);
int		pwd(void);
int		strchri(char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putendl_fd(char *s, int fd);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_putchar_fd(char c, int fd);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_strndup(const char *s, int n);
int		n_occurencies(char *s, char c, int n);
char	*no_more_quotes(char *s);
t_input	*new_input(char *s, int no_type);
t_input	*parsing(char *s, t_root *root);
char	**parsing_cmd(char *cmd, t_input *parse);
char	**find_paths(t_env *env);
void	command_list(t_input	*parse, t_root *root);
char	*skip_char(char *s, char	*c);
char	*is_cmd(t_root *root, char *input);
char	**find_cmd(char *arv, char **paths);
t_input	*next_type(t_input	*input);
int		get_type(char *str);
int		exec(t_root *root);
char	*replace(char *arg);
int		redirection(t_cmd *cmd);
int		no_cmd(t_input *parse);
t_input	*heredoc(t_input *input);
int		input_heredoc(t_input	*sep, t_root *root);
int		cd(char **path, t_env *env);
int		b_exit(char **input, int print);
int		export(char **input, t_env *env);
int		unset(char **input, t_env *env);
t_env	*init_env(char **envp);
int		_env(t_env *env);
int		pwd(void);
int		message_error(int err, int last, int print);
int		echo_print(char **input, int i, int n);
int		echo(char **input);
int		is_num(char c);
int		is_letter(char c);
char	*export_value(char *input);
int		*_heredoc_sigint(void);
void	handler_h(int sig);
t_env	*ft_env_push_back(t_env *list, char *line, char *name, char *value);
int		exit_signal(int status);
void	handler_heredoc(int sig);
void	sig_init(struct sigaction *sa_prompt);
void	handler_prompt(int sig);
void	handler_cmd(int sig);
t_cmd	*new_cmd(char *cmd, t_input *init_input,
			t_input *cmd_input, t_input *parse);
t_input	*add_who_next(t_input **head, char *s, int no_type);
int		count_char(char *s, char c);
char	*skip_char(char *s, char	*c);
char	*got_quotes(char *s, int *i, int *k, t_env *env);
char	*add_arg(t_input **head, char *tmp, int q);
int		arg(char *s);
char	*dup_expand(char *s, int size, t_env *env);
int		how_big(t_input	*parse);
int		exit_status(int status, int b_status, t_root *root);
void	err(int value, t_root	*root);
int		find_pipe(t_input	*input);
int		previous_pipe(t_input *input, t_input *cmd);
int		stop_exec(int err, t_root *root, int print, int exit);
char	*t_has_type(t_input **t, t_input **init_input);
char	*t_zero_type(t_input **t, t_input **init_input,
			t_input **cmd_input, t_root *root);
void	str_exists(char *tmp, t_input **t, t_input **init_input);
int		get_fdin(t_root *root, int *fdin, t_cmd *cmd);
int		get_fdout(t_root	*root, int *fdout, t_cmd *index);
int		command_number(t_input *input);
int		close_init(int	*fd);
int		open_fd(t_input *index, int *fdin, int *fdout);
int		cmd_is_next_input(t_cmd *cmd);

#endif
