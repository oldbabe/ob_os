#ifndef EDITORLOG_GLOBAL_H
#define EDITORLOG_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EDITORLOG_LIBRARY)
#  define EDITORLOG_EXPORT Q_DECL_EXPORT
#else
#  define EDITORLOG_EXPORT Q_DECL_IMPORT
#endif


#endif // EDITORLOG_GLOBAL_H
