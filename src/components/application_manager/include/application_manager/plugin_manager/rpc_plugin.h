#ifndef SRC_COMPONENTS_APPLICATION_MANAGER_INCLUDE_APPLICATION_MANAGER_PLUGIN_MANAGER_RPC_PLUGIN_H
#define SRC_COMPONENTS_APPLICATION_MANAGER_INCLUDE_APPLICATION_MANAGER_PLUGIN_MANAGER_RPC_PLUGIN_H
#include <memory>
#include "utils/macro.h"
#include "application_manager/commands/command.h"
#include "application_manager/application.h"
#include "application_manager/rpc_service.h"
#include "application_manager/hmi_capabilities.h"
#include "application_manager/policies/policy_handler_interface.h"

namespace application_manager {
class CommandFactory;

namespace plugin_manager {

/**
 * @brief The PolicyEvent enum defines events related to policy
 */
enum PolicyEvent { kApplicationPolicyUpdated = 0, kApplicationsDisabled };

/**
 * @brief The ApplicationEvent enum defines events related to single application
 */
enum ApplicationEvent {
  kApplicationExit = 0,
  kApplicationRegistered,
  kApplicationUnregistered
};

class RPCPlugin {
 public:
  virtual bool Init(ApplicationManager& app_manager,
                    rpc_service::RPCService& rpc_service,
                    HMICapabilities& hmi_capabilities,
                    policy::PolicyHandlerInterface& policy_handler) = 0;
  /**
   * @brief IsAbleToProcess check if plugin is able to process function
   * @param function_id RPC identifier
   * @param message_source source of message to process (from HMI from mobile
   * ...)
   * @return true if plugin is able to process this RPC, false if not
   */
  virtual bool IsAbleToProcess(
      const int32_t function_icomponentsd,
      const commands::Command::CommandSource message_source) = 0;

  /**
   * @brief PluginName plugin name
   * @return plugin name
   */
  virtual std::string PluginName() = 0;

  /**
   * @brief GetCommandFactory get that is able to generate command
   * from message
   * @return plugins command factory
   */
  virtual CommandFactory& GetCommandFactory() = 0;
  /**
   * @brief OnPolicyEvent Notifies modules on certain events from policy
   * @param event Policy event
   */
  virtual void OnPolicyEvent(PolicyEvent event) = 0;

  /**
   * @brief OnApplicationEvent Processes application related events
   * @param event Event
   * @param application Pointer to application struct
   */
  virtual void OnApplicationEvent(
      ApplicationEvent event,
      application_manager::ApplicationSharedPtr application) = 0;
};
typedef std::unique_ptr<RPCPlugin> RPCPluginPtr;

}  // namespace plugin_manager
}  // namespace application_manager

#endif  // SRC_COMPONENTS_APPLICATION_MANAGER_INCLUDE_APPLICATION_MANAGER_PLUGIN_MANAGER_RPC_PLUGIN_H