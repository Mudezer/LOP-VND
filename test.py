import os
import csv
# Read the entire file, skipping the header, and apply func to each line

input = "assets/timings/vnd_time.csv"
# def read_file(file_path):
#     with open(file_path, 'r') as file:
#         next(file)  # Skip the header
#         for line in file:
#             instance, avg_time = line.strip().split(',')
#             print(f"{instance}, {avg_time}")




if __name__ == '__main__':

    with open(input, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            instance = row['Instance']
            avg_time = row['AvgTime']

            # Build the command
            command = f"./lop -i assets/size_150/{instance} --ils TEI --perturb exchange --time {avg_time} --moves 2 --init cw"
            print(command)
            os.system(command)

    # os.system("./lop -i assets/size_150/N-tiw56r72_150 --ils TEI --perturb exchange --time 22.41135 --moves 2 --init cw")
    # os.system("./lop -i assets/size_150/N-tiw56r72_150 --ils TEI --perturb exchange --time 22.41135 --moves 2 --init cw")