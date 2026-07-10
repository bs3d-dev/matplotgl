# Empty overlay port: don't build anything, just satisfy the dependency
# graph. find_package(Qt6 ...) will fall through to the system/official
# Qt6 installation via CMAKE_PREFIX_PATH.
set(VCPKG_POLICY_EMPTY_PACKAGE enabled)