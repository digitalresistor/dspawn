import os

env = Environment(**ARGUMENTS)

env.MergeFlags('-Wall -Wextra -Wno-unused-parameter -Wno-parentheses -Werror')

debug_build = ARGUMENTS.get('debug', '0')

if debug_build == '1':
    env.MergeFlags('-DDEBUG -g')

Export("env")

# Add libev as a library
env.MergeFlags('-lev -I/usr/local/include/')

SConscript('src/SConscript')
SConscript('tests/SConscript')

env.Command('src/version.h', [], 'echo "char VERSION[] =" \\"`git describe --always --long --dirty || echo UNKNOWN`\\"";" > src/version.h')
env.AlwaysBuild('src/version.h')

env.Alias('dspawn', 'src/dspawn')
Default('src/dspawn')

test = env.Alias('tests', 'tests/testrunner')
env.Alias('test', 'tests')
runtests = env.Alias('runtests', [ 'tests/testrunner' ], test[0].sources[0].abspath)
env.AlwaysBuild(runtests)
