/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_space_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 14:10:32 by narchiba          #+#    #+#             */
/*   Updated: 2019/03/16 14:10:34 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_space_tab(int c)
{
	if (c == '\t' || c == ' ')
		return (1);
	return (0);
}