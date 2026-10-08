project('Zamhareer', 'cpp', default_options: ['cpp_std=c++17'])

cpp_files = run_command('find', './src', '-name', '*.cpp', check:true).stdout().split()
hpp_files = include_directories('./include/')

deps=[]

build_mode = get_option('build_mode')
rend_api = get_option('rend_api')
platform = get_option('platform')

windowing = true

message('====== building in ' + build_mode + ' mode ======')
if build_mode == 'debug'
  add_project_arguments('-DDEB_BUILD', '-g', '-ggdb', '-Wall', language: 'cpp')
else
  add_project_arguments('-DREL_BUILD', '-O3', language: 'cpp')
endif

message('====== rendering api is ' + rend_api + ' ======')
if rend_api == 'opengl'
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
  deps += dependency('gl', required : true)
  windowing_arg = '-DWINDOWING=1'
else
  windowing_arg = '-DWINDOWING=0'
endif
add_project_arguments(windowing_arg, language: 'cpp')

zmlib = static_library('zm', cpp_files,
  include_directories:hpp_files,
  dependencies: deps)

# users of the engine see the same WINDOWING value and GLFW/GL headers as the engine itself
zmlib_dep = declare_dependency(
  link_with:zmlib,
  include_directories:hpp_files,
  compile_args: [windowing_arg],
  dependencies: deps,
  )

test('zm', executable('zm_test', 'tests/test_zm.cpp', dependencies: zmlib_dep))

