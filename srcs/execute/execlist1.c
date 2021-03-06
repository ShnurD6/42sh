/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execlist1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 20:43:35 by bwerewol          #+#    #+#             */
/*   Updated: 2019/02/27 22:48:24 by nkertzma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <signal.h>

static int	execjob(t_astree *root, int fd[2])
{
	pid_t	pid;

	if (!(pid = fork()))
	{
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		g_isjob = 1;
		g_pgid = setpgrp();
		exit(execlist2(root, fd, 1));
	}
	addjob(JOB_RUN, pid);
	return (0);
}

int			execlist1(t_astree *root, int fd[2], int isfork)
{
	int		res;

	g_pgid = -1;
	if (!root)
		return (EXIT_SUCCESS);
	if (root->type != LIST1 && root->type != AND && root->type != SEMI &&
		root->type != NEWLINE)
		return (execlist2(root, fd, isfork));
	if (root->right && root->right->type == AND)
		res = execjob(root->left, fd);
	else
		res = execlist2(root->left, fd, isfork);
	if (!root->right || !root->right->left)
		return (res);
	if (g_execerr)
		return (-1);
	return (execlist1(root->right, fd, isfork));
}
