## Robust Plane Cut Library for 2-Manifold Meshes

This library is used for quick and robust plane cutting a 2-manifold mesh.

You should install [CGAL](https://github.com/CGAL/cgal) before compiling this project.

# Usage

- Clone this repository:

        git clone https://github.com/chenming-wu/robust-plane-cut.git

- Compiling.

        mkdir build
        cd build
        cmake ..
        make

- Run `robust-plane-cut`

- How to compare our library with CGAL: Simply change the applied template in function `cut_and_fill` from `FillHoleCDT` to `FillHoleCGAL`.


# Citation
If you use this code for your research, please cite our work:

```
@article{wu2019general,
  title={General Support-Effective Decomposition for Multi-Directional 3-D Printing},
  author={Wu, Chenming and Dai, Chengkai and Fang, Guoxin and Liu, Yong-Jin and Wang, Charlie CL},
  journal={IEEE Transactions on Automation Science and Engineering},
  year={2019},
  publisher={IEEE}
}

@inproceedings{wu2017robofdm,
  title={RoboFDM: A robotic system for support-free fabrication using FDM},
  author={Wu, Chenming and Dai, Chengkai and Fang, Guoxin and Liu, Yong-Jin and Wang, Charlie CL},
  booktitle={2017 IEEE International Conference on Robotics and Automation (ICRA)},
  pages={1175--1180},
  year={2017},
  organization={IEEE}
}
```

# License
All rights about the program are reserved by the authors of this project. The programs can only be used for research purpose. In no event shall the author be liable to any party for direct, indirect, special, incidental, or consequential damage arising out of the use of this program.
        
