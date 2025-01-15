/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:56:25 by aarenas-          #+#    #+#             */
/*   Updated: 2025/01/15 17:15:45 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//Algoritmo de Bresenham
static void	draw_pj(mlx_image_t *image, t_player *pj)
{
	float	dx;
	float	dy;
	float	steps;
	float	increment_x;
	float	increment_y;
	float	x;
	float	y;
	int		i;

	i = 0;
	x = pj->x;
	y = pj->y;
	dx = fabs(pj->pdx * 5);
	dy = fabs(pj->pdy * 5);
	steps = fmax(dx, dy);
	increment_x = dx / steps; //increments each axis to know which points to draw
	increment_y = dy / steps;
	while (i < steps) //to draw the points between the start (p1) and end (p2) point
	{
		mlx_put_pixel(image, x, y, get_rgba(51, 255, 246, 255));
		mlx_put_pixel(image, x, y + 1, get_rgba(51, 255, 246, 255));
		mlx_put_pixel(image, x + 1, y, get_rgba(51, 255, 246, 255));
		mlx_put_pixel(image, x, y - 1, get_rgba(51, 255, 246, 255));
		mlx_put_pixel(image, x - 1, y, get_rgba(51, 255, 246, 255));
		if (pj->pdx + pj->x < pj->x)
			x -= increment_x;
		else
			x += increment_x;
		if (pj->pdy + pj->y < pj->y)
			y -= increment_y;
		else
			y += increment_y;
		i++;
	}
}

void	ft_controls_hook(mlx_key_data_t keydata, void *param)
{
	t_game_core	*game;

	game = (t_game_core *)param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			exit(0); //funcion para liberar memoria
			mlx_close_window(game->id);
		}
		if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
			move_up(game);
		if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
			move_down(game);
		if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
			move_left(game);
		if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
			move_right(game);
	}
}

void	ft_resize(int width, int height, void *param)
{
	(void)param;
	(void)width;
	(void)height;
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
}

void	ft_draw_player(t_game_core *game, mlx_image_t *img, int pj_x, int pj_y)
{
	int	i;
	int	j;
	int	z;
	mlx_image_t	*image;

	z = game->pj->pdx;
	i = game->pj->x;
	j = game->pj->y;
	image = img;
	if (pj_x < 0 && pj_y > 0)
		printf("hola");
	draw_pj(game->img, game->pj);
	i = -8;
	while (i < 8)
	{
		j = -8;
		while (j < 8)
		{
			mlx_put_pixel(image, game->pj->x + i, game->pj->y + j, get_rgba(51, 255, 246, 255));
			j++;
		}
		i++;
	}
}

/* void	ft_draw_pixels(void *param)
{
	int			x;
	int			y;
	t_game_core	*game;

	x = 0;
	y = 0;
	game = (t_game_core *)param;
	game->current_time = ft_get_time();
	if (game->current_time - game->last_time >= game->delay)
	{
		game->last_time = game->current_time;
		while (y < game->y_limit)
		{
			x = 0;
			while (x < game->x_limit)
			{
				mlx_put_pixel(game->img, x, y, 0);
				x++;
			}
			y++;
		}
		ft_draw_player(game->img, game->pj->x, game->pj->y);
	}
} */

int	main(void)
{
	mlx_t			*id;
	mlx_image_t		*img;
	t_game_core		*data;
	t_player		*pj;

	id = mlx_init(1024, 512, "cub3d", true);
	data = malloc(sizeof(t_game_core));
	pj = malloc(sizeof(t_player));
	if (!id || !data || !pj)
		exit(EXIT_FAILURE);
	img = mlx_new_image(id, 1024, 512);
	mlx_image_to_window(id, img, 0, 0);
	mlx_resize_hook(id, ft_resize, NULL);
	pj->x = 256;
	pj->y = 256;
	data->pj = pj;
	data->img = img;
	data->x_limit = 1024;
	data->y_limit = 512;
	data->last_time = ft_get_time();
	data->delay = 33;
	data->pj->pangle = 6.28;
	ft_map(data);
	mlx_loop_hook(id, &ft_draw_2d, data);
	mlx_key_hook(id, &ft_controls_hook, data);
	mlx_loop(id);
	mlx_terminate(id);
	return (0);
}
/* -- to do -- */

/* Hacer una funcion para refrescar
la pantalla y que se vea al muñeco moverse */

	//t_game_core		*data; //estructura con datos del mapa y juego

	/* if (!id)
		ft_error_exit("Error: Could not initialize identifier\n"); 
		
		
		
		
while (i >= game->pj->x + game->pj->pdx * 5 && j >= game->pj->y + game->pj->pdy * 5)
	{
		while (i >= game->pj->x + game->pj->pdx * 5)
		{
			j = game->pj->y;
			while (j >= game->pj->y + game->pj->pdy * 5)
			{
				mlx_put_pixel(img, i, j, get_rgba(200, 0, 255, 255));
				j--;
			}
			i--;
		}
	}
	while (i <= game->pj->x + game->pj->pdx * 5 && j <= game->pj->y + game->pj->pdy * 5)
	{
		while (i <= game->pj->x + game->pj->pdx * 5)
		{
			j = game->pj->y;
			while (j <= game->pj->y + game->pj->pdy * 5)
			{
				mlx_put_pixel(img, i, j, get_rgba(200, 0, 255, 255));
				j++;
			}
			i++;
		}
	}
	while (i >= game->pj->x + game->pj->pdx * 5 && j <= game->pj->y + game->pj->pdy * 5)
	{
		while (i >= game->pj->x + game->pj->pdx * 5)
		{
			j = game->pj->y;
			while (j <= game->pj->y + game->pj->pdy * 5)
			{
				mlx_put_pixel(img, i, j, get_rgba(200, 0, 255, 255));
				j++;
			}
			i--;
		}
	}
	while (i <= game->pj->x + game->pj->pdx * 5 && j >= game->pj->y + game->pj->pdy * 5)
	{
		while (i <= game->pj->x + game->pj->pdx * 5)
		{
			j = game->pj->y;
			while (j >= game->pj->y + game->pj->pdy * 5)
			{
				mlx_put_pixel(img, i, j, get_rgba(200, 0, 255, 255));
				j--;
			}
			i++;
		}
	}
	i = -16;
	while (i < 16)
	{
		j = 8;
		while (j < 16)
		{
			mlx_put_pixel(img, pj_x + i, pj_y + j, get_rgba(200, 0, 255, 255));
			j++;
		}
		i++;
	}*/