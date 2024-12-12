/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:26:39 by jcallejo          #+#    #+#             */
/*   Updated: 2024/12/12 13:21:28 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void ft_close(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		ft_exit((t_data *)param, EXIT_SUCCESS);
}

void	ft_clean_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static void ft_clean(t_data *data)
{
	if (!data->mlx)
		return ;
	if (data->n_wall)
		mlx_destroy_texture(data->mlx, data->n_wall);
	if (data->s_wall)
		mlx_destroy_texture(data->mlx, data->s_wall);
	if (data->e_wall)
		mlx_destroy_texture(data->mlx, data->e_wall);
	if (data->w_wall)
		mlx_destroy_texture(data->mlx, data->w_wall);
	if (data->text_paths.east)
		free(data->text_paths.east);
	if (data->text_paths.north)
		free(data->text_paths.north);
	if (data->text_paths.south)
		free(data->text_paths.south);
	if (data->text_paths.west)
		free(data->text_paths.west);
}

void	ft_exit(t_data *data, int status)
{
	if (data->mlx)
	{
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
	}
	ft_clean(data);
	exit(status);
}

void	ft_errors(t_data *data, int error, char *msg)
{
	printf(RED);
	if (error == ERR_SYS)
		printf("Error: System error\n");
	else if (error == ERR_FD)
		printf("Error: File descriptor error\n");
	else if (error == ERR_TEXT)
		perror(msg);
	else if (error == ERR_COLOR)
		perror(msg);
	printf(DEFAULT);
	ft_exit(data, EXIT_FAILURE);
}
