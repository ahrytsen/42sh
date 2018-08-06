/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_autocomp_filenames.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 15:05:56 by dlinkin           #+#    #+#             */
/*   Updated: 2018/08/02 15:06:15 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_sh.h"

static void		rl_choose_mr_anderson(t_list **lst, char *name, char *path)
{
	struct stat	st;
	char		*full;

	full = ft_strjoin(path, name);
	if (!lstat(full, &st) && (st.st_mode & 0xf000) == 0x4000)
	{
		free(full);
		full = ft_strjoin(name, "/");
	}
	else
	{
		free(full);
		full = ft_strjoin(name, " ");
	}
	ft_lstadd_end(lst, ft_lstnew((void *)full, ft_strlen(full) + 1));
	free(full);
}

static t_list	*rl_filename_overseer(char *path, char *str, size_t len)
{
	t_list			*list;
	DIR				*directory;
	struct dirent	*file;

	list = NULL;
	if ((directory = opendir(path)))
	{
		while ((file = readdir(directory)))
		{
			if ((file->d_name[0] != '.' || (*str == '.'
				&& ft_strcmp(file->d_name, ".")
				&& ft_strcmp(file->d_name, "..")))
				&& !ft_strncmp(str, file->d_name, len))
				rl_choose_mr_anderson(&list, file->d_name, path);
		}
		closedir(directory);
	}
	return (ft_lstsort(list));
}

char			*ft_rl_search_filename(char *str, size_t len)
{
	char			*ptr;
	char			path[NAMESIZE];
	t_list			*list;

	if (*str == '~' && *(str + 1) == '/' && (ptr = ft_getenv("HOME")))
	{
		ft_strcpy(path, ptr);
		ptr = ft_strrchr(++str, '/');
		len = ft_strlen(ptr + 1);
		ft_strncat(path, str, ptr + 1 - str);
		str += ptr + 1 - str;
	}
	else if ((ptr = ft_strrchr(str, '/')))
	{
		len = ft_strlen(ptr + 1);
		ft_strncpy(path, str, ptr + 1 - str);
		path[ptr + 1 - str] = '\0';
		str += ptr + 1 - str;
	}
	else
		ft_strcpy(path, "./");
	list = rl_filename_overseer(path, str, len);
	if (!list && write(0, "\a", 1))
		return (NULL);
	return (ft_rl_match_drawer(list, str));
}
