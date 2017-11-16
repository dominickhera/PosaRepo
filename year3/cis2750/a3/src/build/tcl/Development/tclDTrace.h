/*
 * Generated by dtrace(1M).
 */

#ifndef	_TCLDTRACE_H
#define	_TCLDTRACE_H

#include <unistd.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define TCL_STABILITY "___dtrace_stability$tcl$v1$5_5_5_1_1_5_1_1_5_5_5_5_5_5_5"

#define TCL_TYPEDEFS "___dtrace_typedefs$tcl$v2$54636c445472616365537472"

#if !defined(DTRACE_PROBES_DISABLED) || !DTRACE_PROBES_DISABLED

#define	TCL_CMD_ARGS(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) \
do { \
	__asm__ volatile(".reference " TCL_TYPEDEFS); \
	__dtrace_probe$tcl$cmd__args$v1$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); \
	__asm__ volatile(".reference " TCL_STABILITY); \
} while (0)
#define	TCL_CMD_ARGS_ENABLED() \
	({ int _r = __dtrace_isenabled$tcl$cmd__args$v1(); \
		__asm__ volatile(""); \
		_r; })
#define	TCL_CMD_ENTRY(arg0, arg1, arg2) \
do { \
	__asm__ volatile(".reference " TCL_TYPEDEFS); \
	__dtrace_probe$tcl$cmd__entry$v1$54636c445472616365537472$696e74$7374727563742054636c5f4f626a202a2a(arg0, arg1, arg2); \
	__asm__ volatile(".reference " TCL_STABILITY); \
} while (0)
#define	TCL_CMD_ENTRY_ENABLED() \
	({ int _r = __dtrace_isenabled$tcl$cmd__entry$v1(); \
		__asm__ volatile(""); \
		_r; })
#define	TCL_CMD_INFO(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
do { \
	__asm__ volatile(".reference " TCL_TYPEDEFS); \
	__dtrace_probe$tcl$cmd__info$v1$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$696e74$696e74$54636c445472616365537472$54636c445472616365537472(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); \
	__asm__ volatile(".reference " TCL_STABILITY); \
} while (0)
#define	TCL_CMD_INFO_ENABLED() \
	({ int _r = __dtrace_isenabled$tcl$cmd__info$v1(); \
		__asm__ volatile(""); \
		_r; })
#define	TCL_CMD_RESULT(arg0, arg1, arg2, arg3) \
do { \
	__asm__ volatile(".reference " TCL_TYPEDEFS); \
	__dtrace_probe$tcl$cmd__result$v1$54636c445472616365537472$696e74$54636c445472616365537472$7374727563742054636c5f4f626a202a(arg0, arg1, arg2, arg3); \
	__asm__ volatile(".reference " TCL_STABILITY); \
} while (0)
#define	TCL_CMD_RESULT_ENABLED() \
	({ int _r = __dtrace_isenabled$tcl$cmd__result$v1(); \
		__asm__ volatile(""); \
		_r; })
#define	TCL_CMD_RETURN(arg0, arg1) \
do { \
	__asm__ volatile(".reference " TCL_TYPEDEFS); \
	__dtrace_probe$tcl$cmd__return$v1$54636c445472616365537472$696e74(arg0, arg1); \
	__asm__ volatile(".reference " TCL_STABILITY); \
} while (0)
#define	TCL_CMD_RETURN_ENABLED() \
	({ int _r = __dtrace_isenabled$tcl$cmd__return$v1(); \
		__asm__ volatile(""); \
		_r; })
#define	TCL_INST_DONE(arg0, arg1, arg2) \
do { \
	__asm__ volatile(".reference " TCL_TYPEDEFS); \
	__dtrace_probe$tcl$inst__done$v1$54636c445472616365537472$696e74$7374727563742054636c5f4f626a202a2a(arg0, arg1, arg2); \
	__asm__ volatile(".reference " TCL_STABILITY); \
} while (0)
#define	TCL_INST_DONE_ENABLED() \
	({ int _r = __dtrace_isenabled$tcl$inst__done$v1(); \
		__asm__ volatile(""); \
		_r; })
#define	TCL_INST_START(arg0, arg1, arg2) \
do { \
	__asm__ volatile(".reference " TCL_TYPEDEFS); \
	__dtrace_probe$tcl$inst__start$v1$54636c445472616365537472$696e74$7374727563742054636c5f4f626a202a2a(arg0, arg1, arg2); \
	__asm__ volatile(".reference " TCL_STABILITY); \
} while (0)
#define	TCL_INST_START_ENABLED() \
	({ int _r = __dtrace_isenabled$tcl$inst__start$v1(); \
		__asm__ volatile(""); \
		_r; })
#define	TCL_OBJ_CREATE(arg0) \
do { \
	__asm__ volatile(".reference " TCL_TYPEDEFS); \
	__dtrace_probe$tcl$obj__create$v1$7374727563742054636c5f4f626a202a(arg0); \
	__asm__ volatile(".reference " TCL_STABILITY); \
} while (0)
#define	TCL_OBJ_CREATE_ENABLED() \
	({ int _r = __dtrace_isenabled$tcl$obj__create$v1(); \
		__asm__ volatile(""); \
		_r; })
#define	TCL_OBJ_FREE(arg0) \
do { \
	__asm__ volatile(".reference " TCL_TYPEDEFS); \
	__dtrace_probe$tcl$obj__free$v1$7374727563742054636c5f4f626a202a(arg0); \
	__asm__ volatile(".reference " TCL_STABILITY); \
} while (0)
#define	TCL_OBJ_FREE_ENABLED() \
	({ int _r = __dtrace_isenabled$tcl$obj__free$v1(); \
		__asm__ volatile(""); \
		_r; })
#define	TCL_PROC_ARGS(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) \
do { \
	__asm__ volatile(".reference " TCL_TYPEDEFS); \
	__dtrace_probe$tcl$proc__args$v1$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); \
	__asm__ volatile(".reference " TCL_STABILITY); \
} while (0)
#define	TCL_PROC_ARGS_ENABLED() \
	({ int _r = __dtrace_isenabled$tcl$proc__args$v1(); \
		__asm__ volatile(""); \
		_r; })
#define	TCL_PROC_ENTRY(arg0, arg1, arg2) \
do { \
	__asm__ volatile(".reference " TCL_TYPEDEFS); \
	__dtrace_probe$tcl$proc__entry$v1$54636c445472616365537472$696e74$7374727563742054636c5f4f626a202a2a(arg0, arg1, arg2); \
	__asm__ volatile(".reference " TCL_STABILITY); \
} while (0)
#define	TCL_PROC_ENTRY_ENABLED() \
	({ int _r = __dtrace_isenabled$tcl$proc__entry$v1(); \
		__asm__ volatile(""); \
		_r; })
#define	TCL_PROC_INFO(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
do { \
	__asm__ volatile(".reference " TCL_TYPEDEFS); \
	__dtrace_probe$tcl$proc__info$v1$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$696e74$696e74$54636c445472616365537472$54636c445472616365537472(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); \
	__asm__ volatile(".reference " TCL_STABILITY); \
} while (0)
#define	TCL_PROC_INFO_ENABLED() \
	({ int _r = __dtrace_isenabled$tcl$proc__info$v1(); \
		__asm__ volatile(""); \
		_r; })
#define	TCL_PROC_RESULT(arg0, arg1, arg2, arg3) \
do { \
	__asm__ volatile(".reference " TCL_TYPEDEFS); \
	__dtrace_probe$tcl$proc__result$v1$54636c445472616365537472$696e74$54636c445472616365537472$7374727563742054636c5f4f626a202a(arg0, arg1, arg2, arg3); \
	__asm__ volatile(".reference " TCL_STABILITY); \
} while (0)
#define	TCL_PROC_RESULT_ENABLED() \
	({ int _r = __dtrace_isenabled$tcl$proc__result$v1(); \
		__asm__ volatile(""); \
		_r; })
#define	TCL_PROC_RETURN(arg0, arg1) \
do { \
	__asm__ volatile(".reference " TCL_TYPEDEFS); \
	__dtrace_probe$tcl$proc__return$v1$54636c445472616365537472$696e74(arg0, arg1); \
	__asm__ volatile(".reference " TCL_STABILITY); \
} while (0)
#define	TCL_PROC_RETURN_ENABLED() \
	({ int _r = __dtrace_isenabled$tcl$proc__return$v1(); \
		__asm__ volatile(""); \
		_r; })
#define	TCL_TCL_PROBE(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) \
do { \
	__asm__ volatile(".reference " TCL_TYPEDEFS); \
	__dtrace_probe$tcl$tcl__probe$v1$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); \
	__asm__ volatile(".reference " TCL_STABILITY); \
} while (0)
#define	TCL_TCL_PROBE_ENABLED() \
	({ int _r = __dtrace_isenabled$tcl$tcl__probe$v1(); \
		__asm__ volatile(""); \
		_r; })


extern void __dtrace_probe$tcl$cmd__args$v1$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472(TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr);
extern int __dtrace_isenabled$tcl$cmd__args$v1(void);
extern void __dtrace_probe$tcl$cmd__entry$v1$54636c445472616365537472$696e74$7374727563742054636c5f4f626a202a2a(TclDTraceStr, int, struct Tcl_Obj **);
extern int __dtrace_isenabled$tcl$cmd__entry$v1(void);
extern void __dtrace_probe$tcl$cmd__info$v1$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$696e74$696e74$54636c445472616365537472$54636c445472616365537472(TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, int, int, TclDTraceStr, TclDTraceStr);
extern int __dtrace_isenabled$tcl$cmd__info$v1(void);
extern void __dtrace_probe$tcl$cmd__result$v1$54636c445472616365537472$696e74$54636c445472616365537472$7374727563742054636c5f4f626a202a(TclDTraceStr, int, TclDTraceStr, const struct Tcl_Obj *);
extern int __dtrace_isenabled$tcl$cmd__result$v1(void);
extern void __dtrace_probe$tcl$cmd__return$v1$54636c445472616365537472$696e74(TclDTraceStr, int);
extern int __dtrace_isenabled$tcl$cmd__return$v1(void);
extern void __dtrace_probe$tcl$inst__done$v1$54636c445472616365537472$696e74$7374727563742054636c5f4f626a202a2a(TclDTraceStr, int, struct Tcl_Obj **);
extern int __dtrace_isenabled$tcl$inst__done$v1(void);
extern void __dtrace_probe$tcl$inst__start$v1$54636c445472616365537472$696e74$7374727563742054636c5f4f626a202a2a(TclDTraceStr, int, struct Tcl_Obj **);
extern int __dtrace_isenabled$tcl$inst__start$v1(void);
extern void __dtrace_probe$tcl$obj__create$v1$7374727563742054636c5f4f626a202a(const struct Tcl_Obj *);
extern int __dtrace_isenabled$tcl$obj__create$v1(void);
extern void __dtrace_probe$tcl$obj__free$v1$7374727563742054636c5f4f626a202a(const struct Tcl_Obj *);
extern int __dtrace_isenabled$tcl$obj__free$v1(void);
extern void __dtrace_probe$tcl$proc__args$v1$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472(TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr);
extern int __dtrace_isenabled$tcl$proc__args$v1(void);
extern void __dtrace_probe$tcl$proc__entry$v1$54636c445472616365537472$696e74$7374727563742054636c5f4f626a202a2a(TclDTraceStr, int, struct Tcl_Obj **);
extern int __dtrace_isenabled$tcl$proc__entry$v1(void);
extern void __dtrace_probe$tcl$proc__info$v1$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$696e74$696e74$54636c445472616365537472$54636c445472616365537472(TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, int, int, TclDTraceStr, TclDTraceStr);
extern int __dtrace_isenabled$tcl$proc__info$v1(void);
extern void __dtrace_probe$tcl$proc__result$v1$54636c445472616365537472$696e74$54636c445472616365537472$7374727563742054636c5f4f626a202a(TclDTraceStr, int, TclDTraceStr, const struct Tcl_Obj *);
extern int __dtrace_isenabled$tcl$proc__result$v1(void);
extern void __dtrace_probe$tcl$proc__return$v1$54636c445472616365537472$696e74(TclDTraceStr, int);
extern int __dtrace_isenabled$tcl$proc__return$v1(void);
extern void __dtrace_probe$tcl$tcl__probe$v1$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472$54636c445472616365537472(TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr, TclDTraceStr);
extern int __dtrace_isenabled$tcl$tcl__probe$v1(void);

#else

#define	TCL_CMD_ARGS(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) \
do { \
	} while (0)
#define	TCL_CMD_ARGS_ENABLED() (0)
#define	TCL_CMD_ENTRY(arg0, arg1, arg2) \
do { \
	} while (0)
#define	TCL_CMD_ENTRY_ENABLED() (0)
#define	TCL_CMD_INFO(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
do { \
	} while (0)
#define	TCL_CMD_INFO_ENABLED() (0)
#define	TCL_CMD_RESULT(arg0, arg1, arg2, arg3) \
do { \
	} while (0)
#define	TCL_CMD_RESULT_ENABLED() (0)
#define	TCL_CMD_RETURN(arg0, arg1) \
do { \
	} while (0)
#define	TCL_CMD_RETURN_ENABLED() (0)
#define	TCL_INST_DONE(arg0, arg1, arg2) \
do { \
	} while (0)
#define	TCL_INST_DONE_ENABLED() (0)
#define	TCL_INST_START(arg0, arg1, arg2) \
do { \
	} while (0)
#define	TCL_INST_START_ENABLED() (0)
#define	TCL_OBJ_CREATE(arg0) \
do { \
	} while (0)
#define	TCL_OBJ_CREATE_ENABLED() (0)
#define	TCL_OBJ_FREE(arg0) \
do { \
	} while (0)
#define	TCL_OBJ_FREE_ENABLED() (0)
#define	TCL_PROC_ARGS(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) \
do { \
	} while (0)
#define	TCL_PROC_ARGS_ENABLED() (0)
#define	TCL_PROC_ENTRY(arg0, arg1, arg2) \
do { \
	} while (0)
#define	TCL_PROC_ENTRY_ENABLED() (0)
#define	TCL_PROC_INFO(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
do { \
	} while (0)
#define	TCL_PROC_INFO_ENABLED() (0)
#define	TCL_PROC_RESULT(arg0, arg1, arg2, arg3) \
do { \
	} while (0)
#define	TCL_PROC_RESULT_ENABLED() (0)
#define	TCL_PROC_RETURN(arg0, arg1) \
do { \
	} while (0)
#define	TCL_PROC_RETURN_ENABLED() (0)
#define	TCL_TCL_PROBE(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) \
do { \
	} while (0)
#define	TCL_TCL_PROBE_ENABLED() (0)

#endif /* !defined(DTRACE_PROBES_DISABLED) || !DTRACE_PROBES_DISABLED */


#ifdef	__cplusplus
}
#endif

#endif	/* _TCLDTRACE_H */
