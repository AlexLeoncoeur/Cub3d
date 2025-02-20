/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:38:37 by jcallejo          #+#    #+#             */
/*   Updated: 2025/02/20 11:58:06 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_aux_trim(t_data *data, char **arr, char *line)
{
	char	*temp;

	temp = ft_strtrim(arr[1], "\n");
	if (!ft_strncmp(line, "NO ", 3))
		data->text_paths.north = ft_strdup(temp);
	else if (!ft_strncmp(line, "SO ", 3))
		data->text_paths.south = ft_strdup(temp);
	else if (!ft_strncmp(line, "WE ", 3))
		data->text_paths.west = ft_strdup(temp);
	else if (!ft_strncmp(line, "EA ", 3))
		data->text_paths.east = ft_strdup(temp);
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		ft_set_colors(data, arr);
	free(temp);
	ft_clean_array(arr);
}

void	ft_texture_check(t_data *data)
{
	int	fd;

	if (!data->text_paths.east || !data->text_paths.north
		|| !data->text_paths.south || !data->text_paths.west)
		ft_errors(data, ERR_CUST, "Missing or misplaced textures");
	fd = open(data->text_paths.east, O_RDONLY);
	if (fd < 0)
		ft_errors(data, ERR_CUST, "Invalid east fd");
	close(fd);
	fd = open(data->text_paths.north, O_RDONLY);
	if (fd < 0)
		ft_errors(data, ERR_CUST, "Invalid north fd");
	close(fd);
	fd = open(data->text_paths.south, O_RDONLY);
	if (fd < 0)
		ft_errors(data, ERR_CUST, "Invalid south fd");
	close(fd);
	fd = open(data->text_paths.west, O_RDONLY);
	if (fd < 0)
		ft_errors(data, ERR_CUST, "Invalid west fd");
	close(fd);
	if (!data->floor)
		ft_errors(data, ERR_CUST, "Invalid floor color");
	if (!data->sky)
		ft_errors(data, ERR_CUST, "Invalid sky color");
}
