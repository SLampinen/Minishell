/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:08:26 by slampine          #+#    #+#             */
/*   Updated: 2023/08/18 14:59:22 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <string.h>
# include <fcntl.h>

typedef struct s_dllist
{
	void				*content;
	struct	s_dllist	*next;
	struct	s_dllist	*prev;
}	t_dllist;

t_dllist	*ft_lstnewdl(void *content);
t_dllist	*ft_lstlastdl(t_dllist *lst);
void		ft_lstadd_frontdl(t_dllist **lst, t_dllist *new);
void		ft_lstadd_backdl(t_dllist **lst, t_dllist *new);

#endif