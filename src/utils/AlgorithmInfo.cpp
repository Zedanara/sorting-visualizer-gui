#include "sv/utils/AlgorithmInfo.hpp"

namespace sv::utils {

    AlgoDetails AlgorithmInfo::getDetails(const std::string& algoName, sv::core::Language lang) {
        AlgoDetails details;

        if (algoName == "Bubble Sort") {
            if (lang == sv::core::Language::PL) {
                details.description = "Prosty algorytm sortowania, ktory wielokrotnie przechodzi przez liste, porownuje sasiadujace elementy i zamienia je, jesli sa w niewlasciwej kolejnosci.";
                details.bestCase = "O(n) - gdy tablica jest juz posortowana.";
                details.averageCase = "O(n^2)";
                details.worstCase = "O(n^2) - tablica posortowana odwrotnie.";
                details.pros = "Prosty w implementacji, nie wymaga dodatkowej pamieci (in-place).";
                details.cons = "Bardzo wolny dla duzych zbiorow danych.";
                details.useCases = "Wylacznie edukacyjne, sporadycznie do malych zbiorow.";
                details.stepByStepExample = "Dla tablicy: [5, 4, 3, 1]\n"
                                            "Krok 1: 5 > 4 (zamiana) -> [4, 5, 3, 1]\n"
                                            "Krok 2: 5 > 3 (zamiana) -> [4, 3, 5, 1]\n"
                                            "Krok 3: 5 > 1 (zamiana) -> [4, 3, 1, 5]\n"
                                            "Najwiekszy element (5) wybombelkowal na koniec. Powtarzamy proces dla reszty.";
            } else {
                details.description = "A simple sorting algorithm that repeatedly steps through the list, compares adjacent elements and swaps them if they are in the wrong order.";
                details.bestCase = "O(n) - when array is already sorted.";
                details.averageCase = "O(n^2)";
                details.worstCase = "O(n^2) - reverse sorted array.";
                details.pros = "Simple to implement, in-place sorting.";
                details.cons = "Very slow for large datasets.";
                details.useCases = "Educational purposes only.";
                details.stepByStepExample = "Array: [5, 4, 3, 1]\nStep 1: 5 > 4 (swap) -> [4, 5, 3, 1]\nStep 2: 5 > 3 (swap) -> [4, 3, 5, 1]\nStep 3: 5 > 1 (swap) -> [4, 3, 1, 5]\nThe largest element (5) bubbled up. Repeat for the rest.";
            }
            details.cppCode = "void bubbleSort(std::vector<int>& arr) {\n"
                              "    int n = arr.size();\n"
                              "    for (int i = 0; i < n - 1; i++) {\n"
                              "        bool swapped = false;\n"
                              "        for (int j = 0; j < n - i - 1; j++) {\n"
                              "            if (arr[j] > arr[j + 1]) {\n"
                              "                std::swap(arr[j], arr[j + 1]);\n"
                              "                swapped = true;\n"
                              "            }\n"
                              "        }\n"
                              "        if (!swapped) break; // Optymalizacja\n"
                              "    }\n"
                              "}";
        }
        else if (algoName == "Insertion Sort") {
            if (lang == sv::core::Language::PL) {
                details.description = "Buduje posortowana tablice element po elemencie. Pobiera kolejny element i wstawia go w odpowiednie miejsce wsrod juz posortowanych.";
                details.bestCase = "O(n) - tablica posortowana.";
                details.averageCase = "O(n^2)";
                details.worstCase = "O(n^2) - tablica odwrotnie posortowana.";
                details.pros = "Szybki dla malych zbiorow oraz tablic prawie posortowanych. Dziala in-place.";
                details.cons = "Wolny dla duzych, losowych danych.";
                details.useCases = "Czesto uzywany jako algorytm wspomagajacy w zaawansowanych sortowaniach (np. Timsort, std::sort) dla malych paczek danych (n < 16).";
                details.stepByStepExample = "Dla tablicy: [5, 4, 3, 1]\n"
                                            "Bierzemy 4: [5, 4, ...] -> 4 < 5, przesuwamy 5 -> [4, 5, 3, 1]\n"
                                            "Bierzemy 3: [4, 5, 3, ...] -> 3 < 5, 3 < 4 -> [3, 4, 5, 1]\n"
                                            "Bierzemy 1: [3, 4, 5, 1] -> wstawiamy na poczatek -> [1, 3, 4, 5]";
            } else {
                details.description = "Builds the final sorted array one item at a time. It takes an element and inserts it into its correct position.";
                details.bestCase = "O(n) - array already sorted.";
                details.averageCase = "O(n^2)";
                details.worstCase = "O(n^2) - reverse sorted array.";
                details.pros = "Fast for small arrays and nearly sorted data. In-place.";
                details.cons = "Slow for large data.";
                details.useCases = "Often used as a fallback for small arrays in complex algorithms like std::sort.";
                details.stepByStepExample = "Array: [5, 4, 3, 1]\nTake 4: [5, 4, ...] -> 4 < 5 -> [4, 5, 3, 1]\nTake 3: [4, 5, 3, ...] -> 3 < 5, 3 < 4 -> [3, 4, 5, 1]\nTake 1: insert at front -> [1, 3, 4, 5]";
            }
            details.cppCode = "void insertionSort(std::vector<int>& arr) {\n"
                              "    for (size_t i = 1; i < arr.size(); ++i) {\n"
                              "        int key = arr[i];\n"
                              "        int j = i - 1;\n"
                              "        while (j >= 0 && arr[j] > key) {\n"
                              "            arr[j + 1] = arr[j];\n"
                              "            j = j - 1;\n"
                              "        }\n"
                              "        arr[j + 1] = key;\n"
                              "    }\n"
                              "}";
        }
        else if (algoName == "Merge Sort") {
            if (lang == sv::core::Language::PL) {
                details.description = "Algorytm oparty na paradygmacie 'dziel i rzadz'. Rekurencyjnie dzieli tablice na dwie polowy, az do pojedynczych elementow, a nastepnie scala (merge) je w jedna posortowana calosc.";
                details.bestCase = "O(n log n)";
                details.averageCase = "O(n log n)";
                details.worstCase = "O(n log n) - zlozonosc jest gwarantowana niezaleznie od danych.";
                details.pros = "Stabilny (zachowuje kolejnosc rownych elementow), bardzo przewidywalny.";
                details.cons = "Wymaga dodatkowej pamieci O(n) na tablice pomocnicze.";
                details.useCases = "Sortowanie list powiazanych (linked lists), systemy wymagajace stabilnosci (np. sortowanie bazy danych po kilku kolumnach).";
                details.stepByStepExample = "Tablica: [38, 27, 43, 3]\n"
                                            "Podzial 1: [38, 27] oraz [43, 3]\n"
                                            "Podzial 2: [38], [27], [43], [3]\n"
                                            "Scalanie 1: [27, 38] oraz [3, 43]\n"
                                            "Scalanie 2 (Final): [3, 27, 38, 43]";
            } else {
                details.description = "A Divide and Conquer algorithm. It divides input array in two halves, calls itself for the two halves and then merges the two sorted halves.";
                details.bestCase = "O(n log n)";
                details.averageCase = "O(n log n)";
                details.worstCase = "O(n log n) - guaranteed complexity.";
                details.pros = "Stable sort, guaranteed O(n log n) performance.";
                details.cons = "Requires O(n) extra space.";
                details.useCases = "Sorting linked lists, situations where stable sort is required.";
                details.stepByStepExample = "Array: [38, 27, 43, 3]\nSplit 1: [38, 27] and [43, 3]\nSplit 2: [38], [27], [43], [3]\nMerge 1: [27, 38] and [3, 43]\nMerge 2 (Final): [3, 27, 38, 43]";
            }
            details.cppCode = "// Wersja Rekurencyjna (Recursive)\n"
                              "void merge(std::vector<int>& arr, int l, int m, int r) {\n"
                              "    std::vector<int> L(arr.begin() + l, arr.begin() + m + 1);\n"
                              "    std::vector<int> R(arr.begin() + m + 1, arr.begin() + r + 1);\n"
                              "    int i = 0, j = 0, k = l;\n"
                              "    while (i < L.size() && j < R.size()) {\n"
                              "        if (L[i] <= R[j]) arr[k++] = L[i++];\n"
                              "        else arr[k++] = R[j++];\n"
                              "    }\n"
                              "    while (i < L.size()) arr[k++] = L[i++];\n"
                              "    while (j < R.size()) arr[k++] = R[j++];\n"
                              "}\n\n"
                              "void mergeSort(std::vector<int>& arr, int l, int r) {\n"
                              "    if (l >= r) return;\n"
                              "    int m = l + (r - l) / 2;\n"
                              "    mergeSort(arr, l, m);\n"
                              "    mergeSort(arr, m + 1, r);\n"
                              "    merge(arr, l, m, r);\n"
                              "}";
        }
        else if (algoName == "Quick Sort") {
            if (lang == sv::core::Language::PL) {
                details.description = "Algorytm 'dziel i rzadz'. Wybiera element (pivot) i dzieli tablice tak, by elementy mniejsze byly po lewej, a wieksze po prawej stronie pivota. Nastepnie rekurencyjnie sortuje obie polowy.";
                details.bestCase = "O(n log n) - pivot zawsze dzieli tablice idealnie na pol.";
                details.averageCase = "O(n log n)";
                details.worstCase = "O(n^2) - najgorszy pivot (np. pierwszy element z juz posortowanej tablicy).";
                details.pros = "Dziala in-place (bez dodatkowej pamieci). Bardzo niska stala ukryta w Big O - w praktyce najszybszy ogolny algorytm.";
                details.cons = "Niestabilny. Ryzyko degradacji do O(n^2) jesli zle dobierze sie pivota.";
                details.useCases = "Standardowy algorytm w wiekszosci bibliotek jezykowych (np. C++ std::sort to zazwyczaj Introsort lub wariacja QuickSort).";
                details.stepByStepExample = "Tablica: [10, 80, 30, 90, 40, 50, 70]\n"
                                            "Wybieramy Pivot = 70.\n"
                                            "Przenosimy mniejsze od 70 na lewo: [10, 30, 40, 50]\n"
                                            "Przenosimy wieksze na prawo: [80, 90]\n"
                                            "Pivot ląduje w środku: [10, 30, 40, 50,  70,  80, 90]\n"
                                            "Teraz 70 jest na idealnej pozycji. Powtarzamy dla lewej i prawej strony.";
            } else {
                details.description = "Divide and Conquer algorithm. Picks an element as pivot and partitions the given array around the picked pivot.";
                details.bestCase = "O(n log n) - pivot always divides array in half.";
                details.averageCase = "O(n log n)";
                details.worstCase = "O(n^2) - worst pivot choice (e.g. sorted array).";
                details.pros = "In-place sorting. Very small hidden constant - extremely fast in practice.";
                details.cons = "Not stable. Risk of O(n^2) worst case.";
                details.useCases = "Standard system sorting (like std::sort in C++).";
                details.stepByStepExample = "Array: [10, 80, 30, 90, 40, 50, 70]\nPivot = 70.\nSmaller to left: [10, 30, 40, 50]\nGreater to right: [80, 90]\nPivot in middle: [10, 30, 40, 50,  70,  80, 90]\n70 is now fully sorted. Repeat for left/right subsets.";
            }
            details.cppCode = "// Wersja Rekurencyjna z podziałem Lomuto\n"
                              "int partition(std::vector<int>& arr, int low, int high) {\n"
                              "    int pivot = arr[high]; // pivot na koncu\n"
                              "    int i = (low - 1);\n"
                              "    for (int j = low; j <= high - 1; j++) {\n"
                              "        if (arr[j] < pivot) {\n"
                              "            i++;\n"
                              "            std::swap(arr[i], arr[j]);\n"
                              "        }\n"
                              "    }\n"
                              "    std::swap(arr[i + 1], arr[high]);\n"
                              "    return (i + 1);\n"
                              "}\n\n"
                              "void quickSort(std::vector<int>& arr, int low, int high) {\n"
                              "    if (low < high) {\n"
                              "        int pi = partition(arr, low, high);\n"
                              "        quickSort(arr, low, pi - 1);\n"
                              "        quickSort(arr, pi + 1, high);\n"
                              "    }\n"
                              "}";
        }
        else if (algoName == "Heap Sort") {
            if (lang == sv::core::Language::PL) {
                details.description = "Wykorzystuje strukture danych Kopca (Max-Heap). Najpierw transformuje tablice w kopiec, gdzie najwiekszy element jest na szczycie (indeks 0). Nastepnie zamienia szczyt z koncem tablicy i naprawia kopiec.";
                details.bestCase = "O(n log n)";
                details.averageCase = "O(n log n)";
                details.worstCase = "O(n log n)";
                details.pros = "Gwarantowana szybkosc O(n log n), dziala calkowicie in-place (O(1) pamieci).";
                details.cons = "Niestabilny. Wolniejszy w praktyce niz Quick Sort przez duza ilosc skokow w pamieci (cache misses).";
                details.useCases = "Systemy osadzone (embedded) ze scislymi limitami pamieci.";
                details.stepByStepExample = "Dla: [4, 10, 3, 5, 1]\n1. Budowa Max-Heap: [10, 5, 3, 4, 1]\n2. Zamiana 10 z ostatnim (1) -> [1, 5, 3, 4, | 10]\n3. Naprawa kopca: [5, 4, 3, 1, | 10]\n4. Powtarzamy, az tablica bedzie posortowana.";
            } else {
                details.description = "Uses a Binary Heap data structure. First builds a Max-Heap so the largest item is at index 0. Then swaps the root with the end of the array and restores the heap property.";
                details.bestCase = "O(n log n)";
                details.averageCase = "O(n log n)";
                details.worstCase = "O(n log n)";
                details.pros = "Guaranteed O(n log n) speed, strictly in-place (O(1) extra space).";
                details.cons = "Unstable. Slower in practice than Quick Sort due to cache misses.";
                details.useCases = "Embedded systems with strict memory limits.";
                details.stepByStepExample = "For: [4, 10, 3, 5, 1]\n1. Build Max-Heap: [10, 5, 3, 4, 1]\n2. Swap root (10) with end (1) -> [1, 5, 3, 4, | 10]\n3. Heapify: [5, 4, 3, 1, | 10]\n4. Repeat until sorted.";
            }
            details.cppCode = "void heapify(std::vector<int>& arr, int n, int i) {\n"
                              "    int largest = i;\n"
                              "    int l = 2 * i + 1;\n"
                              "    int r = 2 * i + 2;\n"
                              "    if (l < n && arr[l] > arr[largest]) largest = l;\n"
                              "    if (r < n && arr[r] > arr[largest]) largest = r;\n"
                              "    if (largest != i) {\n"
                              "        std::swap(arr[i], arr[largest]);\n"
                              "        heapify(arr, n, largest);\n"
                              "    }\n"
                              "}\n\n"
                              "void heapSort(std::vector<int>& arr) {\n"
                              "    int n = arr.size();\n"
                              "    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);\n"
                              "    for (int i = n - 1; i > 0; i--) {\n"
                              "        std::swap(arr[0], arr[i]);\n"
                              "        heapify(arr, i, 0);\n"
                              "    }\n"
                              "}";
        }
        else if (algoName == "Counting Sort") {
            if (lang == sv::core::Language::PL) {
                details.description = "Algorytm nieporownawczy. Dziala na liczbach calkowitych. Tworzy tablice pomocnicza, w ktorej zlicza wystapienia kazdej liczby z zakresu od min do max, a potem odtwarza wyniki.";
                details.bestCase = "O(n + k) - gdzie k to zakres liczb (max-min).";
                details.averageCase = "O(n + k)";
                details.worstCase = "O(n + k)";
                details.pros = "Ekstremalnie szybki O(n) dla danych o malym zakresie. Stabilny.";
                details.cons = "Nie dziala dla liczb zmiennoprzecinkowych. Zjada gigantyczne ilosci pamieci jesli roznica miedzy min a max jest wielka (np. tablica [1, 1000000]).";
                details.useCases = "Sortowanie wieku ludzi, ocen z egzaminu (skala 1-100), jako podstawa dla Radix Sort.";
                details.stepByStepExample = "Tablica: [4, 2, 2, 8, 3, 3, 1]\n"
                                            "1. Szukamy Max (K = 8)\n"
                                            "2. Tworzymy tablice Zliczen (Count) wielkosci 9 (od 0 do 8).\n"
                                            "3. Liczymy ile jest kazdej liczby np. dwojki sa 2 razy: Count[2] = 2.\n"
                                            "4. Przepisujemy odpowiednia ilosc jedynek, dwojek, trojek... do nowej tablicy.";
            } else {
                details.description = "A non-comparison algorithm for integers. It counts the number of objects having distinct key values, storing the count in an auxiliary array.";
                details.bestCase = "O(n + k) - where k is the range of numbers.";
                details.averageCase = "O(n + k)";
                details.worstCase = "O(n + k)";
                details.pros = "Extremely fast O(n) for small ranges. Stable sort.";
                details.cons = "Fails on floats. Memory intensive if the range (K) is huge (e.g. array [1, 1000000]).";
                details.useCases = "Sorting human ages, exam scores (1-100), foundation for Radix Sort.";
                details.stepByStepExample = "Array: [4, 2, 2, 8, 3, 3, 1]\n1. Find Max (K = 8)\n2. Create Count array of size 9 (0 to 8).\n3. Count occurrences e.g. two 2s: Count[2] = 2.\n4. Write the exact number of 1s, 2s, 3s... back to the output array.";
            }
            details.cppCode = "void countingSort(std::vector<int>& arr) {\n"
                              "    if(arr.empty()) return;\n"
                              "    int max_val = *std::max_element(arr.begin(), arr.end());\n"
                              "    std::vector<int> count(max_val + 1, 0);\n"
                              "    std::vector<int> output(arr.size());\n\n"
                              "    for (int num : arr) count[num]++;\n"
                              "    for (int i = 1; i <= max_val; i++) count[i] += count[i - 1];\n\n"
                              "    for (int i = arr.size() - 1; i >= 0; i--) {\n"
                              "        output[count[arr[i]] - 1] = arr[i];\n"
                              "        count[arr[i]]--;\n"
                              "    }\n"
                              "    arr = output;\n"
                              "}";
        }
        else if (algoName == "Binary Search") {
            if (lang == sv::core::Language::PL) {
                details.description = "Ekstremalnie szybki algorytm wyszukiwania. Wymaga POSORTOWANEJ tablicy. Sprawdza element w samym srodku przedzialu - jezeli jest mniejszy niz szukany, odrzuca cala lewa polowe.";
                details.bestCase = "O(1) - szukany element lezy dokladnie po srodku.";
                details.averageCase = "O(log n)";
                details.worstCase = "O(log n) - element na koncu lub nie istnieje.";
                details.pros = "Ucina przestrzen poszukiwan o polowe (logarytmiczna predkosc). 1 milion elementow to max 20 sprawdzen.";
                details.cons = "Bezposortowanych danych jest bezuzyteczny. Posortowanie przed uzyciem kosztuje O(n log n).";
                details.useCases = "Szukanie indeksu w duzych bazach SQL, sprawdzanie czy slowo istnieje w slowniku.";
                details.stepByStepExample = "Szukamy liczby 23 w: [2, 5, 8, 12, 16, 23, 38, 56, 72, 91]\n"
                                            "Krok 1: Srodek to 16. Nasze 23 > 16, wiec odrzucamy lewa polowe.\n"
                                            "Szukamy w prawej: [23, 38, 56, 72, 91]\n"
                                            "Krok 2: Srodek to 56. Nasze 23 < 56, odrzucamy prawa polowe.\n"
                                            "Szukamy w: [23, 38]\n"
                                            "Krok 3: Znaleziono 23!";
            } else {
                details.description = "Extremely fast search algorithm. Requires a SORTED array. Compares the middle element - if it's smaller than target, the entire left half is discarded.";
                details.bestCase = "O(1) - target is exactly in the middle.";
                details.averageCase = "O(log n)";
                details.worstCase = "O(log n) - target at ends or missing.";
                details.pros = "Halves the search space every step. Searching 1 million items takes at most 20 checks.";
                details.cons = "Useless on unsorted data. Sorting first costs O(n log n).";
                details.useCases = "SQL database indexing, dictionary lookups.";
                details.stepByStepExample = "Target 23 in: [2, 5, 8, 12, 16, 23, 38, 56, 72, 91]\nStep 1: Mid is 16. 23 > 16, discard left half.\nSearch in: [23, 38, 56, 72, 91]\nStep 2: Mid is 56. 23 < 56, discard right half.\nSearch in: [23, 38]\nStep 3: Found 23!";
            }
            details.cppCode = "// Wersja Iteracyjna\n"
                              "int binarySearch(const std::vector<int>& arr, int target) {\n"
                              "    int low = 0;\n"
                              "    int high = arr.size() - 1;\n"
                              "    while (low <= high) {\n"
                              "        int mid = low + (high - low) / 2;\n"
                              "        if (arr[mid] == target) return mid;\n"
                              "        if (arr[mid] < target) low = mid + 1;\n"
                              "        else high = mid - 1;\n"
                              "    }\n"
                              "    return -1; // Nie znaleziono\n"
                              "}";
        }
        else if (algoName == "Sieve of Eratosthenes") {
            if (lang == sv::core::Language::PL) {
                details.description = "Matematyczny algorytm sluzacy do znajdowania wszystkich liczb pierwszych w zadanym przedziale [2, N]. Tworzy tablice i sukcesywnie 'wykresla' wielokrotnosci kolejnych liczb pierwszych.";
                details.bestCase = "O(n log log n) - bardzo bliskie O(n) w liniowej predkosci.";
                details.averageCase = "O(n log log n)";
                details.worstCase = "O(n log log n)";
                details.pros = "Niezwykle szybki sposob na masowe wygenerowanie liczb pierwszych.";
                details.cons = "Kosztowny pod wzgledem pamieci dla bardzo wielkiego N (tablica wielkosci N).";
                details.useCases = "Kryptografia (np. algorytm RSA wymaga szybkich liczb pierwszych), zadania matematyczne.";
                details.stepByStepExample = "Generujemy liczby pierwsze do 20.\n"
                                            "1. Tworzymy liste: 2, 3, 4, 5, ... 20.\n"
                                            "2. Pierwsza liczba to 2. Wykreslamy jej wielokrotnosci: 4, 6, 8, 10, 12, 14, 16, 18, 20.\n"
                                            "3. Nastepna nieskreslona to 3. Wykreslamy wielokrotnosci: 9, 15 (6, 12, 18 juz skreslone).\n"
                                            "4. Wynik: zostaja tylko zielone liczby pierwsze (2, 3, 5, 7, 11, 13, 17, 19).";
            } else {
                details.description = "A mathematical algorithm to find all prime numbers up to any given limit [2, N]. It iteratively marks the multiples of each prime starting from 2 as composite (not prime).";
                details.bestCase = "O(n log log n) - practically linear.";
                details.averageCase = "O(n log log n)";
                details.worstCase = "O(n log log n)";
                details.pros = "Extremely fast way to generate a massive list of primes.";
                details.cons = "High memory cost for very large N.";
                details.useCases = "Cryptography (e.g. RSA requires prime numbers), number theory tasks.";
                details.stepByStepExample = "Primes up to 20.\n1. List: 2, 3, 4, 5, ... 20.\n2. Start at 2. Cross out its multiples: 4, 6, 8, 10, 12, 14, 16, 18, 20.\n3. Next available is 3. Cross out multiples: 9, 15.\n4. Result: remaining numbers are prime.";
            }
            details.cppCode = "void sieve(int n) {\n"
                              "    std::vector<bool> isPrime(n + 1, true);\n"
                              "    isPrime[0] = false; isPrime[1] = false;\n\n"
                              "    for (int p = 2; p * p <= n; p++) {\n"
                              "        if (isPrime[p]) {\n"
                              "            // Wykreslamy wielokrotnosci\n"
                              "            for (int i = p * p; i <= n; i += p) {\n"
                              "                isPrime[i] = false;\n"
                              "            }\n"
                              "        }\n"
                              "    }\n"
                              "    // W isPrime znajduja sie teraz same liczby pierwsze\n"
                              "}";
        }

        return details;
    }

}