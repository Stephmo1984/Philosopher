/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:00:12 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/18 23:26:09 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	len_str_or_num(char *str, unsigned long num, int len)
{
	size_t	i;

	i = 0;
	if (!num)
	{
		while ((str[i] == ' ' || str[i] == '0' || str[i] == '+') && str[i + 1])
			i++;
		while (str[i])
		{
			if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-')
				len++;
			i++;
		}
		return (len);
	}
	if (num < 0)
		len++;
	while (num)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

int	ft_atoi_philo(char *str)
{
	int	i;
	int	num;
	int	sign;

	sign = 1;
	num = 0;
	i = 0;
	while (str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		i++;
		sign = -1;
	}
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - 48);
	return (sign * num);
}

unsigned long	ft_atol_unsigned_philo(char *str)
{
	unsigned long	i;
	unsigned long	num;
	int				sign;

	sign = 1;
	num = 0;
	i = 0;
	while (str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - 48);
	return (sign * num);
}

static int	philo_negative_or_overflow(char *argv, int i)
{
	int				num_atoi;
	unsigned long	num_atol;

	if (ft_strchr(argv, '-'))
		return (error_message("!! Value not conform -> must be > 0\n"));
	else if (i == 1 || i == 5)
	{
		num_atoi = ft_atoi_philo(argv);
		if (num_atoi == 0)
			return (error_message("!! Value not conform -> 0 not accepted\n"));
		if (len_str_or_num(argv, 0, 0) != len_str_or_num(NULL, num_atoi, 0))
			return (error_message("!! Value not conform -> overflow\n"));
	}
	if (i == 3 || i == 4)
	{
		num_atol = ft_atol_unsigned_philo(argv);
		if (num_atol == 0)
			return (error_message("!! Value not conform -> 0 not accepted\n"));
		if (len_str_or_num(argv, 0, 0) != len_str_or_num(NULL, num_atol, 0))
			return (error_message("!! Value not conform -> overflow\n"));
	}
	return (0);
}

int	philo_check_args(int argc, char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	if (argc < 5)
		return (error_message("Not enough args\n"));
	if (argc > 6)
		return (error_message("Too many args\n"));
	while (argv[i])
	{
		if (argv[i][0] == '\0')
			return (error_message("Value not conform -> empty arg\n"));
		while (argv[i][j] == ' ')
			j++;
		if (j == (int)ft_strlen(argv[i]))
			return (error_message("Value not conform-> arg without a value\n"));
		if (check_arg_validity(argv[i]) == 1)
			return (1);
		if (philo_negative_or_overflow(argv[i], i) == 1)
			return (1);
		i++;
		j = 0;
	}
	return (0);
}
