## collision-bench
A C++ learning laboratory focused on spatial data processing, memory efficiency, and high-throughput performance benchmarking.

### Project Objectives

* **Learning performance driven C++:** Moving beyond the basics to write a fast library.
* **Data-Oriented Design**: Exploring the relationship between the structure of data and its performance. 
* **Performance Testing**: Learning industry-standard tools to compare the difference between standard implementations
and optimized versions that make use of SIMD (Single Instruction, Multiple Data) instruction sets.

### Tools and Dependencies:

* **Linear Algebra:** [Eigen 3.4.0](libeigen.gitlab.io) (Used for SIMD-accelerated vector operations).
* **Testing:** [GoogleTest](https://github.com/google/googletest) (Unit verification).
* **Microbenchmarking:** [Google Benchmark 1.8.3](https://github.com/google/benchmark) (Performance quantification).
* **Build System:** CMake 3.28.3 & Make.
* **Compiler:** GCC 13.3.0 (Required for C++20 support).

note: GoogleTest and Google Benchmark are fetched automatically during build.



### Benchmarking and Verification
**Hardware Specs:**
* **CPU:** i9-12900k
* **RAM:** 128GB
* **OS:** Kubuntu 24.04 LTS

#### **The Test:**
In my initial test, I compared two implementations of an extend function for an Axis-Aligned Bounding Box:
* A naive version, which evaluates a conditional for each coordinate before assigning a value.
```C++
// Logic depends on conditional branching
if (p.x() < min_.x()) min_.x() = p.x();
if (p.x() > max_.x()) max_.x() = p.x();
// ... repeated for Y and Z
```
* An optimized version, which uses a component-wise operation to update the values of the bounding box
```C++
// Logic uses component-wise min/max (branchless)
min_ = min_.cwiseMin(p);
max_ = max_.cwiseMax(p);
```


Modern CPUs use a "pipeline", which attempts to start the next task before the current one is finished.  A conditional 
statement is evaluated in advance by using a process called branch prediction, which estimates what part of the conditional 
will be executed.  If the wrong branch is used, the pipeline is discarded and evaluated with the correct one. The assumption 
of this test is that the optimized version will be deterministic and make use of the wider registers available in SIMD instruction sets.


#### **Results:**
| Input Size |        Optimized (Items/s)        | Naive (Items/s) | Speedup | 
|:----------:|:---------------------------------:|:---------------:|:-------:|
|    1024    |             1.21 G/s              |    665.0 M/s    |  1.82x  |
|    4096    |             1.11 G/s              |    708.8 M/s    |  1.57x  |
|   32768    |             1.11 G/s              |    745.4 M/s    |  1.49x  |
|   262144   |             1.11 G/s              |    762.0 M/s    |  1.48x  |

* Items per second refers to individual Vector3d points processed. G/s is "Billions of items/second" while
M/s is "Millions of items/second".

* The results suggest that by using the component-wise operations in Eigen3, the overall number of items processed can nearly double.
* The peak throughput on the optimized code was ~27.0 GiB/s, which suggests a more effiecient use of resources.  

**Resources:**
* [Branchless Programming in C++ - Fedor Pikus - CppCon 2021](https://youtu.be/g-WPhYREFjk?si=2LQg8H-NOH8SknwZ)
* [Algorithmica - The Cost of Branching](https://en.algorithmica.org/hpc/pipelining/branching/)

### Build Instructions
To build and run the current benchmark:
```shell
git clone https://github.com/ledesma6/collision-bench.git
cd collision-bench
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
./build/aabb_bench