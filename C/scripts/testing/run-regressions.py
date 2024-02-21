import os
import subprocess
import sys

# Define ANSI color codes
RED = '\033[0;31m'
GREEN = '\033[0;32m'
YELLOW = '\033[0;33m'
RESET = '\033[0m'  # Reset color to default

main_C_test_directory = "C/regression-tests/regression-tests"

if len(sys.argv) != 2:
    print("[run-regression]: Usage run-regression path/to/elf/dir or Usage run-regression all to run all tests")
    sys.exit(1)

arg = sys.argv[1]

if arg == 'all':
    if os.path.isdir(main_C_test_directory):
        test_files = [os.path.join(dp, f) for dp, dn, filenames in os.walk(main_C_test_directory) for f in filenames if f.endswith('.elf')]
    else:
        print("Directory not found:", main_C_test_directory)
        sys.exit(1)

    for test_file in test_files:
        print("Testing:", test_file)
        test_dir = os.path.dirname(test_file)
        result = subprocess.run(["sh", "scripts/testing/run-regressions.sh", test_dir])
        if result.returncode != 0:
            sys.exit(1)
else:
    if os.path.isdir(arg):
        test_files = [os.path.join(dp, f) for dp, dn, filenames in os.walk(arg) for f in filenames if f.endswith('.elf')]
        if not test_files:
            print("No elf file found in the directory")
            sys.exit(1)
    else:
        print("Directory not found:", arg)
        sys.exit(1)

    test_file = test_files[0]
    test_dir = os.path.dirname(test_file)

    if os.path.getsize(test_file) > 0:
        print(f"{YELLOW}========================================================================================================================================================{RESET}")
        print("RUNNING", test_file, "test")
    else:
        print("No elf file found in the directory")
        sys.exit(1)

    expected_results_file = os.path.join(test_dir, "results.expected")

    if os.path.getsize(expected_results_file) > 0:
        print("Comparing", os.path.join(test_dir, "results.output"), "vs.", expected_results_file)
    else:
        print("No results.expected file found in the directory")
        sys.exit(1)

    subprocess.run(["rm", "-rf", "results.output"])
    result = subprocess.run(["simulavr", "-d", "atmega32", "-f", test_file, "-W", "0x20,-", "-R", "0x22,-", "-T", "exit"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    results_output = result.stdout.decode('utf-8')
    with open(os.path.join(test_dir, "results.output"), 'w') as output_file:
        output_file.write(results_output)

    print("RESULTS:")
    diff_result = subprocess.run(["diff", os.path.join(test_dir, "results.output"), expected_results_file], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if diff_result.returncode == 0:
        print(f"[{test_file}]:{GREEN} PASS {RESET}")
    else:
        print(f"[{test_file}]:{RED} FAIL{RESET}")
        sys.exit(1)

    subprocess.run(["rm", "-rf", os.path.join(test_dir, "results.output")])
