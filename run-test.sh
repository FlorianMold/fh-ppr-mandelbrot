# Clear directory
rm results-maxiterations-100/*
rm results-maxiterations-500/*
rm results-maxiterations-1000/*

echo "Running tests with 100 max-iterations"
for j in $(seq 1 16);
do
   ./make-test.sh -i 100 -t ${j} -m 100 -f results-maxiterations-100/result-t${j}.txt
done

echo "Running tests with 500 max-iterations"
for j in $(seq 1 16);
do
   ./make-test.sh -i 100 -t ${j} -m 500 -f results-maxiterations-500/result-t${j}.txt
done

echo "Running tests with 1000 max-iterations"
for j in $(seq 1 16);
do
   ./make-test.sh -i 100 -t ${j} -m 1000 -f results-maxiterations-1000/result-t${j}.txt
done