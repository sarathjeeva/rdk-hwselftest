/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2017 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**
 * @file
 *
 * @brief Interface of a simple SNMP client.
 */

/** @addtogroup WA_UTILS_SNMP
 *  @{
 */

#ifndef WA_UTILS_SNMP_H
#define WA_UTILS_SNMP_H

/*****************************************************************************
 * STANDARD INCLUDE FILES
 *****************************************************************************/

#include <stdbool.h>

/*****************************************************************************
 * PROJECT-SPECIFIC INCLUDE FILES
 *****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************
 * EXPORTED DEFINITIONS
 *****************************************************************************/

/*****************************************************************************
 * EXPORTED TYPES
 *****************************************************************************/

typedef enum
{
    WA_UTILS_SNMP_REQ_TYPE_GET,
    WA_UTILS_SNMP_REQ_TYPE_WALK

} WA_UTILS_SNMP_ReqType_t;

/*****************************************************************************
 * EXPORTED VARIABLES
 *****************************************************************************/

/*****************************************************************************
 * EXPORTED FUNCTIONS
 *****************************************************************************/

/**
 * Initialize SNMP utility.
 *
 * @retval 0 on success
 * @retval -1 on error
 */
int WA_UTILS_SNMP_Init();

/**
 * Uninitialize SNMP utility.
 *
 * @retval 0 on success
 * @retval -1 on error
 */
int WA_UTILS_SNMP_Exit();

/**
 * Retrieves a string value associated with the specified OID from the default SNMP server.
 *
 * @param server the server to connect to
 * @param oid OID to retrieve
 * @param[out] buffer The retrieved string value
 * @param bufSize Capacity of the buffer
 *
 * @return @a true if a string value associated with the specified OID was retrieved and placed in @a buffer (even if truncated), false otherwise.
 */
bool WA_UTILS_SNMP_GetString(const char *server, const char * oid, char * buffer, size_t bufSize, WA_UTILS_SNMP_ReqType_t reqType);

/**
 * Retrieves an integer value associated with the specified OID from the default SNMP server.
 *
 * @param server the server to connect to
 * @param oid OID to retrieve
 * @param[out] buffer The retrieved integer
 *
 * @return @a true if an integer value associated with the specified OID was retrieved and placed in @a buffer, false otherwise.
 */
bool WA_UTILS_SNMP_GetLong(const char *server, const char * reqoid, long * buffer, WA_UTILS_SNMP_ReqType_t reqType);

#endif
