/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_add_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkertzma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 11:43:46 by nkertzma          #+#    #+#             */
/*   Updated: 2019/02/09 17:18:59 by nkertzma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libut.h"

static t_utest	*g_utcur;

int				ut_add_test(t_utest **ut, int (*test)(void *input, void *expect),
															t_uinput *input)
{
	t_utest		*new;

	if (!ut || !input)
		return (UT_INVALID_INPUT);
	if (!(new = (t_utest *)malloc(sizeof(t_utest))))
		return (UT_MALLOC_CRUSHED);
	new->test = test;
	if (!(new->input = malloc(input->input_size)))
	{
		free(new);
		return (UT_MALLOC_CRUSHED);
	}
	ft_memcpy(new->input, input->input, input->input_size);
	new->input_size = input->input_size;
	if (!(new->expect = malloc(input->expect_size)))
	{
		free(new->input);
		free(new);
		return (UT_MALLOC_CRUSHED);
	}
	ft_memcpy(new->expect, input->expect, input->expect_size);
	new->expect_size = input->expect_size;
	new->next = NULL;
	if (*ut)
	{
		new->id = g_utcur->id + 1;
		g_utcur->next = new;

	}
	else
	{
		new->id = 0;
		*ut = new;
	}
	g_utcur = new;
	return (UT_OK);
}