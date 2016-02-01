
#include <raumkernel/raumkernel.h>
#include <raumkernel/manager/managerEngineer.h>

namespace Raumkernel
{

    Raumkernel::Raumkernel() : RaumkernelBaseMgr()
    {
        // TODO: Subscribe to mediaServerAdded/Delete signals. That will show us the RF System is online if the RF Media Server is going online 
        // Of course not here :)
        // TODO: When media server is added. init zone request manager and start requests.. if removed.. stop zone requests ...
    }


    Raumkernel::~Raumkernel()
    {
    }


    void Raumkernel::init(Log::LogType _defaultLogLevel, std::string _settingsFileName)
    {
        // create the log object (if not already provided) which will be used throughout the whole kernel and his modules 
        if (logObject == nullptr)
        {
            // we do register some log adapters for the log object with standard values and set to log only ERRORS and CRITICALERRORS
            // the log level itself will be set after reading the settings file but we want to have logging while reading settings file
            // so we create the logObject with some standard values
            logObject = std::shared_ptr<Log::Log>(new Log::Log());            
            logObject->registerAdapter(std::shared_ptr<Log::LogAdapter>(new Log::LogAdapter_Console()));
            logObject->registerAdapter(std::shared_ptr<Log::LogAdapter>(new Log::LogAdapter_File()));
            logObject->setLogLevel(_defaultLogLevel);
        }

        logDebug("Preparing Manager-Engineer...", CURRENT_POSITION);

        // create the manager engineer which will hold references to all managers. this engineer will be present in each manager and each class
        // which is inherited from 'RaumfeldBaseMgr', but has to be set explicit
        managerEngineer = std::shared_ptr<Manager::ManagerEngineer>(new Manager::ManagerEngineer());
        managerEngineer->setLogObject(logObject);
        managerEngineer->createManagers();

        // set links to the manager engineer for all managers (this is a little bit of circular dependencies because the managers have a link to the
        // managerEngineer, which has links to the managers again. But this should be no problem, in this case)
        managerEngineer->getSettingsManager()->setManagerEngineer(managerEngineer);        
        managerEngineer->getUPNPManager()->setManagerEngineer(managerEngineer);
        managerEngineer->getDeviceManager()->setManagerEngineer(managerEngineer);        
        managerEngineer->getSubscriptionReceiverManager()->setManagerEngineer(managerEngineer);        
        managerEngineer->getZoneManager()->setManagerEngineer(managerEngineer);

        logDebug("Manager-Engineer is prepared", CURRENT_POSITION);

        // all managers are now created and we can work with them. so first lets get the settings manager in action and let it read our kernel 
        // and application settings.      
        if (!_settingsFileName.empty())
            managerEngineer->getSettingsManager()->setFileName(_settingsFileName);
        managerEngineer->getSettingsManager()->loadSettings();

        // okay now, when the settingsManager is ready and we have loaded the settings we may get the log settings (log level)   
        std::string logLevelString = managerEngineer->getSettingsManager()->getValue(Manager::SETTINGS_RAUMKERNEL_LOGLEVEL);
        logObject->setLogLevel(Log::Log::logTypeStringToLogType(logLevelString));
        logDebug("Log level was set to: " + logLevelString, CURRENT_POSITION);

        // let's wake up the UPNP Stack and start discovering UPNP devices of all kinds
        managerEngineer->getUPNPManager()->init();        
        managerEngineer->getUPNPManager()->discover();

        // the zone manager has to request the actual zone configuration whcih can be done by long polling a special request
        managerEngineer->getZoneManager()->init();        
        

        logInfo("Kernel initialized! Waiting for Raumfeld System to appear!", CURRENT_POSITION);

    }

}