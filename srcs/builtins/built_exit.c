/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkertzma <nkertzma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 14:42:28 by nkertzma          #+#    #+#             */
/*   Updated: 2019/02/27 15:28:05 by nkertzma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

/*
** Exit, returning a status of n to the shell’s parent
** exit [n]
*/

int		built_exit(char **av, char **env)
{
	char	*last;
	int		ret;

	env = NULL;
	if (av[1] && ft_str_is_numeric(av[1]))
	{
		ret = ft_atoi(av[1]);
		destroy();
		exit(ret);
	}
	destroy();
	if ((last = sgetenv("?", ENV_ALL)))
		exit(ft_atoi(last));
	exit(SHERR_OK);
}
