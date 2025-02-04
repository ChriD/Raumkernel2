
#include <raumkernel/device/deviceCreator.h>
#include <raumkernel/manager/managerEngineer.h>
#include <raumkernel/manager/settingsManager.h>

namespace Raumkernel
{
    namespace Devices
    {
        DeviceCreator::DeviceCreator() : RaumkernelBaseMgr()
        {
        }


        DeviceCreator::~DeviceCreator()
        {
        }


        void DeviceCreator::setDeviceInformationFromDeviceXML(Device* _device, pugi::xml_node _deviceNode)
        {
            pugi::xml_document doc;
            pugi::xml_node deviceNode = _deviceNode, valueNode;
            std::string	deviceType, deviceUDN, deviceFriendlyName, deviceModelDescription, deviceModelName, deviceManufacturer, deviceManufacturerUrl;
            std::string	deviceModelNumber, deviceSerialNumber;

            deviceType = deviceNode.child("deviceType").child_value();
            deviceUDN = deviceNode.child("UDN").child_value();
            deviceUDN = Raumkernel::Tools::CommonUtil::formatUDN(deviceUDN);
            valueNode = deviceNode.child("friendlyName");
            if (valueNode)
                deviceFriendlyName = valueNode.child_value();
            valueNode = deviceNode.child("modelDescription");
            if (valueNode)
                deviceModelDescription = valueNode.child_value();
            valueNode = deviceNode.child("modelName");
            if (valueNode)
                deviceModelName = valueNode.child_value();
            valueNode = deviceNode.child("manufacturer");
            if (valueNode)
                deviceManufacturer = valueNode.child_value();
            valueNode = deviceNode.child("manufacturerURL");
            if (valueNode)
                deviceManufacturerUrl = valueNode.child_value();
            valueNode = deviceNode.child("modelNumber");
            if (valueNode)
                deviceModelNumber = valueNode.child_value();
            valueNode = deviceNode.child("serialNumber");
            if (valueNode)
                deviceSerialNumber = valueNode.child_value();
    
            _device->setLogObject(getLogObject());
            _device->setUDN(deviceUDN);
            _device->setDeviceType(deviceType);
            _device->setFriendlyName(deviceFriendlyName);
            _device->setModelDescription(deviceModelDescription);
            _device->setModelName(deviceModelName);
            _device->setModelNumber(deviceModelNumber);
            _device->setSerialNumber(deviceSerialNumber);
            _device->setManufacturer(deviceManufacturer);
            _device->setManufacturerUrl(deviceManufacturerUrl);
        }

        
        Devices::Device* DeviceCreator::createDeviceFromDeviceXML(std::string _deviceXML)
        {
            pugi::xml_document doc;
            pugi::xml_node deviceNode, rootNode, valueNode;
            Devices::MediaRenderer* mediaRenderer = nullptr;
            Devices::MediaServer* mediaServer = nullptr;
            Devices::Device* createdDevice = nullptr;
            std::string deviceType, deviceUDN;     

            logDebug("Try to create device from device XML", CURRENT_POSITION);

           
            pugi::xml_parse_result result = doc.load_string(_deviceXML.c_str());            

            // find the root node which has to be the 'device' node	
            rootNode = doc.child("root");
            if (!rootNode)
            {
                logError("Device XML from device does not contain root block!", CURRENT_POSITION);             
                return nullptr;
            }

            // find the root node which has to be the 'device' node	
            deviceNode = rootNode.child("device");
            if (!deviceNode)
            {
                logError("Device XML from device does not contain device information!", CURRENT_POSITION);                
                return nullptr;
            }

            valueNode = deviceNode.child("UDN");
            if (!valueNode)
            {
                logError("Device XML from device does not contain UDN information!", CURRENT_POSITION);                
                return nullptr;
            }
            deviceUDN = valueNode.child_value();

            valueNode = deviceNode.child("deviceType");
            if (!valueNode)
            {
                logError("Device XML from device does not contain type information!", CURRENT_POSITION);                
                return nullptr;
            }
            deviceType = valueNode.child_value();

            if (deviceType.find(getManagerEngineer()->getSettingsManager()->getValue(Manager::SETTINGS_RAUMKERNEL_MEDIARENDERERIDENTIFICATION)) != std::string::npos)
            {
                logDebug("Createing device (" + deviceUDN  + ")", CURRENT_POSITION);                
                mediaRenderer = createMediaRendererFromDeviceNode(deviceNode);
                if (mediaRenderer)
                {
                    createdDevice = mediaRenderer;
                    logDebug("Media Renderer device created (" + deviceUDN + ")", CURRENT_POSITION);
                }
                else
                {
                    logError("Object for device '" + deviceType + "' with UDN: '" + deviceUDN + "' could not be created", CURRENT_POSITION);                    
                }
            }
            // check if device is of type mediaServer
            // in fact there can only be one raumfeld media server we can use
            else if (deviceType.find(getManagerEngineer()->getSettingsManager()->getValue(Manager::SETTINGS_RAUMKERNEL_MEDIASERVERIDENTIFICATION)) != std::string::npos)
            {
                
                mediaServer = createMediaServerFromDeviceNode(deviceNode);
                if (mediaServer)
                {                   
                    createdDevice = mediaServer;
                    logDebug("Media Server device created (" + deviceUDN + ")", CURRENT_POSITION);                    
                }
                else
                {
                    logError("Object for device '" + deviceType + "' with UDN: '" + deviceUDN + "' could not be created", CURRENT_POSITION);
                }
                
            }
            else
            {
                logDebug("No device was created for " + deviceUDN + ". Device is not usable!", CURRENT_POSITION);
            }            

            return createdDevice;
        }


        Devices::MediaRenderer* DeviceCreator::createMediaRendererFromDeviceNode(pugi::xml_node _deviceNode)
        {  
            pugi::xml_node valueNode;
            std::string deviceModelDescription, deviceManufacturer;
            Devices::MediaRenderer* mediaRenderer;
            bool isVirtualRenderer = false, isRaumfeldRenderer = false;            

            valueNode = _deviceNode.child("manufacturer");
            if (valueNode)
                deviceManufacturer = valueNode.child_value();
            valueNode = _deviceNode.child("modelDescription");
            if (valueNode)
                deviceModelDescription = valueNode.child_value();

            isVirtualRenderer = deviceModelDescription.find(getManagerEngineer()->getSettingsManager()->getValue(Manager::SETTINGS_RAUMKERNEL_RAUMFELDDESCRIPTIONVIRTUALMEDIAPLAYER)) != std::string::npos;
            isRaumfeldRenderer = deviceManufacturer.find(getManagerEngineer()->getSettingsManager()->getValue(Manager::SETTINGS_RAUMKERNEL_RAUMFELDMANUFACTURER)) != std::string::npos;



            if (isRaumfeldRenderer && isVirtualRenderer)
                mediaRenderer = new MediaRenderer_RaumfeldVirtual();
            else if(isRaumfeldRenderer)
                mediaRenderer = new MediaRenderer_Raumfeld();
            else
                mediaRenderer = new MediaRenderer();

            mediaRenderer->setIsRaumfeldDevice(isRaumfeldRenderer);
            setDeviceInformationFromDeviceXML(mediaRenderer, _deviceNode);

            return mediaRenderer;
        }


        Devices::MediaServer* DeviceCreator::createMediaServerFromDeviceNode(pugi::xml_node _deviceNode)
        {
            pugi::xml_node valueNode;
            std::string deviceModelDescription, deviceManufacturer;
            Devices::MediaServer* mediaServer;
            bool isRaumfeldMediaServer = false;           

            valueNode = _deviceNode.child("manufacturer");
            if (valueNode)
                deviceManufacturer = valueNode.child_value();
                        
            isRaumfeldMediaServer = deviceManufacturer.find(getManagerEngineer()->getSettingsManager()->getValue(Manager::SETTINGS_RAUMKERNEL_RAUMFELDMANUFACTURER)) != std::string::npos;

            if (isRaumfeldMediaServer)
                mediaServer = new MediaServer_Raumfeld();
            else
                mediaServer = new MediaServer();
            
            mediaServer->setIsRaumfeldDevice(isRaumfeldMediaServer);
            setDeviceInformationFromDeviceXML(mediaServer, _deviceNode);

            return mediaServer;
        }
    }
}