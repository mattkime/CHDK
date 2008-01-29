#ifndef VMWORKS_H
#define VMWORKS_H


extern const char *_taskName(int tid);
#define taskName _taskName


extern int _taskIdListGet(int idList[], int maxTasks);
#define taskIdListGet _taskIdListGet


#endif
