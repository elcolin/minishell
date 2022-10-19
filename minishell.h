/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:07:37 by ecolin            #+#    #+#             */
/*   Updated: 2022/10/19 18:54:34 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

// # include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

// TO REMOVE !!!
# include <stdio.h>


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
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_input
{
	char			*input;
	int				type;
	struct s_input	*prev;
	struct s_input	*next;
}				t_input;

typedef struct s_root
{
	t_env			*env;
	pid_t			pid;
	int				pipefd[2];
	int				stdin;
	int				stdout;
}				t_root;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
int		ft_strlen(const char *s);
char	*ft_strndup(const char *s, int n);
int		n_occurencies(char *s, char c, int n);
int		strchri(char *s, int c);
t_input	*parsing(char *s);
int		ft_isascii(int c);

#endif