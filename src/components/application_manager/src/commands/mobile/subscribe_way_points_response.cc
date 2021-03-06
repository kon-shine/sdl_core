#include "application_manager/application_manager.h"
#include "application_manager/commands/mobile/subscribe_way_points_response.h"

namespace application_manager {

namespace commands {

SubscribeWayPointsResponse::SubscribeWayPointsResponse(
    const MessageSharedPtr& message, ApplicationManager& application_manager)
    : CommandResponseImpl(message, application_manager) {}

SubscribeWayPointsResponse::~SubscribeWayPointsResponse() {}

void SubscribeWayPointsResponse::Run() {
  LOG4CXX_AUTO_TRACE(logger_);

  application_manager_.SendMessageToMobile(message_);
}

}  // namespace commands

}  // namespace application_manager
