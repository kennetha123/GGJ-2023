import subprocess

source_dir = "../2DRPG"
build_dir = "../2DRPG/project" 

cmake_command = ["cmake", '-S', source_dir, '-B', build_dir]

subprocess.run(cmake_command)