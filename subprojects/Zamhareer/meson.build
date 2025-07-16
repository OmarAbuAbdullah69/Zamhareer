project('Zamhareer', 'cpp')

cpp_files = run_command('find', './src', '-name', '*.cpp', check:true).stdout().split()
hpp_files = include_directories('./include/')

build_mode = get_option('build_mode')
rend_api = get_option('rend_api')
platform = get_option('platform')

message('====== building in ' + build_mode + ' mode ======')
if build_mode == 'debug'
  add_project_arguments('-DDEB_BUILD', '-g', '-ggdb', language: 'cpp')
elif
  add_project_arguments('-DREL_BUILD', '-o3', language: 'cpp')
endif

message('====== rendering api is ' + rend_api + ' ======')
if rend_api == 'opengl'
  add_project_arguments('-DAPI_GL', language: 'cpp')
  #TODO: add opengl linking later
endif

message('====== platform is ' + platform + ' ======')
if platform == 'linux'
  add_project_arguments('-DPLAT_LINUX', '-DWINDOWING=1', language: 'cpp')
elif platform == 'windows'
  add_project_arguments('-DPLAT_WIN', '-DWINDOWING=1', language: 'cpp')
elif platform == 'android'
  add_project_arguments('-DPLAT_ANDROID', '-DWINDOWING=0', language: 'cpp')
endif

zmlib = static_library('zm', cpp_files,
  include_directories:hpp_files)

zmlib_dep = declare_dependency(
  link_with:zmlib,
  include_directories:hpp_files,
  )

