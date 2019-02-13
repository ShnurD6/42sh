/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkertzma <nkertzma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 21:15:41 by nkertzma          #+#    #+#             */
/*   Updated: 2019/02/13 21:34:48 by nkertzma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstring.h"

char 	*string_push(t_string *string, char *push, size_t push_size)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (!string || !push)
		return (NULL);
	if (!push_size)
		push_size = ft_strlen(push);
	while (string->size <= string->len + push_size)
		if ((string_resize(string) == STRING_ERR))
			return (NULL);
	ret = &(string->str[string->len + 1]);
	while (i < push_size)
	{
		string->str[string->len + 1] = push[i];
		string->len++;
		i++;
	}
	string->str[string->len + 1] = '\0';
	string->len++;
	return (ret);
}
