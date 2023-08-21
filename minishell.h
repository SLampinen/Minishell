/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:49:51 by slampine          #+#    #+#             */
/*   Updated: 2023/08/21 12:43:23 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <string.h>
# include <fcntl.h>

typedef struct s_data
{
	char	**env;
	char	*pwd;
	char	*old_pwd;
}t_data;
typedef struct s_simple_cmd
{
	
}t_simple_cmd;

void executor(char *source, t_data *data);
void lexer(char *source, t_data *data);
char	*get_path_line(char **env);
char	*get_cmd_path(char *path_line, char *cmd);
int	ft_strcmp(const char *str1, const char *str2);
#endif