/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CWorkingSet_8A3E6D31
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CWorkingSet_8A3E6D31
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "CWorkingSet.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "IEcoSystem1.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IWorkingSet
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CWorkingSet_8A3E6D31_QueryInterface(/* in */ struct IWorkingSet* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CWorkingSet_8A3E6D31* pCMe = (CWorkingSet_8A3E6D31*) me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if (IsEqualUGUID(riid, &IID_IWorkingSet)) {
        *ppv = &pCMe->m_pVTblIWorkingSet;
        pCMe->m_pVTblIWorkingSet->AddRef((IWorkingSet*) pCMe);
    } else if (IsEqualUGUID(riid, &IID_IEcoUnknown)) {
        *ppv = &pCMe->m_pVTblIWorkingSet;
        pCMe->m_pVTblIWorkingSet->AddRef((IWorkingSet*) pCMe);
    } else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IWorkingSet
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CWorkingSet_8A3E6D31_AddRef(/* in */ struct IWorkingSet* me) {
    CWorkingSet_8A3E6D31* pCMe = (CWorkingSet_8A3E6D31*) me;

    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IWorkingSet
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CWorkingSet_8A3E6D31_Release(/* in */ struct IWorkingSet* me) {
    CWorkingSet_8A3E6D31* pCMe = (CWorkingSet_8A3E6D31*) me;

    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if (pCMe->m_cRef == 0) {
        deleteCWorkingSet_8A3E6D31((IWorkingSet*) pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

int16_t ECOCALLMETHOD CWorkingSet_8A3E6D31_init(/* in */ struct IWorkingSet* me, uint32_t capacity) {
    CWorkingSet_8A3E6D31* pCMe = (CWorkingSet_8A3E6D31*) me;

    /* Проверка указателей */
    if (me == 0 || capacity == 0) {
        return -1;
    }

    pCMe->m_Capacity = capacity;

    return 0;
}

int32_t ECOCALLMETHOD CWorkingSet_8A3E6D31_page_faults(/* in */ struct IWorkingSet* me, int32_t* pages, uint32_t size) {
    CWorkingSet_8A3E6D31* pCMe = (CWorkingSet_8A3E6D31*) me;
    uint32_t capacity = pCMe->m_Capacity;
    IEcoMap1* map = pCMe->m_Map;
    int32_t i;
    int32_t faults = 0;
    int32_t time = 1;

    int32_t start = 0;

    if (me == 0 || pages == 0 || pCMe->m_Capacity == 0) {
        return -1;
    }

    for (i = 0; i < size; ++i) {
        if ((i - start) == capacity) {
            if (time - (*(int32_t*) map->pVTbl->Get(map, &pages[start])) >= capacity) {
                map->pVTbl->Remove(map, &pages[start]);
            }

            if (map->pVTbl->Get(map, &pages[i]) == 0) {
                printf("Fault on %d, index %d\n", pages[i], i);
                faults++;
            }
            map->pVTbl->Set(map, &pages[i], &time);

            start++;
        } else {
            map->pVTbl->Set(map, &pages[i], &time);
            printf("Fault on %d, index %d\n", pages[i], i);
            faults++;
        }

        time++;
    }

    return faults;
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD initCWorkingSet_8A3E6D31(/*in*/ struct IWorkingSet* me, /* in */ struct IEcoUnknown* pIUnkSystem) {
    CWorkingSet_8A3E6D31* pCMe = (CWorkingSet_8A3E6D31*) me;
    IEcoInterfaceBus1* pIBus = 0;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*) pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void**) &pIBus);

    /* Проверка указателей */
    if (me == 0) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*) pIUnkSystem;

    pCMe->m_Map->pVTbl->InitByTypeAndComparator(pCMe->m_Map, ECO_COMPARATOR_1_INTEGER_32_TYPE, ECO_COMPARATOR_1_INTEGER_32_TYPE, pCMe->comp);

    pCMe->m_Capacity = 0;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return result;
}

/* Create Virtual Table IWorkingSet */
IWorkingSetVTbl g_x7A3652051F7B4E7FA01BDCF950DB01BCVTbl_8A3E6D31 = {
        CWorkingSet_8A3E6D31_QueryInterface,
        CWorkingSet_8A3E6D31_AddRef,
        CWorkingSet_8A3E6D31_Release,
        CWorkingSet_8A3E6D31_init,
        CWorkingSet_8A3E6D31_page_faults
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCWorkingSet_8A3E6D31(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IWorkingSet** ppIWorkingSet) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CWorkingSet_8A3E6D31* pCMe = 0;
    UGUID* rcid = (UGUID*) &CID_EcoMemoryManager1;

    /* Проверка указателей */
    if (ppIWorkingSet == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem1, (void**) &pISys);

    /* Проверка */
    if (result != 0 && pISys == 0) {
        return result;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void**) &pIBus);

    /* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**) &pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*) pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CWorkingSet_8A3E6D31*) pIMem->pVTbl->Alloc(pIMem, sizeof(CWorkingSet_8A3E6D31));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IWorkingSet */
    pCMe->m_pVTblIWorkingSet = &g_x7A3652051F7B4E7FA01BDCF950DB01BCVTbl_8A3E6D31;

    /* Инициализация данных */
    pCMe->m_Name = 0;

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMap1, 0, &IID_IEcoMap1, (void**) &pCMe->m_Map);
    if (result != 0 || pCMe->m_Map == 0) {
        return result;
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoComparator1, 0, &IID_IEcoComparator1Int32, (void**) &pCMe->comp);
    if (result != 0 || pCMe->comp == 0) {
        return result;
    }

    /* Возврат указателя на интерфейс */
    *ppIWorkingSet = (IWorkingSet*) pCMe;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCWorkingSet_8A3E6D31(/* in */ IWorkingSet* pIWorkingSet) {
    CWorkingSet_8A3E6D31* pCMe = (CWorkingSet_8A3E6D31*) pIWorkingSet;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIWorkingSet != 0) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if (pCMe->m_Name != 0) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if (pCMe->m_pISys != 0) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
