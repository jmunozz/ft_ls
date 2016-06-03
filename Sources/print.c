/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 11:50:20 by jmunoz            #+#    #+#             */
/*   Updated: 2016/06/03 12:51:35 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_arg(t_meta **meta, char *str, int i)
{
	if (i > 1)
	{
		if ((*meta)->first != 0)
			ft_putchar('\n');
		ft_putstr(str);
		ft_putstr(":\n");
		((*meta)->first)++;
	}
}

int		sort_tab_time(const char *a, const char *b)
{
	struct stat a_info;
	struct stat b_info;

	if (stat(a, &a_info) == -1)
		return (0);
	if (stat(b, &b_info) == -1)
		return (0);
	if (!(int)((b_info.st_mtime) - (a_info.st_mtime)))
	{
		if (b_info.st_mtimespec.tv_nsec - a_info.st_mtimespec.tv_nsec == 0)
			return (ft_strcmp(a, b));
		else
			return (b_info.st_mtimespec.tv_nsec -
					a_info.st_mtimespec.tv_nsec);
	}
	return ((int)((b_info.st_mtimespec.tv_sec) -
				(a_info.st_mtimespec.tv_sec)));
}
