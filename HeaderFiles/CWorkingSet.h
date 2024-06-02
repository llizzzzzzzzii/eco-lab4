/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CWorkingSet
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CWorkingSet
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_WORKINGSET_H__
#define __C_WORKINGSET_H__

#include "IEcoSystem1.h"
#include "IWorkingSet.h"
#include "IdEcoMemoryManager1.h"

#include "IdEcoList1.h"
#include "IdEcoMap1.h"
#include "IdEcoComparator1.h"

typedef struct CWorkingSet_8A3E6D31 {

    /* Таблица функций интерфейса IWorkingSet */
    IWorkingSetVTbl* m_pVTblIWorkingSet;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Данные экземпляра */
    char_t* m_Name;

    IEcoMap1* m_Map;

    IEcoComparator1* comp;

    uint32_t m_Capacity;

} CWorkingSet_8A3E6D31, *CWorkingSet_8A3E6D31Ptr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCWorkingSet_8A3E6D31(/*in*/ struct IWorkingSet* me, /* in */ IEcoUnknown* pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCWorkingSet_8A3E6D31(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IWorkingSet** ppIWorkingSet);
/* Удаление */
void ECOCALLMETHOD deleteCWorkingSet_8A3E6D31(/* in */ IWorkingSet* pIWorkingSet);

#endif /* __C_WORKINGSET_H__ */
