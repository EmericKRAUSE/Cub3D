/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_types_fixed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:14:15 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/11 17:22:09 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

int	is_blank_line(char *line)
{
	if (!line)
		return (FALSE);
	else
		while (*line)
			if (!ft_strchr(BLANK_CHAR, *line++))
				return (FALSE);
	return (TRUE);
}

int	is_map(char *line)
{
	if (!line)
		return (FALSE);
	else if (*line == '\n')
		return (FALSE);
	else
		while (*line)
			if (!ft_strchr(MAP_CHARS, *line++))
				return (FALSE);
	return (TRUE);
}

int	is_texture(t_game *game, char *line)
{
	char	**texture_balise;
	int		i;
	int		found;

	texture_balise = ft_split(TEXTURES_BALISE, '/');
	if (!texture_balise)
		clean_exit(game, "Error: malloc failed", ERR_MALLOC);
	i = 0;
	found = FALSE;
	if (!line)
		return (FALSE);
	else
		while (texture_balise[i] && !found)
			if (ft_strncmp(line, texture_balise[i++], 3) == CMP_FOUND)
				found = TRUE;
	ft_free_split(&texture_balise);
	return (found);
}

// is_rgb return if the string contains 3 numbers in the range 0 - 255
// and separated by a ',';
int	is_rgb(char *str)
{
	int	i;
	int	count;
	int	nb;

	i = 0;
	count = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			nb = nb * 10 + (str[i] - '0');
		else if (str[i] == ',')
		{
			count++;
			nb = 0;
		}
		else if (nb > 255)
			return (FALSE);
		else if (!ft_strchr(BLANK_CHAR, str[i]))
			return (FALSE);
		i++;
	}
	return (count == 2 && nb <= 255);
}

int	is_color(char *line)
{
	if (*line == 'F' || *line == 'C')
		line = ft_get_next_wd(line, ' ');
	return (is_rgb(line));
}
