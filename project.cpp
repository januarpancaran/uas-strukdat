#include <iostream>
#include <climits>
#include <vector>
#include <set>
#define OUT(x) std::cout << x << std::endl
using namespace std;

const string username = "admin";
const string password = "atminsudahdatang";

const int N = 5;
const string Vertex[N] = {"Gudang 1", "Gudang 2", "Gudang 3", "Gudang 4", "Gudang 5"}; 
const int Edge[N][N] = {
    {0, 150, 0, 90, 0},
    {0, 0, 60, 40, 0},
    {0, 0, 0, 0, 180},
    {0, 90, 200, 0, 30},
    {70, 0, 60, 0, 0},
};

const int INF = INT_MAX;

struct Graph {
    string V[N];
    int E[N][N];
};

struct Baju {
    string namaBaju;
    int nomorRak;
    Baju* next = nullptr;
};

struct LinkedList {
    // * Initialize Head and Tail
    Baju* head = nullptr;
    Baju* tail = nullptr;
    
    // * Add Node to LinkedList
    void add(const Baju& newBaju) {
        Baju* temp = new Baju();
        *temp = newBaju;
        temp -> next = nullptr;

        if(head == nullptr) {
            head = temp;
            tail = temp;
        } else {
            tail -> next = temp;
            tail = temp;
        }
    }

    // * Print/Show Nodes in LinkedList
    void print() {
        if(head == nullptr) {
            OUT("Belum ada baju yang ditambahkan");
            return;
        } else {
            Baju* temp = head;
            int urutan = 1;
            OUT("Daftar Baju: \n");
            while(temp != nullptr) {
                OUT(urutan << ".");
                OUT("Nama Baju: " << temp -> namaBaju);
                OUT("Nomor Rak: " << temp -> nomorRak);
                cout << "\n";
                urutan++;
                temp = temp -> next;
            }
        }
    }

    void edit(string editBaju, const Baju& newBaju) {
        Baju* temp = head;
        bool found = false;
        while(temp != nullptr) {
            if(temp -> namaBaju == editBaju) {
                temp -> namaBaju = newBaju.namaBaju;
                temp -> nomorRak = newBaju.nomorRak;
                OUT("\nData baju berhasil di edit\n");
                found = true;
            }
            temp = temp -> next;
        }

        if(!found) {
            OUT("\nBaju dengan nama " << editBaju << " tidak ditemukan");
            return;
        }
    }

    void del(string delBaju) {
        Baju* cur = head;
        Baju* prev = nullptr;
        bool found = false;
        
        while(cur != nullptr) {
            if(cur -> namaBaju == delBaju) {
              if(prev == nullptr) {
                head = cur -> next;
              } else {
                prev -> next = cur -> next;
              }
              delete cur;
              found = true;
              OUT("\n" << delBaju << " telah dihapus dari list");
              return;
            } else {
                prev = cur;
                cur = cur -> next;
            }
        }

        if(!found) {
            OUT("\nBaju dengan nama " << delBaju << " tidak ditemukan");
            return;
        }
    }

    void swap(Baju* a, Baju* b) {
        string tempNama = a -> namaBaju;
        a -> namaBaju = b -> namaBaju;
        b -> namaBaju = tempNama;

        int tempRak = a -> nomorRak;
        a -> nomorRak = b -> nomorRak;
        b -> nomorRak = tempRak;
    }

    Baju* findLast(Baju* head) {
        while(head != nullptr && head -> next != nullptr) {
            head = head -> next;
        }
        return head;
    }

    Baju* partition(Baju* head, Baju* tail, bool sortByName, bool ascending) {
        Baju* pivot = tail;
        Baju* i = head;
        Baju* j = head;

        while (j != tail) {
            if(sortByName) {
                if((ascending && j -> namaBaju.compare(pivot -> namaBaju) < 0) || (!ascending && j -> namaBaju.compare(pivot -> namaBaju) > 0)) {
                    swap(i, j);
                    i = i -> next;
                }
            } else {
                if((ascending && j -> nomorRak < pivot -> nomorRak) || (!ascending && j -> nomorRak > pivot -> nomorRak)) {
                    swap(i, j);
                    i = i -> next;
                }
            }
            j = j -> next;
        }
        swap(i, tail);
        return i;
    }

    void quickSort(Baju* l, Baju* r, bool sortByName, bool ascending) {
        if(l != r && l != nullptr && r != nullptr && l != r -> next) {
            Baju* p = partition(l, r, sortByName, ascending);

            if(p != nullptr && p != l) {
                Baju* temp = l;
                while(temp -> next != p) {
                    temp = temp->next;
                }
                quickSort(l, temp, sortByName, ascending);
            }

            if(p != nullptr && p -> next != r) {
                quickSort(p -> next, r, sortByName, ascending);
            }
        }
    }

    Baju* findNthNode(Baju* head, int n) {
        Baju* temp = head;
        for (int i = 0; i < n; i++) {
            if (temp == nullptr) {
                return nullptr;
            }
            temp = temp -> next;
        }
        return temp;
    }

    Baju* binarySearch(Baju* head, string target, bool sortByName, bool ascending) {
        Baju* temp = head;
        int left = 0;
        int right = 0;

        while(temp != nullptr) {
            right = left + 1;
            left = left;
            temp = temp->next;
        }

        while(left <= right) {
            int mid = left + (right - left) / 2;
            Baju* midNode = findNthNode(head, mid);

            if(sortByName) {
                if (ascending && target.compare(midNode -> namaBaju) < 0) {
                    left = mid + 1;
                } else if (!ascending && target.compare(midNode -> namaBaju) > 0) {
                    left = mid + 1;
                } else {
                    return midNode;
                }
            }
        }

        return nullptr;
    }

    // ! Delete Nodes in LinkedList Afterwards to Avoid Memory Leak
    ~LinkedList() {
        Baju* temp = head;
        while (temp != nullptr) {
            Baju* next = temp -> next;
            delete temp;
            temp = next;
        }
    }
};

void Jalur(Graph G) {
    int i, j;
    cout << "\nDaftar Jalur yang Tersedia: " << endl;
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            if(G.E[i][j] > 0) {
                cout << "(" << G.V[i] << ", " << G.V[j] << ") = " << G.E[i][j] << " KM" << endl;
            }
        }
    }
}

void DataGraph(Graph *G) {
    int i, j;
    for(i = 0; i < N; i++) {
        G -> V[i] = Vertex[i];
    }

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            G -> E[i][j] = Edge[i][j];
        }
    }
}

int FindClosestVertex(const vector<int>& P, const set<int>& done) {
    int minDistance = INF;
    int closestVertex = -1;

    for(int i = 0; i < P.size(); i++) {
        if(done.find(i) == done.end() && P[i] < minDistance) {
            minDistance = P[i];
            closestVertex = i;
        }
    }
    return closestVertex;
}

void Dijkstra(Graph G, int source, int destination) {
    int V = N;
    vector<int> P(V, INF); // Jarak terpendek dari source ke setiap vertex
    vector<vector<int>> paths(V); // Jalur terpendek dari source ke setiap vertex
    set<int> done;

    P[source] = 0;
    done.insert(source);

    for (int i = 0; i < V; ++i) {
        if (i != source && G.E[source][i] != 0) {
            P[i] = G.E[source][i];
            paths[i].push_back(source); // Vertex 'source' adalah titik awal jalur terpendek ke 'i'
            paths[i].push_back(i);
        }
    }

    for (int count = 1; count < V; ++count) {
        int closest = FindClosestVertex(P, done);
        if (closest == -1 || closest == destination) break;
        done.insert(closest);

        for (int j = 0; j < V; ++j) {
            if (done.find(j) == done.end() && G.E[closest][j] != 0) {
                if (P[closest] + G.E[closest][j] < P[j]) {
                    P[j] = P[closest] + G.E[closest][j];
                    paths[j] = paths[closest]; // Jalur terpendek ke 'j' adalah jalur terpendek ke 'closest' diikuti dengan 'j'
                    paths[j].push_back(j);
                }
            }
        }
    }

    // Tampilkan hasil
    cout << "\nJarak terpendek dari " << G.V[source] << " ke " << G.V[destination] << " adalah " << (P[destination] == INF ? -1 : P[destination]) << " KM" << endl;
    if (P[destination] != INF) {
        cout << "Jalur yang dilalui: ";
        for (int i = 0; i < paths[destination].size(); ++i) {
            cout << G.V[paths[destination][i]];
            if (i != paths[destination].size() - 1) cout << " -> ";
        }
        cout << endl;
    }
}


void menu() {
    string menuList[] = {
        "1. List Baju", 
        "2. Tambah Baju",
        "3. Edit Baju",
        "4. Hapus Baju",
        "5. Urutkan Baju", 
        "6. Cari Baju", 
        "7. Rute Terpendek Antar Gudang", 
        "8. Exit"
    };

    int menuSize = sizeof(menuList) / sizeof(menuList[0]); 

    for(int i = 0; i < menuSize; i++) {
        OUT(menuList[i]);
    }
}

void backToMenu(char back) {
    OUT("Ketik 'q' untuk kembali ke menu");
    do {
        cin >> back;

        if(cin.fail())
            cin.clear();

    } while(back != 'q');
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else 
        system("clear");
    #endif
}

int main() {
    // ! Add Nodes
    LinkedList list;
    list.add({"Kemeja", 23});
    list.add({"Batik", 15});
    list.add({"Seragam SMA", 45});

    string authName, authPass;
    bool showMenu = true, isAuth = false;
    int chooseMenu;
    char back;

    string newBaju, editBaju, deleteBaju, cariBaju;
    int newRak;

    // * Show Menu
    while(showMenu) {
        clear_screen();
        OUT("Log In");
        cout << "Username: ";
        cin >> authName;
        cout << "Password: ";
        cin >> authPass;

        // * Check Username and Password
        if(authName == username && authPass == password) {
            isAuth = true;
            
            // ! Initialize Loop
            while(isAuth) {
                clear_screen(); 
                OUT("\nAplikasi Distributor Baju: ");
                menu();
                cout << "\nPilih Menu: ";
                cin >> chooseMenu;
                cout << "\n";

                switch(chooseMenu) {
                    case 1:
                        clear_screen(); 
                        list.print();
                        
                        backToMenu(back);

                        break;
                    
                    case 2:
                        clear_screen();
                        OUT("Masukkan Data Baju Baru \n");
                        cout << "Masukkan Nama Baju: ";
                        cin.ignore();
                        getline(cin, newBaju);
                        cout << "Masukkan Rak Baju: ";
                        cin >> newRak;

                        list.add({newBaju, newRak});
                        cout << endl;

                        backToMenu(back);
                        
                        break;
                    
                    case 3:
                        clear_screen();   
                        list.print();
                        
                        cout << "Masukkan Nama Baju yang Ingin Diedit: ";
                        cin.ignore();
                        getline(cin, editBaju);
                        cout << endl;

                        cout << "Masukkan Nama Baju Baru: ";
                        getline(cin, newBaju);
                        cout << "Masukkan Nomor Rak Baru: ";
                        cin >> newRak;

                        list.edit(editBaju, {newBaju, newRak});
                        
                        backToMenu(back);
                        
                        break;

                    case 4:
                        clear_screen(); 
                        list.print();

                        cout << "Masukkan Nama Baju yang Ingin Dihapus: ";
                        cin.ignore();
                        getline(cin, deleteBaju);
                        list.del(deleteBaju);
                        cout << endl;

                        backToMenu(back);

                        break;

                    case 5:
                        int pilihSort;
                        int hurufSort;
                        int rakSort;

                        clear_screen();
                        OUT("1. Urutkan Berdasarkan Huruf");
                        OUT("2. Urutkan Berdasarkan Nomor Rak");
                        cout << "\nPilih Sort: ";
                        cin >> pilihSort;

                        if(pilihSort == 1) {
                            clear_screen();
                            OUT("1. A-Z");
                            OUT("2. Z-A");
                            cout << "\nPilih Sort: ";
                            cin >> hurufSort;

                            clear_screen();      
                            if(hurufSort == 1) {
                                list.quickSort(list.head, list.findLast(list.head), true, true);
                                list.print();
                            } else if(hurufSort == 2) {
                                list.quickSort(list.head, list.findLast(list.head), true, false);
                                list.print();
                            } else {
                                OUT("Pilihan tidak tersedia\n");
                            }
                        } else if(pilihSort == 2) {
                            clear_screen();
                            OUT("1. Nomor rak terkecil");
                            OUT("2. Nomor rak terbesar");

                            cout << "\nPilih Sort: ";
                            cin >> rakSort;

                            clear_screen();
                            if(rakSort == 1) {
                                list.quickSort(list.head, list.findLast(list.head), false, true);
                                list.print();
                            } else if(rakSort == 2) {
                                list.quickSort(list.head, list.findLast(list.head), false, false);
                                list.print();
                            } else {
                                OUT("Pilihan tidak tersedia\n");
                            }
                        } else {
                            OUT("Pilihan tidak tersedia\n");
                        }

                        backToMenu(back);

                        break;

                    case 6: {
                        clear_screen();
                        list.quickSort(list.head, list.findLast(list.head), true, true);
                        list.print();

                        cout << "Masukkan Nama Baju yang Ingin Dicari: ";
                        cin.ignore();
                        getline(cin, cariBaju);

                        Baju* foundNode = list.binarySearch(list.head, cariBaju, true, true);
                        if(foundNode != nullptr) {
                            Baju* temp = list.head;
                            int urutan = 1;
                            while (temp != nullptr) {
                                if (temp -> namaBaju == cariBaju) {
                                    clear_screen();   
                                    OUT(cariBaju << " ditemukan di urutan ke-" << urutan << "\n");
                                    OUT("Nama Baju: " << temp -> namaBaju);
                                    OUT("Nomor Rak: " << temp -> nomorRak);
                                    cout << endl;
                                }
                                temp = temp -> next;
                                urutan++;
                            }
                        } else {
                            OUT(cariBaju << " tidak ditemukan! \n");
                        }

                        backToMenu(back);

                        break;
                    }

                    case 7: {
                        clear_screen();
                        Graph G;
                        DataGraph(&G);
                        Jalur(G);
                        cout << endl;

                        int source, destination, urutan;
                        
                        for(int i = 0; i < N; i++) {
                            urutan = i + 1;
                            OUT(urutan << ". " << Vertex[i]);
                        }
                        cout << endl;
                        cout << "Masukkan Nomor Vertex Asal: ";
                        cin >> source;
                        source--;

                        cout << "Masukkan Nomor Vertex Tujuan: ";
                        cin >> destination;
                        destination--;

                        if(source >= 0 && source < N && destination >= 0 && destination < N) 
                            Dijkstra(G, source, destination);
                        else 
                            OUT("\nPilihan Gudang Tidak Valid");
                        cout << endl;

                        backToMenu(back);

                        break;
                    }

                    case 8:
                        isAuth = false; // ! Change isAuth to false
                        break;
                    default:
                        OUT("Pilihan tidak tersedia \n");

                        backToMenu(back);

                        break;
                }
            }
            // ! Stop the Loop
            showMenu = false;
        } else {
            OUT("\nUsername atau Password salah\n");

            backToMenu(back);
        }
    }
    return 0;
}