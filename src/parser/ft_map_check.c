/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:22:37 by jcallejo          #+#    #+#             */
/*   Updated: 2025/01/21 13:17:15 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	ft_check_arround(t_data *data, int i, int j)
{
	if (i == 0 || j == 0 || !data->map[i + 1][j] || !data->map[i][j + 1]
		|| !data->map[i + 1][j + 1])
		ft_errors(data, ERR_CUST, "Open map, missing walls");
	if (data->map[i + 1][j] != '1' && data->map[i + 1] != '0'
		&& data->map[i + 1][j] != ' ') && //aqui falta acabar la condicion
}

static void	ft_wall_check(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '0')
				ft_check_arround(data, i, j);
			j++;
		}
		i++;
	}
}

static int	ft_count_chars(char **map, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static void	ft_character_check(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[j])
		{
			if (data->map[i][j] != '1' && data->map[i][j] != '0'
				&& data->map[i][j] != ' ' && data->map[i][j] != 'N'
				&& data->map[i][j] != 'S' && data->map[i][j] != 'E'
				&& data->map[i][j] != 'W')
				ft_errors(data, ERR_CUST, "Invalid character in map");
			j++;
		}
		i++;
	}
}

void	ft_map_check(t_data *data)
{
	int	count;

	count = 0;
	ft_character_check(data);
	count += ft_count_chars(data->map, 'N');
	count += ft_count_chars(data->map, 'S');
	count += ft_count_chars(data->map, 'E');
	count += ft_count_chars(data->map, 'W');
	if (count != 1)
		ft_errors(data, ERR_CUST, "Invalid, duplicated or non existent player");
	if (data->player->x == 0 || data->player->y == 0)
		ft_errors(data, ERR_CUST, "Invalid player position");
	ft_wall_check(data);
}
