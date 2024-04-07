# INFO-H413 - Linear Ordering Problem Otpimization

## Description
This repository is about implementing multiple algorithms in order to optimize
the Linear Ordering Problem (LOP). This is part of the INFO-H413 - "Heuristic Optimization" Course.


## Usage

Two ways to execute the code:
1) One algorithm on a certain instance, by providing the specifications of the algorithm you want and the
instance you want to run directly as argument in the command line.
2) All algorithm of a kind on all instances, by running the `runner.py` python script and by providing the algorithm kind.


### One Algorithm, One Instance

One algorithm, one instance is about running the desired algorithm on a specific instance
and outputting the results in the `algorithm` folder of the `results` folder.

Usage: ```./lop -i <instance_path> <algorithm> <algorithm_parameters>```

- `<instance_path>`: The path to the instance file.
- `<algorithm>`: The algorithm you want to run. It can be one of the following:
    - `--iter` : single perturbation iterative improvement
    - `--vnd` : variable neighbor descent 

- `<algorithm_parameters>`: the parameters for the algorithm you want to run.
  - For `--iter`:= `<pivot> <neighborhood> <initialisation>`
    - `<pivot>`: the pivot selection strategy. It can be one of the following:
        - `--first` : select the first pivot
        - `--best` : select the best pivot
    - `<neighborhood>`: the neighborhood strategy. It can be one of the following:
        - `--transpose` : the transpose neighborhood
        - `--exchange` : the exchange neighborhood
        - `--insert` : the insert neighborhood
    - `<initialisation>`: the perturbation strategy. It can be one of the following:
        - `--cw` : the Chenery and Watanabe initialisation
        - `--random` : the exchange perturbation

  - For `--vnd`:= `<neighborhood_sequence>`
    - `TIE` : the sequence of neighborhood perturbation Transpose, Insert, Exchange
    - `TEI` : the sequence of neighborhood perturbation Transpose, Exchange, Insert

Example: run the first improvement iterative improvement algorithm with
the transpose neighborhood and the Chenery and Watanabe initialisation
on the instance `N-tiw56r72_250`:

```bash
make
./lop -i assets/instances/N-tiw56r72_250 --iter --first --exchange --cw
```

### One Algorithm, All Instances
One algorithm, all instances is about running the desired algorithm on all instances provided in a folder
and outputting the results in the `algorithm` folder of the `results` folder.

Usage: ```./runner.py <instances_directory> <algorithm>```

- `<instances_directory>`: The path to the folder containing the instances.
- `<algorithm>`: The algorithm you want to run. It can be one of the following:
    - `--iter` : single perturbation iterative improvement
    - `--vnd` : variable neighbor descent

Example: run all the simple iterative improvement algorithm on all instances in the `assets/instances` folder:

```bash
python3 runner.py assets/instances --iter
```

