# Введение в MPI. Операции с массивами. Пузырьковая сортировка
# Task 1
## Описание

Программа `task1_1.c` выполняет:

- инициализацию массива случайными числами;
- подсчёт суммы элементов;
- измерение времени выполнения.

Принимает один аргумент командной строки — размер массива.

---

## Компиляция и выполнение последовательного варианта
```bash
#!/bin/bash
#BSUB -J task1_1                   # Название задания
#BSUB -n 1                         # Количество CPU (1 ядро)
#BSUB -W 00:05                     # Лимит времени (часы:минуты)
#BSUB -R "rusage[mem=256]"         # Запрос 256 МБ оперативной памяти
#BSUB -o output.%J.txt             # Стандартный вывод (%J — ID задания)
#BSUB -e error.%J.txt              # Стандартный поток ошибок

# Загрузка модуля компилятора, если используется модульная система
# module load gcc

# Компиляция программы
gcc -O2 -o task1_1 task1_1.c

# Запуск программы с аргументом (размер массива)
./task1_1 10000000
```

## Компиляция и выполнение параллельного варианта
```bash
#!/bin/bash
#BSUB -J task1_2_mpi
#BSUB -n 8                     # максимум нужных процессов
#BSUB -W 00:05
#BSUB -R "rusage[mem=512]"
#BSUB -o output.%J.txt
#BSUB -e error.%J.txt

# Загрузка модуля (если используется)
# module load mpi
module load mpi/openmpi-x86_64

# Компиляция
mpicc -O2 -o task1_2 task1_2.c

# Запуск с 2 процессами
echo "RUNNING WITH 2 PROCESSES :"
mpirun -np 2 ./task1_2

# Запуск с 4 процессами
echo "RUNNING WITH 4 PROCESSES :"
mpirun -np 4 ./task1_2

# Запуск с 8 процессами
echo "RUNNING WITH 8 PROCESSES :"
mpirun -np 8 ./task1_2

```
# Пузырьковая сортировка массива (Bubble Sort) — Task 2

## Описание

Программа `task2_1.c` — последовательная версия пузырьковой сортировки массива.

Программа `task2_2.c` — параллельная версия пузырьковой сортировки с использованием MPI.

Входные данные: размер массива (через аргумент командной строки или файл `input.txt`).

---

## Компиляция и выполнение последовательного варианта (task2_1.c)

```bash
#!/bin/bash
#BSUB -J task2_1_seq                # Название задания
#BSUB -n 1                         # Один процессор
#BSUB -W 00:10                    # Время 10 минут
#BSUB -R "rusage[mem=1024]"       # Память 1 ГБ
#BSUB -o output.%J.txt
#BSUB -e error.%J.txt

# module load gcc                 # При необходимости загрузить модуль

gcc -O2 -o task2_1 task2_1.c       # Компиляция последовательной версии

./task2_1                         # Запуск программы
```
## Компиляция и выполнение параллельного варианта (task2_2.c)

```bash
#!/bin/bash
#BSUB -J task2_2_mpi               # Название задания
#BSUB -n 8                         # Количество MPI процессов (8)
#BSUB -W 00:10                    # Время 10 минут
#BSUB -R "rusage[mem=2048]"       # Память 2 ГБ
#BSUB -o output.%J.txt
#BSUB -e error.%J.txt

# module load mpi                 # Загрузка MPI модуля, если есть
module load mpi/openmpi-x86_64

mpicc -O2 -o task2_2 task2_2.c     # Компиляция параллельной версии

echo "RUNNING WITH 2 PROCESSES:"
mpirun -np 2 ./task2_2

echo "RUNNING WITH 4 PROCESSES:"
mpirun -np 4 ./task2_2

echo "RUNNING WITH 8 PROCESSES:"
mpirun -np 8 ./task2_2
```
# Task 3
## Описание
Данная программа реализует параллельные операции сложения, вычитания, умножения и деления элементов двух массивов с использованием MPI. Массивы разбиваются на равные части, которые распределяются между процессами, каждый из которых выполняет операции на своей части, после чего результаты собираются обратно.

## Компиляция и выполнение параллельного варианта
```bash

#!/bin/bash
#BSUB -J task3_2_job
#BSUB -n 8
#BSUB -W 00:10
#BSUB -o output.%J.txt
#BSUB -e error.%J.txt

module load mpi/openmpi-x86_64 

ARRAY_SIZE=100000
EXEC=./task3_2

mpirun -np 8 $EXEC $ARRAY_SIZE

```

# Task 4
## Описание
Программа выполняет параллельную сортировку массива с использованием MPI и стандартной функции qsort:
Данные распределяются между процессами (MPI_Scatter);
Программа принимает один аргумент командной строки — размер массива.
## Компиляция и выполнение (последовательная версия)
```bash
#!/bin/bash
#BSUB -J task4_1
#BSUB -n 1
#BSUB -W 00:05
#BSUB -R "rusage[mem=1024]"
#BSUB -o output.%J.txt
#BSUB -e error.%J.txt

gcc -O2 -o task4_1 task4_1.c

./matrix_ops
```
## Компиляция и выполнение (MPI версия)
```bash
#!/bin/bash
#BSUB -J task4_2
#BSUB -W 00:10
#BSUB -o output.%J.log
#BSUB -e error.%J.log

module load mpi/openmpi-x86_64

EXEC=./task4_2
ARRAY_SIZE=100000

echo "Running with 2 processes"
mpirun -np 2 $EXEC $ARRAY_SIZE

echo "Running with 4 processes"
mpirun -np 4 $EXEC $ARRAY_SIZE

echo "Running with 8 processes"
mpirun -np 8 $EXEC $ARRAY_SIZE
```