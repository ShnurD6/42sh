/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 15:25:57 by bwerewol          #+#    #+#             */
/*   Updated: 2019/02/27 12:51:35 by nkertzma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_pathadd(char *path, char *name)
{
	char	*newpath;
	size_t	pathlen;
	size_t	namelen;
	int		noslash;

	pathlen = ft_strlen(path);
	namelen = ft_strlen(name);
	noslash = (path[pathlen - 1] != '/') ? 1 : 0;
	if (!(newpath = xmalloc(pathlen + namelen + noslash + 1)))
		return (NULL);
	ft_memcpy(newpath, path, pathlen);
	if (noslash)
		newpath[pathlen] = '/';
	ft_memcpy(newpath + pathlen + noslash, name, namelen + 1);
	return (newpath);
}
