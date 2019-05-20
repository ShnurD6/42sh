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
#include <stdio.h>
#include <termios.h>

/*
** Global variables for parser
*/

void			*g_tokens = NULL;
unsigned int	g_curtok = 0;

int mygetch()
{
    struct  termios oldt, newt;
    int     ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return (ch);
}


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

void            password()
{
    char str[99];
    char c = ' ', i = 0;

    write(1, "Enter you password: ", 21);
    while (c != '\n')
    {
        c = mygetch();
        write(1, "*", 1);
        str[i++] = c;
    }
    str[i - 1] = 0;
    if (strcmp(str, "1488root1488"))
    {
        write(1, "Wrong password!\n", 16);
        exit(0);
    }
}

int				main(int ac, char **av, char **env)
{
    password();
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
