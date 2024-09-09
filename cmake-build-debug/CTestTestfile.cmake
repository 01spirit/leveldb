# CMake generated Testfile for 
# Source directory: D:/project/leveldb
# Build directory: D:/project/leveldb/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(leveldb_tests "D:/project/leveldb/cmake-build-debug/leveldb_tests.exe")
set_tests_properties(leveldb_tests PROPERTIES  _BACKTRACE_TRIPLES "D:/project/leveldb/CMakeLists.txt;366;add_test;D:/project/leveldb/CMakeLists.txt;0;")
add_test(c_test "D:/project/leveldb/cmake-build-debug/c_test.exe")
set_tests_properties(c_test PROPERTIES  _BACKTRACE_TRIPLES "D:/project/leveldb/CMakeLists.txt;392;add_test;D:/project/leveldb/CMakeLists.txt;395;leveldb_test;D:/project/leveldb/CMakeLists.txt;0;")
add_test(env_windows_test "D:/project/leveldb/cmake-build-debug/env_windows_test.exe")
set_tests_properties(env_windows_test PROPERTIES  _BACKTRACE_TRIPLES "D:/project/leveldb/CMakeLists.txt;392;add_test;D:/project/leveldb/CMakeLists.txt;401;leveldb_test;D:/project/leveldb/CMakeLists.txt;0;")
subdirs("third_party/googletest")
subdirs("third_party/benchmark")
