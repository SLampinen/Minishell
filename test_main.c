/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:32:31 by slampine          #+#    #+#             */
/*   Updated: 2023/08/21 14:42:18 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int is_token(char *src)
{
	if (src[0] == '|')
	{
		if (ft_strlen(src) == 1)
			return (1);
	}
	if (src[0] == '<')
	{
		if (ft_strlen(src) == 1)
			return (1);
		if (src[1] == '<' && ft_strlen(src) == 2)
			return (1);
		return (0);
	}
	if (src[0] == '>')
	{
		if (ft_strlen(src) == 1)
			return (1);
		if (src[1] == '>' && ft_strlen(src) == 2)
			return (1);
		return (0);
	}
	return (0);
}

t_dllist	*ft_lstnewdl(void *content)
{
	t_dllist	*newnode;

	newnode = malloc(sizeof(*newnode));
	if (!newnode)
		return (NULL);
	newnode->content = content;
	newnode->next = NULL;
	newnode->prev = NULL;
	return (newnode);
}

void	ft_lstadd_frontdl(t_dllist **lst, t_dllist *new)
{
	if (lst != NULL && new != NULL)
	{
		new->next = *lst;
		new->prev = NULL;
		*lst = new;
	}
}

void	ft_lstadd_backdl(t_dllist **lst, t_dllist *new)
{
	t_dllist	*temp;

	if (new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = ft_lstlastdl(*lst);
		temp->next = new;
		new->prev = temp;
	}
}

t_dllist	*ft_lstlastdl(t_dllist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
			lst = lst->next;
	return (lst);
}

char *get_input(void)
{
	char *line;
	line = readline("Testshell> ");
	if (ft_strncmp(line, "exit", 4) == 0)
		return (NULL);
	return (line);
}

void output_trunc(char *file, char *src)
{
	int outfile;
	int saved_out;

	outfile = open(file,O_TRUNC | O_CREAT | O_RDWR, 0777);
	saved_out = dup(1);
	dup2(outfile,1);
	printf("%s\n",src);
	dup2(saved_out,1);
	close(saved_out);
}

void output_add(char *file, char *src)
{
	int outfile;
	int saved_out;

	outfile = open(file, O_CREAT | O_RDWR | O_APPEND, 0777);
	saved_out = dup(1);
	dup2(outfile,1);
	char *text = strtok(src, " ,");
	while (text)
	{
	printf("%s\n",text);
	text = strtok(NULL, " ,");
	}
	dup2(saved_out,1);
	close(saved_out);	
}
int	count_pipes(char *source)
{
	int	i;
	int	in_quote;
	int	pipes;

	i = 0;
	pipes = 0;
	in_quote = 0;
	while (source[i])
	{
		if (source[i] == 34)
		{
			if (in_quote)
			{
				in_quote = 0;
				if (i > 0 && source[i - 1] == '\\')
					in_quote = 1;
			}
			else
			{
				in_quote = 1;
				if (i > 0 && source[i - 1] == '\\')
					in_quote = 0;

			}
		}
		printf("%c",source[i]);
		if (source[i] == '|' && in_quote == 0)
			pipes++;
		i++;
	}
	printf("\n%i pipes\n",pipes);
	return (pipes);
}
int	is_in_quote(char *source, int place)
{

	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (source[i])
	{
		if (i == place)
			return (in_quote);
		if (source[i] == 34)
		{
			if (in_quote)
			{
				in_quote = 0;
				if (i > 0 && source[i - 1] == '\\')
					in_quote = 1;
			}
			else
			{
				in_quote = 1;
				if (i > 0 && source[i - 1] == '\\')
					in_quote = 0;

			}
		}
		i++;
	}
	return (-1);
}

void lexer(char *source)
{
	int		pipes;
	int		i;
	int		index_arr;
	int		index_cmd;
	int		start;
	char	**commands;

	pipes = count_pipes(source);
	commands = malloc(sizeof(char * ) * (pipes + 2));
	i = 0;
	index_arr = 0;
	index_cmd = 0;
	start = 0;
	while (source[i])
	{
		if (source[i] == '|')
		{
			if (is_in_quote(source,i) == 0)
			{
				printf("Not in quote, is real pipe\n");
				commands[index_arr] = malloc(sizeof(char) * (i - start + 1));
				while (start < i)
				{
					commands[index_arr][index_cmd] = source[start];
					index_cmd++;
					start++;
				}
				start++;
				commands[index_arr][index_cmd] = '\0';
				index_cmd = 0;
				index_arr++;
			}
		}
		i++;
	}
	commands[index_arr] = malloc(sizeof(char) * (i - start + 1));
	while (start < i)
	{
		commands[index_arr][index_cmd] = source[start];
		index_cmd++;
		start++;
	}
	commands[index_arr][index_cmd] = '\0';
	
	index_arr = 0;
	while (commands[index_arr])
	{
		printf("%s\n",commands[index_arr]);
		index_arr++;
	}
}

int main(int argc, char **argv)
{
	if (argc < 1 || !argv[0])
		return (0);
	char *line;
	while ((line = readline("test>")) != NULL)
	{
		add_history(line);
		lexer(line);
		free(line);
	}
	return (0);
}