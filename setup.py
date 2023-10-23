import subprocess
import argparse

def build_project():
    source_dir = "."
    build_dir = "./project"

    cmake_command = ["cmake", '-S', source_dir, '-B', build_dir]
    subprocess.run(cmake_command)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Build project or its dependencies')
    parser.add_argument('--build', action='store_true', help='Build the solution + exe')

    args = parser.parse_args()

    if args.build:
        build_project()