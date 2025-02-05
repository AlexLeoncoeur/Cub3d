/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_position.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:14:13 by jcallejo          #+#    #+#             */
/*   Updated: 2025/02/05 16:54:26 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	ft_map_measuring(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
			j++;
		if (j > data->map_longest_col)
			data->map_longest_col = j;
		i++;
	}
	data->map_rows = i;
}

void	ft_player_coords(t_data *data, char **map)
{
	int	i;
	int	j;
	int	coords[2];

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'E'
				|| map[j][i] == 'W')
			{
				coords[0] = i;
				coords[1] = j;
				data->player->start_x = coords[0];
				data->player->start_y = coords[1];
				ft_map_measuring(data);
				return ;
			}
			i++;
		}
		j++;
	}
}
