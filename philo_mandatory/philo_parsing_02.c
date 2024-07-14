/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing_02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:00:12 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/14 13:20:34 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"

size_t	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (2048);
	else
		return (0);
}

int	ft_is_sign(char sign, char c)
{
	return (c == sign);
}

int	ft_isother(int c)
{
	if (c >= '!' && c <= '*')
		return (1);
	else if (c == ',' || c == '.' || c == '/')
		return (1);
	else if (c >= ':' && c <= 127)
		return (1);
	return (0);
}

void	check_validity(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_is_sign('-', str[i]))
			exit_error_message("Value not conform\n");
		if (ft_is_sign('+', str[i]) && (!str[i + 1] || ft_isdigit(str[i - 1]) != 0))
			exit_error_message("Value not conform\n");
		else if (ft_is_sign('+', str[i]) && str[i + 1] == ' ')
			exit_error_message("Value not conform\n");
		else if (ft_is_sign('+', str[i]) && ft_is_sign('+', str[i + 1]))
			exit_error_message("Value not conform\n");
		else if (ft_isother(str[i]) == 1)
			exit_error_message("Value not conform -> args must be integers\n");
		i++;
	}
}