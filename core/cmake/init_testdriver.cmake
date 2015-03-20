function(init)
  message("initializing test driver for core")
  map_tryget(global testEngine)
  ans(testEngine)
  if(NOT  testEngine)
    message("test engine not found (global.testEngine) cts installed?")
    return()
  endif()
  
  new(CoreTestDriver)
  ans(testDriver)


  call(testEngine.addDriver(${testDriver}))

  return()
  map_tryget(global test_drivers)
  if(NOT test_drivers)
    map_new()
    ans(test_drivers)
    map_set(global test_drivers "${test_drivers}")
  endif()

  
  obj_new(CoreTestingTestDriver "${package_dir}")
  ans(td)

  map_set(${test_drivers} "core.testing" "${td}")


  
  
endfunction()