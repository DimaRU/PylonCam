// swift-tools-version:5.3

import PackageDescription

let package = Package(
    name: "PylonCam",
    platforms: [.macOS(.v11)],
    dependencies: [
    ],
    targets: [
        .target(
            name: "PylonCam",
            dependencies: ["CPylon", "COpencv4"],
            linkerSettings: [
                .linkedFramework("Pylon", .when(platforms: [.macOS])),
                .unsafeFlags(["-rpath"], .when(platforms: [.macOS])),
                .unsafeFlags(["/Library/Frameworks"], .when(platforms: [.macOS])),
            ]
        ),
        .systemLibrary(name: "CPylon", pkgConfig: "Pylon"),
        .systemLibrary(name: "COpencv4", pkgConfig: "opencv4"),
    ],
    cxxLanguageStandard: .cxx1z
)
