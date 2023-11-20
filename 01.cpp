#include <iostream>
#include <list>
#include <vector>

void readGraph(int& V, int& E, std::list<int>*& FwdAdjList, std::list<int>*& PrevAdjList) {
    char comma;
    std::cin >> V >> comma >> E;

    FwdAdjList = new std::list<int>[V + 1];
    PrevAdjList = new std::list<int>[V + 1];

    for (int i = 0; i < E; i++) {
        int v1, v2;
        std::cin >> v1 >> v2;
        FwdAdjList[v1].push_front(v2);
        PrevAdjList[v2].push_front(v1);
    }
}

void calculateHistogram(const std::list<int>* FwdAdjList, int V, std::vector<int>& hist) {
    for (int i = 1; i <= V; i++) {
        hist[FwdAdjList[i].size()]++;
    }
}

void printConnections(const std::list<int>* list, int V, const char* title) {
    std::vector<int> histogram(V, 0);

    for (int i = 1; i <= V; i++) {
        int connections = list[i].size();
        histogram[connections]++;
    }

    std::cout << title << "\n";
    for (int i = 0; i < V; i++) 
        std::cout << histogram[i] << "\n";
}

int findCommonFriends(const std::list<int>& list1, const std::list<int>& list2) {
    int friends = 0;
    for (int friend_i : list1) {
        for (int v : list2) {
            if (friend_i == v) {
                friends++;
                break;
            }
        }
    }
    return friends;
}

void printFriendshipMatrix(const std::list<int>* FwdAdjList, int V) {
    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {
            int friends = findCommonFriends(FwdAdjList[i], FwdAdjList[j]);
            std::cout << friends << " ";
        }
        std::cout << "\n";
    }
}


void cleanupMemory(std::list<int>*& FwdAdjList, std::list<int>*& PrevAdjList) {
    delete[] FwdAdjList;
    delete[] PrevAdjList;
}

int main() {
    int V, E;
    std::list<int>* FwdAdjList;
    std::list<int>* PrevAdjList;
    std::vector<int> hist;

    readGraph(V, E, FwdAdjList, PrevAdjList);
    printConnections(FwdAdjList, V, "Histograma 1");
    printConnections(PrevAdjList, V, "Histograma 2");

    hist.resize(V);
    std::fill(hist.begin(), hist.end(), 0);

    calculateHistogram(FwdAdjList, V, hist);
    printFriendshipMatrix(FwdAdjList, V);

    cleanupMemory(FwdAdjList, PrevAdjList);

    return 0;
}
