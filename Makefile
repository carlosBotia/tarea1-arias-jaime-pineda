sobel: sobel.cpp Image.h Image.cpp
	g++ -o sobel sobel.cpp Image.cpp -lrt -pthread 

run:
	./sobel

.PHONY : clean
clean:
	rm -rf sobel 
