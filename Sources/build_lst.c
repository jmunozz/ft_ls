/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 10:03:22 by jmunoz            #+#    #+#             */
/*   Updated: 2016/05/17 15:49:20 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_add_sort_lst(t_lst **begin_list, t_lst *current, int (*cmp)())
{
	t_lst	*elem;
	t_lst	*prev;

	if (!current)
		return ;
	elem = *begin_list;
	prev = 0;
	while (elem && (*cmp)(current, elem) > 0)
	{
		prev = elem;
		elem = elem->next;
	}
	if (prev)
		prev->next = current;
	else
		*begin_list = current;
	current->next = elem;
}

t_lst	*do_lst(char *str, t_meta **meta)
{
	t_lst	*current;

	current = (t_lst*)malloc(sizeof(t_lst));
	current->name = ft_strdup(str);
	if ((lstat(manage_path(str, meta, 1), &(current->info)) == -1))
		perror("do_lst");
	manage_path(str, meta, 2);
	current->next = NULL;
	return (current);
}

void	lst_free(t_lst *current)
{
	free(current->name);
	free(current);
	current = NULL;
}

t_lst	*ft_build_lst(DIR *stream, t_meta **meta)
{
	struct dirent	*file;
	t_lst			*begin;
	t_lst			*current;
	int				(*cmp)(t_lst*, t_lst*);

	begin = NULL;
	cmp = (SORT_TIME) ? &sort_lst_time : &sort_lst_lexico;
	while ((file = readdir(stream)) != NULL)
	{
		current = do_lst(file->d_name, meta);
		if (current->name[0] == '.' && PRINT_HIDDEN == 0)
		{
			lst_free(current);
			current = NULL;
		}
		get_padding(meta, current);
		ft_add_sort_lst(&begin, current, cmp);
	}
	if (SORT_REVERT)
		begin = sort_lst_revert(begin);
	return (begin);
}

void	get_padding(t_meta **meta, t_lst *current)
{
	size_t			temp;
	struct passwd	*user;
	struct group	*grp;

	if (!current)
		return ;
	PADDING.total_size += (current->info.st_blocks);
	if ((temp = ft_nbr_len((int)current->info.st_nlink)) > (PADDING.link))
		PADDING.link = temp;
	user = getpwuid(current->info.st_uid);
	temp = (user != NULL) ? ft_strlen(user->pw_name)
			: ft_nbr_len(current->info.st_uid);
	if (temp > PADDING.usr)
		PADDING.usr = temp;
	grp = getgrgid(current->info.st_gid);
	temp = (grp != NULL) ? ft_strlen(grp->gr_name)
			: ft_nbr_len(current->info.st_gid);
	if (temp > PADDING.grp)
		PADDING.grp = temp;
	temp = (ft_get_type(current->info.st_mode) == 'c' ||
			ft_get_type(current->info.st_mode) == 'b') ?
		ft_get_padding_minmaj(meta, current->info.st_rdev) :
		ft_nbr_len(current->info.st_size);
	if (temp > PADDING.size)
		PADDING.size = temp;
}
