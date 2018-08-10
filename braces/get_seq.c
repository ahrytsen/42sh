#include "twenty_one_sh.h"

char	*check_braces(char *s);
char	*put_str_to_buf(char *buf, int *i, char *s);
void	print_lst(t_list *lst);
char	*get_brace_seq(char **s, t_list **lst);
char 	*put_backslash_to_buf(char *buf, int *i, char *s);
char 	*put_quote_content_to_buf(char *buf, int *i, char *s);
int		check_comma(char *s);

t_list	*get_num_range(char	**s)
{
	int 	lim1;
	int 	lim2;
	char 	*tmp;
	t_list	*lst;

	lst = NULL;
	lim1 = ft_atoi(++(*s));
	*s += ft_count_digits(lim1) + 2;
	lim2 = ft_atoi(*s);
	*s += ft_count_digits(lim2) + 1;
	if (lim1 < lim2)
		while (lim1 <= lim2)
		{
			tmp = ft_itoa(lim1++);
			ft_lstpush_back(&lst, tmp, ft_strlen(tmp) + 1);
			free(tmp);
		}
	else
		while (lim1 >= lim2)
		{
			tmp = ft_itoa(lim1--);
			ft_lstpush_back(&lst, tmp, ft_strlen(tmp) + 1);
			free(tmp);
		}
	return (lst);
}

t_list	*get_alpha_range(int lim1, int lim2, char **s)
{
	char	buf[2];
	t_list	*lst;

	lst = NULL;
	buf[1] = 0;
	if (lim1 < lim2)
		while (lim1 <= lim2)
		{
			buf[0] = lim1++;
			ft_lstpush_back(&lst, buf, 2);
		}
	else
		while (lim1 >= lim2)
		{
			buf[0] = lim1--;
			ft_lstpush_back(&lst, buf, 2);
		}
	*s += 6;
	return (lst);
}

t_list	*get_valid_range(char **s)
{
	t_list	*lst;
	int 	i;

	lst = NULL;
	i = 1;
	if (ft_isprint((*s)[1]) && (*s)[1] != ',' && (*s)[2] == '.' &&(*s)[3] == '.'
		&& ft_isprint((*s)[4]) && (*s)[4] != ','&& (*s)[5] == '}')
		lst = get_alpha_range((*s)[1], (*s)[4], s);
	else if (ft_isdigit((*s)[i]) || (*s)[i] == '+' || (*s)[i] == '-')
	{
		++i;
		while (ft_isdigit((*s)[i]))
			++i;
		if ((*s)[i] == '.' && (*s)[++i] == '.')
		{
			++i;
			if ((*s)[i] == '+' || (*s)[i] == '-')
				++i;
			if (ft_isdigit((*s)[i]))
			{
				while (ft_isdigit((*s)[i]))
					++i;
				if ((*s)[i] == '}')
					lst = get_num_range(s);
			}
		}
	}
	return (lst);
}


char	*get_one_elem(char *s, char *buf, t_list **lst)
{
	int 	i;
	int 	j;
	t_list	*vals;
	t_list	*tmp;

	i = ft_strlen(buf);
	while (*s)
		if (*s == ',')
		{
			++s;
			break ;
		}
		else if (*s == '}')
			break ;
		else if (*s && ft_strchr("\"'`", *s))
			s = put_quote_content_to_buf(buf, &i, s);
		else if (*s == '\\')
			s = put_backslash_to_buf(buf, &i, s);
		else if (*s == '{')
		{
			vals = NULL;
			s = get_brace_seq(&s, &vals);
			tmp = vals;
			while (vals->next)
			{
				j = i;
				put_str_to_buf(buf, &j, vals->content);
				get_one_elem(s, buf, lst);
				ft_bzero(buf + i, ft_strlen(buf + i));
				vals = vals->next;
			}
			put_str_to_buf(buf, &i, vals->content);
			ft_lstdel(&tmp, (void (*)(void *, size_t))free);
		}
		else
			buf[i++] = *s++;
	ft_lstpush_back(lst, buf, i + 1);
	return (s);
}

char	*get_brace_seq(char **s, t_list **lst)
{
	char 	buf[ft_strlen(*s) + 1];
	char 	*tmp;

	if ((*lst = get_valid_range(s)))
		return (*s);
	else if (!check_comma(*s))
	{
		*lst = NULL;
		return (*s);
	}
	tmp = *s + 1;
	while (*tmp && *tmp != '}')
	{
		ft_bzero(buf, ft_strlen(*s));
		tmp = get_one_elem(tmp, buf, lst);
	}
	if (*(tmp - 1) == ',')
		ft_lstpush_back(lst, "\0", 2);
	return (*tmp ? ++tmp : tmp);
}
