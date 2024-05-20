set -e
c++-11 main.cpp -o main
c++-11 gen.cpp -o gen
c++-11 brute.cpp -o brute
for((i = 1; ; ++i)); do
    ./gen $i > input
    ./main < input > out
    ./brute < input > ans
    diff out ans > /dev/null || break
    echo "AC: "  $i
done
echo "WA:"
cat input
echo "Out:"
cat out
echo "Ans:"
cat ans