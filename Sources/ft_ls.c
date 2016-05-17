/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 16:59:15 by jmunoz            #+#    #+#             */
/*   Updated: 2016/05/17 15:48:18 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_ls_single(char *str, t_meta **meta)
{
	t_lst	*begin;
	t_lst	*tmp;

	manage_path(".", meta, 0);
	ft_init_padding(meta);
	begin = do_lst(str, meta);
	get_padding(meta, begin);
	(*meta)->options |= (1 << 5);
	ft_print_all(begin, meta);
	while (begin)
	{
		tmp = begin->next;
		lst_free(begin);
		begin = tmp;
	}
	(*meta)->options &= ~(1 << 5);
	((*meta)->first)++;
}

static void		ft_ls_recursive(t_meta **meta, t_lst *begin, char *str)
{
	t_lst *tmp;

	while (begin)
	{
		if ((ft_strcmp(begin->name, ".")) && (ft_strcmp(begin->name, ".."))
			&& (ft_get_type(begin->info.st_mode) == 'd'))
		{
			ft_putchar('\n');
			ft_putstr(PATH);
			ft_putchar('/');
			ft_putstr(begin->name);
			ft_putstr(":\n");
			ft_ls(manage_path(begin->name, meta, 1), meta);
			manage_path(str, meta, 2);
		}
		tmp = begin->next;
		lst_free(begin);
		begin = tmp;
	}
}

void			ft_ls(char *str, t_meta **meta)
{
	DIR		*stream;
	t_lst	*begin;
	t_lst	*tmp;

	begin = NULL;
	ft_init_padding(meta);
	if (!(stream = opendir(str)))
	{
		ft_print_all(begin, meta);
		return ;
	}
	begin = ft_build_lst(stream, meta);
	ft_print_all(begin, meta);
	if (RECURSIVE)
		ft_ls_recursive(meta, begin, str);
	else
		while (begin)
		{
			tmp = begin->next;
			lst_free(begin);
			begin = tmp;
		}
	if (closedir(stream) == -1)
		perror("closedir");
}

void			multi_arg(t_meta **meta, char **av, int ac, int begin_arg)
{
	int			temp;
	struct stat isdir;

	temp = begin_arg - 1;
	while (++temp < ac)
	{
		if (stat(av[temp], &isdir) == -1)
			ft_errors(av[temp]);
		if (stat(av[temp], &isdir) != -1 && ft_get_type(isdir.st_mode) != 'd')
			ft_ls_single(av[temp], meta);
	}
	temp = begin_arg - 1;
	while (++temp < ac)
	{
		if (stat(av[temp], &isdir) != -1 && ft_get_type(isdir.st_mode) == 'd')
		{
			errno = 0;
			ft_print_arg(meta, av[temp], (ac - begin_arg));
			ft_ls(manage_path(av[temp], meta, 0), meta);
			manage_path(NULL, meta, 3);
		}
	}
}

int				main(int ac, char **av)
{
	int			begin_arg;
	t_meta		*meta;

	meta = ft_init_meta();
	if ((begin_arg = ft_get_options(ac, av, &meta)) == -1)
	{
		ft_ls(manage_path(".", &meta, 0), &meta);
		return (0);
	}
	ft_sort_char_tab(&av[begin_arg], (ac - begin_arg));
	multi_arg(&meta, av, ac, begin_arg);
	ft_free_meta(meta);
	return (0);
}
