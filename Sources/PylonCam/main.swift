import Foundation
import Logging
import LoggingSyslog
import Qlift
#if os(Linux)
import Backtrace
#endif

let logger = Logger(label: "PylonCam")

func main() -> Int32 {
    #if os(Linux)
    Backtrace.install()
    #endif
    LoggingSystem.bootstrap(SyslogLogHandler.init)
    logger.info("PylonCam start")

    let application = QApplication()
    application.setStyle("Fusion")
    let mainWindow = MainWindow()
    if
        let emulate = (CommandLine.arguments.first { $0.hasPrefix("-emulate=") }) {
        setenv("PYLON_CAMEMU", "1", 1)
        let emulatePath = emulate.dropFirst("-emulate=".count)
        mainWindow.emulatePath = String(emulatePath)
    }

    mainWindow.show()
    return application.exec()
}

setbuf(stdout, nil)
exit(main())
