/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_infos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 16:02:07 by jmunoz            #+#    #+#             */
/*   Updated: 2016/04/20 17:21:49 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	ft_get_type(mode_t mode)
{
	char c;

	c = '\0';
	if (S_ISBLK(mode))
		c = 'b';
	else if (S_ISCHR(mode))
		c = 'c';
	else if (S_ISDIR(mode))
		c = 'd';
	else if (S_ISLNK(mode))
		c = 'l';
	else if (S_ISFIFO(mode))
		c = 'p';
	else if (S_ISWHT(mode))
		c = '?';
	else if (S_ISSOCK(mode))
		c = 's';
	else if (S_ISREG(mode))
		c = '-';
	return (c);
}

char	*ft_get_mode(mode_t mode)
{
	char *str;

	str = ft_strnew(9);
	str[0] = ((mode & S_IRUSR) != 0) ? 'r' : '-';
	str[1] = ((mode & S_IWUSR) != 0) ? 'w' : '-';
	str[2] = ((mode & S_IXUSR) != 0) ? 'x' : '-';
	str[2] = ((mode & S_ISUID) != 0 && str[2] == 'x') ? 's' : str[2];
	str[2] = ((mode & S_ISUID) != 0 && str[2] == '-') ? 'S' : str[2];
	str[3] = ((mode & S_IRGRP) != 0) ? 'r' : '-';
	str[4] = ((mode & S_IWGRP) != 0) ? 'w' : '-';
	str[5] = ((mode & S_IXGRP) != 0) ? 'x' : '-';
	str[5] = ((mode & S_ISGID) != 0 && str[5] == 'x') ? 's' : str[5];
	str[5] = ((mode & S_ISGID) != 0 && str[5] == '-') ? 'S' : str[5];
	str[6] = ((mode & S_IROTH) != 0) ? 'r' : '-';
	str[7] = ((mode & S_IWOTH) != 0) ? 'w' : '-';
	str[8] = ((mode & S_IXOTH) != 0) ? 'x' : '-';
	str[8] = ((mode & S_ISVTX) != 0) && str[8] == 'x' ? 't' : str[8];
	str[8] = ((mode & S_ISVTX) != 0) && str[8] == '-' ? 'T' : str[8];
	return (str);
}

char	*ft_get_usr_id(uid_t id)
{
	struct passwd *user;

	user = getpwuid(id);
	if (user)
		return (ft_strdup(user->pw_name));
	return (ft_itoa(id));
}

char	*ft_get_grp_id(gid_t id)
{
	struct group *grp;

	grp = getgrgid(id);
	if (grp)
		return (ft_strdup(grp->gr_name));
	return (ft_itoa(id));
}

size_t	ft_get_padding_minmaj(t_meta **meta, dev_t dev)
{
	size_t minor;
	size_t major;

	minor = dev & MINOR_MASK;
	major = dev >> 20;
	PADDING.minor = (ft_nbr_len(minor) > PADDING.minor)
				? ft_nbr_len(minor) : PADDING.minor;
	PADDING.major = (ft_nbr_len(major) > PADDING.major)
				? ft_nbr_len(major) : PADDING.major;
	return (PADDING.major + PADDING.minor + 2);
}
