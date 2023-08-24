/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:40:59 by slampine          #+#    #+#             */
/*   Updated: 2023/08/24 14:21:11 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "env_var.h"
#include "executor.h"

int	is_abs_path(char *src)
{
	if (access(src, X_OK) == 0)
		return (1);
	return (0);
}

char	*get_cmd_path(char *path_line, char *cmd)
{
	char	*temp;
	char	*cmd_path;
	char	**allpaths;
	int		i;

	allpaths = ft_split(path_line, ':');
	i = 0;
	while (allpaths[i])
	{
		temp = ft_strjoin(allpaths[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(cmd_path, X_OK) == 0)
		{
			free_array(allpaths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	ft_printf("minishell: "CMD_NOT_FOUND": %s\n", cmd);
	free_array(allpaths);
	return (NULL);
}

void	find_n_exec(char **array, t_ms *ms)
{
	t_ev	*path_line;
	char	*cmd_path;
	pid_t	pid;

	path_line = ft_find_var(&ms->env_var, "PATH");
	if (!path_line)
		return ;
	cmd_path = get_cmd_path(path_line->value, array[0]);
	if (cmd_path)
	{
		pid = fork();
		if (pid == 0)
			execve(cmd_path, array, NULL);
		free(cmd_path);
	}
}

int	executor(char *source, t_ms *ms)
{
	char	**array;
	pid_t	pid;

	array = ft_split(source, ' ');
	if (array == NULL)
		return (0);
	if (array[0])
	{
		if (is_abs_path(array[0]))
		{
			pid = fork();
			if (pid == 0)
				execve(array[0], array, NULL);
		}
		else
			find_n_exec(array, ms);
	}
	free_array(array);
	return (1);
}

/* runs builtin-command based on spec
*/

void	run_builtin(char *input, int spec, t_ms *ms)
{
	char	*temp;

	if (spec == 1)
	{
		if (ft_strlen(input) > 3)
			builtin_cd(input + 3, ms);
		else
			builtin_cd(NULL, ms);
	}
	if (spec == 2)
		builtin_env(ms);
	if (spec == 3)
		builtin_pwd();
	if (spec == 4)
		builtin_export(ms, input + 7);
	if (spec == 5)
		builtin_unset(ms, input + 6);
	if (spec == 6)
	{
		temp = ft_strtrim(input + 5, " ");
		builtin_echo(temp);
		free(temp);
	}
}
