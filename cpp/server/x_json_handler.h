#ifndef CERT_TRANS_SERVER_X_JSON_HANDLER_H_
#define CERT_TRANS_SERVER_X_JSON_HANDLER_H_

#include <memory>

#include "log/logged_entry.h"
#include "server/handler.h"
#include "server/staleness_tracker.h"
#include "util/json_wrapper.h"

namespace cert_trans {


class XJsonHttpHandler : public HttpHandler {
 public:
  // Does not take ownership of its parameters, which must outlive this
  // instance.  The |frontend| parameters can be NULL, in which case this
  // server will not accept "add-json" requests.
  XJsonHttpHandler(LogLookup* log_lookup, const ReadOnlyDatabase* db,
                   const ClusterStateController* controller,
                   Frontend* frontend, ThreadPool* pool,
                   libevent::Base* event_base, StalenessTracker*);

  ~XJsonHttpHandler() = default;
  XJsonHttpHandler(const XJsonHttpHandler&) = delete;
  XJsonHttpHandler& operator=(const XJsonHttpHandler&) = delete;

 protected:
  void AddHandlers(libevent::HttpServer* server) override;

 private:
  Frontend* const frontend_;

  void AddJson(evhttp_request* req);

  void BlockingAddJson(evhttp_request* req,
                       std::shared_ptr<JsonObject> json) const;
};


}  // namespace cert_trans


#endif  // CERT_TRANS_SERVER_X_JSON_HANDLER_H_
