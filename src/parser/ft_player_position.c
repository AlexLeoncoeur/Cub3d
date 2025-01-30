/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_position.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:14:13 by jcallejo          #+#    #+#             */
/*   Updated: 2025/01/09 11:25:39 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_player_coords(t_data *data, char **map)
{
	int	i;
	int	j;
	int	coords[2];

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				coords[0] = i;
				coords[1] = j;
				data->player->x = coords[0];
				data->player->y = coords[1];
				return (coords);
			}
			j++;
		}
	}
	return (NULL);
}
