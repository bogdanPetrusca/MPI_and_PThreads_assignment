build:
	mpic++ main.cpp -o main
run:
	mpirun -np 5 -oversubscribe main text.in
clean:
	rm main