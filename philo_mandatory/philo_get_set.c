/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_get_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:59 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/15 15:58:59 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"

unsigned long	get_value_unlong(pthread_mutex_t *mtx, unsigned long *to_get)
{
	unsigned long	value;
	
	pthread_mutex_lock(mtx);
	value = *to_get;
	pthread_mutex_unlock(mtx);
	return (value);
}

t_bool	get_value_bool(pthread_mutex_t *mtx, t_bool *to_get)
{
	t_bool	value;
	
	pthread_mutex_lock(mtx);
	value = *to_get;
	pthread_mutex_unlock(mtx);
	return (value);
}

void	set_value_bool(pthread_mutex_t *mtx, t_bool *to_modify, t_bool value)
{
	pthread_mutex_lock(mtx);
	*to_modify = value;
	pthread_mutex_unlock(mtx);
}

void	set_value_unlong(pthread_mutex_t *mtx, unsigned long *to_modify, unsigned long value)
{
	pthread_mutex_lock(mtx);
	*to_modify = value;
	pthread_mutex_unlock(mtx);
}

// unsigned long	get_value_startmeal_unlong(t_philo_thread *thread, pthread_mutex_t *mtx)
// {
// 	unsigned long	value;
	
// 	pthread_mutex_lock(mtx);
// 	value = thread->start_meal;
// 	pthread_mutex_unlock(mtx);
// 	return (value);
// }

// void	set_value_startmeal_unlong(t_philo_thread *thread, pthread_mutex_t *mtx, unsigned long value)
// {
// 	pthread_mutex_lock(mtx);
// 	thread->start_meal = value;
// 	pthread_mutex_unlock(mtx);
// }
