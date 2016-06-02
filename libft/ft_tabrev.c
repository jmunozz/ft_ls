#include "Includes/libft.h"

//size = taille du tableau 'NULL' compris.

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
