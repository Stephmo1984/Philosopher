/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mandatory_OK_TEST.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:12:56 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/15 15:38:13 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"


t_bool	get_timestamp_millisecget_value_bool(pthread_mutex_t *mtx, unsigned long *to_get)
{
	t_bool	value;
	
	pthread_mutex_lock(mtx);
	value = *to_get;
	pthread_mutex_unlock(mtx);
	return (value);
}

unsigned long	test_get_value_unlong(pthread_mutex_t *mtx, unsigned long *to_get)
{
	unsigned long	value;
	
	pthread_mutex_lock(mtx);
	value = *to_get;
	pthread_mutex_unlock(mtx);
	return (value);
}

t_bool	test_get_value_bool(pthread_mutex_t *mtx, t_bool *to_get)
{
	t_bool	value;
	
	pthread_mutex_lock(mtx);
	value = *to_get;
	pthread_mutex_unlock(mtx);
	return (value);
}

void	test_set_value_bool(pthread_mutex_t *mtx, t_bool *to_modify, t_bool value)
{
	pthread_mutex_lock(mtx);
	*to_modify = value;
	pthread_mutex_unlock(mtx);
}

void	test_set_value_unlong(pthread_mutex_t *mtx, unsigned long *to_modify, unsigned long value)
{
	pthread_mutex_lock(mtx);
	*to_modify = value;
	pthread_mutex_unlock(mtx);
}


void	philo_eat(t_philo_thread *thread_n, pthread_mutex_t *forks, int first_fork, int second_fork)
{
	unsigned long meal_start;
	
	meal_start = get_timestamp_millisec(thread_n->start_simu);
	thread_n->last_meal = thread_n->start_meal;
	set_value_startmeal_unlong(thread_n, &thread_n->data->mtx_time, meal_start);
	if(get_value_bool(thread_n, &thread_n->data->mtx_bool, 'D') != TRUE)
		print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " is eating");
	usleep(thread_n->data->t_eat * 1000);
	pthread_mutex_unlock(&forks[second_fork]);
	pthread_mutex_unlock(&forks[first_fork]);
}

void philo_is_dead(t_philo_thread *thread, int nbr_phi, unsigned long death, int count)
{
	unsigned long time_stamp;
	int i;

	while(1)
	{
		i = 0;
		count = 1;
		while (i < nbr_phi)
		{
			if(get_value_bool(thread, &thread->data->mtx_bool, 'F') == TRUE)
			{
				count++;
				if (count == nbr_phi)
					return ;
			}
			else
			{
				time_stamp = get_timestamp_millisec(thread[i].start_simu);
				if (time_stamp - get_value_startmeal_unlong(&thread[i], &thread[i].data->mtx_time) > death)
					return (philo_dead(&thread[i], &thread->data->mtx_print, thread[i].start_simu));
			}
			i++;
		}
		usleep(1000);
	}
}

void	philo_take_forks(t_philo_thread *thread, pthread_mutex_t *forks, int l, int r)
{
		pthread_mutex_lock(&forks[l]);
		print_philo(thread, &thread->data->mtx_print, thread->data->start, " has taken a fork");
		pthread_mutex_lock(&forks[r]);
		print_philo(thread, &thread->data->mtx_print, thread->data->start, " has taken a fork");
		philo_eat(thread, forks, l, r);
}




void	*philo_do_test(void *thread_philo_n)
{
	t_philo_thread *thread_n;

	unsigned long ret_unsigned;
	
	thread_n = (t_philo_thread *) thread_philo_n;
	
	thread_n->start_meal = 100;
	printf("------\nstart_meal = %lu \n", thread_n->start_meal);
	ret_unsigned = test_get_value_unlong(&thread_n->data->mtx_time, &thread_n->start_meal);
	printf("GET start_meal = %lu \n", ret_unsigned );
	test_set_value_unlong(&thread_n->data->mtx_time, &thread_n->start_meal,  999);
	printf("SET start_meal = %lu \n", thread_n->start_meal);


	thread_n->data->one_dead = FALSE;
	printf("t_bool = %hhu \n",  thread_n->data->one_dead);
	test_set_value_bool(&thread_n->data->mtx_bool, &thread_n->data->one_dead, TRUE);
	printf("1.SET t_bool = %hhu \n\n",  thread_n->data->one_dead);

	t_bool ret = test_get_value_bool(&thread_n->data->mtx_bool, &thread_n->data->one_dead);
	printf("1.RET t_bool = %hhu \n\n",  ret);
	test_set_value_bool(&thread_n->data->mtx_bool, &thread_n->data->one_dead, FALSE);

	printf("2.SET t_bool = %hhu \n\n",  thread_n->data->one_dead);
	ret = test_get_value_bool(&thread_n->data->mtx_bool, &thread_n->data->one_dead);
	printf("2.RET t_bool = %hhu \n\n",  ret);

	return (NULL);
}
void	*philo_do(void *thread_philo_n)
{
	t_philo_thread *thread_n;
	pthread_mutex_t *forks;	
	int l;
	int r;

	thread_n = (t_philo_thread *) thread_philo_n;
	forks = thread_n->data->forks;
	l = thread_n->phi_num - 1;
	r =  thread_n->phi_num % thread_n->data->nbr_phi;
	while(1)
	{
			if(get_value_bool(thread_n, &thread_n->data->mtx_bool, 'D') == TRUE)
				return (NULL);
			print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " is thinking");
			if(get_value_bool(thread_n, &thread_n->data->mtx_bool, 'D') != TRUE)
			{
				if(thread_n->data->nbr_phi % 2 == 0 && thread_n->phi_num % 2 == 0 )
					philo_take_forks(thread_n, forks, l, r);
				else if (thread_n->data->nbr_phi % 2 == 0 )
					philo_take_forks(thread_n, forks, r, l);
				else
					philo_take_forks(thread_n, forks, r, l);
			}
			if (thread_n->meals_are_limited == TRUE)
				thread_n->counter_meals--;
			if(thread_n->counter_meals == 0)
				return (philo_full(thread_n, &thread_n->data->mtx_print, thread_n->data->start));
			if(get_value_bool(thread_n, &thread_n->data->mtx_bool, 'D') == TRUE)
				return (NULL);
			print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " is sleeping");
			usleep(thread_n->data->t_sleep * 1000);
	}
	return (NULL);
}

void	join_and_destroy(t_data *data, t_philo_thread *threads)
{
	int i;

	i = 0;
	while( i < data->nbr_phi)
    {
        pthread_join(threads[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < data->nbr_phi)
	{
		 pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mtx_print);
	pthread_mutex_destroy(&data->mtx_time);
	pthread_mutex_destroy(&data->mtx_bool);
}

int main(int argc, char **argv) 
{
	int nbr_of_chairs;
    t_philo_thread *threads;
	t_data data;
	
// !! faire fonction pour nbr_phi == 1 
// protections
// make file

	if (argc < 5)
		exit_error_message("Not enough args\n");
	if (argc > 6)
		exit_error_message("Too many args\n");
	init_data(&data, argv);
	nbr_of_chairs = data.nbr_phi;
	threads = malloc(sizeof(t_philo_thread) * nbr_of_chairs);// protections
	pthread_mutex_init(&data.mtx_print, NULL);// protections
	pthread_mutex_init(&data.mtx_time, NULL);// protections
	pthread_mutex_init(&data.mtx_bool, NULL);// protections
	init_mutex(&data);// protections
	init_thread(&data, threads);// protections
	philo_is_dead(threads, nbr_of_chairs, data.t_death, 1);
	join_and_destroy(&data, threads);// protections
	free(threads);
	free(data.forks);
	return (0);
}
