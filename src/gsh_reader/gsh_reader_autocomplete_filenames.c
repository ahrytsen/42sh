/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader_autocomplete_filenames.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 16:35:04 by dlinkin           #+#    #+#             */
/*   Updated: 2018/05/03 16:35:05 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

static void		choose_mr_anderson(t_list **lst, char *name, char *path)
{
	struct stat	st;
	char		*full;

	full = ft_strjoin(path, name);
	if (!lstat(full, &st) && (st.st_mode & 0xf000) == 0x4000)
	{
		free(full);
		full = ft_strjoin(name, "/");
		ft_lstpushback(lst, ft_lstnew((void *)full, ft_strlen(full) + 1));
		free(full);
	}
	else
	{
		free(full);
		ft_lstpushback(lst, ft_lstnew((void *)name, ft_strlen(name) + 1));
	}
}

static t_list	*filename_overseer(char *path, char *str, size_t len)
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
	&& ft_strcmp(file->d_name, ".") && ft_strcmp(file->d_name, "..")))
	&& !ft_strncmp(str, file->d_name, len))
				choose_mr_anderson(&list, file->d_name, path);
		}
		closedir(directory);
	}
	return (ft_lstsort(list));
}

int				get_max_name(t_list *lst)
{
	size_t max;

	max = 0;
	while (lst)
	{
		if (max < lst->content_size - 1)
			max = lst->content_size - 1;
		lst = lst->next;
	}
	max += 2;
	return ((int)max);
}

void			gogo_filename(char *str, size_t len, t_pos *pos, char *out)
{
	char			*ptr;
	char			path[NAMESIZE];
	t_list			*list;

	if (*str == '~')
	{
		ptr = gsh_get_env("HOME");
		ft_memmove(str + ft_strlen(ptr), str + 1, len);
		ft_strncpy(str, ptr, ft_strlen(ptr));
	}
	if ((ptr = ft_strrchr(str, '/')))
	{
		len = ft_strlen(ptr + 1);
		ft_strncpy(path, str, ptr + 1 - str);
		path[ptr + 1 - str] = 0;
		str += ptr + 1 - str;
	}
	else
		ft_strcpy(path, "./");
	list = filename_overseer(path, str, ft_strlen(str));
	reprint(list, out, pos, len);
}
