#include <stdbool.h>
#include "twenty_one_sh.h"

t_list		*regex(char *pattern);

void		print_regex_lst(t_list *lst)
{
	while (lst)
	{
		ft_printf("%s\n", lst->content);
		lst = lst->next;
	}
}

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

bool	check_brace_quote(char *s)
{
	while (*s)
	{
		if (ft_strchr("\"'`", *s))
			s = skip_quotes(s);
		else if (*s == '\\')
			++s;
		else if (*s == ' ')
			return (false);
		++s;
	}
	return (true);
}

bool	check_braces(char *pattern)
{
//	if (strchr_spec(pattern, ','))
//		return (true);
//	return (false);
	while (*pattern)
	{
		if (ft_strchr("\"'`", *pattern))
			pattern = skip_quotes(pattern);
		else if (*pattern == '\\')
			++pattern;
		else if (*pattern == ' ')
			return (false);
		++pattern;
	}
	return ()
}

int 	main(int ac, char **av)
{
	char 	*pat = "{1,,2,}";

	return (check_braces(pat));
//	print_regex_lst(regex("/*"));
}