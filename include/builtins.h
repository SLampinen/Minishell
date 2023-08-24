/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:20:52 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/24 14:02:23 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <fcntl.h>

void	builtin_env(t_ms *ms);
void	builtin_pwd(void);
void	builtin_cd(char *dir, t_ms *ms);
void	builtin_export(t_ms *ms, char *arg);
void	builtin_unset(t_ms *ms, char *key);
void	builtin_echo(char *src);

#endif