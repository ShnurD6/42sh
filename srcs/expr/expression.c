/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bits_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkertzma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 20:32:33 by nkertzma          #+#    #+#             */
/*   Updated: 2019/01/23 11:14:56 by nkertzma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expression.h"
#include "lexer.h"
#include "exprlexer.h"
#include "expr.h"

unsigned int		g_excurtok;
void				*g_extokens = NULL;
int					g_exprerr;

char				*expression(char *arg)
{
	t_lexer		*lexer;
	t_astree	*root;
	intmax_t	res;

	lexer = exprlexer(arg, ft_strlen(arg));
	g_extokens = lexer->lexems;
	g_excurtok = 0;
	g_exprerr = 0;
	root = expr();
	if (g_exprerr)
		return ((char *)0);
	if (!root)
		return (ft_itoa(0));
	res = calc(root);
	if (g_exprerr)
	{
		exfreeastree(root);
		return ((char *)0);
	}
	lexer_free(lexer);
	exfreeastree(root);
	return (ft_itoa(res));
}
