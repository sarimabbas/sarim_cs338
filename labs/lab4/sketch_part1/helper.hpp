#ifdef __cplusplus
extern "C" {
#endif

#include "concurrency.h"

void SerialPrintWrapper(char* msg);
void pPrint(process_t* process);
psm* psmCreate(void);
void psmDestroy(psm** managerPtr);
void psmAddToBack(psm* manager, process_t* process);
void psmAddToFront(psm* manager, process_t* process);
process_t* psmRemoveFromFront(psm* manager);
process_t* psmRemoveByPtr(psm* manager, process_t* process);
process_t* psmFind(psm* manager, unsigned int sp);
void psmPrint(psm* manager);
void psmPush(psm* manager, unsigned int sp);

#ifdef __cplusplus
}
#endif
