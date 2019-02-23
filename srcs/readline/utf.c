/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sitlcead <sitlcead@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 00:21:21 by sitlcead          #+#    #+#             */
/*   Updated: 2019/02/22 00:21:21 by sitlcead         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_yet_utf(unsigned char c)
{
	if (((c >> 7) & 1) && ((c >> 6) & 1) == 0)
		return (1);
	return (0);
}

int			get_utf_offset_left(char *str, int pos)
{
	int	i;

	i = 0;
	while (pos > 0 && is_yet_utf(str[pos]))
	{
		pos--;
		i++;
	}
	return (i);
}

int			get_utf_offset_right(unsigned char c)
{
	int	i;

	if (c > 127)
	{
		i = 0;
		while (i < 7 && ((c >> (6 - i)) & 1))
			i++;
		return (i);
	}
	return (0);
}