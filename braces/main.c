#include <stdbool.h>
#include "twenty_one_sh.h"

t_list		*regex(char *pattern);

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

bool	check_braces(char *braces)
{
//	while ()
	return (1);
}

t_list	*get_brace_seq(char *s)
{
	char 	**vals;
	t_list	*vals_lst;

	vals_lst = NULL;
	vals = ft_strsplit(s, ',');
	while (*vals)
	{
		ft_lstpush_back(&vals_lst, *vals, ft_strlen(*vals) + 1);
		++vals;
	}
	return (vals_lst);
}

void	lstadd_list(t_list **alst, t_list *new)
{
	t_list	*tmp;

	if (alst && new)
	{
		tmp = new;
		while (new->next)
			new = new->next;
		new->next = *alst;
		*alst = tmp;
	}
}

t_list	*expand_braces(char *s, int i,  char *buf)
{
	t_list	*vals;
	t_list	*vals_first;
	t_list	*ret;
	t_list	*tmp;

	ret = NULL;
	while (*s)
	{
		if (*s == '{')
		{
			vals_first = get_brace_seq(ft_strsub(s++, 1, 3));
			s += 4;
			vals = vals_first->next;
			while (vals)
			{
				buf[i] = *(char *)vals->content;
				lstadd_list(&ret, expand_braces(s, i + 1, buf));
				ft_printf("\n------------------------\n");
				print_lst(ret);
				vals = vals->next;
			}
			buf[i++] = *(char *)vals_first->content;
		}
		else
			buf[i++] = *s++;
	}
	ft_lstpush_front(&ret, buf, 500);
	ft_printf("\n------------------------\n");
	print_lst(ret);
	return (ret);
}

int 	main(int ac, char **av)
{
	char 	buf[500];
	int 	i;
	t_list	*toks = ft_lstnew("{1,2}{3,4}", ft_strlen("{1,2}{3,4}") + 1);

	ft_bzero(buf, 500);
	i = 0;
	expand_braces("{1,2}{3,4}{5,6}", i, buf);
//	print_lst(expand_braces("{1,2}{3,4}{5,6}", i, buf));

}