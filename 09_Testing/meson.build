project('buf', 'c', default_options : 'b_coverage=true')

tests = [
	'clear',
	'grow_trunc',
    'init_free',
    'pop',
    'push'
]

buf = library('buf', 'buf.c')
foreach test : tests
    test_exe = executable(test, 'tests/' + test + '.c', link_with: buf)
	test(test, test_exe)
endforeach