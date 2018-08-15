#include "ft_expansions.h"

static char	*check_brackets(char *pattern)
{
	char 	quote;

	quote = 0;
	while (*pattern)
	{
		if (!quote && *pattern == ']')
			return (pattern);
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

int 	check_vals(char *buf, char *buf_q, char *brackets_end, char *str)
{
	int		eq;
	int 	i;
	char 	j;

	eq = (*buf == '!' || *buf == '^') && !*buf_q ? 0 : 1;
	buf += eq ? 0 : 1;
	i = -1;
	while (buf[++i])
	{
		if (buf[i + 1] == '-' && buf[i + 2] && !buf_q[i + 1])
		{
			j = buf[i] - 1;
			i += 2;
			while (++j <= buf[i])
				if ((eq && j == *str) || (!eq && j != *str))
					return (ft_regex_str(brackets_end + 1, str + 1, 0));
		}
		else if ((eq && buf[i] == *str) || (!eq && buf[i] != *str))
			return (ft_regex_str(brackets_end + 1, str + 1, 0));
	}
}

void	get_vals(char *pattern, char *buf, char *buf_q, char *brackets_end)
{
	char 	quote;
	int 	i;

	quote = 0;
	i = 0;
	while (pattern != brackets_end)
	{
		if (*pattern == '\\' && pattern++)
			buf_q[i] = 1;
		else if (*pattern == '\'' || *pattern == '"' && !quote)
			quote = *pattern++;
		else if (*pattern == '\'' || *pattern == '"' && quote && pattern++)
			quote = 0;
		else
		{
			buf[i] = *pattern++;
			if (buf_q[i] != 1)
				buf_q[i] = quote;
			++i;
		}
	}
}

int			ft_regex_brackets(char *pattern, char *str, char q)
{
	char 	*brackets_end;
	char	buf[ft_strlen(pattern) + 1];
	char	buf_q[ft_strlen(pattern) + 1];

	if ((brackets_end = check_brackets(pattern)))
	{
		ft_bzero(buf, sizeof(buf));
		ft_bzero(buf_q, sizeof(buf));
		get_vals(pattern, buf, buf_q, brackets_end);
		return (check_vals(buf, buf_q, brackets_end, str));
	}
	else if (*pattern == *str)
		return (ft_regex_str(pattern + 1, str + 1, q));
	return (0);
}