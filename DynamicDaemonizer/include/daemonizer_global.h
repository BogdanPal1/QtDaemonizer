#ifndef DAEMONIZER_GLOBAL_H
#define DAEMONIZER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DAEMONIZER_LIBRARY)
#  define DAEMONIZERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DAEMONIZERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DAEMONIZER_GLOBAL_H
