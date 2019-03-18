/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_flags.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaelor- <bbaelor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 16:12:45 by bbaelor-          #+#    #+#             */
/*   Updated: 2019/03/18 20:33:03 by bbaelor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

char	*autocomplete_get_real_programm_name(char *str)
{
	int i;
	int	pr_begin;
	int	pr_end;
	
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	pr_begin = i;
	while (str[i])
	{
		if (str[i] != ' ' && str[i + 1] == ' ')
			pr_end = i;
		if (str[i] == '-')
			break;
		i++;
	}
	return (ft_strndup(&str[pr_begin], pr_end - pr_begin + 1));
}

int		get_autocomplite_flags_len(char *str, int *fd_to_free)
{
	char	*line;
	char	*prog;
	int		res;
	char	*tmp;

	if (!(ft_strchr(str, '-')))
		return (0);
	res = 0;
	prog = autocomplete_get_real_programm_name(str);
	tmp = prog;
	prog = ft_strjoin(g_path_to_database, prog, 0);
	// printf("Program name = |%s|\n", prog);
	free(tmp);
	*fd_to_free = open(prog, O_RDONLY);
	free(prog);
	if (*fd_to_free < 0)
		return (0);
	while ((get_next_line(*fd_to_free, &line)) > 0)
	{
		res++;
		free(line);
		// printf("Line = %s\n", line);
	}
	return (res + 1);
}

char	*get_autocomplite_real_flags(char *str, int strdup)
{
	char	*res;
	int		i;

	i = (int)ft_strlen(str);
	while (i >= 0 && str[i] != ' ')
		i--;
	res = &str[i + 1];
	if (strdup)
		res = ft_strdup(res);
	return (res);
}

char	*autocomplete_beautifulizing_string(char *str, int max)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = xmalloc(sizeof(char) * (ft_strlen(str) + max + 1));
	while (str[i] != '[')
	{
		res[j] = str[i];
		i++;
		j++;
	}
	while (j <= max)
	{
		res[j] = ' ';
		j++;
	}
	while (str[i])
	{
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	free(str);
	return (res);
}

char	**autocomplete_beautifulizing_mas(char **str)
{
	int		i;
	int		max;
	int		i_tmp;

	i = 0;
	max = 0;
	while (str[i])
	{
		i_tmp = ft_strchr(str[i], '[') - str[i];
		if (max < i_tmp)
			max = i_tmp;
		i++;
	}
	i = 0;
	while (str[i])
	{
		str[i] = autocomplete_beautifulizing_string(str[i], max);
		i++;
	}
	return (str);
}

char	**get_autocomplite_flags_mas(char *str, char **res, int *c)
{
	int		fd;
	char	*line;
	char	*prog;
	char	*tmp;
	char	*flag;

	if (!ft_strchr(str, '-'))
		return (0);
	prog = autocomplete_get_real_programm_name(str);
	flag = get_autocomplite_real_flags(str, 0);
	tmp = prog;
	prog = ft_strjoin(g_path_to_database, prog, 0);
	free(tmp);
	fd = open(prog, O_RDONLY);
	if (fd < 0)
		return (0);
	while ((get_next_line(fd, &line)) > 0)
	{
		if (!(ft_strncmp(flag, line, ft_strlen(flag))))
		{
			res[*c] = ft_strdup(line);
			(*c)++;
		}
		free(line);
	}
	close(fd);
	free(prog);
	return (autocomplete_beautifulizing_mas(res));
}
