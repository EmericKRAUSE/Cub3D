/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/10 18:28:40 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

int	is_map_available(t_game *game)
{
	if (game->map.tab == NULL)
		return (FALSE);
	if (!one_player_only(game, game->map.tab))
		return (FALSE);
	if (!is_map_closed(game->map.tab))
		return (FALSE);
	return (TRUE);
}
