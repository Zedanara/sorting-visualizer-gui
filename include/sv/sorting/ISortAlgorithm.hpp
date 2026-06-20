#pragma once

#include <vector>
#include <utility>
#include <string>

namespace sv::sorting {

    // Interfejs bazowy dla wszystkich algorytmow sortowania.
    // Wykorzystuje model krokowy (step-based) do wizualizacji bez blokowania watku UI.
    class ISortAlgorithm {
    public:
        // Wirtualny destruktor - konieczny w klasach bazowych w C++
        virtual ~ISortAlgorithm() = default;

        // Inicjalizuje algorytm z poczatkowymi danymi
        virtual void init(std::vector<int> data) = 0;

        // Wykonuje pojedynczy krok algorytmu (np. jedno porownanie lub zamiane).
        // Zwraca false, gdy sortowanie jest zakonczone.
        virtual bool step() = 0;

        // Zwraca aktualny stan tablicy
        virtual const std::vector<int>& getData() const = 0;

        // Zwraca indeksy elementow, ktore aktualnie sa porownywane lub zamieniane (do podswietlenia)
        virtual std::pair<int, int> getHighlightedIndices() const = 0;

        // Zwraca aktualna liczbe porownan
        virtual int getComparisonsCount() const = 0;

        // Zwraca aktualna liczbe zamian (swaps)
        virtual int getSwapsCount() const = 0;

        // Zwraca nazwe algorytmu (np. "Bubble Sort")
        virtual std::string getName() const = 0;

        // Metody zwracajace zlozonosc obliczeniowa (Big O)
        virtual std::string getComplexityBest() const = 0;
        virtual std::string getComplexityAverage() const = 0;
        virtual std::string getComplexityWorst() const = 0;

        // Zwraca true, jesli algorytm zakonczyl sortowanie
        virtual bool isFinished() const = 0;
    };

}