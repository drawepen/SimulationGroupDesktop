#ifndef ACTIONLIB_GLOBAL_H
#define ACTIONLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ACTIONLIB_LIBRARY)
#  define ACTIONLIB_EXPORT Q_DECL_EXPORT
#else
#  define ACTIONLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // ACTIONLIB_GLOBAL_H
