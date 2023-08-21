/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:58:12 by slampine          #+#    #+#             */
/*   Updated: 2023/08/16 13:04:00 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(const char *str1, const char *str2, int n)
{
	int	max;

	max = 1;
	if (n == 0)
		return (0);
	while (*str1 == *str2 && *str1 != '\0' && *str2 != '\0' && max < n)
	{
		str1++;
		str2++;
		max++;
	}
	if ((unsigned char) *str1 > (unsigned char) *str2)
		return (1);
	if ((unsigned char) *str1 < (unsigned char) *str2)
		return (-1);
	return (0);
}
