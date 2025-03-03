/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/02/18 21:07:40 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int tab_len(char **tab)
{
    int len;

    len = 0;
    if (tab)
        while (tab[len])
            len++;
    return (len);
}

char **append_tab(char **tab, char *str)
{
    char **ret;
    int len;

    len = tab_len(tab);
    ret = malloc((len + 2) * sizeof(char *));
    if (!ret)
        return (NULL);
    ret[len] = str;
    ret[len + 1] = NULL;
    if (tab)
        while (len--)
            ret[len] = tab[len];
    if (tab)
        free(tab);
    return (ret);
}