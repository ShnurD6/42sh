/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:01:20 by narchiba          #+#    #+#             */
/*   Updated: 2019/03/09 11:18:53 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "libshell.h"
#include "autocomplete.h"

int			print_default(t_matrix *matrix)
{
	set_matrix_limits(matrix);
	add_cursor_offset();
	array_add(CURSOR_CLEAR_TO_END_SCREEN,
			ft_strlen(CURSOR_CLEAR_TO_END_SCREEN));
	add_lines_text(matrix);
	add_cursor_offset();
	add_cursor_text(matrix);
	array_flush();
	return (1);
}

int			print_end(t_matrix *matrix)
{
	set_matrix_limits(matrix);
	add_cursor_offset();
	array_add(CURSOR_CLEAR_TO_END_SCREEN,
			ft_strlen(CURSOR_CLEAR_TO_END_SCREEN));
	add_lines_text(matrix);
	array_add("\n", 1);
	array_flush();
	return (1);
}

int			print_search(t_matrix *matrix)
{
	t_line	*line;
	size_t	symbols;

	set_matrix_limits(matrix);
	add_cursor_offset();
	array_add(CURSOR_CLEAR_TO_END_SCREEN,
			ft_strlen(CURSOR_CLEAR_TO_END_SCREEN));
	add_lines_text(matrix);
	array_add("\n", 1);
	line = g_history->search_line;
	array_add(SEARCH_PROMPT, ft_strlen(SEARCH_PROMPT));
	add_line(line, 0, line->len, 0);
	symbols = line->symbols + ft_strlen(SEARCH_PROMPT);
	g_history->last_offset += 1 + symbols / g_w.ws_col;
	if (symbols % g_w.ws_col == 0)
		array_add("\n", 1);
	array_flush();
	return (1);
}

static int	print_possibilities(t_matrix *matrix, char **matches, size_t cnt)
{
	size_t	i;

	set_matrix_limits(matrix);
	add_cursor_offset();
	add_lines_text(matrix);
	array_add("\n", 1);
	i = 0;
	while (i < cnt)
	{
		array_add(matches[i], ft_strlen(matches[i]));
		free(matches[i]);
		array_add("\n", 1);
		i++;
	}
	array_flush();
	print_prompt();
	reset_last_offset();
	free(matches);
	return (1);
}

int			print_autocomplete(t_matrix *matrix)
{
	char	**matches;
	size_t	cnt;

	matches =
		autocomplete(matrix->lines[matrix->cursor->row], matrix->cursor->col);
	if (matches == NULL)
		return (1);
	cnt = 0;
	while (matches[cnt])
		cnt++;
	if (cnt > 1)
		return (print_possibilities(matrix, matches, cnt));
	*matrix->cursor = matrix_string_insert(matrix, *matrix->cursor,
			matches[0], ft_strlen(matches[0]));
	free(matches[0]);
	free(matches);
	return (1);
}