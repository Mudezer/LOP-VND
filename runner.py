import os
import sys
import csv

algorithm_types = ["--iter", "--vnd", "--memetic"]
vnd_sequences = ["TIE", "TEI"]
initialisations = ["--init random", "--init cw"]
pivot_rules = ["--pivot best", "--pivot first"]
neighbourhoods = ["--neighbour exchange", "--neighbour insert", "--neighbour transpose"]
perturbations = ["exchange", "insert", "transpose"]
popSize = [10, 20, 50, 100, 200]
mutRate = [0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.7, 0.9, 1.0]


input = "assets/instances"
input_150 = "assets/size_150"
timings = "assets/timings/vnd_time.csv"


if __name__ == '__main__':
    """
    Allows to run all the algorithms of a certain type on all the instances in the directory
    example:
        python3 runner.py assets/instances/ --iter
        
        means to run all the different iterative algorithms on
         all the instances in the assets/instances directory
         
    note: for the ILS and the memetic algorithm, the timings file is used to determine the time to run the algorithm
    hence, a timing file with [instance, time] must be provided 
    """
    os.system("make clean")
    os.system("make")



    # input = sys.argv[1]
    # algotype = sys.argv[1]

    algotype = "--memetic"

    w = os.walk(input)

    instanceNames = []

    for(dirpath, dirnames, filenames) in w:
        instanceNames.extend(filenames)
        break

    if algotype == "--iter":
        for instance in instanceNames:
            for init in initialisations:
                for pivot in pivot_rules:
                    for neighbour in neighbourhoods:
                        command = f"./lop -i {input}/{instance} {algotype} {pivot} {neighbour} {init}"
                        print(command)
                        os.system(command)


    elif algotype == "--vnd":
        for instance in instanceNames:
            for seq in vnd_sequences:
                command = f"./lop -i {input}/{instance} {algotype} {seq}"
                print(command)
                os.system(command)

    elif algotype == "--ils":
        with open(timings, newline='') as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                instance = row['Instance']
                avg_time = row['AvgTime']

                # Build the command
                command = f"./lop -i {input_150}/{instance} --ils TEI --perturb insert --time {avg_time} --moves 4 --init cw "
                print(command)
                os.system(command)


    elif algotype == "--memetic":
        with open(timings, newline='') as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                instance = row['Instance']
                avg_time = row['AvgTime']

                command = f"./lop -i {input_150}/{instance} --memetic --neighbour exchange --rank-comb --rank-select --rank-mut --pop 20 --rate 0.3 --time {avg_time}"                    # ./lop -i assets/size_150/N-tiw56r72_150 --memetic --neighbour exchange --rank-comb --rank-select --rank-mut --pop 10 --rate 0.1 --time 22.41135
                print(command)
                os.system(command)


