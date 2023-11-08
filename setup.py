import subprocess
import argparse
import pandas as pd

def build_project():
    source_dir = "."
    build_dir = "./project"
    cmake_command = ["cmake", '-S', source_dir, '-B', build_dir]
    subprocess.run(cmake_command)

def update_localization():
    csv_file = 'resources/Localization/localization.csv'
    json_file = 'resources/Localization/localization.json'
    
    # Read CSV file using pandas
    df = pd.read_csv(csv_file)
    
    # Convert to JSON, orient records for a list of records format
    df.to_json(json_file, orient='records', force_ascii=False)
    
    print(f"Localization updated: {json_file}")

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Build project or its dependencies')
    parser.add_argument('--build-all', action='store_true', help='Build the solution + exe + all dependencies')
    parser.add_argument('--build', action='store_true', help='Build the solution + exe')
    parser.add_argument('--up-loc', action='store_true', help='Update the localization files')

    args = parser.parse_args()

    if args.build_all:
        build_project()
        update_localization()    
    if args.build:
        build_project()
    elif args.up_loc:
        update_localization()
