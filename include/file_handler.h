#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif

int saveRecordsToFile(const char* filename);
int loadRecordsFromFile(const char* filename);

#ifdef __cplusplus
}
#endif

#endif