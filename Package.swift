// swift-tools-version:5.3

import PackageDescription

let package = Package(
    name: "PylonCam",
    platforms: [.macOS(.v11)],
    dependencies: [
        .package(name: "Qlift", url: "https://github.com/DimaRU/qlift", .branch("master")),
        .package(url: "https://github.com/ianpartridge/swift-log-syslog.git", from: "1.0.0"),
    ],
    targets: [
        .target(
            name: "PylonCam",
            dependencies: [
                "Qlift",
                "PylonLib",
                .product(name: "LoggingSyslog", package: "swift-log-syslog")
            ],
            linkerSettings: [
                .linkedFramework("QtWidgets", .when(platforms: [.macOS])),
                .linkedFramework("QtCore", .when(platforms: [.macOS])),
                .linkedFramework("QtGui", .when(platforms: [.macOS])),
                .linkedFramework("Pylon", .when(platforms: [.macOS])),
                .unsafeFlags(["-rpath"], .when(platforms: [.macOS])),
                .unsafeFlags(["/Library/Frameworks"], .when(platforms: [.macOS])),
            ]
        ),
        .target(
            name: "PylonLib",
            dependencies: ["CPylon", "COpencv4"]
        ),
        .systemLibrary(name: "CPylon", pkgConfig: "Pylon"),
        .systemLibrary(name: "COpencv4", pkgConfig: "opencv4"),
    ],
    cxxLanguageStandard: .cxx1z
)
