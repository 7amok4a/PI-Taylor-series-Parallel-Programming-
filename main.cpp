// Author: 7amok4a
// Return Dark ^_^ &_&
#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;


//  model : 
double getTerm(int n) {
    double term = 1.0 / ((2.0 * n) + 1.0);
    return (n % 2 == 0) ? term : -term;
}

int main(int argc, char *argv[]) {
    const double PI = 3.141592653589793238462643; // test 
    int rank = 0, size = 0, term = 0;
    double sum = 0.0, total = 0.0, propPi = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    // cout << "Size " << size << "\n" ; 
    if (rank == 0) {
        cout << "Enter the number of intervals: ";
        cin >> term;
    }


    MPI_Bcast(&term, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (term == 0) {
        MPI_Finalize();
        return 0; 
    }

    for (int i = rank; i < term; i += size) {   
      //  cout << "rank " << rank << "\n" ; 
        sum += getTerm(i);
    }

    cout << "Process Rank: " << rank << " Sum: " << sum << "\n";


    MPI_Reduce(&sum, &total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);


    if (rank == 0) {
        propPi = 4 * total;
        cout << "pi is approximately " << propPi << "\n"
             << "Error is " << abs(propPi - PI) << "\n";
    }

 
    MPI_Finalize();
    return 0;
}
