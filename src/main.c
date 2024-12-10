/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:56:25 by aarenas-          #+#    #+#             */
/*   Updated: 2024/12/10 13:05:35 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_resize(int width, int height, void *param)
{
	(void)param;
	(void)width;
	(void)height;
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
}

int	main(void)
{
	mlx_t			*id;
	mlx_image_t		*img;

	id = mlx_init(1920, 1080, "cub3d", true);
	if (!id)
		exit(EXIT_FAILURE);
	img = mlx_new_image(id, 1920, 1080);
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	mlx_image_to_window(id, img, 0, 0);
	mlx_resize_hook(id, ft_resize, NULL);
	mlx_loop(id);
	mlx_terminate(id);
	return (0);
}
	//t_game_core		*data; //estructura con datos del mapa y juego

	/* if (!id)
		ft_error_exit("Error: Could not initialize identifier\n"); */