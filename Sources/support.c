/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 17:17:56 by jmunoz            #+#    #+#             */
/*   Updated: 2016/06/03 12:00:02 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_lst_lexico(t_lst *a, t_lst *b)
{
	return (ft_strcmp(a->name, b->name));
}

int		sort_lst_time(t_lst *a, t_lst *b)
{
	if (!(int)((b->info.st_mtime) - (a->info.st_mtime)))
	{
		if (b->info.st_mtimespec.tv_nsec - a->info.st_mtimespec.tv_nsec == 0)
			return (sort_lst_lexico(a, b));
		else
			return (b->info.st_mtimespec.tv_nsec -
					a->info.st_mtimespec.tv_nsec);
	}
	return ((int)((b->info.st_mtimespec.tv_sec) -
		(a->info.st_mtimespec.tv_sec)));
}

t_lst	*sort_lst_revert(t_lst *begin)
{
	t_lst *list;
	t_lst *prev;

	if (begin)
	{
		list = begin;
		prev = NULL;
		if (!begin->next)
			return (begin);
		while (begin->next)
		{
			prev = begin;
			begin = begin->next;
		}
		prev->next = NULL;
		begin->next = sort_lst_revert(list);
	}
	return (begin);
}

void	ft_errors(char *str)
{
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	errno = 0;
}

char	*manage_path(char *str, t_meta **meta, int mode)
{
	int	size;

	if (mode == 0)
		PATH = ft_strcpy(PATH, str);
	if (mode == 1)
	{
		if (PATH[(ft_strlen(PATH) - 1)] != '/')
			PATH = ft_strcat(PATH, "/");
		PATH = ft_strcat(PATH, str);
	}
	if (mode == 2)
		PATH = ft_path_back(PATH, '/');
	if (mode == 3)
	{
		size = -1;
		while (PATH[++size])
			PATH[size] = '\0';
	}
	return (PATH);
}
