/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 20:20:46 by bwerewol          #+#    #+#             */
/*   Updated: 2019/02/20 17:50:40 by bwerewol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	g_execerr = 0;

int pipeerror(void)
{
	ft_putstr("42sh: pipe create error\n");
	return (-1);
}

int fileerror(char *file)
{
	ft_putstr("42sh: can't open file : ");
	ft_putstr(file);
	return (-1);
}

int forkerror(char *cmd)
{
	ft_putstr("42sh: unable to fork : ");
	ft_putstr(cmd);
	g_execerr = 1;
	return (-1);
}