/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 08:39:35 by narchiba          #+#    #+#             */
/*   Updated: 2019/02/07 11:29:07 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "readline.h"
#include "term.h"
#include "shell.h"

int		main(void)
{
	char *str;

	while ((str = readline()))
	{
		write(1, str, strlen(str));
	}
	return (0);
}
