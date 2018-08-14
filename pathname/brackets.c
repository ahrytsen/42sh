#include "ft_expansions.h"

//static char	*skip_quotes(char *pattern)
//{
//	char 	quote;
//
//	quote = *pattern;
//	while (*++pattern != quote)
//		if (*pattern == '\\')
//			++pattern;
//	return (pattern + 1);
//}

static char	*check_brackets(char *pattern)
{
	char 	quote;

	quote = 0;
	while (*pattern)
	{
		if (!quote && *pattern == ']')
			return (pattern + 1);
		else if (*pattern == '\\')
			++pattern;
		else if (*pattern == '\'' || *pattern == '"')
		{
			quote = *pattern++;
			while (*pattern != quote)
				++pattern;
			quote = 0;
		}
		++pattern;
	}
	return (0);
}

int 		brackets_range(char **pattern, char *str, int eq)
{
	char	min;
	char	max;
	char 	q;

	min = *(*pattern)++;
	max = *++*pattern;
	q = 0;
	while (min <= max)
	{
//		if (**pattern == '\\')
//			++pattern;
//		else if ((**pattern == '\'' || **pattern == '"') && !q)
//			q = *(*pattern++);
//		else if (**pattern == q)
//		{
//			q = 0;
//			++*pattern;
//		}
		if (eq && min == *str)
			return (1);
		else if (!eq && min != *str)
			return (1);
		++min;
	}
	return (0);
}

int			ft_regex_brackets(char *pattern, char *str, char q)
{
	int 	eq;
	char 	*brackets_end;

	if ((brackets_end = check_brackets(pattern)))
	{
		eq = *pattern == '!' || *pattern == '^' ? 0 : 1;
		pattern += *pattern == '!' || *pattern == '^' ? 1 : 0;
		while (pattern + 1 != brackets_end)
		{
			if (!q && *(pattern + 1) == '-' && pattern + 2 != brackets_end
				&& brackets_range(&pattern, str, eq))
				return (ft_regex_str(brackets_end, str + 1, q));
			if (*pattern == '\\')
				++pattern;
			else if ((*pattern == '\'' || *pattern == '"') && !q)
				q = *pattern++;
			else if (*pattern == q)
			{
				q = 0;
				++pattern;
			}
			if (eq && *pattern == *str)
				return (ft_regex_str(brackets_end, str + 1, q));
			else if (!eq && *pattern != *str)
				return (ft_regex_str(brackets_end, str + 1, q));
			++pattern;
		}
	}
	else if (*pattern == *str)
		return (ft_regex_str(pattern + 1, str + 1, q));
	return (0);
}