#ifndef JEWELRYDATABASELAYER_GLOBAL_H
#define JEWELRYDATABASELAYER_GLOBAL_H

#include <Qt/qglobal.h>

#ifdef JEWELRYDATABASELAYER_LIB
# define JEWELRYDATABASELAYER_EXPORT Q_DECL_EXPORT
#else
# define JEWELRYDATABASELAYER_EXPORT Q_DECL_IMPORT
#endif

#endif // JEWELRYDATABASELAYER_GLOBAL_H