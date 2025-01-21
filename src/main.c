/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:55:55 by jcallejo          #+#    #+#             */
/*   Updated: 2025/01/21 11:03:58 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	ft_check_cub(char *name)
{
	char	*aux;

	aux = name;
	while (*aux)
		aux++;
	while (name < aux)
	{
		if (*aux == '.')
			if (*aux + 1 && *aux + 2 && *aux + 3)
				if (aux[1] == 'c' && aux[2] == 'u' && aux[3] == 'b' && !aux[4])
					return (1);
		aux--;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	if (argc != 2)
		ft_errors(&data, ERR_ARGC, NULL);
	if (ft_check_cub(argv[1]) != 1)
		ft_errors(&data, ERR_EXT, NULL);
	ft_init(&data, argv[1]);
}
