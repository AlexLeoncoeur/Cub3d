/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:22:37 by jcallejo          #+#    #+#             */
/*   Updated: 2024/12/12 13:27:18 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	set_colors(t_data *data, char **aux)
{
	uint8_t		color[3];
	char		**rgb;
	int			i;

	i = 0;
	rgb = ft_split(aux[1], ',');
	if (!rgb)
		ft_errors(data, ERR_COLOR, "error: invalid color");
	while(rgb[i])
		i++;
	if (i < 3 && aux[0][0] != '\n')
	{
		ft_clean_array(rgb);
		ft_clean_array(aux);
		ft_errors(data, ERR_COLOR, "error: no color");
	}
	i = -1;
	while (++i < 3)
		rgb[i] = ft_atoi(rgb[i]);
	if (aux[0][0] == 'F')
		data->floor = color[0] << 24 | color[1] << 16 | color[2] << 8 | 0x000000FF;
	else
		data->sky = color[0] << 24 | color[1] << 16 | color[2] << 8 | 0x000000FF;
	ft_clean_array(rgb);
}

static void	save_textures(t_data *data, char *line)
{
	char	**aux;
	int		len;
	
	len = 0;
	aux = ft_split(line, ' ');
	if (!aux)
	{
		ft_clean_array(aux);
		ft_errors(data, ERR_SYS, NULL);
	}
	while (aux[len])
		len++;
	if (len <= 1 && aux[0][0] != '\n')
		ft_errors(data, ERR_TEXT, "Error: no texture");
	if (!ft_strncmp(line, "NO ", 3))
		data->n_wall = ft_strdup(aux[1]);
	else if (!ft_strncmp(line, "SO ", 3))
		data->s_wall = ft_strdup(aux[1]);
	else if (!ft_strncmp(line, "WE ", 3))
		data->e_wall = ft_strdup(aux[1]);
	else if (!ft_strncmp(line, "EA ", 3))
		data->w_wall = ft_strdup(aux[1]);
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		set_colors(data, aux);
	ft_clean_array(aux);
}

static void	parse_textures(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) ||
			!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3) ||
			!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2) || 
			!ft_strncmp(line, "\n", 1))
	{
		if (!ft_strncmp(line, "NO ", 3) && data->text_paths.north)
			ft_error(data, ERR_TEXT, "Error: north wall texture");
		if (!ft_strncmp(line, "SO ", 3) && data->text_paths.south)
			ft_error(data, ERR_TEXT, "Error: south wall texture");
		if (!ft_strncmp(line, "WE ", 3) && data->text_paths.west)
			ft_error(data, ERR_TEXT, "Error: west wall texture");
		if (!ft_strncmp(line, "EA ", 3) && data->text_paths.east)
			ft_error(data, ERR_TEXT, "Error: east wall texture");
		if (!ft_strncmp(line, "F ", 2) && data->floor)
			ft_error(data, ERR_TEXT, "Error: floor color");
		if (!ft_strncmp(line, "C ", 2) && data->sky)
			ft_error(data, ERR_TEXT, "Error: sky color");
		save_textures(data, line);
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

static int	count_lines(char *file)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (count);
}

void	ft_main_parser(t_data *data, char *file)
{
	char	**map;
	int		fd;
	int		i;
	
	i = count_lines(file);
	map = malloc(sizeof(char *) * (i + 1));
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_errors(data, ERR_FD, NULL);
	}
	i = 0;
	parse_textures(data, fd);
}
