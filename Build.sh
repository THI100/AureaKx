echo "Compiling..."

gcc AureaKx_main.c Internal_dependencies/Logics.c Internal_dependencies/Salting.c Internal_dependencies/Shufflers.c Internal_dependencies/Solutioners.c -o AureaKx_main -lm

echo "Run: AureaKx.exe for windows or ./AureaKx for linux/mac"