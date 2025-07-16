project('app', 'cpp')


cpp_files = run_command('find', 'source/src', '-name', '*.cpp', check:true).stdout().split()
hpp_files = include_directories('./source/include/')

zmlib = subproject('Zamhareer', default_options: ['build_mode=debug',
  'rend_api=opengl',
  'platform=linux'])

zmlib_dep = zmlib.get_variable('zmlib_dep')

executable('app', cpp_files,
  include_directories: hpp_files,
  dependencies:zmlib_dep)
