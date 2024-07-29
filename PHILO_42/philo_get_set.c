/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_get_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:59 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/16 14:17:55 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

t_ulong	get_value_unlong(t_mutex *mtx, t_ulong *to_get)
{
	t_ulong	value;

	pthread_mutex_lock(mtx);
	value = *to_get;
	pthread_mutex_unlock(mtx);
	return (value);
}

t_bool	get_value_bool(t_mutex *mtx, t_bool *to_get)
{
	t_bool	value;

	pthread_mutex_lock(mtx);
	value = *to_get;
	pthread_mutex_unlock(mtx);
	return (value);
}

void	set_value_bool(t_mutex *mtx, t_bool *to_modify, t_bool value)
{
	pthread_mutex_lock(mtx);
	*to_modify = value;
	pthread_mutex_unlock(mtx);
}

void	set_value_unlong(t_mutex *mtx, t_ulong *to_modify, t_ulong value)
{
	pthread_mutex_lock(mtx);
	*to_modify = value;
	pthread_mutex_unlock(mtx);
}
