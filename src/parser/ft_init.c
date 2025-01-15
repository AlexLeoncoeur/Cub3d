/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:22:37 by jcallejo          #+#    #+#             */
/*   Updated: 2025/01/15 13:37:41 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void ft_init_data(t_data *data)
{
    data->width = 1280;
    data->height = 720;
    data->sky = 0;
    data->floor = 0;
    data->text_paths.east = NULL;
    data->text_paths.north = NULL;
    data->text_paths.south = NULL;
    data->text_paths.west = NULL;
    data->n_wall = NULL;
    data->s_wall = NULL;
    data->e_wall = NULL;
    data->w_wall = NULL;
}

static void    ft_init_mlx(t_data *data)
{
    data->mlx = mlx_init(data->width, data->height, "cub3D", false);
    if (!data->mlx)
        ft_errors(data, ERR_MLX, NULL);
    data->img = mlx_new_image(data->mlx, data->width, data->height);
    if (!data->img)
        ft_error(data, ERR_MLX, NULL);
    if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
        ft_error(data, ERR_MLX, NULL);
}

void    ft_init(t_data *data, char *file)
{
    ft_init_data(data);
    ft_init_mlx(data);
}
