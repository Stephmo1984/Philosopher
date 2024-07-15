/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:03:47 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/14 22:25:26 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "struct.h"

// PHILO_PARSING_01 ---------------------------------------------------------------
int 			len_num(long long num);
int				len_str_num(char *str);
int				ft_atoi_philo(char *str);
unsigned long	ft_atol_unsigned_philo(char *str);
void 			philo_check_args(char **argv);

// PHILO_PARSING_02 ---------------------------------------------------------------
size_t	ft_strlen(const char *str);
int		ft_isdigit(int c);
int		ft_is_sign(char sign, char c);
int		ft_isother(int c);
void	check_validity(char *str);

#endif