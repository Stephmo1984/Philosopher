/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mandatory_OK.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:12:56 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/11 23:20:19 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"


// t_bool	get_value_bool(pthread_mutex_t *mtx, t_bool to_get)
// {
// 	t_bool	value;
// 	pthread_mutex_lock(mtx);
// 	value = to_get;
// 	// write(1, "t_bool updated\n", 16);
// 	pthread_mutex_unlock(mtx);
// 	return (value);
// }

void	set_value_bool(pthread_mutex_t *mtx, t_bool to_modify, t_bool value)
{
	pthread_mutex_lock(mtx);
	to_modify = value;
	pthread_mutex_unlock(mtx);
}
void	set_value_unlong(pthread_mutex_t *mtx, unsigned long to_modify, unsigned long value)
{
	pthread_mutex_lock(mtx);
	to_modify = value;
	pthread_mutex_unlock(mtx);
}

void	philo_eat(t_philo_thread *thread_n, pthread_mutex_t *forks, int fisrt_fork, int second_fork)
{
	unsigned long meal_start;
	
	meal_start = get_timestamp_millisec(thread_n->data->start);
	thread_n->last_meal = thread_n->start_meal;
	thread_n->start_meal = meal_start;//set_get
	// set_value_unlong(&thread_n->mtx_time, thread_n->start_meal, meal_start);//
	print_philo(&thread_n->data->mtx_print, thread_n->phi_num, thread_n->data->start, " is eating");
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
	
	time_stamp = 0;
	count = 0;
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
				i++;
				count++;
				if (count == nbr_phi - 1)
					return(NULL);
			}
			else
			{
				time_stamp = get_timestamp_millisec(thread[i].start_simu);
				diff = time_stamp - (thread[i].start_meal);//set_get
				if (diff > death)
				{
					// printf("MONITOR TimeStamp= %li\n", time_stamp );
					// printf("MONITOR thread[i].start_meal= %li\n", thread[i].start_meal );
					// printf("MONITOR diff = %li\n", diff);
					print_philo(&thread->data->mtx_print, thread[i].phi_num, thread->data->start, " PHILOSOPHER IS DEAD");	
					
					// set_value_bool(&thread->data->mtx_death, thread->data->one_dead, TRUE);
					
					// pthread_mutex_lock(&thread->data->mtx_death);
					thread->data->one_dead = TRUE;
					// pthread_mutex_unlock(&thread->data->mtx_death);
					
					return(NULL);
				}	
			}
		}
		usleep(5000);
		i = 0;
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
	thread_n->start_meal = 0;

	l = n - 1;
	r =  n % thread_n->data->nbr_phi;
	while(1)
	{
			if(thread_n->data->one_dead == TRUE)
				return(NULL);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " is thinking");
			pthread_mutex_lock(&forks[l]);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " has taken a fork");
			pthread_mutex_lock(&forks[r]);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " has taken a fork");
			philo_eat(thread_n, forks, l, r);
			if(thread_n->data->one_dead == TRUE)
				return(NULL);
			counter_meals--;
			if(counter_meals == 0)
			{
				thread_n->is_full = TRUE;
				print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " PHILOSOPHER IS FULL");
				return (NULL);
			}
			if(thread_n->data->one_dead == TRUE)
				return(NULL);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " is sleeping");
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
	thread_n->start_meal = 0;

	l = n - 1;
	r =  n % thread_n->data->nbr_phi;
	while(1)
	{
			if(thread_n->data->one_dead == TRUE)
				return(NULL);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " is thinking");
			pthread_mutex_lock(&forks[r]);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " has taken a fork");
			pthread_mutex_lock(&forks[l]);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " has taken a fork");
			philo_eat(thread_n, forks, r, l);
			if(thread_n->data->one_dead == TRUE)
				return(NULL);
			counter_meals--;
			if(counter_meals == 0)
			{
				thread_n->is_full = TRUE;
				print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " PHILOSOPHER IS FULL");
				return (NULL);
			}
			if(thread_n->data->one_dead == TRUE)
				return(NULL);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " is sleeping");
			usleep(thread_n->data->t_sleep * 1000);
	}
	return (NULL);
}


// void	*philo_do(void *thread_philo_n)
// {
// 	t_philo_thread *thread_n;
// 	int n;
// 	pthread_mutex_t *forks;
// 	int counter_meals;
// 	int l;
// 	int r;

// 	thread_n = (t_philo_thread *) thread_philo_n;
// 	n = thread_n->phi_num;
// 	forks = thread_n->data->forks;
// 	counter_meals = thread_n->data->nbr_meals;
// 	thread_n->last_meal = 0;
// 	thread_n->start_meal = 0;

// 	l = n - 1;
// 	r =  n % thread_n->data->nbr_phi;
// 	while(1)
// 	{
// 		if (n % 2 == 0)
// 		{
// 			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " is thinking");
// 			pthread_mutex_lock(&forks[l]);
// 			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " has taken a fork");
// 			pthread_mutex_lock(&forks[r]);
// 			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " has taken a fork");
// 			philo_eat(thread_n, forks, l, r);
// 			counter_meals--;
// 			if(counter_meals == 0)
// 			{
// 				thread_n->is_full = TRUE;
// 				print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " PHILOSOPHER IS FULL");
// 				return (NULL);
// 			}
// 			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " is sleeping");
// 			usleep(thread_n->data->t_sleep * 1000);
// 		}
// 		else
// 		{
// 			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " is thinking");
// 			pthread_mutex_lock(&forks[r]);
// 			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " has taken a fork");
// 			pthread_mutex_lock(&forks[l]);
// 			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " has taken a fork");
// 			philo_eat(thread_n, forks, r, l);
// 			counter_meals--;
// 			if(counter_meals == 0)
// 			{
// 				thread_n->is_full = TRUE;
// 				print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " PHILOSOPHER IS FULL");
// 				return (NULL);
// 			}
// 			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " is sleeping");
// 			usleep(thread_n->data->t_sleep * 1000);
// 		}
// 	}
// 	return (NULL);
// }

int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	sign;

	sign = 1;
	num = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - 48);
	return (sign * num);
}

long long	ft_atol_unsigned(const char *str)
{
	long long	i;
	unsigned long	num;
	int			sign;

	sign = 1;
	num = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - 48);
	if (num > 2147483647)
	{
		printf("overflow %li", num);
		exit (1);
	}
	return (num);
}

void	exit_error_message(char *str)
{
	printf("%s", str);
	exit (1);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (2048);
	else
		return (0);
}

int	ft_is_sign(char sign, char c)
{
	return (c == sign);
}

size_t	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_isother(int c)
{
	if (c >= '!' && c <= '*')
		return (1);
	else if (c == ',' || c == '.' || c == '/')
		return (1);
	else if (c >= ':' && c <= 127)
		return (1);
	return (0);
}

void	check_validity(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_is_sign('-', str[i]))
			exit_error_message("a value is not conform -> an arg is negative\n");
		if (ft_is_sign('+', str[i]) && (!str[i + 1] || ft_isdigit(str[i - 1]) != 0))
			exit_error_message("a value is not conform\n");
		else if (ft_is_sign('+', str[i]) && str[i + 1] == ' ')
			exit_error_message("a value is not conform\n");
		else if (ft_is_sign('+', str[i]) && ft_is_sign('+', str[i + 1]))
			exit_error_message("a value is not conform-> ++\n");
		else if (ft_isother(str[i]) == 1)
			exit_error_message("a value is not conform-> an arg is not a number\n");
		i++;
	}
}

void	check_space_arg(char *argv)
{

	int	i;

	i = 0;
	while (argv[i] == ' ')
			i++;
	if (i == (int)ft_strlen(argv))
			exit_error_message("a value is not conform -> arg without a value\n");
}

void	check_empty_arg(char *argv)
{
	if (!argv[0])
		exit_error_message("a value is not conform -> empty arg\n");

}

void philo_check_args(char **argv)
{
	int i;
	
	i = 1;
	while (argv[i])
	{
		check_empty_arg(argv[i]);
		check_space_arg(argv[i]);
		check_validity(argv[i]);
		i++;
	}
	
}

void init_data(t_data *data, char **argv)
{
	philo_check_args(argv);
	

	data->nbr_phi = 4;
	data->t_death = 310;
	data->t_eat= 200;
	data->t_sleep = 100;
	data->nbr_meals = 7;
	
	// data->nbr_meals = 1;
	// data->limited_meals = FALSE;
	
	// data->nbr_phi = ft_atoi(argv[1]);
	// data->t_death =  ft_atol_unsigned(argv[2]);
	// data->t_eat=  ft_atol_unsigned(argv[3]);
	// data->t_sleep =  ft_atol_unsigned(argv[4]);
	// if (argv[5])
	// {
	// 	data->nbr_meals =  ft_atoi(argv[5]);
	// 	data->limited_meals = TRUE;
	// }	
	
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
			// threads[i].meals_are_limited = data->limited_meals;
			threads[i].is_full = FALSE;
			threads[i].phi_num = i + 1;
			threads[i].data = data;
			threads[i].start_simu = data->start;
			threads[i].counter_meals_eaten = data->nbr_meals;
			threads[i].last_meal = data->start;
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
			// threads[i].one_dead = &data->one_dead;
			// threads[i].is_full = FALSE;
			// threads[i].phi_num = i + 1;
			// threads[i].data = data;
			// threads[i].start_simu = data->start;
			// threads[i].counter_meals_eaten = data->nbr_meals;
			// threads[i].last_meal = data->start;
			if( (i + 1) % 2 == 0)
			{
				ret = pthread_create(&threads[i].thread_id, NULL, philo_do_even, (void *) &threads[i]);
				if (ret)
				{
					printf("ERROR; return (code from pthread_create() is %d\n", ret);
					exit(-1);
				}
			}
			else
			{
				usleep(1000);
				ret = pthread_create(&threads[i].thread_id, NULL, philo_do_odd, (void *) &threads[i]);
				if (ret)
				{
					printf("ERROR; return (code from pthread_create() is %d\n", ret);
					exit(-1);
				}

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
	// pthread_mutex_destroy(&data->mtx_death);
}



int main(int argc, char **argv) 
{
	int nbr_places = 4;
	int i;
    t_philo_thread *threads;
	t_data data;
	
	if (argc > 6)
		exit_error_message("Too many args\n");
	init_data(&data, argv);
	threads = malloc(sizeof(t_philo_thread) * nbr_places);
	pthread_mutex_init(&data.mtx_print, NULL);
	// pthread_mutex_init(&data.mtx_death, NULL);//

	init_mutex(&data);
	init_thread(&data, threads);
	philo_is_dead(threads);
	join_and_destroy(&data, threads);
	free(threads);
	free(data.forks);
	return (0);
}
