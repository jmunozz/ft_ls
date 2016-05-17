/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 09:14:11 by jmunoz            #+#    #+#             */
/*   Updated: 2016/05/17 14:44:20 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <errno.h>
# include <dirent.h>
# include <stdio.h>
# include <grp.h>
# include <uuid/uuid.h>
# include "../libft/Includes/libft.h"

# define OPTIONS_LST "Ralrt"
# define OPTIONS_NBR 5
# define OPTIONS (*meta)->options
# define IS_SINGLE ((*meta)->options & (1 << 5))
# define SORT_REVERT ((*meta)->options & (1 << 3))
# define SORT_TIME ((*meta)->options & (1 << 4))
# define PRINT_LINE ((*meta)->options & (1 << 2))
# define PRINT_HIDDEN ((*meta)->options & (1 << 1))
# define RECURSIVE ((*meta)->options & (1 << 0))
# define PADDING (*meta)->padding
# define PATH (*meta)->path
# define LINE_SIZE 256 + 1
# define MINOR_MASK (1 << 20) - 1
# define SIXMONTH 15778800
# define SEC current->info.st_mtimespec.tv_sec

typedef struct		s_padding
{
	size_t	link;
	size_t	usr;
	size_t	grp;
	size_t	size;
	int		total_size;
	size_t	minor;
	size_t	major;
}					t_padding;

typedef struct		s_meta
{
	char		first;
	int			options;
	char		*path;
	t_padding	padding;
}					t_meta;

typedef struct		s_lst
{
	char			*name;
	struct stat		info;
	struct s_lst	*next;
}					t_lst;

t_lst				*ft_build_lst(DIR *stream, t_meta **meta);
void				lst_free(t_lst *current);
t_lst				*do_lst(char *str, t_meta **meta);

int					ft_get_options(int ac, char **av, t_meta **meta);
t_meta				*ft_init_meta(void);
void				ft_free_meta(t_meta *meta);
void				ft_init_padding(t_meta **meta);

void				get_padding(t_meta **meta, t_lst *current);
void				ft_print_all(t_lst *begin, t_meta **meta);
void				ft_print_line(t_lst *current, t_meta **meta);

char				ft_get_type(mode_t mode);
char				*ft_get_mode(mode_t mode);
char				*ft_get_usr_id(uid_t id);
char				*ft_get_grp_id(gid_t id);
char				*ft_get_time(struct timespec time);
size_t				ft_get_padding_minmaj(t_meta **meta, dev_t dev);

int					sort_lst_lexico(t_lst *a, t_lst *b);
int					sort_lst_time(t_lst *a, t_lst *b);
t_lst				*sort_lst_revert(t_lst *begin);
char				*manage_path(char *str, t_meta **meta, int mode);
void				ft_errors(char *str);
void				ft_print_arg(t_meta **meta, char *str, int i);

void				ft_ls(char *str, t_meta **meta);
void				print_options(t_meta **meta);

void				ft_print_arg(t_meta **meta, char *str, int i);

#endif
