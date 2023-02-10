#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <mpi.h>

using namespace std;

void max_min_avg(double v[], long start, long end, long windowSize, double max, double min, double media) {
    //priority_queue<double> maxqueue;
    //priority_queue<double,vector<double>,greater<double>>minqueue;
    multiset<double> m;
    double sum = 0;
    //cout << start << ' ' << end  << ' ' << windowSize << endl;
    if (end - start + 1 < windowSize) return;

    for (long i = start; i < start + windowSize; i++) {
        m.insert(v[i]);
        sum += v[i];
        //cout << v[i] << endl;
    }
    //cout << *m.begin() << ' ' << *m.rbegin() << endl;

    cout << "Janela: " << start << "-" << start + windowSize - 1 << endl;
    cout << "Media: " << sum / windowSize << "\nMinimo: " << *m.begin() << "\nMaximo: " << *m.rbegin() << "\n\n";

    for (long i = start + windowSize; i < end; i++) {
        m.insert(v[i]);
        multiset<double>::iterator hit(m.find(v[i - windowSize]));
        if (hit != m.end()) m.erase(hit);

        sum += v[i];
        sum -= v[i - windowSize];

        cout << "Janela: " << i - windowSize + 1 << '-' << i << endl;
        cout << "Media: " << sum / windowSize << "\nMinimo: " << *m.begin() << "\nMaximo: " << *m.rbegin() << "\n\n";
    }
}

int main (int argc, char** argv) {

    //cout << argc << '\n';
    if (argc < 3) {
        cerr << "Usage: ./paralelo [arraySize] [windowSize]\n";
        exit (1);
    }
    long arraySize, windowSize;
    arraySize = atol(argv[1]);
    windowSize = atol(argv[2]);
    //cout << arraySize << ' ' << windowSize << '\n';

    MPI_Init(&argc, &argv);

    int num_proc;
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    /*if (rank != 0) {
        cout << ":(\n";
        MPI_Finalize();
        return 0;
    }*/

    double v[arraySize];
    if (rank == 0) { //gerente
        for (long i = 0; i < arraySize; i++)
            cin >> v[i];
    }
        
    MPI_Bcast(v, arraySize, MPI_DOUBLE , 0, MPI_COMM_WORLD);


    /*cout << rank << ": ";
    for (int i = 0; i < arraySize; i++) cout << v[i] << ' ';
    cout << '\n';*/

    double max,min,media;
    long start, end;
    if (rank == 0) {
        max_min_avg(v, 0, arraySize, arraySize, max, min, media);
    }
    else {
        //start = 0;
        /*if (rank == num_proc -1)
            start = (rank - 1) * (arraySize / num_proc) + arraySize % num_proc;
        else*/
        start = (rank - 1) * (arraySize / (num_proc - 1));
        end = (rank - 1) * (arraySize / (num_proc - 1)) + windowSize - 1;
        if (rank == num_proc - 1)
            end = arraySize;

        /*if (rank == 0)
            max_min_avg(v, 0, end / 2 + windowSize - 1, windowSize, max, min, media);
        else
            max_min_avg(v, end / 2, end, windowSize, max, min, media);*/
        max_min_avg(v, start, end, windowSize ,max, min, media);
    }
    MPI_Finalize();
}