#include <iostream>
#include <fstream>
#include <string>

long long generateHash(int prime, int root, int data_size, std::string data) {

    long long mem = 0;
    for (int k = 0; k < data_size - 1; k++) {
        mem += int(data[k]) % prime;
        mem %= prime;
        mem *= root;
        mem %= prime;
    }
    mem += int(data[data_size - 1]);
    mem += prime;
    mem %= prime;

    return mem;
}

int main()
{
    int sym = 256;
    int prime = 151;
    int root = sym % prime;

    int c;
    std::cin >> c;

    for (int i = 0; i < c; i++) {

        char in[100];
        std::cin >> in;

        std::string data;
        std::cin >> data;

        std::ifstream infile(in);

        int data_size = data.length();

        std::string buff;
        buff.assign(std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>());

        infile.clear();

        int file_size = buff.length();

        long long mem = generateHash(prime, root, data_size, data);

        long long sum = generateHash(prime, root, data_size, buff.substr(0, data_size));

        for (int i = 0; i <= file_size - data_size; i++) {

            if (sum == mem) {

                int flag = buff.substr(i, data_size).compare(data);
                if (flag == 0) {
                    std::cout << i << " ";
                }
            }

            long long sha = int(buff[i]) % prime;

            long long s = root;
            for (int k = 0; k < data_size - 2; k++)
                s = (s * root) % prime;
            sum -= (sha * s) % prime;

            if (sum <= 0)
                sum = (sum + prime) % prime;

            //
            sum = (sum * root) % prime;

            sum = (sum + int(buff[i + data_size])) % prime;
        }
        std::cout << "\n";
    }
    

    return 0;
}