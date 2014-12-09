/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 15:56:05 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/09 14:57:32 by ncolliau         ###   ########.fr       */
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

typedef struct			s_dirlist
{
	char				*name;
	struct s_dirlist	*next;
}						t_dirlist;

typedef struct			s_filelist
{
	char				*name;
	char				*dir_name;
	t_stat				*st;
	char				*path;
	struct s_filelist	*next;
}						t_filelist;

typedef struct			s_info
{
	size_t				nlink;
	size_t				size;
	size_t				uid;
	size_t				gid;
	size_t				total;
}						t_info;

#endif
