//
// The MIT License (MIT)
//
// Copyright (c) 2015 by ChriD
//
// Permission is hereby granted, free of charge,  to any person obtaining a copy of
// this software and  associated documentation  files  (the "Software"), to deal in
// the  Software  without  restriction,  including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software,  and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this  permission notice  shall be included in all
// copies or substantial portions of the Software.
//
// THE  SOFTWARE  IS  PROVIDED  "AS IS",  WITHOUT  WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE  AND NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE  LIABLE FOR ANY CLAIM,  DAMAGES OR OTHER LIABILITY, WHETHER
// IN  AN  ACTION  OF  CONTRACT,  TORT  OR  OTHERWISE,  ARISING  FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#pragma once
#ifndef RAUMKERNEL_MANAGERENGINEER_H
#define RAUMKERNEL_MANAGERENGINEER_H

#include <raumkernel/raumkernelBase.h>
#include <raumkernel/manager/settingsManager.h>
#include <raumkernel/manager/upnpManager.h>
#include <raumkernel/manager/deviceManager.h>
#include <raumkernel/manager/zoneManager.h>
#include <raumkernel/manager/mediaListManager.h>

namespace Raumkernel
{
    namespace Manager
    {
        /*
        This class holds pointers to all the available managers loaded in the kernel
        */
        class ManagerEngineer : public RaumkernelBase 
        {
            public:
                EXPORT ManagerEngineer();
                EXPORT virtual ~ManagerEngineer();
                void createManagers();      
                EXPORT virtual void raiseSigsegv();

                EXPORT std::shared_ptr<SettingsManager> getSettingsManager();
                EXPORT std::shared_ptr<UPNPManager> getUPNPManager();
                EXPORT std::shared_ptr<DeviceManager> getDeviceManager();                
                EXPORT std::shared_ptr<ZoneManager> getZoneManager();
                EXPORT std::shared_ptr<MediaListManager> getMediaListManager();

            protected:
                std::shared_ptr<SettingsManager> settingsManager;
                std::shared_ptr<UPNPManager> upnpManager;
                std::shared_ptr<DeviceManager> deviceManager;                
                std::shared_ptr<ZoneManager> zoneManager;
                std::shared_ptr<MediaListManager> mediaListManager;
        };
    }
}


#endif