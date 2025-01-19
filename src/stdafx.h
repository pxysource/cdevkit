#ifndef STD_AFX_H_
#define STD_AFX_H_

#if defined(_MSC_VER)
# ifdef CDEVKIT_LIBRARY
#  define CDEVKIT_EXPORT __declspec(dllexport)
# else
#  define CDEVKIT_EXPORT __declspec(dllimport)
# endif
#else
# define CDEVKIT_EXPORT
#endif

#ifdef __cplusplus
# define CDEVKIT_DECLS_BEGIN extern "C" {
# define CDEVKIT_DECLS_END }
#else
# define CDEVKIT_DECLS_BEGIN
# define CDEVKIT_DECLS_END
#endif

#endif  // STD_AFX_H_