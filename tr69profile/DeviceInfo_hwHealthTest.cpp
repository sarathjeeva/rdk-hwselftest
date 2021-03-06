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

/*****************************************************************************
 * STANDARD INCLUDE FILES
 *****************************************************************************/
#include <string>
#include <memory>
#include <cstring>

/*****************************************************************************
 * PROJECT-SPECIFIC INCLUDE FILES
 *****************************************************************************/
#include "DeviceInfo_hwHealthTest.h"
#include "hostIf_tr69ReqHandler.h"
#include "wa_wsclient.h"
#include <rdk_debug.h>

/*****************************************************************************
 * LOCAL DEFINITIONS
 *****************************************************************************/
#define FILE "wa_wsclient.cpp"

/*****************************************************************************
 * EXPORTED FUNCTIONS
 *****************************************************************************/

namespace hwselftest {

bool set_Device_DeviceInfo_xOpsDeviceMgmt_hwHealthTest_Enable(const char *log_module, HOSTIF_MsgData_t *stMsgData)
{
    bool ret = false;

    RDK_LOG(RDK_LOG_DEBUG, log_module, "[%s:%s] attempting to enable/disable the hwselftest component...\n", FILE, __FUNCTION__);

    wa_wsclient *pInst = wa_wsclient::instance();
    if (pInst)
    {
        bool *value = reinterpret_cast<bool *>(stMsgData->paramValue);
        ret = pInst->enable(*value);

        if (ret)
            RDK_LOG(RDK_LOG_DEBUG, log_module, "[%s:%s] hwselftest %s successfully\n", FILE, __FUNCTION__, ((*value)? "enabled" : "disabled"));
        else
            RDK_LOG(RDK_LOG_ERROR, log_module,"[%s:%s] failed to %s hwselftest\n", FILE, __FUNCTION__, ((*value)? "enable" : "disable"));
    }
    else
        RDK_LOG(RDK_LOG_ERROR, log_module,"[%s:%s] failed to get wa_wsclient instance\n", FILE, __FUNCTION__);

    return ret;
}

bool set_Device_DeviceInfo_xOpsDeviceMgmt_hwHealthTest_ExecuteTest(const char *log_module, HOSTIF_MsgData_t *stMsgData)
{
    bool ret = false;

    RDK_LOG(RDK_LOG_DEBUG, log_module, "[%s:%s] attempting to execute tests...\n", FILE, __FUNCTION__);

    wa_wsclient *pInst = wa_wsclient::instance();
    if (pInst)
    {
        int cookie = *((int *)stMsgData->paramValue);
        ret = pInst->execute_tests(cookie);

        if (ret)
            RDK_LOG(RDK_LOG_DEBUG, log_module, "[%s:%s] tests scheduled successfully (%i)\n", FILE, __FUNCTION__, cookie);
        else
            RDK_LOG(RDK_LOG_ERROR, log_module,"[%s:%s] failed to schedule test execution\n", FILE, __FUNCTION__);
    }
    else
        RDK_LOG(RDK_LOG_ERROR, log_module,"[%s:%s] failed to get wa_wsclient instance\n", FILE, __FUNCTION__);

    return ret;
}

bool get_Device_DeviceInfo_xOpsDeviceMgmt_hwHealthTest_Results(const char *log_module, HOSTIF_MsgData_t *stMsgData)
{
    bool ret = false;

    RDK_LOG(RDK_LOG_DEBUG, log_module, "[%s:%s] attempting to retrieve test results...\n", FILE, __FUNCTION__);

    stMsgData->paramValue[0] = '\0';

    wa_wsclient *pInst = wa_wsclient::instance();
    if (pInst)
    {
        std::string result;
        ret = pInst->get_results(result);

        if (ret)
        {
            RDK_LOG(RDK_LOG_DEBUG, log_module, "[%s:%s] test results retrieved successfully\n", FILE, __FUNCTION__);
            strncpy(stMsgData->paramValue, result.c_str(), TR69HOSTIFMGR_MAX_PARAM_LEN - 1)[TR69HOSTIFMGR_MAX_PARAM_LEN - 1] = '\0';
            stMsgData->paramLen = (result.length() > TR69HOSTIFMGR_MAX_PARAM_LEN - 1? TR69HOSTIFMGR_MAX_PARAM_LEN - 1 : result.length()) + 1;
            stMsgData->paramtype = hostIf_StringType;
        }
        else
            RDK_LOG(RDK_LOG_ERROR,log_module,"[%s:%s] failed to retrieve test results\n", FILE, __FUNCTION__);
    }
    else
        RDK_LOG(RDK_LOG_ERROR, log_module,"[%s:%s] failed to get wa_wsclient instance\n", FILE, __FUNCTION__);

    return ret;
}

} // namespace hwselftest
