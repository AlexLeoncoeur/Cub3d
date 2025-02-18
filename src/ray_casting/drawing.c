/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:04:50 by aarenas-          #+#    #+#             */
/*   Updated: 2025/02/18 18:05:04 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	find_wall_side(t_game_core *game, t_ray *ray)
{
	if (ray->v_h == 0)
	{
		ray->wall_side = game->pj->y + ray->real_distance * sin(ray->rangle);
		ray->wall_side = ray->wall_side / 16;
	}
	else if (ray->v_h == 1)
	{
		ray->wall_side = game->pj->x + ray->real_distance * cos(ray->rangle);
		ray->wall_side = ray->wall_side / 16;
	}
	ray->wall_side -= floor(ray->wall_side);
	if (ray->wall_side < 0)
		ray->wall_side += 1.0;
	if (ray->wall_side > 1.0)
		ray->wall_side -= 1.0;
	game->data->tx = (int)(ray->wall_side * 64);
	if (game->data->tx >= 64)
		game->data->tx = 63;
	if (game->data->tx < 0)
		game->data->tx = 0;
}

static void	ft_wall_thickness(mlx_image_t *image, t_wall *wall, t_ray *ray, t_game_core *game)
{
	int	texture;
	int	tx;
	int	ty;

	texture = 0;
	tx = (int)(game->data->tx);
	ty = (int)(game->data->ty);
	if (ray->v_h == 0)
	{
		if ((ray->rangle <= (PI / 2) || ray->rangle > (3 * PI) / 2)) //Este, amarillo
			texture = get_rgba(game->data->texture_buffer[0][(int)(ty * 64 + tx) * 4], game->data->texture_buffer[0][(int)(ty * 64 + tx) * 4 + 1], game->data->texture_buffer[0][(int)(ty * 64 + tx) * 4 + 2], 255);
		else//Oeste, rojo
			texture = get_rgba(game->data->texture_buffer[3][(int)(ty * 64 + tx) * 4], game->data->texture_buffer[3][(int)(ty * 64 + tx) * 4 + 1], game->data->texture_buffer[3][(int)(ty * 64 + tx) * 4 + 2], 255);
	}
	else if (ray->v_h == 1)
	{
		if (ray->rangle < (PI) && ray->rangle > (0)) //Sur, rosa
			texture = get_rgba(game->data->texture_buffer[1][(int)(ty * 64 + tx) * 4], game->data->texture_buffer[1][(int)(ty * 64 + tx) * 4 + 1], game->data->texture_buffer[1][(int)(ty * 64 + tx) * 4 + 2], 255);
		else//Norte, azul
			texture = get_rgba(game->data->texture_buffer[2][(int)(ty * 64 + tx) * 4], game->data->texture_buffer[2][(int)(ty * 64 + tx) * 4 + 1], game->data->texture_buffer[2][(int)(ty * 64 + tx) * 4 + 2], 255);
	}
	mlx_put_pixel(image, ray->count, wall->y + wall->y_offset, texture);
}

static void	draw_wall_lines(mlx_image_t *image, t_ray *ray, t_wall *wall, t_game_core *game, int i)
{
	float	dx;
	float	dy;
	float	steps;
	float	increment_x;
	float	increment_y;

	wall->x = ray->rx;
	wall->y = 0;
	game->data->ty = (game->data->ty_step * game->data->ty_off);
	find_wall_side(game, ray);
	dx = fabs(ray->rx - wall->x);
	dy = fabs((wall->lineheight) - wall->y);
	steps = fmax(dx, dy);
	increment_x = dx / steps; //increments each axis to know which points to draw
	increment_y = dy / steps;
	while (++i < steps)//to draw the points between the start (p1) and end (p2) point
	{
		ft_wall_thickness(image, wall, ray, game);
		if (ray->rx < wall->x)
			wall->x -= increment_x;
		else
			wall->x += increment_x;
		if (wall->lineheight < wall->y)
			wall->y -= increment_y;
		else
			wall->y += increment_y;
		game->data->ty += game->data->ty_step;
	}
}

void	ft_manage_3d_walls(t_game_core *game, t_ray *ray)
{
	t_wall	*wall;

	wall = malloc(sizeof(t_wall));
	if (!wall)
		exit(EXIT_FAILURE);
	ray->a_cos = ray->rangle - game->pj->pangle;
	if (ray->a_cos < 0)
		ray->a_cos += 2 * PI;
	if (ray->a_cos >= 2 * PI)
		ray->a_cos -= 2 * PI;
	ray->real_distance = ray->total_dis;
	ray->total_dis = ray->total_dis * cos(ray->a_cos);
	ray->total_dis = fmax(ray->total_dis, 0.0001);
	wall->lineheight = (16 * game->data->height) / ray->total_dis; //cube size * wall desired height. Distance to wall changes size
	game->data->ty_step = 64 / wall->lineheight;
	game->data->ty_off = 0;
	if (wall->lineheight > game->data->height)
	{
		game->data->ty_off = (wall->lineheight - game->data->height) / 2;
		wall->lineheight = game->data->height;
	}
	wall->y_offset = (game->data->height / 2) - (wall->lineheight / 2);
	draw_wall_lines(game->img, ray, wall, game, -1);
}

static void	ft_draw_pj_icon(mlx_image_t *image, t_player *pj)
{
	mlx_put_pixel(image, pj->pic_x, pj->pic_y, get_rgba(51, 255, 246, 255));
	mlx_put_pixel(image, pj->pic_x, pj->pic_y + 1, get_rgba(51, 255, 246, 255));
	mlx_put_pixel(image, pj->pic_x + 1, pj->pic_y, get_rgba(51, 255, 246, 255));
	mlx_put_pixel(image, pj->pic_x, pj->pic_y - 1, get_rgba(51, 255, 246, 255));
	mlx_put_pixel(image, pj->pic_x - 1, pj->pic_y, get_rgba(51, 255, 246, 255));
}

void	draw_pj(mlx_image_t *image, t_player *pj, int i)
{
	double	dx;
	double	dy;
	double	steps;
	double	increment_x;
	double	increment_y;

	pj->pic_x = pj->x;
	pj->pic_y = pj->y;
	dx = fabs(pj->pdx * 5);
	dy = fabs(pj->pdy * 5);
	steps = fmax(dx, dy);
	increment_x = dx / steps; //increments each axis to know which points to draw
	increment_y = dy / steps;
	while (++i < steps - 8) //to draw the points between the start (p1) and end (p2) point
	{
		ft_draw_pj_icon(image, pj);
		if (pj->pdx + pj->x < pj->x)
			pj->pic_x -= increment_x;
		else
			pj->pic_x += increment_x;
		if (pj->pdy + pj->y < pj->y)
			pj->pic_y -= increment_y;
		else
			pj->pic_y += increment_y;
	}
}

void	draw_ray_line(mlx_image_t *image, t_player *pj, t_ray *ray, int i)
{
	float	dx;
	float	dy;
	float	steps;
	float	increment_x;
	float	increment_y;

	pj->pic_x = pj->x;
	pj->pic_y = pj->y;
	dx = fabs(ray->rx - pj->pic_x);
	dy = fabs(ray->ry - pj->pic_y);
	steps = fmax(dx, dy);
	increment_x = dx / steps; //increments each axis to know which points to draw
	increment_y = dy / steps;
	while (++i < steps && pj->pic_x > 0 && pj->pic_x < 1280 && pj->pic_y > 0 && pj->pic_y < 720) //to draw the points between the start (p1) and end (p2) point
	{
		mlx_put_pixel(image, pj->pic_x, pj->pic_y, get_rgba(165, 51, 255, 255));
		if (ray->rx < pj->x)
			pj->pic_x -= increment_x;
		else
			pj->pic_x += increment_x;
		if (ray->ry < pj->y)
			pj->pic_y -= increment_y;
		else
			pj->pic_y += increment_y;
	}
}
