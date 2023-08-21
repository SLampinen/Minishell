/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 09:24:56 by slampine          #+#    #+#             */
/*   Updated: 2023/08/21 13:00:15 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int	n;

	n = 0;
	while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if ((unsigned char) *str1 > (unsigned char) *str2)
		return (1);
	if ((unsigned char) *str1 < (unsigned char) *str2)
		return (-1);
	return (0);
}

int	check_cmd(char *src)
{
	if (ft_strcmp(src, "cd") == 0)
		return (1);
	if (ft_strcmp(src, "exit") == 0)
		return (1);
	return (0);
}

int	is_abs_path(char *src)
{
	if (access(src, X_OK) == 0)
		return (1);
	return (0);
}

void	executor(char *source, t_data *data)
{
	char	**array;
	char	*path_line;
	char	*cmd_path;
	int		i;
	pid_t	pid;

	array = ft_split(source, ' ');
	if (array == NULL)
	{
		perror("");
		exit(-1);
	}
	if (array[0])
	{
		if (check_cmd(array[0]))
		{
			if (ft_strcmp(array[0], "cd") == 0)
				chdir(array[1]);
			if (ft_strcmp(array[0], "exit") == 0)
				exit(0);
		}
		else
		{
			if (is_abs_path(array[0]))
			{
				pid = fork();
				if (pid == 0)
					execve(array[0], array, data->env);
			}
			else
			{
				path_line = get_path_line(data->env);
				cmd_path = get_cmd_path(path_line, array[0]);
				if (cmd_path)
				{
					pid = fork();
					if (pid == 0)
						execve(cmd_path, array, data->env);
					free(cmd_path);
				}
			}
		}
	}
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void lexer(char *source, t_data *data)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = 0;
	while (source[i])
	{
		if (source[i] == 34)
		{
			if (i > 0 && source[i - 1] == '\\')
			{
				i++;
			}
			else
			{
				i++;
				while (source[i] != 34)
				{
					i++;
				}
			}
		}
		if (source[i] == '|')
			pipes++;
		i++;
	}
	printf("%i pipes\n",pipes);
	(void)data;
}