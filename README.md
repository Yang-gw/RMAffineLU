# 基于LU矩阵分解的Reed-Muller码商空间下仿射等价算法

本仓库实现了一个算法，用于判断Reed-Muller码在商空间下的仿射等价性。该算法通过LU矩阵分解来高效判断Reed-Muller码的仿射等价性，相比于传统方法，具有更高的计算效率，减少了计算复杂度。

## 主要特点

- **LU矩阵分解**：算法的核心是LU矩阵分解，通过将仿射变换矩阵分解为上三角和下三角矩阵，从而简化了仿射变换搜索的复杂度。
- **优化**：算法采用了搜索空间剪枝和位操作技术，进一步提升了运行效率。
- **与现有方法比较**：实验结果表明，本算法相比传统的PDR方法，在寻找解决方案时所需的变换步骤显著减少，具有更高的计算效率。

## 环境要求

- 支持C++11及以上的编译器
- 必要的库：
  - `<bits/stdc++.h>`：用于标准操作

## 文件

- `algorithm.cpp`: C++实现代码文件，包含主要算法实现。
- `input.txt` 和 `output.txt`: 用于输入和输出的数据文件（如果有）。

## 使用方法

1. 克隆本仓库。
2. 编译 `algorithm.cpp` 文件。
3. 输入Reed-Muller码，运行算法进行仿射等价性判定。
4. 查看输出结果。

------

### **README.md (English)**

# Affine Equivalence Algorithm for Reed-Muller Codes in Quotient Spaces Based on LU Matrix Decomposition

This repository implements an algorithm for determining the affine equivalence of Reed-Muller codes in quotient spaces. The algorithm uses LU matrix decomposition to efficiently check affine equivalence, outperforming traditional methods by reducing computational complexity.

## Key Features

- **LU Matrix Decomposition**: The core of the algorithm is LU matrix decomposition, which simplifies the affine transformation search by decomposing the transformation matrix into upper and lower triangular matrices.
- **Optimization**: The algorithm employs pruning of the search space and bit-level operations to further improve computational efficiency.
- **Comparison with Existing Methods**: Experimental results show that the algorithm outperforms traditional methods such as PDR, requiring fewer transformation steps to reach a solution.

## Prerequisites

- C++ compiler with support for C++11 or later
- Required libraries:
  - `<bits/stdc++.h>` for standard operations

## Files

- `algorithm.cpp`: C++ source file containing the main algorithm implementation.
- `input.txt` and `output.txt`: Input and output data files (if applicable).

## Usage

1. Clone this repository.
2. Compile the `algorithm.cpp` file.
3. Input the Reed-Muller codes and run the algorithm to check affine equivalence.
4. View the output results.
