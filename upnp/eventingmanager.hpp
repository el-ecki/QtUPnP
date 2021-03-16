#ifndef EVENTING_MANAGER_HPP
#define EVENTING_MANAGER_HPP

#include "using_upnp_namespace.hpp"
#include "upnp_global.hpp"
#include "QEventLoop"
#include <QtNetwork/QNetworkReply>
#include <QHostAddress>

START_DEFINE_UPNP_NAMESPACE

/*! \brief Provides the mechanism to handle UPnP events. */
class CEventingManager : public QEventLoop
{
  Q_OBJECT
public:
  /*! Time type. */
  enum ETime { RequestTimeout = 30000, //!< HTTP request timeout in ms (30s). See http://upnp.org/specs/arch/UPnP-arch-DeviceArchitecture-v1.0.pdf
               RenewalDelay = 1800 }; //!< Renewal delay in s (half an hour).

  enum EError { Timeout = -1, //!< The event occurs timeout.
                NoError = 0, //<! No error.
                // The over are HTTP errors.
              };

  /*! Constructor. */
  CEventingManager ();

  /*! Constructor with network access manager.
   *
   * The internal QNetworkAccessManager is not created. The object use naMgr.
   * It is sometimes useful because create and destroy the network access manager
   * consumes time.
   */
  CEventingManager (QNetworkAccessManager* naMgr);

  /*! Returns the service that has generated the event. */
  QByteArray const & sid () const { return m_sid; }

  /*! Subcrible a service.
   * \param url: The device url.
   * \param eventSubURL: The path for subscription.
   * \param serverAddress: Ip server address for the response.
   * \param serverPort: Server port  address for the response.
   * \param renewalDelay: Maxumim time between 2 renew subscribe.
   * \param requestTimeout: Waiting delay for the response.
   */
  bool subscribe (QUrl const & url, QString const & eventSubURL, QHostAddress const & serverAddress,
                  quint16 serverPort, int renewalDelay = RenewalDelay, int requestTimeout = RequestTimeout);

  /*! Renew subscribe a service.
   * \param url: The device url.
   * \param eventSubURL: The path for subscription.
   * \param sid: SID to renew.
   * \param requestTimeout: Waiting delay for the response.
   */
  bool renewSubscribe (QUrl const & url, QString const & eventSubURL, QString const & sid,
                       int requestTimeout = RequestTimeout);

  /*! Unsubscribe a service.
   * \param url: The device url.
   * \param eventSubURL: The path for subsciption.
   * \param sid: SID to renew.
   * \param requestTimeout: Waiting delay for the response.
   */
  bool unsubscribe (QUrl const & url, QString const & eventSubURL, QString const & sid,
                    int requestTimeout = RequestTimeout);

protected:
  /*! The delay for the response has been exceeded. */
  virtual void timerEvent (QTimerEvent*);

private :
  /*! Format and send the request to the device.
   * \param url: The device url.
   * \param verb: SUBSCRIBE or UNSUBSCRIBE.
   * \param eventSubURL: The path for subscription.
   * \param req: The QNetqworkRequest.
   * \param requestTimeout: Waiting delay for the response.
   */
  bool sendRequest (QUrl url, char const * verb, QString const & eventSubURL,
                    QNetworkRequest& req, int requestTimeout);

private slots:
  /*! The response is terminated. */
  void finished ();

  /*! A newtwork error has been generated. */
  void error (QNetworkReply::NetworkError err);

private :
  QByteArray m_sid;
  int m_renewDelay = RenewalDelay; // In seconds
  QNetworkAccessManager* m_naMgr = nullptr;

  static int m_elapsedTime; //!< The time to execute the last action.
  static QString m_lastError; //!< The error generated by the last action.
};

} // Namespace

#endif // EVENTING_MANAGER_HPP
