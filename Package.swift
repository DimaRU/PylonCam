// swift-tools-version:5.3

import PackageDescription

let package = Package(
    name: "PylonCam",
    platforms: [.macOS(.v11)],
    dependencies: [
        .package(name: "Qlift", url: "https://github.com/DimaRU/qlift", .branch("master")),
        .package(url: "https://github.com/ianpartridge/swift-log-syslog", from: "1.0.0"),
        .package(url: "https://github.com/swift-server/swift-backtrace", from: "1.0.0")
    ],
    targets: [
        .target(
            name: "PylonCam",
            dependencies: [
                "Qlift",
                "PylonFrameGrabber",
                "FocusMeasure",
                "CameraSharedMem",
                .product(name: "Backtrace", package: "swift-backtrace", condition: .when(platforms: [.linux])),
                .product(name: "LoggingSyslog", package: "swift-log-syslog")
            ],
            cSettings: [.headerSearchPath("../../include")],
            linkerSettings: [
                .linkedLibrary("rt", .when(platforms: [.linux])),
                .linkedFramework("QtWidgets", .when(platforms: [.macOS])),
                .linkedFramework("QtCore", .when(platforms: [.macOS])),
                .linkedFramework("QtGui", .when(platforms: [.macOS])),
                .linkedFramework("pylon", .when(platforms: [.macOS])),
                .unsafeFlags(["-Xlinker", "-rpath", "/Library/Frameworks"], .when(platforms: [.macOS])),
                .unsafeFlags([
                    "-Xlinker", "-rpath=/opt/pylon/lib",
                    "-Xlinker", "-rpath=/opt/qt5.15/lib",
                ], .when(platforms: [.linux])),
            ]
        ),
        .target(name: "CameraSharedMem", cSettings: [.headerSearchPath("../../include")]),
        .target(name: "PylonFrameGrabber", dependencies: ["CPylon"], cSettings: [.headerSearchPath("../../include")]),
        .target(name: "FocusMeasure", dependencies: ["COpencv4"]),
        .systemLibrary(name: "CPylon", pkgConfig: "pylon"),
        .systemLibrary(name: "COpencv4", pkgConfig: "opencv4"),
    ],
    cLanguageStandard: .c99,
    cxxLanguageStandard: .cxx1z
)
