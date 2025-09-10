#use 'chmod +x Build.sh' to enable running the file, then run the file by using './Build.sh'

echo "Compiling..."

gcc -O3 -march=native -funroll-loops src/TvMain.c src/AureaKx.c src/Logics.c src/Salting.c src/Shufflers.c src/Solutioners.c -o benchmark -lm

echo "Run: benchmark.exe for windows or ./benchmark for linux/mac"