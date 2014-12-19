/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 15:56:05 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/19 10:38:22 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include "libft.h"

# define NAME 1
# define NO_NAME 0

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

typedef struct			s_dlist
{
	char				*name;
	struct s_dlist		*next;
}						t_dlist;

typedef struct			s_flist
{
	char				*name;
	char				*dir_name;
	t_stat				st;
	char				*path;
	struct s_flist		*next;
}						t_flist;

typedef struct			s_info
{
	size_t				nlink;
	size_t				size;
	size_t				uid;
	size_t				gid;
	size_t				dev;
	size_t				total;
}						t_info;

#endif
