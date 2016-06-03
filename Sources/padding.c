/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 19:26:05 by jmunoz            #+#    #+#             */
/*   Updated: 2016/06/03 12:43:00 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_print_minmaj(dev_t dev, t_meta **meta)
{
	char	*str;
	char	*begin;
	int		min;
	int		maj;

	min = dev & MINOR_MASK;
	maj = dev >> 24;
	str = ft_strnew(PADDING.minor + PADDING.major + 2);
	begin = str;
	ft_strcpy(str, ft_padding_right(ft_itoa(maj), ' ', (size_t)PADDING.major));
	str += PADDING.major;
	*(str++) = ',';
	*(str++) = ' ';
	ft_strcpy(str, ft_padding_right(ft_itoa(min), ' ', (size_t)PADDING.minor));
	return (begin);
}

void	ft_print_symlink(t_meta **meta, char *str)
{
	char *buff;

	buff = ft_strnew(100);
	if (readlink(manage_path(str, meta, 1), buff, 100) == -1)
		perror("");
	manage_path(str, meta, 2);
	ft_putstr(" -> ");
	ft_putstr(buff);
	free(buff);
}

void	ft_print_line_r(t_lst *current, t_meta **meta)
{
	char	*temp;
	char	*temp2;
	time_t	clock;

	ft_putstr("  ");
	temp = (ft_get_type(current->info.st_mode) == 'c' ||
			ft_get_type(current->info.st_mode) == 'b') ?
			ft_print_minmaj(current->info.st_rdev, meta) :
			ft_itoa(current->info.st_size);
	temp2 = ft_padding_right(temp, ' ', PADDING.size);
	ft_putstr(temp2);
	free(temp);
	free(temp2);
	temp = ctime(&(current->info.st_mtimespec.tv_sec));
	ft_putstrn(temp + 3, 8);
	if (SEC < time(&clock) - SIXMONTH || SEC > time(&clock))
		ft_putstrn(temp + 19, 5);
	else
		ft_putstrn(temp + 11, 5);
	ft_putchar(' ');
	ft_putstr(current->name);
	if (ft_get_type(current->info.st_mode) == 'l')
		ft_print_symlink(meta, current->name);
	ft_putchar('\n');
}

void	ft_print_line(t_lst *current, t_meta **meta)
{
	char		*temp;
	char		*temp2;

	ft_putchar(ft_get_type(current->info.st_mode));
	ft_putstr((temp = ft_get_mode(current->info.st_mode)));
	free(temp);
	ft_putstr("  ");
	temp = ft_itoa(current->info.st_nlink);
	ft_putstr((temp2 = ft_padding_right(temp, ' ', PADDING.link)));
	free(temp);
	free(temp2);
	ft_putchar(' ');
	temp = ft_get_usr_id(current->info.st_uid);
	ft_putstr((temp2 = ft_padding_left(temp, ' ', PADDING.usr)));
	free(temp);
	free(temp2);
	ft_putstr("  ");
	temp = ft_get_grp_id(current->info.st_gid);
	ft_putstr((temp2 = ft_padding_left(temp, ' ', PADDING.grp)));
	free(temp);
	free(temp2);
	ft_print_line_r(current, meta);
}

void	ft_print_all(t_lst *begin, t_meta **meta)
{
	char	*tmp;

	tmp = NULL;
	if (!begin && errno)
	{
		ft_putstr_fd("ls: ", 2);
		ft_putstr_fd(ft_strrchr(PATH, '/') + 1, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		errno = 0;
	}
	if (begin && PRINT_LINE && !IS_SINGLE)
		ft_putendl((tmp = ft_strjoin("total ", ft_itoa(PADDING.total_size))));
	if (tmp)
		free(tmp);
	while (begin)
	{
		if (PRINT_LINE)
			ft_print_line(begin, meta);
		else
			ft_putendl(begin->name);
		begin = begin->next;
	}
}
