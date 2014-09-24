#ifndef __CONTEXTMANAGER_H__
#define __CONTEXTMANAGER_H__

typedef struct _ContextManager ContextManager;

ContextManager *new_ContextManager();

void delete_ContextManager();

void ContextManager_AddTask(ContextManager *self, void *data, void (callback_func)(void*));

#endif
