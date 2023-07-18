
#include "../libft/libft.h"

/*Doit recevoir av au format :
	[nimporte, option, "bail a echo1", "bail a echo2"] (deja expand etc.)
*/
void    echo(char **av)
{
	int i;
	int endline;

	i = 1;
	endline = 1;
	if (av[i] && ft_strlen(av[i]) == 2 && !ft_strncmp(av[i], "-n", 2))
	{
		endline = 0;
		i++;
	}
	while (av[i])
	{
		ft_putstr(av[i]);
		if (av[i+1])
			ft_putchar(' ');
		i++;
	}
	if (endline)
		ft_putchar('\n');
}
