#include "Includes/libft.h"

int		main(int ac, char **av)
{
	int i;

	i = -1;
	ft_tabrev(&av[1], ac - 1);
	while (++i < ac)
		printf("%s\n", av[i]);
	return (0);
}
