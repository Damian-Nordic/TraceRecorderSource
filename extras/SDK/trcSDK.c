/*
 * Percepio Trace Recorder SDK for Tracealyzer v4.5.0b
 * Copyright 2021 Percepio AB
 * www.percepio.com
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Percepio Tracealyzer Recorder SDK
 */

#include <stdio.h>
#include "trcSDK.h"

extern uint16_t CurrentFilterMask;

extern uint16_t CurrentFilterGroup;

void vTraceSDKSetObjectFilter();

/*******************************************************************************
* xTraceSDKRegisterObject
*
* This function will register an object in the trace.
*
* @param uiEventCode The event code.
* @param pxObject The pointer to the object.
* @param uiData The object's initial data.
* @return Function result. TRACE_SUCCESS or TRACE_FAIL.
******************************************************************************/
traceResult xTraceSDKRegisterObject(uint32_t uiEventCode, void* pxObject, uint32_t uiData)
{
#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)
	prvTraceSaveObjectData(pxObject, uiData); \
	prvTraceStoreEvent2((uint16_t)uiEventCode, (uint32_t)pxObject, uiData);
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */

#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_SNAPSHOT)
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */

	return 0;
}

/*******************************************************************************
* xTraceSDKUnregisterObject
*
* This function will unregister an object in the trace.
*
* @param uiEventCode The event code.
* @param pxObject The pointer to the object.
* @param uiData The object's end data.
* @return Function result. TRACE_SUCCESS or TRACE_FAIL.
******************************************************************************/
traceResult xTraceSDKUnregisterObject(uint32_t uiEventCode, void* pxObject, uint32_t uiData)
{
#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)
	prvTraceStoreEvent2((uint16_t)uiEventCode, (uint32_t)pxObject, uiData);
	/* Only remove the symbol entry */
	prvTraceDeleteSymbol(pxObject);
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */

#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_SNAPSHOT)
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */

	return 0;
}

/*******************************************************************************
* xTraceSDKSetObjectName
*
* This function will set an object's name.
*
* @param pxObject The pointer to the object.
* @param pszName The task name.
* @return Function result. TRACE_SUCCESS or TRACE_FAIL.
******************************************************************************/
traceResult xTraceSDKSetObjectName(void* pxObject, const char* pszName)
{
#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)
	prvTraceSaveObjectSymbol(pxObject, (const char*)pszName);
	prvTraceStoreStringEvent(1, PSF_EVENT_OBJ_NAME, (const char*)pszName, (uint32_t)pxObject);
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */

#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_SNAPSHOT)
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */

	return 0;
}

/*******************************************************************************
* xTraceSDKSetObjectData
*
* This function will register a task in the trace.
*
* @param pxObject The pointer to the object.
* @param uiData The object's data.
* @return Function result. TRACE_SUCCESS or TRACE_FAIL.
******************************************************************************/
traceResult xTraceSDKSetObjectData(void* pxObject, uint32_t uiData)
{
#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)
	prvTraceSaveObjectData(pxObject, uiData);
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */

#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_SNAPSHOT)
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */

	return 0;
}

/*******************************************************************************
* xTraceSDKTaskSwitch
*
* This function will register a task switch and priority.
*
* @param pxTCB The pointer to the TCB.
* @param uiPriority The task priority.
* @return Function result. TRACE_SUCCESS or TRACE_FAIL.
******************************************************************************/
traceResult xTraceSDKTaskSwitch(void* pxTCB, uint32_t uiPriority)
{
#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)
	extern volatile uint32_t uiTraceSystemState;
	uiTraceSystemState = TRC_STATE_IN_TASKSWITCH;
	if (prvTraceGetCurrentTask() != (uint32_t)pxTCB)
	{
		prvTraceSetCurrentTask((uint32_t)pxTCB);
		prvTraceStoreEvent2(PSF_EVENT_TASK_ACTIVATE, (uint32_t)pxTCB, uiPriority);
	}
	uiTraceSystemState = TRC_STATE_IN_APPLICATION;
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */

#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_SNAPSHOT)
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */

	return 0;
}

/*******************************************************************************
* xTraceSDKTaskReady
*
* This function will set a task to ready in the trace.
*
* @param pxTCB The pointer to the TCB.
* @return Function result. TRACE_SUCCESS or TRACE_FAIL.
******************************************************************************/
traceResult xTraceSDKTaskReady(void* pxTCB)
{
#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)
	prvTraceStoreEvent1(PSF_EVENT_TASK_READY, (uint32_t)pxTCB);
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */

#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_SNAPSHOT)
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */

	return 0;
}

/*******************************************************************************
* xTraceSDKEventBegin
*
* This function will begin an event and allow for payload to be added via the
* xTraceSDKEventAdd****() functions.
*
* @param uiEventCode The event code.
* @param uiPayloadSize The expected payload size in bytes.
* @return Function result. TRACE_SUCCESS or TRACE_FAIL.
******************************************************************************/
traceResult xTraceSDKEventBegin(uint32_t uiEventCode, uint32_t uiPayloadSize)
{
#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)
	return prvTraceBeginStoreEvent(uiEventCode, uiPayloadSize);
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */

#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_SNAPSHOT)
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */
}

/*******************************************************************************
* xTraceSDKEventEnd
*
* This function ends an event.
*
* @return Function result. TRACE_SUCCESS or TRACE_FAIL.
******************************************************************************/
traceResult xTraceSDKEventEnd()
{
#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)
	return prvTraceEndStoreEvent();
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */

#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_SNAPSHOT)
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */
}

/*******************************************************************************
* xTraceSDKEventAddData
*
* This function will add a variable size of data as payload.
*
* @param pvData The pointer to the data.
* @param uiSize The data size.
* @return Function result. TRACE_SUCCESS or TRACE_FAIL.
******************************************************************************/
traceResult xTraceSDKEventAddData(void* pvData, uint32_t uiSize)
{
#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)
	return prvTraceStoreEventPayload(pvData, uiSize);
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */

#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_SNAPSHOT)
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */
}

/*******************************************************************************
* xTraceSDKEventAddObject
*
* This function will add an object as payload.
*
* @param pxObject The pointer to the object.
* @return Function result. TRACE_SUCCESS or TRACE_FAIL.
******************************************************************************/
traceResult xTraceSDKEventAddObject(void* pxObject)
{
#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)
	return xTraceSDKEventAdd32((uint32_t)pxObject);
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */

#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_SNAPSHOT)
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */
}

/*******************************************************************************
* xTraceSDKEventAdd32
*
* This function will add a 32-bit value as payload.
*
* @param value The value.
* @return Function result. TRACE_SUCCESS or TRACE_FAIL.
******************************************************************************/
traceResult xTraceSDKEventAdd32(uint32_t value)
{
#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)
	return prvTraceStoreEventPayload32(value);
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */

#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_SNAPSHOT)
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */
}

/*******************************************************************************
* xTraceSDKEventAdd16
*
* This function will add an uint16_t as payload.
*
* @param value The value.
* @return Function result. TRACE_SUCCESS or TRACE_FAIL.
******************************************************************************/
traceResult xTraceSDKEventAdd16(uint16_t value)
{
#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)
	return prvTraceStoreEventPayload16(value);
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */

#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_SNAPSHOT)
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */
}

/*******************************************************************************
* xTraceSDKEventAdd8
*
* This function will add an uint8_t as payload.
*
* @param value The value.
* @return Function result. TRACE_SUCCESS or TRACE_FAIL.
******************************************************************************/
traceResult xTraceSDKEventAdd8(uint8_t value)
{
#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)
	return prvTraceStoreEventPayload8(value);
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */

#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_SNAPSHOT)
#endif /* (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING) */
}
