/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 14:09:04 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/09/05 14:42:11 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	*ft_get_job_error(int sig)
{
	if (sig == SIGHUP || sig == SIGQUIT)
		return (sig == SIGHUP ? "Hangup" : "Quit");
	else if (sig == SIGILL || sig == SIGTRAP)
		return (sig == SIGILL ? "Illegal instruction" : "Trace/BPT trap");
	else if (sig == SIGABRT || sig == SIGEMT)
		return (sig == SIGABRT ? "Abort trap" : "EMT trap");
	else if (sig == SIGFPE || sig == SIGKILL)
		return (sig == SIGFPE ? "Floating point exception" : "Killed");
	else if (sig == SIGBUS || sig == SIGSEGV)
		return (sig == SIGBUS ? "Bus error" : "Segmentation fault");
	else if (sig == SIGSYS || sig == SIGALRM)
		return (sig == SIGSYS ? "Bad system call" : "Alarm clock");
	else if (sig == SIGTERM || sig == SIGXCPU)
		return (sig == SIGTERM ? "Terminated" : "Cputime limit exceeded");
	else if (sig == SIGXFSZ)
		return ("Filesize limit exceeded");
	else if (sig == SIGVTALRM)
		return ("Virtual timer expired");
	else if (sig == SIGPROF)
		return ("Profiling timer expired");
	else if (sig == SIGUSR1)
		return ("User defined signal 1");
	else
		return (sig == SIGUSR2 ? "User defined signal 2" : NULL);
}
