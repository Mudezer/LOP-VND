import os
import sys

algorithm_types = ["--iter", "--vnd", "--memetic"]
vnd_sequences = ["TIE", "TEI"]
initialisations = ["--init random", "--init cw"]
pivot_rules = ["--pivot best", "--pivot first"]
neighbourhoods = ["--neighbour exchange", "--neighbour insert", "--neighbour transpose"]



input = "assets/instances"
input = "assets/size_150"

if __name__ == '__main__':
    """
    Allows to run all the algorithms of a certain type on all the instances in the directory
    example:
        python3 runner.py assets/instances/ --iter
        
        means to run all the different iterative algorithms on
         all the instances in the assets/instances directory
    """
    os.system("make clean")
    os.system("make")



    input = sys.argv[1]
    algotype = sys.argv[2]

    # algotype = "--vnd"

    w = os.walk(input)

    instanceNames = []

    for(dirpath, dirnames, filenames) in w:
        instanceNames.extend(filenames)
        break

    for instance in instanceNames:
        if algotype == "--iter":
            for init in initialisations:
                for pivot in pivot_rules:
                    for neighbour in neighbourhoods:
                        command = f"./lop -i {input}/{instance} {algotype} {pivot} {neighbour} {init}"
                        print(command)
                        os.system(command)


        elif algotype == "--vnd":
            for seq in vnd_sequences:
                command = f"./lop -i {input}/{instance} {algotype} {seq}"
                print(command)
                os.system(command)


        elif algotype == "--memetic":
            command = f"./lop -i {input}/{instance} --memetic --neighbour exchange --rank-comb --rank-select --rank-mut --pop 10 --rate 0.1 --gen 10"
            print(command)
            os.system(command)


