/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:35:55 by aarenas-          #+#    #+#             */
/*   Updated: 2024/12/12 13:42:51 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "colors.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

/*ERROR CODES*/
# define ERR_SYS		1
# define ERR_FD			2
# define ERR_TEXT		3
# define ERR_COLOR		4

typedef struct s_player
{
	int				x;
	int				y;
	mlx_image_t		*img;
}	t_player;

typedef struct s_game_core
{
	mlx_t			*id;
	t_player		*pj;
}	t_game_core;

typedef struct s_paths
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_paths;

typedef struct s_data
{
	char 			**map;
	t_player 		*player;
	mlx_t			*mlx;
	mlx_image_t		*img;
	int32_t			width;
	int32_t			height;
	uint32_t		sky;
	uint32_t		floor;
	mlx_texture_t	*n_wall;
	mlx_texture_t	*s_wall;
	mlx_texture_t	*e_wall;
	mlx_texture_t	*w_wall;
	t_paths			text_paths;
}	t_data;


/* -- main.c -- */
void	ft_resize(int width, int height, void *param);

/* -- movement.c -- */
void	move_up(t_game_core *game);
void	move_down(t_game_core *game);
void	move_left(t_game_core *game);
void	move_right(t_game_core *game);

/* -- parser.c -- */

/**
 * @brief Function that handles all the parsing of the map
 * 
 * @param data 
 * @param file 
 */
void	ft_main_parser(t_data *data, char *file);

/* -- ft_exit.c -- */

/**
 * @brief Guess what this does, displays an error based on error code provided
 * 
 * @param data 
 * @param error 
 * @param msg 
 */
void	ft_errors(t_data *data, int error, char *msg);

/**
 * @brief Exits the whole program, who would have guessed
 * 
 * @param data 
 * @param status 
 */
void	ft_exit(t_data *data, int status);

/**
 * @brief Cleans arrays, duh
 * 
 * @param array 
 */
void	ft_clean_array(char **array);

#endif