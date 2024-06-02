/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdWorkingSet
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdWorkingSet
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

#ifndef __ID_WORKINGSET_H__
#define __ID_WORKINGSET_H__

#include "IEcoBase1.h"
#include "IWorkingSet.h"

/* WorkingSet CID = {3B82574C-7428-4B28-BB88-B4FF8A3E6D31} */
#ifndef __CID_WorkingSet
static const UGUID CID_WorkingSet = {0x01, 0x10, 0x3B, 0x82, 0x57, 0x4C, 0x74, 0x28, 0x4B, 0x28, 0xBB, 0x88, 0xB4, 0xFF, 0x8A, 0x3E, 0x6D, 0x31};
#endif /* __CID_WorkingSet */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_3B82574C74284B28BB88B4FF8A3E6D31;
#endif

#endif /* __ID_WORKINGSET_H__ */
