/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_get_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:59 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/14 16:17:52 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"

t_bool	get_value_onedead_bool(t_philo_thread *thread, pthread_mutex_t *mtx)
{
	t_bool	value;
	
	pthread_mutex_lock(mtx);
	value = *thread->one_dead;
	pthread_mutex_unlock(mtx);
	return (value);
}

t_bool	get_value_isfull_bool(t_philo_thread *thread, pthread_mutex_t *mtx)
{
	t_bool	value;
	
	pthread_mutex_lock(mtx);
	value = thread->is_full;
	pthread_mutex_unlock(mtx);
	return (value);
}

unsigned long	get_value_startmeal_unlong(t_philo_thread *thread, pthread_mutex_t *mtx)
{
	unsigned long	value;
	
	pthread_mutex_lock(mtx);
	value = thread->start_meal;
	pthread_mutex_unlock(mtx);
	return (value);
}

void	set_value_onedead_bool(t_philo_thread *thread, pthread_mutex_t *mtx, t_bool value)
{
	pthread_mutex_lock(mtx);
	thread->data->one_dead = value;
	pthread_mutex_unlock(mtx);
}

void	set_value_startmeal_unlong(t_philo_thread *thread, pthread_mutex_t *mtx, unsigned long value)
{
	pthread_mutex_lock(mtx);
	thread->start_meal = value;
	pthread_mutex_unlock(mtx);
}

void	set_value_isfull_bool(t_philo_thread *thread, pthread_mutex_t *mtx, t_bool value)
{
	pthread_mutex_lock(mtx);
	thread->is_full = value;
	pthread_mutex_unlock(mtx);
}
