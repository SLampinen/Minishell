/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:52:02 by slampine          #+#    #+#             */
/*   Updated: 2023/08/21 12:37:11 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_line(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strnstr(env[i], "PATH", ft_strlen(env[i])))
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *path_line, char *cmd)
{
	char	*temp;
	char	*cmd_path;
	char	**allpaths;
	char	**saved;

	allpaths = ft_split(path_line, ':');
	saved = allpaths;
	while (*allpaths)
	{
		temp = ft_strjoin(*allpaths, "/");
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(cmd_path, X_OK) == 0)
		{
			while (*saved)
			{
				free(*saved);
				saved++;
			}
			return (cmd_path);
		}
		free(cmd_path);
		allpaths++;
	}
	ft_printf("testshell: command not found: %s\n", cmd);
	while (*saved)
	{
		free(*saved);
		saved++;
	}
	return (NULL);
}

int	check_quotes(char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if (src[i] == 34)
		{
			i++;
			while (src[i] && src[i] != 34)
			{
				i++;
			}
		}
		if (src[i] == 39)
		{
			i++;
			while (src[i] && src[i] != 39)
			{
				i++;
			}
		}
		i++;
	}
	return (0);
}

char	**add_to_array(char **src, char *new)
{
	char	**temp;
	int		i;
	int		max;

	i = 0;
	while (src[i])
	{
		i++;
	}
	temp = malloc(sizeof(char *) * (i + 1));
	//printf("malloced %i\n",i + 1);
	max = i;
	i = 0;
	while (i < max)
	{
		temp[i] = ft_strdup(src[i]);
	//	printf("%s copied to place %i\n",temp[i],i);
		i++;
	}
	temp[i] = ft_strdup(new);
	//printf("%s copied to place %i\n",temp[i],i);
	temp[i + 1] = NULL;
	//printf("Put NULL to place %i\n",i+1);
	return (temp);
}

char	**rm_from_array(char **src, char *del)
{
	char	**temp;
	int		i;
	int		j;
	int		max;

	i = 0;
	while (src[i])
	{
		i++;
	}
	temp = malloc(sizeof(char *) * (i + 1));
	max = i;
	i = 0;
	j = 0;
	while (i < max)
	{
		if (ft_strcmp(src[i], del))
			temp[j] = ft_strdup(src[i]);
		else
			j--;
		i++;
		j++;
	}
	if (i == j)
		printf("nothing removed\n");
	temp[j] = NULL;
	return (temp);
}

char	**handle_quotes(char *src)
{
	int		i;
	char	**array;

	array = NULL;
	i = 0;
	while (src[i])
	{
		if (src[i] == 34)
		{
			i++;
			while (src[i] && src[i] != 34)
			{
				i++;
			}
		}
		i++;
	}
	return (array);
}

char	*get_input(void)
{
	char	*line;

	line = readline("Testshell> ");
	return (line);
}

void	output_trunc(char *file, char *src)
{
	int	outfile;
	int	saved_out;

	outfile = open(file, O_TRUNC | O_CREAT | O_RDWR, 0777);
	saved_out = dup(1);
	dup2(outfile, 1);
	printf("%s\n", src);
	dup2(saved_out, 1);
	close(saved_out);
}

void	output_add(char *file, char *src)
{
	int	outfile;
	int	saved_out;

	outfile = open(file, O_CREAT | O_RDWR | O_APPEND, 0777);
	saved_out = dup(1);
	dup2(outfile, 1);
	printf("%s\n", src);
	dup2(saved_out, 1);
	close (saved_out);
}

void	show_prompt(t_data	*data)
{
	char	*input;

	while (1)
	{
		input = get_input();
		if (!input)
			return ;
		if (ft_strlen(input))
			add_history(input);
		lexer(input, data);
		free(input);
	}
}

int	main(void)
{	
	extern char	**environ;
	t_data		*data;

	data = malloc(sizeof(t_data));
	data->env = environ;
	show_prompt(data);
	return (0);
}
