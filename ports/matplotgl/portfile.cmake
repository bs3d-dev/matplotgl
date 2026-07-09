vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO bs3d-dev/matplotgl
    REF 12c27350f7f433570ad5f7b0b49a9e2cc0b831f7
    SHA512 cf05d1f4b079591fc5a5892e609ced336a72554297584576fec42341d98bee1702d498952c6fe36150f9440dcd48d794e83ed8add24f643d6a81e635ad1f5576
    HEAD_REF main
)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(
    PACKAGE_NAME matplotgl
    CONFIG_PATH share/cmake/matplotgl
)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
