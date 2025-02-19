/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:10:46 by aarenas-          #+#    #+#             */
/*   Updated: 2025/02/19 18:11:04 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	increment_x = dx / steps;
	increment_y = dy / steps;
	while (++i < steps - 8)
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
