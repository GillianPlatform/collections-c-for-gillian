import os
import glob
import subprocess

TIMEOUT=30  # Timeout in seconds

class bcolors:
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'

# Setting directories and arguments
lib_dir = "../../libs/fixed"
include_dir = f"{lib_dir}/include"
test_folder = "../../gillian-cbmc/normal"
utils_folder = "../../gillian-cbmc/utils"

args = (f"{lib_dir}/*.c {utils_folder}/utils.c -I{include_dir} -I{utils_folder} "
        "--bounds-check --pointer-check --div-by-zero-check "
        "--pointer-primitive-check --havoc-undefined-functions "
        "--unwind 10 --os macos --arch x86_64 --function main --drop-unused-functions")

# Function to execute the cbmc command
def run_cbmc(file_path, args):
    cmd = f"/usr/bin/time -p cbmc {file_path} {args}"
    try:
        output = subprocess.check_output(cmd, shell=True, stderr=subprocess.STDOUT, text=True, timeout=TIMEOUT)
        # Extract execution time from the stderr output where time utility reports it
        time_str = next((line for line in output.split('\n') if 'real' in line), None)
        if time_str:
            exec_time = float(time_str.split()[1])
    except subprocess.TimeoutExpired:
        print(f"{bcolors.FAIL}Timeout:{bcolors.ENDC} Command exceeded {TIMEOUT} seconds on file: {file_path}")
        exec_time = TIMEOUT  # Count the time as 60s if it times out
        output = "Command timed out"
    except subprocess.CalledProcessError as e:
        output = e.output
        time_str = next((line for line in output.split('\n') if 'real' in line), None)
        if time_str:
            exec_time = float(time_str.split()[1])
    # print(f"Execution time: {exec_time:.2f} seconds")
    return output, exec_time

# Main script
if __name__ == "__main__":
    for folder in sorted(glob.glob(f"{test_folder}/*")):
        if os.path.isdir(folder):
            total_time = 0.0
            print(f"Processing folder: {folder}")
            for file_path in sorted(glob.glob(f"{folder}/*.c")):
                if os.path.isfile(file_path):
                    # print(f"Running command on file: {file_path}")
                    output, exec_time = run_cbmc(file_path, args)
                    if exec_time < 1:
                        print(f"{file_path} execution time is {exec_time:.2f} seconds. This is too low, probably an error.")
                    total_time += exec_time

                    if "VERIFICATION FAILED" in output:
                        print(f"{bcolors.FAIL}{file_path}: VERIFICATION FAILURE!!{bcolors.ENDC}")

            print(f"Total execution time for folder {folder}: {total_time:.2f} seconds")
