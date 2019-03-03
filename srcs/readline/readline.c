/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sitlcead <sitlcead@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 14:12:10 by sitlcead          #+#    #+#             */
/*   Updated: 2019/03/03 17:18:59 by sitlcead         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <string.h>
#include <unistd.h>
#include "term.h"
#include "libshell.h"
#include <pwd.h>

void	ft_puts(char *buf)
{
	int	len;

	len = strlen(buf);
	write(1, buf, len);
}

void	history_resize(void)
{
	g_history->matrix =
			(t_matrix **)xrealloc(g_history->matrix,
								  g_history->size * RATIO * sizeof(t_matrix *),
								  g_history->size * sizeof(t_matrix *));
	g_history->size *= RATIO;
}

void	write_history_on_disk(t_string *str)
{
	int				fd;
	char			*file_name;
	struct passwd	*pw;

	pw = getpwuid(getuid());
	file_name = ft_strjoin(pw->pw_dir, "/", 0);
	file_name = ft_strjoin(file_name, HISTORY_FILE, 1);
	fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0777);
	write(fd, str->buf, str->len);
	write(fd, "\n", 1);
	close(fd);
	free(file_name);
}

void	fill_history(int fd)
{
	(void)fd;
	return ;
}

void	read_history_from_disk(void)
{
	int				fd;
	char			*file_name;
	struct passwd	*pw;

	pw = getpwuid(getuid());
	file_name = ft_strjoin(pw->pw_dir, "/", 0);
	file_name = ft_strjoin(file_name, HISTORY_FILE, 1);
	fd = open(file_name, O_CREAT | O_RDONLY | O_APPEND, 0777);
	fill_history(fd);
	close(fd);
	free(file_name);
}

int		history_save_elem(void)
{
	if (g_history->tmp->str->buf[0] == '\0')
	{
		matrix_del(&g_history->matrix[g_history->len - 1]);
		matrix_del(&g_history->tmp);
		g_history->len--;
		return (1);
	}
	if (g_history->len - 1 &&
			matrix_cmp(g_history->tmp,
					   g_history->matrix[g_history->len - 2]) == 0)
	{
		matrix_del(&g_history->matrix[g_history->len - 1]);
		matrix_del(&g_history->tmp);
		g_history->len--;
		return (0);
	}
	matrix_del(&g_history->matrix[g_history->len - 1]);
	g_history->matrix[g_history->len - 1] = matrix_dup(g_history->tmp);
	matrix_del(&g_history->tmp);
	write_history_on_disk(g_history->matrix[g_history->len - 1]->str);
	return (0);
}

void	init_history(void)
{
	g_history = (t_history *)xmalloc(sizeof(t_history));
	g_history->matrix = (t_matrix **)xmalloc(HISTORY_DEFAULT_SIZE * sizeof(t_matrix *));
	g_history->size = HISTORY_DEFAULT_SIZE;
	g_history->len = 0;
	g_history->cur = 0;
	g_history->last_offset = 0;
	read_history_from_disk();
}

void	history_add_new_elem(void)
{
	if (g_history == NULL)
		init_history();
	if (g_history->size == g_history->len)
		history_resize();
	g_history->len++;
	g_history->cur = g_history->len - 1;
	g_history->last_offset = 0;
	g_history->tmp = matrix_init();
	matrix_create_line(g_history->tmp, 0);
	g_history->matrix[g_history->cur] = matrix_dup(g_history->tmp);
}

void	init_readline(void)
{
	get_term_params(&g_w);
	history_add_new_elem();
	g_mode = VI;
}

t_string	*readline(void)
{
	int			ret;

	print_prompt();
	init_readline();
	set_term();
	ret = 1;
	while (ret > 0)
	{
		print_default(g_history->tmp);
		ret = check_next_symbol(g_history->tmp);
	}
	if (ret == 0)
	{
		print_lines(g_history->tmp);
		write(1, "\n", 1);
		matrix_to_string(g_history->tmp, g_history->tmp->str);
		if (history_save_elem())
			return (readline());
		unset_term();
		return (g_history->matrix[g_history->len - 1]->str);
	}
	history_del(&g_history);
	unset_term();
	return (NULL);
}
