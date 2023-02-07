#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

void max_min_avg(vector<double> v, long start, long end, long windowSize, double max, double min, double media) {
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

    //cout << "Janela: " << start << "-" << start + windowSize - 1 << endl;
    //cout << "Media: " << sum / windowSize << "\nMinimo: " << *m.begin() << "\nMaximo: " << *m.rbegin() << "\n\n";

    for (long i = start + windowSize; i < end; i++) {
        m.insert(v[i]);
        multiset<double>::iterator hit(m.find(v[i - windowSize]));
        if (hit != m.end()) m.erase(hit);

        sum += v[i];
        sum -= v[i - windowSize];

        //cout << "Janela: " << i - windowSize + 1 << '-' << i << endl;
        //cout << "Media: " << sum / windowSize << "\nMinimo: " << *m.begin() << "\nMaximo: " << *m.rbegin() << "\n\n";
    }
}

int main () {
    long arraySize, windowSize;
    cin >> arraySize >> windowSize;
    vector<double> v(arraySize);
    for (long i = 0; i < arraySize; i++)
        cin >> v[i];
    double max,min,media;
    long start, end;
    start = 0;
    end = v.size();
    max_min_avg(v, 0, end / 2 + windowSize - 1, windowSize, max, min, media);
    max_min_avg(v, end / 2, end, windowSize, max, min, media);
    //max_min_avg(v, start, end, windowSize ,max, min, media);
    
}