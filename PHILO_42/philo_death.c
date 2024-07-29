/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:55:11 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/18 17:10:47 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

t_bool	philo_time_dead(t_philo *thrd, int i)
{
	t_ulong	time_stamp;
	t_ulong	start_meal;

	time_stamp = get_timestamp_millisec(thrd[i].start_simu);
	start_meal = get_value_unlong(&thrd->data->mtx_time, &thrd[i].start_meal);
	if (time_stamp - start_meal > thrd->data->t_death)
		return (TRUE);
	return (FALSE);
}

void	philo_is_dead(t_philo *thread, int nbr_phi, int count, int i)
{
	while (1)
	{
		i = 0;
		count = 1;
		while (i < nbr_phi)
		{
			if (get_value_bool(&thread->data->mtx_bool, &thread->is_full) == 1)
			{
				count++;
				if (count == nbr_phi)
					return ;
			}
			else
			{
				if (philo_time_dead(thread, i) == TRUE)
					return (philo_dead(&thread[i], &thread->data->mtx_print,
							thread[i].start_simu));
			}
			i++;
		}
	}
}
