# Structured Parallel Pattern framework

SPP is a framework for Structured Parallel Patterns, also known as algorithmic skeletons.
It is currently implemented using just multithreads.

The parallel patterns offered are:
* Fork-join
* Map
* Reduce
* Stencil
* Nesting (paralllel recurrence)
* Future

The parallel patterns can be used as a blocking or non-blocking construction. The non-blocking construction is implemented using the Future pattern. Every parallel pattern offered can be used in a nested construction. In order to keep the framework simple, determinism must be assured by the programmer.

### Motivation

The main purpose of this framework is to offer the maximum number of structured parallel patterns as possible, while still allowing for nesting constructions. It is very important to keep the framework general, flexible and easy to use. It is also my intention to support for hybrid (and distributed) architectures.

### References

[1] Cole, Murray I. Algorithmic skeletons: structured management of parallel computation. London: Pitman, 1989.

[2] McCool, Michael D. "Structured parallel programming with deterministic patterns." Proceedings of the 2nd USENIX conference on Hot topics in parallelism. USENIX Association, 2010.

[3] McCool, Michael, James Reinders, and Arch Robison. Structured parallel programming: patterns for efficient computation. Elsevier, 2012.
