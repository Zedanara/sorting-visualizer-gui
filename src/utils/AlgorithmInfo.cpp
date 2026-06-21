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
                details.useCases = "Wylacznie edukacyjne, sporadycznie do malych zbiorow, gdy pamiec jest krytyczna.";
            } else {
                details.description = "A simple sorting algorithm that repeatedly steps through the list, compares adjacent elements and swaps them if they are in the wrong order.";
                details.bestCase = "O(n) - when array is already sorted.";
                details.averageCase = "O(n^2)";
                details.worstCase = "O(n^2) - reverse sorted array.";
                details.pros = "Simple to implement, in-place sorting.";
                details.cons = "Very slow for large datasets.";
                details.useCases = "Educational purposes only, rarely for very small datasets.";
            }
        }
        else if (algoName == "Merge Sort") {
            if (lang == sv::core::Language::PL) {
                details.description = "Algorytm oparty na paradygmacie 'dziel i rzadz'. Dzieli tablice na dwie polowy, sortuje je rekurencyjnie, a nastepnie scala (merge) w jedna posortowana calosc.";
                details.bestCase = "O(n log n)";
                details.averageCase = "O(n log n)";
                details.worstCase = "O(n log n) - zlozonosc jest gwarantowana.";
                details.pros = "Stabilny, gwarantowana zlozonosc O(n log n).";
                details.cons = "Wymaga dodatkowej pamieci O(n) na tablice pomocnicze.";
                details.useCases = "Sortowanie duzych zbiorow danych (np. w bazach danych), sortowanie list powiazanych.";
            } else {
                details.description = "A Divide and Conquer algorithm. It divides input array in two halves, calls itself for the two halves and then merges the two sorted halves.";
                details.bestCase = "O(n log n)";
                details.averageCase = "O(n log n)";
                details.worstCase = "O(n log n) - guaranteed complexity.";
                details.pros = "Stable sort, guaranteed O(n log n) performance.";
                details.cons = "Requires O(n) extra space.";
                details.useCases = "Sorting large datasets, database implementations, sorting linked lists.";
            }
        }
        else if (algoName == "Quick Sort") {
            if (lang == sv::core::Language::PL) {
                details.description = "Algorytm 'dziel i rzadz'. Wybiera element (pivot) i dzieli tablice tak, by elementy mniejsze byly po lewej, a wieksze po prawej stronie pivota.";
                details.bestCase = "O(n log n) - pivot zawsze dzieli tablice na pol.";
                details.averageCase = "O(n log n)";
                details.worstCase = "O(n^2) - najgorszy pivot (np. tablica juz posortowana).";
                details.pros = "Bardzo szybki w praktyce (niska stala), dziala in-place.";
                details.cons = "Niestabilny, podatny na degradacje do O(n^2) w zlych warunkach.";
                details.useCases = "Standardowy algorytm w wielu bibliotekach systemowych (np. std::sort w C++ czesto uzywa jego wariantu).";
            } else {
                details.description = "Divide and Conquer algorithm. Picks an element as pivot and partitions the given array around the picked pivot.";
                details.bestCase = "O(n log n) - pivot always divides array in half.";
                details.averageCase = "O(n log n)";
                details.worstCase = "O(n^2) - worst pivot choice.";
                details.pros = "Very fast in practice, in-place sorting.";
                details.cons = "Not stable, worst-case O(n^2).";
                details.useCases = "Standard system sorting (like std::sort in C++).";
            }
        }
        else if (algoName == "Binary Search") {
            if (lang == sv::core::Language::PL) {
                details.description = "Szybki algorytm wyszukiwania, ktory sprawdza srodkowy element POSORTOWANEJ tablicy i odrzuca polowe przedzialu, w ktorej na pewno nie ma szukanej wartosci.";
                details.bestCase = "O(1) - element jest dokladnie na srodku.";
                details.averageCase = "O(log n)";
                details.worstCase = "O(log n)";
                details.pros = "Ekstremalnie szybki dla duzych posortowanych kolekcji.";
                details.cons = "Wymaga uprzednio posortowanych danych.";
                details.useCases = "Wyszukiwanie w bazach danych, slownikach, systemach gdzie dane zmieniaja sie rzadko, a szuka sie czesto.";
            } else {
                details.description = "A fast search algorithm that finds the position of a target value within a SORTED array by halving the search interval.";
                details.bestCase = "O(1) - element is exactly in the middle.";
                details.averageCase = "O(log n)";
                details.worstCase = "O(log n)";
                details.pros = "Extremely fast for large sorted collections.";
                details.cons = "Requires data to be already sorted.";
                details.useCases = "Database lookups, dictionaries, read-heavy systems.";
            }
        }
        else {
            // Domyślny tekst dla nieopisanych jeszcze algorytmów (np. Heap, Counting, Insertion, Sito)
            if (lang == sv::core::Language::PL) {
                details.description = "Opis tego algorytmu w krotce zostanie dodany.";
                details.bestCase = "Zalezy od algorytmu";
                details.averageCase = "Zalezy od algorytmu";
                details.worstCase = "Zalezy od algorytmu";
                details.pros = "Brak danych";
                details.cons = "Brak danych";
                details.useCases = "Brak danych";
            } else {
                details.description = "Description for this algorithm will be added soon.";
                details.bestCase = "Algorithm specific";
                details.averageCase = "Algorithm specific";
                details.worstCase = "Algorithm specific";
                details.pros = "No data";
                details.cons = "No data";
                details.useCases = "No data";
            }
        }

        return details;
    }

}