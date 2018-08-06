#include "twenty_one_sh.h"

char	*check_braces(char *s);

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
			ft_lstpush_back(&lst, tmp, 2);
			free(tmp);
		}
	else
		while (lim2 >= lim1)
		{
			tmp = ft_itoa(lim2--);
			ft_lstpush_back(&lst, tmp, 2);
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
		while (lim2 >= lim1)
		{
			buf[0] = lim2--;
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
	if (ft_isalpha((*s)[1]) && (*s)[2] == '.' &&(*s)[3] == '.'
		&& ft_isalpha((*s)[4]) && (*s)[5] == '}')
		lst = get_alpha_range((*s)[4], (*s)[1], s);
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
			while (ft_isdigit((*s)[i]))
				++i;
			if ((*s)[i] == '}')
				lst = get_num_range(s);
		}
	}
	return (lst);
}

t_list	*get_brace_seq(char **s)
{
	char 		*simple_braces;
	char		**vals;
	t_list		*vals_lst;

	if (!(vals_lst = get_valid_range(s)))
	{
		vals = ft_strsplit(ft_strsub(*s, 1, 3), ',');
		while (*vals)
		{
			ft_lstpush_back(&vals_lst, *vals, ft_strlen(*vals) + 1);
			++vals;
		}
		*s += 5;
	}
	return (vals_lst);
}