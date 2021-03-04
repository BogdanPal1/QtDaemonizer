#ifndef DAEMON_H
#define DAEMON_H

#include <QObject>
#include <QString>
#include <QSocketNotifier>

#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syslog.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <memory>

/*!
 * \brief The Daemon class
 */
class Daemon : public QObject
{
    Q_OBJECT
public:

    /*!
     * \brief pDaemon Alias for std::unique_ptr<Daemon>.
     */
    typedef std::unique_ptr<Daemon> pDaemon;

public:

    /*!
     * \brief Daemon Basic constructor.
     * \param parent
     */
    Daemon(QObject* parent = nullptr);
    Daemon(Daemon& other) = delete;
    Daemon& operator=(Daemon& other) = delete;
    Daemon(Daemon&& other) = delete;
    Daemon& operator=(Daemon&& other) = delete;
    /*!
     * \brief Destructor
     */
    ~Daemon();

    /*!
     * \brief Daemonize Main method of class. Use for daemonisation.
     */
    void daemonize();

    // Unix signal handlers
    /*!
     * \brief termHandler Handler of UNIX SIGTERM signal.
     * \param sig Unused variable. Number of UNIX signal.
     */
    static void termHandler(int sig);

    /*!
     * \brief intHandler Handler of UNIX SIGINT signal.
     * \param sig Unused variable. Number of UNIX signal.
     */
    static void intHandler(int sig);

    /*!
     * \brief hupHandler Handler of UNIX SIGHUP signal.
     * \param sig Unused variable. Number of UNIX signal.
     */
    static void hupHandler(int sig);
    static void pauseHandler(int sig);
    static void resumeHandler(int sig);

    void logMessage(const QString& message);

public slots:
    // Qt signal handlers
    /*!
     * \brief handleSigHup Handler of SIGHUP signal which can work with Qt objects.
     */
    void handleSigHup();

    /*!
     * \brief handleSigTerm Handler of SIGTERM signal which can work with Qt objects.
     */
    void handleSigTerm();

    /*!
     * \brief handleSigInt Handler of SIGINT signal which can work with Qt objects.
     */
    void handleSigInt();

private:

    /*!
     * \brief signalHandlerConfig Method that configure signal handlers.
     */
    static void signalHandlerConfig();
private:

    pDaemon _daemon; //!< Unique pointer to Daemon
    QString _pidFile; //!< Name of file with process ID
    static int _sigHupFd[2]; //!< File descriptor for HUP signal
    static int _sigTermFd[2]; //!< File descriptor for TERM signal
    static int _sigIntFd[2]; //!< File descriptor for INT signal
    QSocketNotifier* _snHup = nullptr; //!< Socket notifier for HUP signal
    QSocketNotifier* _snTerm = nullptr; //!< Socket notifier for TERM signal
    QSocketNotifier* _snInt = nullptr; //!< Socket notifier for INT signal
};

#endif // DAEMON_H
