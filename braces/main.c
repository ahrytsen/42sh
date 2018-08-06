#include "twenty_one_sh.h"

t_list	*get_brace_seq(char **s);
t_list	*get_valid_range(char **s);
t_list	*get_alpha_range(int lim1, int lim2, char **s);
t_list	*get_num_range(char	**s);

void		print_lst(t_list *lst)
{
	while (lst)
	{
		ft_printf("%s\n", lst->content);
		lst = lst->next;
	}
}

//char 	*strchr_unquoted()

char 	*skip_quotes(char *s)
{
	char 	c;

	c = *s;
	while (++*s)
		if (*s == '\\')
			++s;
		else if (*s == c)
			return (s);
}

char	*check_braces(char *s)
{
	while (*s++)
		if (*s == '\\')
			++*s;
		else if (ft_strchr("\"'`", *s))
			s = skip_quotes(s);
		else if (*s == '}')
			break ;
		else if (*s == '{')
			s = check_braces(s);
	return (s);
}

t_list	*expand_braces(char *s, int i,  char *buf)
{
	t_list	*vals;
	t_list	*vals_first;
	t_list	*ret;

	ret = NULL;
	while (*s)
		if (*s == '{')
		{
			vals_first = get_brace_seq(&s);
			vals = vals_first->next;
			print_lst(vals_first);
			ft_printf("---------------------------\n\n");
			while (vals)
			{
				buf[i] = *(char *)vals->content;
				ft_lstadd_list(&ret, expand_braces(s, i + 1, buf));
				vals = vals->next;
			}
			buf[i++] = *(char *)vals_first->content;
		}
		else
			buf[i++] = *s++;
	ft_lstpush_front(&ret, buf, 500);
	return (ret);
}

int 	main(int ac, char **av)
{
	char 	buf[500];
	int 	i;
	t_list	*toks = ft_lstnew("{1,2}{3,4}", ft_strlen("{1,2}{3,4}") + 1);

	ft_bzero(buf, 500);
	i = 0;
//	expand_braces("a{1,2}b{3,4}c{5,6d}", i, buf);
	print_lst(expand_braces("{1,2}{F,G}", i, buf));

//	print_lst(expand_braces("{1,2}{3,4}{5,6}", i, buf));

}