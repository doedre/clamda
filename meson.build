project('clamda', 'c')

cmocka_dep = dependency('cmocka')

src = [
  'src/parser/utils.c',
  'src/string/trim.c'
]

clamda = library('clamda',
  include_directories : 'include',
  sources : src)

parser_utils_test = executable('parser_utils_test',
  sources : 'tests/parser/utils.c',
  include_directories : 'include',
  dependencies : cmocka_dep,
  link_with : clamda)

string_trim_test = executable('string_trim_test',
  sources : 'tests/string/trim.c',
  include_directories : 'include',
  dependencies : cmocka_dep,
  link_with : clamda)

test('clamda_parser_utilities_test', parser_utils_test)
test('clamda_string_trim_test', string_trim_test)

