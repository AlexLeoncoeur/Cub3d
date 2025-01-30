/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:22:37 by jcallejo          #+#    #+#             */
/*   Updated: 2025/01/30 13:51:37 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	ft_init_data(t_data *data)
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

static void	ft_init_mlx(t_data *data)
{
	data->mlx = mlx_init(data->width, data->height, "cub3D", false);
	if (!data->mlx)
		ft_errors(data, ERR_MLX, NULL);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img)
		ft_errors(data, ERR_MLX, NULL);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
		ft_errors(data, ERR_MLX, NULL);
}

static char	*ft_clean_textures(char *texture)
{
	char	*remove;

	if (texture)
	{
		remove = ft_strtrim(texture, " ");
		free(texture);
		return (remove);
	}
	return (NULL);
}

void	ft_init(t_data *data, char *file)
{
	ft_init_data(data);
	ft_init_mlx(data);
	ft_main_parser(data, file);
	data->text_paths.east = ft_clean_textures(data->text_paths.east);
	data->text_paths.north = ft_clean_textures(data->text_paths.north);
	data->text_paths.south = ft_clean_textures(data->text_paths.south);
	data->text_paths.west = ft_clean_textures(data->text_paths.west);
	ft_map_check(data);
	ft_texture_check(data);
}
