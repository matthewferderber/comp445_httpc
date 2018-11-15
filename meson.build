inc_dir = include_directories('include')

http_sources = files(
	'src/main.c',
	'src/help.c',
	'src/request.c',
	'src/response.c',
	'src/url.c',
	'src/util.c',
	'src/header.c',
	'src/file_reader.c'
	)

executable('httpc', http_sources, include_directories: [inc_dir], install: true)
