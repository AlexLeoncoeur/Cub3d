/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:22:37 by jcallejo          #+#    #+#             */
/*   Updated: 2025/02/21 12:16:27 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_set_colors(t_data *data, char **aux)
{
	uint8_t		col[3];
	char		**rgb;
	int			i;

	i = 0;
	rgb = ft_split(aux[1], ',');
	if (!rgb)
		ft_errors(data, ERR_COLOR, "Error: invalid color");
	while (rgb[i])
		i++;
	if (i < 3 && aux[0][0] != '\n')
	{
		ft_clean_array(rgb);
		ft_clean_array(aux);
		ft_errors(data, ERR_COLOR, "Error: no color");
	}
	i = -1;
	while (++i < 3)
		col[i] = ft_atoi(rgb[i]);
	if (aux[0][0] == 'F')
		data->floor = col[0] << 24 | col[1] << 16 | col[2] << 8 | 0x000000FF;
	else
		data->sky = col[0] << 24 | col[1] << 16 | col[2] << 8 | 0x000000FF;
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
	if (aux && aux[0][0] != '\n')
		ft_aux_trim(data, aux, line);
	else
		ft_clean_array(aux);
}

static char	*parse_textures(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
			|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)
			|| !ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2)
			|| !ft_strncmp(line, "\n", 1)))
	{
		if (!ft_strncmp(line, "NO ", 3) && data->text_paths.north)
			ft_errors(data, ERR_TEXT, "Error: north wall texture duplicated");
		if (!ft_strncmp(line, "SO ", 3) && data->text_paths.south)
			ft_errors(data, ERR_TEXT, "Error: south wall texture duplicated");
		if (!ft_strncmp(line, "WE ", 3) && data->text_paths.west)
			ft_errors(data, ERR_TEXT, "Error: west wall texture duplicated");
		if (!ft_strncmp(line, "EA ", 3) && data->text_paths.east)
			ft_errors(data, ERR_TEXT, "Error: east wall texture ducplicated");
		if (!ft_strncmp(line, "F ", 2) && data->floor)
			ft_errors(data, ERR_TEXT, "Error: floor color duplicated");
		if (!ft_strncmp(line, "C ", 2) && data->sky)
			ft_errors(data, ERR_TEXT, "Error: sky color duplicated");
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
		ft_errors(data, ERR_FD, NULL);
	i = 0;
	map[i] = parse_textures(data, fd);
	if (!map[i])
		ft_errors(data, ERR_CUST, "Invalid map\n");
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) == 1 && map[i][0] == '\n')
			ft_errors(data, ERR_CUST, "Map can't have empty line/s\n");
		i++;
		map[i] = get_next_line(fd);
	}
	if (map[i] && map[i][0] == '\n')
		free(map[i]);
	data->map = map;
	ft_player_coords(data, map);
	ft_map_check(data);
}
