
# a simple and stupid setup tests function
function(core_tests_setup ip)
  rcall(core_ip = project.getInstalledPackage(core))
  rcall(test_runner_cpp = core_ip.glob("resources/test_runner.cpp"))
  cps_import_package_vars(${ip}) 
  rcall(tests = ip.glob("tests/*.cpp"))
  if(tests)
    message("setting up tests for ${package_id}")

    add_executable("${package_unique_id}.tests" ${tests} ${test_runner_cpp})
    add_test("${package_unique_id}.tests" COMMAND "${package_unique_id.tests}")
    nav(libraries = ip.cpp.libraries)
    if(libraries)
     target_link_libraries("${package_unique_id}.tests" ${libraries})
    endif()
  endif()
endfunction()