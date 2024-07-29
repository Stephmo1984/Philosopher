/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing_02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:00:12 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/18 19:41:08 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (2048);
	else
		return (0);
}

static int	ft_isother(int c)
{
	if (c >= '!' && c <= '*')
		return (1);
	else if (c == ',' || c == '.' || c == '/')
		return (1);
	else if (c >= ':' && c <= 127)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			*r;

	r = s;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			r = &s[i];
			return (r);
		}
		i++;
	}
	if (c == '\0')
	{
		r = &s[i];
		return (r);
	}
	return (NULL);
}

int	check_arg_validity(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-' && !ft_isdigit(str[i + 1]))
			return (error_message("Value not conform->args must be numbers\n"));
		if (str[i] == '+' && (!str[i + 1] || str[i + 1] == '+'))
			return (error_message("Value not conform -> ++ \n"));
		if (str[i] == '+' && (!str[i + 1] || str[i + 1] == ' '))
			return (error_message("Value not conform -> no space after +\n"));
		if (ft_isother(str[i]) == 1)
			return (error_message("Value not conform->args must be numbers\n"));
		i++;
	}
	return (0);
}
