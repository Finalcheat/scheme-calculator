scheme-calculator
=======
A simple implementation of scheme calculator

## build
cd src && mkdir build && cd build && make

## example
```
./scheme-calculator
Welcome to scheme-calculator
> (+ 1 2)
3
> (* (+ 1 2) (- 4 3) (/ 10 5))
6
> (+ 1 (+ 2 3 (+ 4 (+ 5 6 (+ 7 8 9)))) 10)
55
```