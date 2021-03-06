/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execshellcmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 16:39:04 by bwerewol          #+#    #+#             */
/*   Updated: 2019/02/27 22:45:42 by nkertzma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "conditions.h"

static int	execarith(char *expr)
{
	char		*calc;
	intmax_t	res;

	calc = expression(expr);
	res = ft_atoi(calc);
	free(calc);
	return (res ? EXIT_SUCCESS : EXIT_FAILURE);
}

int		execshellcmd(t_astree *root, int fd[2], int isfork)
{
	if (root->type == FUNCTION)
		return (execfunction(root));
	if (root->type == FOR)
		return (execfor(root, fd, 0));
	if (root->type == CASE)
		return (execcase(root, fd, 0));
	if (root->type == WHILE)
		return (execwhile(root, fd, 0));
	if (root->type == UNTIL)
		return (execuntil(root, fd, 0));
	if (root->type == SELECT)
		return (1);
	if (root->type == IF)
		return (execif(root, fd, 0));
	if (root->type == ARITH)
		return (execarith(root->content));
	if (root->type == COND)
		return (!conditions(strsplit_to_conditions(root->content)));
	if (root->type == SUBSHELL)
		return (execsubshell(root, fd, isfork));
	if (root->type == COMMAND)
		return (execscmd(root, fd, isfork));
	return (execlist1(root, fd, 0));
}
