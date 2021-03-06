/*	Public domain	*/

#ifndef _AGAR_CORE_EXEC_H_
#define _AGAR_CORE_EXEC_H_
#include <agar/core/begin.h>

#include <agar/config/have_execvp.h>

#ifdef HAVE_EXECVP
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#endif

enum ag_exec_wait_type {
	AG_EXEC_WAIT_IMMEDIATE,
	AG_EXEC_WAIT_INFINITE
};

#ifdef HAVE_EXECVP
typedef pid_t AG_ProcessID;
#else
typedef int AG_ProcessID;
#endif

__BEGIN_DECLS
AG_ProcessID AG_Execute(const char *, char **);
AG_ProcessID AG_WaitOnProcess(AG_ProcessID, enum ag_exec_wait_type);
int AG_Kill(AG_ProcessID);
__END_DECLS

#include <agar/core/close.h>
#endif /* _AGAR_CORE_EXEC_H_ */
