/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:00:12 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/12 10:20:19 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"

int len_num(long long num)
{
    int len;

    len = 0;
    if(num < 0)
      len++;
    while(num)
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
    while(str[i])
    {
        if(str[i] == '-')
            len++;
        if(str[i] >= '0' && str[i] <= '9')
         len++;
        i++;
    }
    return(len);
}

int	ft_atoi(char *str)
{
	int	i;
	int	num;
	int	sign;

	sign = 1;
	num = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - 48);
	printf(" num %d \n", num);

    if (len_str_num(str) != len_num(num))
	{
		printf("overflow\n");
		exit (1);
	}
	return (sign * num);
}

long long	ft_atol_unsigned(const char *str)
{
	long long	i;
	unsigned long	num;
	int			sign;

	sign = 1;
	num = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - 48);
	if (num > 2147483647)
	{
		printf("overflow %li", num);
		exit (1);
	}
	return (num);
}

void	exit_error_message(char *str)
{
	printf("%s", str);
	exit (1);
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

size_t	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
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
			exit_error_message("a value is not conform -> an arg is negative\n");
		if (ft_is_sign('+', str[i]) && (!str[i + 1] || ft_isdigit(str[i - 1]) != 0))
			exit_error_message("a value is not conform\n");
		else if (ft_is_sign('+', str[i]) && str[i + 1] == ' ')
			exit_error_message("a value is not conform\n");
		else if (ft_is_sign('+', str[i]) && ft_is_sign('+', str[i + 1]))
			exit_error_message("a value is not conform-> ++\n");
		else if (ft_isother(str[i]) == 1)
			exit_error_message("a value is not conform-> an arg is not a number\n");
		i++;
	}
}

void	check_space_arg(char *argv)
{

	int	i;

	i = 0;
	while (argv[i] == ' ')
			i++;
	if (i == (int)ft_strlen(argv))
			exit_error_message("a value is not conform -> arg without a value\n");
}

void	check_empty_arg(char *argv)
{
	if (!argv[0])
		exit_error_message("a value is not conform -> empty arg\n");

}

void philo_check_args(char **argv)
{
	int i;
	
	i = 1;
	while (argv[i])
	{
		check_empty_arg(argv[i]);
		check_space_arg(argv[i]);
		check_validity(argv[i]);
		i++;
	}
	
}