project('Zamhareer', 'cpp')

cpp_files = run_command('find', './src', '-name', '*.cpp', check:true).stdout().split()
hpp_files = include_directories('./include/')

deps=[]

build_mode = get_option('build_mode')
rend_api = get_option('rend_api')
platform = get_option('platform')

windowing = true

message('====== building in ' + build_mode + ' mode ======')
if build_mode == 'debug'
  add_project_arguments('-DDEB_BUILD', '-g', '-ggdb', language: 'cpp')
elif
  add_project_arguments('-DREL_BUILD', '-o3', language: 'cpp')
endif

message('====== rendering api is ' + rend_api + ' ======')
if rend_api == 'opengl'
  add_project_arguments('-DAPI_GL', language: 'cpp')
  deps += dependency('gl', required: true)
endif

message('====== platform is ' + platform + ' ======')
if platform == 'linux'
  add_project_arguments('-DPLAT_LINUX', language: 'cpp')
  windowing = true
elif platform == 'windows'
  add_project_arguments('-DPLAT_WIN', language: 'cpp')
  windowing = true
elif platform == 'android'
  add_project_arguments('-DPLAT_ANDROID', language: 'cpp')
  windowing = false
endif

if windowing
  deps += dependency('glfw3', required : true)
  add_project_arguments('-DWINDOWING=1', language: 'cpp')
else
  add_project_arguments('-DWINDOWING=0', language: 'cpp')
endif

zmlib = static_library('zm', cpp_files,
  include_directories:hpp_files,
  dependencies: deps)

zmlib_dep = declare_dependency(
  link_with:zmlib,
  include_directories:hpp_files,
  )

