import Foundation
import Logging
import LoggingSyslog
import Qlift

let logger = Logger(label: "PylonCam")

func main() -> Int32 {
    LoggingSystem.bootstrap(SyslogLogHandler.init)

    logger.info("PylonCam start")

    let application = QApplication()
    application.setStype("Fusion")
    let mainWindow = MainWindow()
    mainWindow.show()
    return application.exec()
}

setbuf(stdout, nil)
exit(main())
