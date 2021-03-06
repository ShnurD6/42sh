/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkertzma <nkertzma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:15:05 by nkertzma          #+#    #+#             */
/*   Updated: 2019/02/27 13:42:38 by nkertzma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "readline.h"
#include "lexer.h"
#include "parser.h"
#include "execute.h"

/*
** Global variables for parser
*/

void			*g_tokens = NULL;
unsigned int	g_curtok = 0;

static void		readshell(void)
{
	t_string	*line;
	t_lexer		*lex;
	t_astree	*ast;
	int			last;
	char		*tmp;

	while ((line = readline()))
	{
		lex = lexer(line->buf, line->len);
		string_del(&line);
		g_tokens = lex->lexems;
		ast = inputunit();
		if (g_dontexec == FALSE)
		{
			last = execute(ast);
			tmp = ft_itoa(last);
			ssetenv("?", tmp, ENV_RO);
			ft_strdel(&tmp);
		}
		freeastree(ast);
		lexer_free(lex);
	}
}

int				main(int ac, char **av, char **env)
{
	init(env, av);
	if (argv_parser(ac, av))
	{
		destroy();
		return (EXIT_SUCCESS);
	}
	readshell();
	destroy();
	return (EXIT_SUCCESS);
}
