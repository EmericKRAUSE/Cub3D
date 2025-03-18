/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/11 15:48:26 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

int	param_missing_but_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->textures.ceiling.r == UNSET_COLOR)
		return (TRUE);
	if (game->textures.floor.r == UNSET_COLOR)
		return (TRUE);
	while (i < 4)
	{
		if (game->textures.f_names[i] == NULL)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	param_missing(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.tab == NULL)
		clean_exit(game, "[param_missing] map is missing", ERR_MAP);
	if (game->textures.ceiling.r == UNSET_COLOR)
		clean_exit(game, "[param_missing] ceiling is missing", ERR_MAP);
	if (game->textures.floor.r == UNSET_COLOR)
		clean_exit(game, "[param_missing] floor is missing", ERR_MAP);
	while (i < 4)
	{
		if (game->textures.f_names[i] == NULL)
			clean_exit(game, "[param_missing] texture is missing", ERR_MAP);
		i++;
	}
	return (FALSE);
}
