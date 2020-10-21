project('EngineTests', 'cpp', 'c', default_options : ['c_std=c11', 'cpp_std=c++17'])

engine_sub = subproject('Engine')
engine = engine_sub.get_variable('engine')
glm = engine_sub.get_variable('glm')
termcolors = engine_sub.get_variable('termcolors')

executable('RenderTest', 'tests/RenderTest.cpp', dependencies: [engine, glm, termcolors])