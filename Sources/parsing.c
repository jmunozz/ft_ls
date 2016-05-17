/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 14:29:49 by jmunoz            #+#    #+#             */
/*   Updated: 2016/05/17 15:47:56 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_init_padding(t_meta **meta)
{
	PADDING.link = 0;
	PADDING.usr = 0;
	PADDING.grp = 0;
	PADDING.size = 0;
	PADDING.total_size = 0;
	PADDING.minor = 0;
	PADDING.major = 0;
}

t_meta	*ft_init_meta(void)
{
	t_meta *meta;

	meta = (t_meta*)malloc(sizeof(t_meta));
	meta->options = 0;
	meta->path = ft_strnew(400);
	meta->first = 0;
	return (meta);
}

void	ft_free_meta(t_meta *meta)
{
	free(meta->path);
	free(meta);
	meta = NULL;
}

void	ft_error_option(char c)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("usage: ls [-Ralrt] [file ...]", 2);
	exit(EXIT_FAILURE);
}

int		ft_get_options(int ac, char **av, t_meta **meta)
{
	int i;
	int j;
	int n;

	i = 0;
	while (++i < ac && av[i][0] == '-' && av[i][1] != '-' && av[i][1] != '\0')
	{
		j = 0;
		while (av[i][++j])
		{
			if ((n = ft_strlenc(OPTIONS_LST, av[i][j])) != OPTIONS_NBR)
				OPTIONS |= (1 << n);
			else if (av[i][j] != '1')
				ft_error_option(av[i][j]);
		}
	}
	if (i == ac || (i == ac - 1 && (!(ft_strcmp(av[i], "--")))))
		return (-1);
	if (av[i][0] == '-' && av[i][1] == '-' && av[i][2] != '\0')
		ft_error_option('-');
	if (!(ft_strcmp(av[i], "--")))
		return (i + 1);
	return (i);
}
