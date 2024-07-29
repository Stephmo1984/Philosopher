/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:03:47 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/18 19:32:01 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "struct.h"

// PHILO_PARSING_01 --------------------------------------------------------
int				ft_atoi_philo(char *str);
unsigned long	ft_atol_unsigned_philo(char *str);
int				philo_check_args(int argc, char **argv);

// PHILO_PARSING_02 ---------------------------------------------------------
size_t			ft_strlen(const char *str);
char			*ft_strchr(char *s, int c);
int				check_arg_validity(char *str);

#endif