/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 11:46:37 by bwerewol          #+#    #+#             */
/*   Updated: 2019/03/01 12:37:05 by nkertzma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int		execute(t_astree *root)
{
	int		res;
	int		fd[2];

	g_execerr = 0;
	if (!root)
		return (EXIT_FAILURE);
	fd[0] = 0;
	fd[1] = 1;
	res = execlist1(root, fd, 0, 0);
	return (res);
}