/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:00:12 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/15 16:00:11 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

int len_str_or_num(char *str, long long num, int len)
{
    size_t i;

    i = 0;
	if (!num)
	{
		while (str[i] == ' ' || str[i] == '0' || str[i] == '+' )
       		i++;
		while (str[i])
		{
			if (str[i] >= '0' && str[i] <= '9')
				len++;
			i++;
		}
 	   return(len);
	}
	if (num < 0)
    	len++;
	while (num)
	{
		num = num/10;
		len++;
	}
    return(len);
}

int len_num(long long num)
{
    int len;

    len = 0;
    if (num < 0)
      len++;
    while (num)
    {
        num = num/10;
        len++;
    }
    return(len);
}

int len_str_num(char *str)
{
    int len;
    int i;

    len = 0;
    i = 0;
	while (str[i] == ' ')
        i++;
    if (str[i] == '-')
        len++;
    while (str[i] == '0' || str[i] == '+' )
        i++;
    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
         len++;
        i++;
    }
    return(len);
}

int	ft_atoi_philo(char *str)
{
	int	i;
	int	num;

	num = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - 48);
    if (len_str_or_num(str, 0, 0) != len_str_or_num(NULL, num, 0))
	    exit_error_message("Value not conform -> overflow\n");
    if (num == 0)
		exit_error_message("Value not conform -> args must be > 0\n");
	return (num);
}

unsigned long	ft_atol_unsigned_philo(char *str)
{
	unsigned long	i;
	unsigned long	num;
	int				sign;

	sign = 1;
	num = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - 48);
	// if (len_str_num(str) != len_num(num))
	//     exit_error_message("Value not conform -> overflow\n");
	if (len_str_or_num(str, 0, 0) != len_str_or_num(NULL, num, 0))
	    exit_error_message("Value not conform -> overflow\n");
    if (num == 0)
		exit_error_message("Value not conform -> args must be > 0\n");
	return (num);
}

void philo_check_args(char **argv)
{
	int i;
	int j;
	
	j = 0;
	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '\0')
			exit_error_message("Value not conform -> empty arg\n");
		while (argv[i][j] == ' ')
			j++;
		if (j == (int)ft_strlen(argv[i]))
			exit_error_message("Value not conform -> arg without a value\n");
		check_validity(argv[i]);
		i++;
		j = 0;
	}	
}