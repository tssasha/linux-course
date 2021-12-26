project('rhasher', 'c')

c_args = []
deps = []

cc = meson.get_compiler('c')
lib_rhash = cc.find_library('librhash', dirs: '/usr/local/lib')
deps += lib_rhash

if not get_option('disable-readline')
	lib_readline = dependency('readline', required: false)
	if lib_readline.found()
		c_args += '-DUSE_READLINE'
		deps += lib_readline
	endif
endif

executable('rhasher', 'rhasher.c', dependencies: deps, c_args: c_args)

test_algos = ['SHA1', 'MD5', 'TTH']
test_script = find_program('test.sh', required: false)
foreach algo: test_algos
	test(algo, test_script, env: 'ALGO=' + algo, is_parallel: false)
endforeach