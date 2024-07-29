/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_diner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:54:20 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/18 23:26:25 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

void	philo_take_forks(t_philo *thread, t_mutex *forks, int l, int r)
{
	t_ulong	meal_start;

	pthread_mutex_lock(&forks[l]);
	print_philo(thread, &thread->data->mtx_print, thread->data->start, FORK);
	pthread_mutex_lock(&forks[r]);
	print_philo(thread, &thread->data->mtx_print, thread->data->start, FORK);
	meal_start = get_timestamp_millisec(thread->start_simu);
	thread->last_meal = thread->start_meal;
	set_value_unlong(&thread->data->mtx_time, &thread->start_meal, meal_start);
	if (get_value_bool(&thread->data->mtx_bool, &thread->data->one_dead) != 1)
		print_philo(thread, &thread->data->mtx_print, thread->data->start, EAT);
	philo_is_sleeping_eating(thread, thread->data->t_eat);
	pthread_mutex_unlock(&forks[r]);
	pthread_mutex_unlock(&forks[l]);
}

void	*philo_is_dinning(t_philo *thrd, t_mutex *forks, int l, int r)
{
	philo_take_forks(thrd, forks, l, r);
	if (get_value_bool(&thrd->data->mtx_bool, &thrd->data->one_dead) == 1)
		return (NULL);
	if (thrd->meals_are_limited == TRUE)
		thrd->counter_meals--;
	if (thrd->counter_meals == 0)
		return (philo_full(thrd, &thrd->data->mtx_print, thrd->data->start));
	return (thrd);
}

void	*philo_do(void *thread_philo_n)
{
	t_philo		*thrd;
	t_mutex		*forks;	
	int			l;
	int			r;

	thrd = (t_philo *) thread_philo_n;
	forks = thrd->data->forks;
	l = thrd->phi_num - 1;
	r = thrd->phi_num % thrd->data->nbr_phi;
	if (thrd->phi_num % 2 == 0)
		usleep(5000);
	while (1)
	{
		if (get_value_bool(&thrd->data->mtx_bool, &thrd->data->one_dead) == 1)
			return (NULL);
		print_philo(thrd, &thrd->data->mtx_print, thrd->data->start, THINK);
		if (get_value_bool(&thrd->data->mtx_bool, &thrd->data->one_dead) != 1)
			if (!philo_is_dinning(thrd, forks, l, r))
				return (NULL);
		if (get_value_bool(&thrd->data->mtx_bool, &thrd->data->one_dead) == 1)
			return (NULL);
		print_philo(thrd, &thrd->data->mtx_print, thrd->data->start, SLEEP);
		philo_is_sleeping_eating(thrd, thrd->data->t_sleep);
	}
	return (NULL);
}
