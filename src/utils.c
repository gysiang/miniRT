/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:16:11 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/19 15:16:26 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char *normalize_whitespace(const char *str)
{
	char *cleaned_str;
	int i = 0;
	int	j = 0;
	int	space_found = 0;

	cleaned_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!cleaned_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\t')
			cleaned_str[j++] = ' ';
		else if (ft_isspace(str[i]))
		{
			if (!space_found)
			{
				cleaned_str[j++] = ' ';
				space_found = 1;
			}
		}
		else
		{
			cleaned_str[j++] = str[i];
			space_found = 0;
		}
		i++;
	}
	cleaned_str[j] = '\0';
	return (cleaned_str);
}
