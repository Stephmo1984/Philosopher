/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mandatory_TEST.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:12:56 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/15 15:18:20 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"

t_bool	get_value_bool(pthread_mutex_t *mtx, unsigned long *to_get)
{
	t_bool	value;
	
	pthread_mutex_lock(mtx);
	// value = thread->one_dead;
	value = *to_get;
	pthread_mutex_unlock(mtx);
	// printf("///RET value  t_bool = %hhu \n\n",  value);
	return (value);
}

unsigned long	get_value_unlong(pthread_mutex_t *mtx, unsigned long *to_get)
{
	unsigned long	value;
	
	pthread_mutex_lock(mtx);
	value = *to_get;
	pthread_mutex_unlock(mtx);
	return (value);
}

void	set_value_bool(pthread_mutex_t *mtx, t_bool *to_modify, t_bool value)
{
	pthread_mutex_lock(mtx);
	printf("\nto_modify before bool=%hhu\n", to_modify);
	*to_modify = value;
	printf("value after to_modify=%hhu\n\n", to_modify);
	pthread_mutex_unlock(mtx);
}

void	set_value_unlong(pthread_mutex_t *mtx, unsigned long *to_modify, unsigned long value)
{
	pthread_mutex_lock(mtx);
	printf("\nto_modify before ulong=%lu\n", to_modify);
	*to_modify = value;
	printf("to_modify after ulong=%lu\n\n", to_modify);
	pthread_mutex_unlock(mtx);
}



void	philo_eat(t_philo_thread *thread_n, pthread_mutex_t *forks, int fisrt_fork, int second_fork)
{
	unsigned long meal_start;
	
	meal_start = get_timestamp_millisec(thread_n->start_simu);
	thread_n->last_meal = thread_n->start_meal;

	set_value_start_meal_unlong(thread_n, &thread_n->data->mtx_time, meal_start);

	if(*thread_n->one_dead != TRUE)//(thread_n->data->one_dead == TRUE)
		print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " ---------------> is eating");
	usleep(thread_n->data->t_eat * 1000);
	pthread_mutex_unlock(&forks[second_fork]);
	pthread_mutex_unlock(&forks[fisrt_fork]);
}


void *philo_is_dead(void *thread_philo)
{
	t_philo_thread *thread;
	unsigned long death;
	unsigned long diff;
	unsigned long time_stamp;
	int nbr_phi;
	int i;
	int count;

	unsigned long last_meal_start;


	time_stamp = 0;
	count = 1;
	thread = (t_philo_thread *) thread_philo;	
	death = thread->data->t_death;
	i = 0;
	nbr_phi = thread->data->nbr_phi;
	
	while(1)
	{
		while (i < nbr_phi)
		{
			if (thread[i].is_full == TRUE)
			{
				count++;
				if (count == nbr_phi)
					return(NULL);
			}
			
			i++;
		}
		usleep(1000);
		i = 0;
		count = 1;
	}
	return(thread_philo);
}


void	*philo_do_even(void *thread_philo_n)
{
	t_philo_thread *thread_n;

	thread_n = (t_philo_thread *) thread_philo_n;
	
	thread_n->start_meal = 100;
	printf("------\nstart_meal = %lu \n", thread_n->start_meal);
	set_value_unlong(thread_n, &thread_n->data->mtx_time, 999);
	printf("SET start_meal = %lu \n", thread_n->start_meal);

	
	thread_n->data->one_dead = FALSE;
	printf("t_bool = %hhu \n",  thread_n->data->one_dead);
	set_value_bool(thread_n, &thread_n->data->mtx_bool, TRUE);
	printf("1.SET t_bool = %hhu \n\n",  thread_n->data->one_dead);

	t_bool ret = get_value_bool(thread_n, &thread_n->data->mtx_bool);
	printf("1.RET t_bool = %hhu \n\n",  ret);
	set_value_bool(thread_n, &thread_n->data->mtx_bool, FALSE);

	printf("2.SET t_bool = %hhu \n\n",  thread_n->data->one_dead);
	ret = get_value_bool(thread_n, &thread_n->data->mtx_bool);
	printf("2.RET t_bool = %hhu \n\n",  ret);

	return (NULL);
}

void	*philo_do_odd(void *thread_philo_n)
{
		t_philo_thread *thread_n;
// 	int n;
// 	pthread_mutex_t *forks;
// 	int counter_meals;
// 	int l;
// 	int r;

	thread_n = (t_philo_thread *) thread_philo_n;

	thread_n->start_meal = 100;

	// printf("------\nstart_meal = %lu \n", thread_n->start_meal);
	// set_value_unlong(&thread_n->data->mtx_time, thread_n->start_meal, 300);
	// printf("start_meal = %lu \n", thread_n->start_meal);
	
	// thread_n->data->one_dead = FALSE;
	// printf("t_bool = %hhu \n",  thread_n->data->one_dead);

	// set_value_bool(&thread_n->data->mtx_bool, thread_n->data->one_dead, TRUE);
	// printf("t_bool = %hhu \n",  thread_n->data->one_dead);
	
	return (NULL);

}


void init_data(t_data *data, char **argv)
{
	philo_check_args(argv);

	data->nbr_meals = 1;
	data->meals_number = FALSE;
	data->nbr_phi = ft_atoi_philo(argv[1]);
	if (data->nbr_phi > 124098)
		exit_error_message("Too many threads (philosophers) -> to see max threads value: cat /proc/sys/kernel/threads-max\n"); //         cat /proc/sys/kernel/threads-max       
	data->t_death =  ft_atol_unsigned_philo(argv[2]);
	data->t_eat=  ft_atol_unsigned_philo(argv[3]);
	data->t_sleep =  ft_atol_unsigned_philo(argv[4]);
	if (argv[5])
	{
		data->nbr_meals =  ft_atoi_philo(argv[5]);
		data->meals_number = TRUE;
	}	
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_phi);
	data->one_dead = FALSE;
	data->start = get_time_millisec();
}

void	init_philo(t_data *data, t_philo_thread *threads)
{
	int i;

	i = 0;
	while( i < data->nbr_phi )
	{
		// threads[i].one_dead = &data->one_dead;
		threads[i].meals_are_limited = TRUE;
		threads[i].is_full = FALSE;
		threads[i].phi_num = i + 1;
		threads[i].data = data;
		threads[i].start_simu = data->start;
		threads[i].counter_meals_eaten = 5;
		threads[i].last_meal = data->start;
		threads[i].start_meal = 0;
		i++;
	}
}

void	init_thread(t_data *data, t_philo_thread *threads)
{
	int ret;
	int i;
	
	init_philo(data, threads);
	i = 0;
	while( i < data->nbr_phi )
	{
		if( i == 0 || i % 2 == 0)
		{
			ret = pthread_create(&threads[i].thread_id, NULL, philo_do_even, (void *) &threads[i]);
			if (ret)
				exit_error_message("ERROR: pthread_create()\n");
		}
		i++;
	}
	usleep(1000);
	i = 1;
	while( i < data->nbr_phi )
	{
		if( i % 2 != 0)
		{
			ret = pthread_create(&threads[i].thread_id, NULL, philo_do_odd, (void *) &threads[i]);
			if (ret)
				exit_error_message("ERROR: pthread_create()\n");
		}
		i++;
	}
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
	while (i < data->nbr_phi)
	{
		 pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mtx_print);
	
	pthread_mutex_destroy(&data->mtx_time);//

	pthread_mutex_destroy(&data->mtx_bool);//
}



int main(int argc, char **argv) 
{
	int nbr_of_chairs;
	int i;
    t_philo_thread *threads;
	t_data data;
	
	if (argc > 1)
		exit_error_message("Too many args\n");
	init_data(&data, argv);
	nbr_of_chairs = data.nbr_phi;
	threads = malloc(sizeof(t_philo_thread) * nbr_of_chairs);
	pthread_mutex_init(&data.mtx_print, NULL);
	pthread_mutex_init(&data.mtx_time, NULL);//
	pthread_mutex_init(&data.mtx_bool, NULL);//
	init_mutex(&data);
	init_thread(&data, threads);
	join_and_destroy(&data, threads);
	free(threads);
	free(data.forks);
	return (0);
}
