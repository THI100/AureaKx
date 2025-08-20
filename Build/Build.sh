echo "Compiling..."

gcc -O3 -march=native -funroll-loops src/AureaKx.c src/Logics.c src/Salting.c src/Shufflers.c src/Solutioners.c -o AureaKx -lm

echo "Run: AureaKx.exe for windows or ./AureaKx for linux/mac"