[![Build Status](https://travis-ci.org/mariobarbareschi/phemap.svg?branch=master)](https://travis-ci.org/mariobarbareschi/phemap)
# PHEMAP
The repository contains a demonstrator of the Physical Hardware-Enabled Mutual Authentication Protocol (PHEMAP)

## Getting started
Once you've cloned the repository, just use cmake to configure the compilation environment

    mkdir build
    cd build
    cmake ..

Then, run the compilation by using make
    make
    
## How it works
PHEMAP is based on the usage of a strong PUF circuit and on a novel enrollment procedure, which takes place by self-iterating the PUF itself.
An exaustive description of the protocol is available on the [Journal of Parallel and Distributed Computing, Elsevier, Volume 119](https://www.sciencedirect.com/science/article/pii/S0743731518302582).

## Documentation
As soon as possible, a doxygen implementation will be available for the whole project
    
# License
This software is part of a scientific work. It is released under the [GNU Affero General Public License](https://www.gnu.org/licenses/agpl-3.0.html). Please read a copy of that license before use the software.
Moreover, before using it or divulging, I kindly ask you to contact me.

## Citations
In case you make usage of PHEMAP and need to cite our work, please refers to the following paper:
```bibtex
@article{barbareschi2018puf,
  title={A PUF-based hardware mutual authentication protocol},
  author={Barbareschi, Mario and De Benedictis, Alessandra and Mazzocca, Nicola},
  journal={Journal of Parallel and Distributed Computing},
  volume={119},
  pages={107--120},
  year={2018},
  publisher={Elsevier}
}

# PHEMAP
