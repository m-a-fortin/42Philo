/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:34:51 by mafortin          #+#    #+#             */
/*   Updated: 2021/11/14 12:37:05 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo_utils.h"
# include <pthread.h>
# include <stdbool.h>

typedef enum e_state
{
	SLEEP,
	EAT,
	THINK,
	DEAD,
}	t_state;

typedef struct s_rules
{
	unsigned long	r_eat;
	unsigned long	r_die;
	unsigned long	r_sleep;
	unsigned long	start;
}	t_rules;

typedef struct s_table
{
	pthread_t			th;
	int					id;
	int					index;
	int					nb_meal;
	unsigned long		starving;
	bool				b_fork;
	pthread_mutex_t		m_fork;
	t_state				state;
	struct s_args		*data;
}	t_table;

typedef struct s_args
{
	int				nb_philo;
	int				nb_done;
	int				nb_meal;
	unsigned long	time_save;
	bool			game_over;
	bool			b_meal;
	int				*queue;
	struct s_rules	time;
	struct s_table	*philo;
	pthread_mutex_t	m_write;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_meal;
}	t_args;

//EXEC
unsigned long	ph_get_time(void);
bool			ph_exec_main(t_args *data);
void			ph_print_util(int id, unsigned long t, char *s, t_args *data);
bool			ph_print_state(t_args *data, char *string, t_table *philo);
bool			ph_starvation(t_table *philo, t_args *data);
bool			ph_join(t_args *data);
bool			ph_print_state(t_args *data, char *string, t_table *philo);
void			ph_solo(t_table *philo, t_args *data);
void			ph_first_turn(t_args *data, t_table *philo);
//ACTIVITY
bool			ph_wait(t_args *data, long time_to, t_table *philo);
bool			ph_take_forks(t_table *p, t_table *n_philo, t_args *data);
bool			ph_sleep(t_table *philo, t_args *data);
bool			ph_eat(t_table *philo, t_table *next_philo, t_args *data);
bool			ph_think(t_table *philo, t_table *next_philo, t_args *data);
//ERROR
bool			ph_parsing_error(char type);
bool			ph_perror(void);
//PARSING & INIT
bool			ph_parsing_args(int argc, char **argv, t_args *data);
bool			ph_init_main(t_args *data);

#endif