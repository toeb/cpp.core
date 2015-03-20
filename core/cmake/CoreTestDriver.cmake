function(core_test_create file pd)
    new()
    ans(test_descriptor)
    get_filename_component(name "${file}" NAME)
    get_filename_component(file "${file}" REALPATH)
    obj_set(${test_descriptor} name "${name}" )
    obj_set(${test_descriptor} id "${file}")
    checksum_file(${file})
    ans(cache_key)
    obj_set(${test_descriptor} cache_key ${cache_key})
    obj_set(${test_descriptor} path ${file})
    obj_set(${test_descriptor} sources ${file})
    nav(target_descriptor.versioned_package FORMAT "{pd.id}@{pd.version}")
    return(${test_descriptor})
endfunction()

function(CoreTestDriver)
  proto_declarefunction(createTarget)
  proto_declarefunction(run)
  proto_declarefunction(discover)
  
  message("instanciated CoreTestDriver")

  function(${createTarget} name tests project)
      

    map_select("from test in ${tests} select {test.sources}")
    ans(sources)
    
    map_select("from test in ${tests} select {test.dependencies}")
    ans(dependencies)

    call(project.getPackageDirectory(core))
    ans(core_package_dir)
    message("core_package_dir ${core_package_dir}")

    add_executable("${name}" ${sources} "${core_package_dir}/resources/test_runner.cpp")
      message("createtarget core: ${dependencies}")
    target_link_libraries("${name}" ${dependencies})

  endfunction()

  function(${run} test project)

  endfunction()

  function(${discover} locations project pd)
    set(res)
    # get the direct dependencies to get targets
    call(project.getDirectDependencies(${pd}))
    ans(dependencies)
    message(FORMAT "{pd.id} dependencies: ${dependencies}")

    set(targets)
    foreach(dependency ${dependencies})
      call(project.getTargets("${pd}"))
      ans(target)
      list(APPEND targets ${target})
    endforeach()

    foreach(location ${${locations}})
      json_read("${location}/CoreTestDriver.json")
      ans(cfg)
      if(NOT cfg)
        set(globs "*.core.test.cpp")
      else()
        nav(globs = cfg.include)
      endif()
      set(slash /)
      list_combinations(location slash globs)
      ans(combinations)
      file(GLOB files ${combinations})
      message("CoreTestDriver: ${location}: ${files} from ${combinations}")
      foreach(file ${files})
        core_test_create(${file} ${pd})
        ans(test_descriptor)
        obj_set(${test_descriptor} driver CoreTestDriver)
        obj_set(${test_descriptor} dependencies ${targets})


        list(APPEND res ${test_descriptor})
      endforeach()
    endforeach()
    return_ref(res)
    return()

    #obsolete
    message("discovering tests in ${directory}")
    map_get(${test_config} "include")
    ans(includes)
    if(includes)
      ref_get(${includes})
      ans(includes)
    else()
      set(includes "*.core.test.cpp")
    endif()
    set(all_tests)
    foreach(include ${includes})
      file(GLOB tests "${directory}/${include}")
      list(APPEND all_tests "${tests}")
    endforeach()
    message("allo tests found: ${all_tests}")
    

    # package mananager get local package, get resource dir
    this_get(core_package_dir)
    message("core_package_dir ${core_package_dir}")

    add_executable(
      "core.testing.application" 
      "${all_tests}" 
      "${core_package_dir}/resources/test_runner.cpp"
      )

    call(project.getDependencyOrder())
    ans(dependencies)

    set(target_list)
    foreach(dependency ${dependencies})
      nav(id FORMAT {dependency.id}@{dependency.version})
      list(APPEND target_list "${id}")
    endforeach()
    message("target list ${target_list}")
    target_link_libraries("core.testing.application" ${target_list})

    message("added test target core.testing.application with dependencies: ${target_list}")

  endfunction()
  



endfunction()