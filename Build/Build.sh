#use 'chmod +x Build.sh' to enable running the file.

echo "Compiling..."
gcc -O3 -march=native -funroll-loops src/AureaKx.c src/Salting.c src/Solutioners.c -o AureaKx -lm
echo "Run: AureaKx.exe for windows or ./AureaKx for linux/mac"