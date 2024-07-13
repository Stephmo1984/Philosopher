/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mandatory_OK.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:12:56 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/13 22:42:22 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"

// t_bool	get_value_bool(pthread_mutex_t *mtx, t_bool to_get)
// {
// 	t_bool	value;
// 	pthread_mutex_lock(mtx);
// 	value = to_get;
// 	pthread_mutex_unlock(mtx);
// 	return (value);
// }

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

unsigned long	get_value_unlong(pthread_mutex_t *mtx, unsigned long to_get)
{
	unsigned long	value;
	
	pthread_mutex_lock(mtx);
	value = to_get;
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

// void	set_value_bool(pthread_mutex_t *mtx, t_bool to_modify, t_bool value)
// {
// 	pthread_mutex_lock(mtx);
// 	printf("\nto_modify before bool=%hhu\n", to_modify);
// 	to_modify = value;
// 	printf("value after to_modify=%hhu\n\n", to_modify);

// 	pthread_mutex_unlock(mtx);
// }

// void	set_value_unlong(pthread_mutex_t *mtx, unsigned long to_modify, unsigned long value)
// {
// 	pthread_mutex_lock(mtx);
// 	printf("\nto_modify before ulong=%lu\n", to_modify);

// 	to_modify = value;
// 	printf("to_modify after ulong=%lu\n\n", to_modify);

// 	pthread_mutex_unlock(mtx);
// }


void	set_value_one_dead_bool(t_philo_thread *thread, pthread_mutex_t *mtx, t_bool value)
{
	pthread_mutex_lock(mtx);
	thread->data->one_dead = value;
	pthread_mutex_unlock(mtx);
}

void	set_value_isfull_bool(t_philo_thread *thread, pthread_mutex_t *mtx, t_bool value)
{
	pthread_mutex_lock(mtx);
	thread->is_full = value;
	pthread_mutex_unlock(mtx);
}

void	set_value_start_meal_unlong(t_philo_thread *thread, pthread_mutex_t *mtx, unsigned long value)
{
	pthread_mutex_lock(mtx);
	thread->start_meal = value;
	pthread_mutex_unlock(mtx);
}

void	philo_eat(t_philo_thread *thread_n, pthread_mutex_t *forks, int fisrt_fork, int second_fork)
{
	unsigned long meal_start;
	
	meal_start = get_timestamp_millisec(thread_n->start_simu);
	thread_n->last_meal = thread_n->start_meal;

	
	// set_value_unlong(&thread_n->data->mtx_time, thread_n->start_meal, thread_n->start_meal);
	
	// set_value_unlong(&thread_n->data->mtx_time, thread_n->start_meal, meal_start);//

	set_value_start_meal_unlong(thread_n, &thread_n->data->mtx_time, meal_start);

	// thread_n->start_meal = meal_start;////data_race
	// if(*thread_n->one_dead != TRUE)//(thread_n->data->one_dead == TRUE)
	if(get_value_onedead_bool(thread_n, &thread_n->data->mtx_bool) == TRUE)
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
			// if (thread[i].is_full == TRUE)
			if(get_value_isfull_bool(thread, &thread->data->mtx_bool) == TRUE)
			{
				count++;
				if (count == nbr_phi)
					return(NULL);
			}
			else
			{
				time_stamp = get_timestamp_millisec(thread[i].start_simu);
				// last_meal_start = get_value_unlong(&thread[i].data->mtx_time, thread[i].start_meal);
				last_meal_start = get_value_startmeal_unlong(&thread[i], &thread[i].data->mtx_time);
				
				// if(i==1)
				// 	printf("thread[i].last_meal_start= %lu\n", last_meal_start);
				// last_meal_start = thread[i].start_meal;
				// diff = time_stamp - (thread[i].start_meal);//set_get
				// diff = time_stamp - last_meal_start;//set_get
				// diff = time_stamp - get_value_unlong(&thread[i].data->mtx_time, thread[i].start_meal);//set_get
				if (time_stamp - last_meal_start > death)
				{
					// printf("Philosopher  num=%d thread[i].start_meal = %lu \n", thread[i].phi_num, last_meal_start);

					// print_philo(thread_philo, &thread->data->mtx_print, thread->data->start, " PHILOSOPHER IS DEAD");	
					// thread->data->one_dead = TRUE;

					
					set_value_one_dead_bool(&thread[i], &thread[i].data->mtx_bool, TRUE);
					
					// *thread->one_dead = TRUE;

					
					// set_value_bool(&thread->data->mtx_bool, thread->data->one_dead, TRUE);
					// set_value_bool(&thread->data->mtx_bool, *thread->one_dead, TRUE);

					pthread_mutex_lock(&thread->data->mtx_print);
					printf("[%li]  ", get_timestamp_millisec( thread->data->start));
					printf("P%d %s\n", thread[i].phi_num, "XXXXXXXXXXX PHILOSOPHER IS DEAD XXXXXXXXXXXXxxx");
					pthread_mutex_unlock(&thread->data->mtx_print);
					return(NULL);
				}	
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
	int n;
	pthread_mutex_t *forks;
	int counter_meals;
	int l;
	int r;

	thread_n = (t_philo_thread *) thread_philo_n;
	n = thread_n->phi_num;
	forks = thread_n->data->forks;
	counter_meals = thread_n->data->nbr_meals;
	thread_n->last_meal = 0;
	// thread_n->start_meal = 0;

	l = n - 1;
	r =  n % thread_n->data->nbr_phi;
	while(1)
	{
	//		if(*thread_n->one_dead == TRUE)//(thread_n->data->one_dead == TRUE)
			// if(get_value_onedead_bool(thread_n, thread_n->data->mtx_bool) == TRUE)
			if(get_value_onedead_bool(thread_n, &thread_n->data->mtx_bool) == TRUE)
				return(NULL);
			// if(*thread_n->one_dead != TRUE)//(thread_n->data->one_dead == TRUE)
			if(get_value_onedead_bool(thread_n, &thread_n->data->mtx_bool) != TRUE)
			{
				print_philo( thread_n, &thread_n->data->mtx_print, thread_n->data->start, " is thinking");
				pthread_mutex_lock(&forks[l]);
				print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " has taken a fork");
				pthread_mutex_lock(&forks[r]);
				print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " has taken a fork");
				philo_eat(thread_n, forks, l, r);
			}
			// if(*thread_n->one_dead == TRUE)//(thread_n->data->one_dead == TRUE)
			if(get_value_onedead_bool(thread_n, &thread_n->data->mtx_bool) == TRUE)
				return(NULL);
			if (thread_n->meals_are_limited == TRUE)
				counter_meals--;
			if(counter_meals == 0)
			{
				// thread_n->is_full = TRUE;
				set_value_isfull_bool(thread_n, &thread_n->data->mtx_bool, TRUE);
				// print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " PHILOSOPHER IS FULL");
				return (NULL);
			}
			// if(*thread_n->one_dead == TRUE)//(thread_n->data->one_dead == TRUE)
			if(get_value_onedead_bool(thread_n, &thread_n->data->mtx_bool) == TRUE)
				return(NULL);
			print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " is sleeping");
			usleep(thread_n->data->t_sleep * 1000);
	}
	return (NULL);
}

void	*philo_do_odd(void *thread_philo_n)
{
	t_philo_thread *thread_n;
	int n;
	pthread_mutex_t *forks;
	int counter_meals;
	int l;
	int r;

	thread_n = (t_philo_thread *) thread_philo_n;
	n = thread_n->phi_num;
	forks = thread_n->data->forks;
	counter_meals = thread_n->data->nbr_meals;
	thread_n->last_meal = 0;


	l = n - 1;
	r =  n % thread_n->data->nbr_phi;
	while(1)
	{
		if(get_value_onedead_bool(thread_n, &thread_n->data->mtx_bool) == TRUE)
			return(NULL);
		// if(*thread_n->one_dead != TRUE)//(thread_n->data->one_dead == TRUE)
		if(get_value_onedead_bool(thread_n, &thread_n->data->mtx_bool) != TRUE)
		{
			print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " is thinking");
			pthread_mutex_lock(&forks[r]);
			print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " has taken a fork");
			pthread_mutex_lock(&forks[l]);
			print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " has taken a fork");
			philo_eat(thread_n, forks, r, l);
		}
		// if(*thread_n->one_dead == TRUE)//(thread_n->data->one_dead == TRUE)
		if(get_value_onedead_bool(thread_n, &thread_n->data->mtx_bool) == TRUE)
			return(NULL);
		if (thread_n->meals_are_limited == TRUE)
			counter_meals--;
		if(counter_meals == 0)
		{
			thread_n->is_full = TRUE;
			print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " PHILOSOPHER IS FULL");
			return (NULL);
		}
		// if(*thread_n->one_dead == TRUE)//(thread_n->data->one_dead == TRUE)
		if(get_value_onedead_bool(thread_n, &thread_n->data->mtx_bool) == TRUE)
			return(NULL);;
		print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " is sleeping");
		usleep(thread_n->data->t_sleep * 1000);
	}
	return (NULL);
}


// void	*philo_do_even(void *thread_philo_n)
// {
// 	t_philo_thread *thread_n;
// // 	int n;
// // 	pthread_mutex_t *forks;
// // 	int counter_meals;
// // 	int l;
// // 	int r;

// 	thread_n = (t_philo_thread *) thread_philo_n;
	
// 	thread_n->start_meal = 100;
// 	printf("------\nstart_meal = %lu \n", thread_n->start_meal);
// 	set_value_unlong(thread_n, &thread_n->data->mtx_time,  thread_n->start_meal, 200);
// 	printf("SET start_meal = %lu \n", thread_n->start_meal);

// 	thread_n->data->one_dead = FALSE;
// 	printf("t_bool = %hhu \n",  thread_n->data->one_dead);

// 	set_value_bool(thread_n, &thread_n->data->mtx_bool, thread_n->data->one_dead, TRUE);
// 	printf("SET t_bool = %hhu \n\n",  thread_n->data->one_dead);


// 	return (NULL);
// }

// void	*philo_do_odd(void *thread_philo_n)
// {
// 		t_philo_thread *thread_n;
// // 	int n;
// // 	pthread_mutex_t *forks;
// // 	int counter_meals;
// // 	int l;
// // 	int r;

// 	thread_n = (t_philo_thread *) thread_philo_n;

// 	thread_n->start_meal = 100;

// 	// printf("------\nstart_meal = %lu \n", thread_n->start_meal);
// 	// set_value_unlong(&thread_n->data->mtx_time, thread_n->start_meal, 300);
// 	// printf("start_meal = %lu \n", thread_n->start_meal);
	
// 	// thread_n->data->one_dead = FALSE;
// 	// printf("t_bool = %hhu \n",  thread_n->data->one_dead);

// 	// set_value_bool(&thread_n->data->mtx_bool, thread_n->data->one_dead, TRUE);
// 	// printf("t_bool = %hhu \n",  thread_n->data->one_dead);
	
// 	return (NULL);

// }
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
		threads[i].one_dead = &data->one_dead;
		threads[i].meals_are_limited = data->meals_number;
		threads[i].is_full = FALSE;
		threads[i].phi_num = i + 1;
		threads[i].data = data;
		threads[i].start_simu = data->start;
		threads[i].counter_meals_eaten = data->nbr_meals;
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
	
	if (argc < 5)
		exit_error_message("Missing args\n");
	if (argc > 6)
		exit_error_message("Too many args\n");
	init_data(&data, argv);
	nbr_of_chairs = data.nbr_phi;
	threads = malloc(sizeof(t_philo_thread) * nbr_of_chairs);
	pthread_mutex_init(&data.mtx_print, NULL);
	
	pthread_mutex_init(&data.mtx_time, NULL);//

	pthread_mutex_init(&data.mtx_bool, NULL);//

	
	init_mutex(&data);
	
	init_thread(&data, threads);

	philo_is_dead(threads);
	
	join_and_destroy(&data, threads);
	free(threads);
	free(data.forks);
	return (0);
}
