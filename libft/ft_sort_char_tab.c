/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_char_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 15:08:41 by jmunoz            #+#    #+#             */
/*   Updated: 2016/06/03 12:49:30 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_char_tab(char **tab, size_t size,
		int (*cmp)(const char*, const char*))
{
	size_t	i;
	size_t	j;
	char	*temp;

	if (tab)
	{
		i = -1;
		while (++i < size - 1)
		{
			j = i;
			while (++j < size)
				if (cmp(tab[i], tab[j]) > 0)
				{
					temp = tab[i];
					tab[i] = tab[j];
					tab[j] = temp;
				}
		}
	}
}
