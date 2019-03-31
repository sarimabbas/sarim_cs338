#ifdef __cplusplus
extern "C" {
#endif

#include "concurrency.h"

void SerialPrintWrapper(char* msg);
psm* psmCreate(void);
void psmDestroy(psm** managerPtr);
void psmAddToBack(psm* manager, process_t* process);
void psmAddToFront(psm* manager, process_t* process);
process_t* psmRemoveFromFront(psm* manager);
void psmDeleteByPtr(psm* manager, process_t* process);
process_t* psmFind(psm* manager, unsigned int sp);
void psmPrint(psm* manager);

#ifdef __cplusplus
}
#endif
