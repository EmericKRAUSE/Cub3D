/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/11 13:10:34 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	tab_len(char **tab)
{
	int	len;

	len = 0;
	if (tab)
		while (tab[len])
			len++;
	return (len);
}

char	**append_tab(char **tab, char *str)
{
	char	**ret;
	int		len;

	len = tab_len(tab);
	ret = ft_calloc((len + 2), sizeof(char *));
	if (!ret)
	{
		ft_free_split(&tab);
		return (NULL);
	}
	ret[len] = str;
	ret[len + 1] = NULL;
	if (tab)
		while (len--)
			ret[len] = tab[len];
	free(tab);
	return (ret);
}
