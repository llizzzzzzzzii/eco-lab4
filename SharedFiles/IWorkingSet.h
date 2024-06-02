/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IWorkingSet
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IWorkingSet
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_WORKINGSET_H__
#define __I_WORKINGSET_H__

#include "IEcoBase1.h"

/* IWorkingSet IID = {7A365205-1F7B-4E7F-A01B-DCF950DB01BC} */
#ifndef __IID_IWorkingSet
static const UGUID IID_IWorkingSet = {0x01, 0x10, 0x7A, 0x36, 0x52, 0x05, 0x1F, 0x7B, 0x4E, 0x7F, 0xA0, 0x1B, 0xDC, 0xF9, 0x50, 0xDB, 0x01, 0xBC};
#endif /* __IID_IWorkingSet */

typedef struct IWorkingSetVTbl {

    /* IEcoUnknown */
    int16_t(ECOCALLMETHOD* QueryInterface)(/* in */ struct IWorkingSet* me, /* in */ const UGUID* riid, /* out */ void** ppv);
    uint32_t(ECOCALLMETHOD* AddRef)(/* in */ struct IWorkingSet* me);
    uint32_t(ECOCALLMETHOD* Release)(/* in */ struct IWorkingSet* me);

    /* IWorkingSet */
    int16_t(ECOCALLMETHOD* Init)(/* in */ struct IWorkingSet* me, uint32_t capacity);
    int32_t(ECOCALLMETHOD* Page_Faults)(/* in */ struct IWorkingSet* me, int32_t* pages, uint32_t size);

} IWorkingSetVTbl, *IWorkingSetVTblPtr;

interface IWorkingSet {
    struct IWorkingSetVTbl* pVTbl;
} IWorkingSet;


#endif /* __I_WORKINGSET_H__ */
