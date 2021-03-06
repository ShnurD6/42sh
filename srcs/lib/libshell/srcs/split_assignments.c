/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkertzma <nkertzma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 18:42:14 by nkertzma          #+#    #+#             */
/*   Updated: 2019/02/28 14:11:50 by nkertzma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

/*
** Splits environment string like "key=value" into array of two cells
*/

char	**split_assignments(char *str)
{
	char	**pair;
	char	*tmp;
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	pair = (char **)xmalloc(sizeof(char *) * 3);
	if ((tmp = ft_strchr(str, '=')))
	{
		i = tmp - str;
		pair[0] = ft_strsub(str, 0, i);
		pair[1] = i++ ? ft_strsub(str, i, len - i) : NULL;
		pair[2] = NULL;
		return (pair);
	}
	pair[0] = ft_strdup(str);
	pair[1] = ft_strnew(0);
	pair[2] = NULL;
	return (pair);
}
