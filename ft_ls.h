/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 15:56:05 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/20 15:11:08 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "libft.h"

# define DISP_NAME 1
# define DO_NOT_DISP_NAME 0

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

typedef struct			s_options
{
	int					l;
	int					r_caps;
	int					r;
	int					a;
	int					t;
}						t_options;

void					disp_if_needed(t_dirent *sdir, t_options *is_option);
int						opendir_and_list(char *dir_name, t_options *is_option, int disp_name_dir);
void					do_ls(int argc, char **argv, t_options *is_option);

int						is_option(char c);
int						check_error_options(char *arg);

t_options				*init_options_to_zero(t_options *is_option);
t_options				*get_options(t_options *is_option, char c);
int						check_options(char **arg, t_options *is_option);

#endif
