/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 12:49:50 by jmunoz            #+#    #+#             */
/*   Updated: 2016/06/03 12:49:58 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

void	ft_tabrev(char **tab, size_t size)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (tab)
	{
		while (i < --size)
		{
			tmp = tab[i];
			tab[i] = tab[size];
			tab[size] = tmp;
			i++;
		}
	}
}
