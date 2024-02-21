import os

# Define the directory containing the files
directory = 'rules-scripts/scripts/rules'

# Open the output file for writing
with open('rules-description.txt', 'w') as outfile:
    # Iterate over the files in the directory
    for filename in os.listdir(directory):
        # Check if the file is a text file
        if filename.endswith('.tcl'):
            # Open the file and read the second line
            with open(os.path.join(directory, filename)) as infile:
                lines = infile.readlines()
                second_line = lines[1].strip()
            # Write the file name and second line to the output file
            outfile.write(os.path.splitext(filename)[0] + " " + second_line + "\n")