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
    - `--ils` : iterated local search
    - `--memetic` : memetic algorithm

- `<algorithm_parameters>`: the parameters for the algorithm you want to run.
  - For `--iter`:= `--pivot <pivot_argument> --neighbour <neighborhood_argument> --init <initialisation_argument>`
    - `<pivot_argument>`: the pivot selection strategy. It can be one of the following:
        - `first` : select the first pivot
        - `best` : select the best pivot
    - `<neighborhood_argument>`: the neighborhood strategy. It can be one of the following:
        - `transpose` : the transpose neighborhood
        - `exchange` : the exchange neighborhood
        - `insert` : the insert neighborhood
    - `<initialisation_argument>`: the initialization strategy. It can be one of the following:
        - `cw` : the Chenery and Watanabe initialisation
        - `random` : the exchange perturbation

  - For `--vnd`:= `<neighborhood_sequence>`
    - `TIE` : the sequence of neighborhood perturbation Transpose, Insert, Exchange
    - `TEI` : the sequence of neighborhood perturbation Transpose, Exchange, Insert
    
  - For `--ils` := `<neighborhood_sequence> --perturb <perturbation_argument> --time <max_run_time> --move <number_of_perturbation_steps> --init <initialization_argument>`
    - `<neighborhood_sequence>`: the sequence of neighborhood perturbation for the local search. It can be one of the following:
      - `TIE` : the sequence of neighborhood perturbation Transpose, Insert, Exchange
      - `TEI` : the sequence of neighborhood perturbation Transpose, Exchange, Insert
    - `<perturbation_argument>`: the perturbation operation. It can be one of the following:
        - `transpose` : the transpose operation
        - `exchange` : the exchange operation
        - `insert` : the insert operation
    - `<max_run_time>`: termination Criterion: maximum amount of time the algorithm will run
    - `<number_of_perturbation_steps>`: the number of simple perturbation steps per perturbation phase
    - `<initialization_argument>`: the initialization strategy. It can be one of the following:
      - `cw` : the Chenery and Watanabe initialisation
      - `random` : the exchange perturbation

  - For `--memetic` := `--neighbour <local_search_neighbour_argument> --rank-comb --rank-select --rank-mut --pop <population_size> --rate <mutation_rate> --time <max_run_time`
    - `<local_search_neighbour_argument>` : neighborhood perturbation for the local search. It can be one of the following:
      - `exchange` : the exchange neighborhood
      - `insert` : the insert neighborhood
    - `--rank-com` : the recombination strategy
    - `--rank-select` : the selection strategy
    - `--rank-mut` : the mutation strategy
    - `<population_size>` : the population size
    - `<mutation_rate>` : the mutation rate
    - `<max_run_time>` : termination Criterion: maximum amount of time the algorithm will run

Example: run the first improvement iterative improvement algorithm with
the transpose neighborhood and the Chenery and Watanabe initialisation
on the instance `N-tiw56r72_250`:

```bash
make
./lop -i assets/instances/N-tiw56r72_250 --iter --pivot first --neihgoubr exchange --init cw
```

Example : run the memetic algorithm with exchange operation with 10 of population size and 10% of mutation rate 
and 22,41135 of max run time on the instance `N-tiw56r72_250`:

```bash
make
./lop ./lop -i assets/instances/N-tiw56r72_150 --memetic --neighbour exchange --rank-comb --rank-select --rank-mut --pop 10 --rate 0.1 --time 22,41135
```

### One Algorithm, All Instances
One algorithm, all instances is about running the desired algorithm on all instances provided in a folder
and outputting the results in the `algorithm` folder of the `results` folder.

Usage: ```./runner.py <instances_directory> <algorithm>```

- `<instances_directory>`: The path to the folder containing the instances.
- `<algorithm>`: The algorithm you want to run. It can be one of the following:
    - `--iter` : single perturbation iterative improvement
    - `--vnd` : variable neighbor descent
    - `--ils <max_run_time>` : iterated local search
    - `--memetic <max_run_time>` : memetic algorithm

Example: run all the simple iterative improvement algorithm on all instances in the `assets/instances` folder:

```bash
python3 runner.py assets/instances --iter
```

