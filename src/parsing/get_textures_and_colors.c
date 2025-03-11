/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_line_fixed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/10 13:53:44 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

int	get_texture_ind_from_balise(char *balise)
{
	if (ft_strncmp(balise, "NO ", 3) == CMP_FOUND)
		return (NORTH);
	else if (ft_strncmp(balise, "SO ", 3) == CMP_FOUND)
		return (SOUTH);
	else if (ft_strncmp(balise, "WE ", 3) == CMP_FOUND)
		return (WEST);
	else if (ft_strncmp(balise, "EA ", 3) == CMP_FOUND)
		return (EAST);
	return (BALISE_ERROR);
}

int	get_texture(t_game *game, char *line)
{
	int	ind;

	ind = get_texture_ind_from_balise(line);
	if (ind == BALISE_ERROR)
		clean_exit(game, "Error: Invalid texture balise", ERR_LOADING_TEXTURE);
	return (load_texture(game, ind, line));
}

t_rgb	*get_rgb(t_game *game, char *line, t_rgb *rgb)
{
	if (rgb->b != UNSET_COLOR)
		clean_exit(game, "Error: Duplicated color", ERR_LOADING_TEXTURE);
	rgb->r = ft_atoi(line);
	line = ft_get_next_wd(line, ',');
	rgb->g = ft_atoi(line);
	line = ft_get_next_wd(line, ',');
	rgb->b = ft_atoi(line);
	return (rgb);
}

int	get_color(t_game *game, char *line)
{
	if (*line == 'F')
	{
		line = ft_get_next_wd(line, ' ');
		get_rgb(game, line, &game->textures.floor);
	}
	else if (*line == 'C')
	{
		line = ft_get_next_wd(line, ' ');
		get_rgb(game, line, &game->textures.ceiling);
	}
	return (OK);
}
