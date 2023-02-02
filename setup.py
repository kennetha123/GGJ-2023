import subprocess

source_dir = "."
build_dir = "./project" 

cmake_command = ["cmake", '-S', source_dir, '-B', build_dir]

subprocess.run(cmake_command)