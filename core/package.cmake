{
	"id":"core",
	"version":"0.0.1",
	"name":"c++ core library",
	"description":"contains functionality for executing cmake unit tests",
	"license":"MIT",
	"owner":"Tobias Becker",
	"owner_email":"becker.tobi@gmail.com",
	"authors":"Tobias Becker",
  "dependencies":{

  },
  "include":"**",
  "exclude":[".git/**", "build/**", "packages/**"],
  "cpp":"default_layout",
  "cutil":{
    "exports":"cmake/*.cmake",
    "onLoad":"cmake/init_testdriver.cmake"
  }
}

