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
#ifndef RAUMKERNEL_DEVICECREATOR_H
#define RAUMKERNEL_DEVICECREATOR_H

#include <raumkernel/raumkernelBase.h>
#include <raumkernel/raumkernelBaseMgr.h>
#include <raumkernel/device/device.h>
#include <raumkernel/device/deviceMediaRenderer.h>
#include <raumkernel/device/deviceMediaRenderer_RFVirtual.h>
#include <raumkernel/device/deviceMediaServer.h>
#include <raumkernel/device/deviceMediaServer_RF.h>
#include <raumkernel/xml/pugixml/pugixml.hpp>

#include <OpenHome/Net/Cpp/OhNet.h>
#include <OpenHome/Net/Cpp/CpDevice.h>


namespace Raumkernel
{
    namespace Devices
    {

        class DeviceCreator : public RaumkernelBaseMgr
        {
            public:
                DeviceCreator();
                virtual ~DeviceCreator();
                /**
                * Not intended for external use
                * Creates a device from a device xml gathered by upnp discovery
                */
                Devices::Device*  createDeviceFromDeviceXML(std::string _deviceXML);
                
            protected:
                void setDeviceInformationFromDeviceXML(Device* _device, pugi::xml_node _deviceNode);                           
                Devices::MediaRenderer* createMediaRendererFromDeviceNode(pugi::xml_node _deviceNode);
                Devices::MediaServer* createMediaServerFromDeviceNode(pugi::xml_node _deviceNode);
        };

    }
}

#endif