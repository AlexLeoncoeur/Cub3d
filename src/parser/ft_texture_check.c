/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:38:37 by jcallejo          #+#    #+#             */
/*   Updated: 2025/02/04 10:56:28 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void    ft_texture_check(t_data *data)
{
    int    fd;

    if (!data->text_paths.east || !data->text_paths.north
        || !data->text_paths.south || !data->text_paths.west)
        ft_errors(data, ERR_CUST, "Textures are not at the start of the file");
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
