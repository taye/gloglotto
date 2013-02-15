require 'rake'
require 'rake/clean'
require 'fileutils'

CXX    = 'clang++'
CFLAGS = "-Wall -Werror-implicit-function-declaration -std=c++11 -Iinclude #{ENV['CFLAGS']}"
LDFLAGS = "-lGL -lGLEW -lglut #{ENV['LDFLAGS']}"

SOURCES = FileList['source/**/*.cpp']
OBJECTS = SOURCES.ext('o')

CLEAN.include(OBJECTS)
CLOBBER.include('libgloglotto.so', 'libgloglotto.a')

task :default => ['libgloglotto.so', 'libgloglotto.a']

task :install, [:path] => ['libgloglotto.so', 'libgloglotto.a'] do |t, args|
	path = args[:path] || '/usr/local'

	FileUtils.install 'include/gloglotto', path
	FileUtils.install FileList['source/*.tpp'], "#{path}/include/gloglotto"
	FileUtils.install FileList['source/maths/*.tpp'], "#{path}/include/gloglotto/maths"
end

task :doc do
	sh "cldoc #{CFLAGS} -- --output doc #{FileList['include/**/**']} #{FileList['source/**/*.cpp']}"
end

file 'libgloglotto.so' => OBJECTS do
	sh "#{CXX} #{CFLAGS} -fPIC #{OBJECTS} -shared -Wl,-soname,libgloglotto -o libgloglotto.so #{LDFLAGS}"
end

file 'libgloglotto.a' => OBJECTS do
	sh "ar rcs libgloglotto.a #{OBJECTS}"
end

rule '.o' => '.cpp' do |t|
	sh "#{CXX} #{CFLAGS} -fPIC -o #{t.name} -c #{t.source}"
end
