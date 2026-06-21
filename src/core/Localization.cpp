#include "sv/core/Localization.hpp"

namespace sv::core {

    Language Localization::s_currentLanguage = Language::PL;

    const std::unordered_map<std::string, std::unordered_map<Language, std::string>> Localization::s_dict = {
        {"window_main", { {Language::PL, "Panel Wizualizacji"}, {Language::EN, "Visualization Panel"} }},
        {"window_db", { {Language::PL, "Baza Danych (Historia)"}, {Language::EN, "Database (History)"} }},
        {"combo_algo", { {Language::PL, "Wybierz algorytm"}, {Language::EN, "Select algorithm"} }},
        {"btn_start", { {Language::PL, "Start / Wznow"}, {Language::EN, "Start / Resume"} }},
        {"btn_pause", { {Language::PL, "Pauza"}, {Language::EN, "Pause"} }},
        {"btn_reset", { {Language::PL, "Reset"}, {Language::EN, "Reset"} }},
        {"lbl_active", { {Language::PL, "Aktywny"}, {Language::EN, "Active"} }},
        {"lbl_complexity", { {Language::PL, "Zlozonosc (Srednia)"}, {Language::EN, "Complexity (Avg)"} }},
        {"lbl_comparisons", { {Language::PL, "Porownania"}, {Language::EN, "Comparisons"} }},
        {"lbl_swaps", { {Language::PL, "Zamiany"}, {Language::EN, "Swaps"} }},
        {"btn_del_last", { {Language::PL, "Usun ostatni"}, {Language::EN, "Delete last"} }},
        {"btn_clear_all", { {Language::PL, "Wyczysc wszystko"}, {Language::EN, "Clear all"} }},
        {"tbl_algo", { {Language::PL, "Algorytm"}, {Language::EN, "Algorithm"} }},
        {"tbl_time", { {Language::PL, "Czas"}, {Language::EN, "Time"} }},
        {"input_target", { {Language::PL, "Szukana wartosc"}, {Language::EN, "Target value"} }},
        {"input_limit", { {Language::PL, "Gorna granica (max)"}, {Language::EN, "Upper limit (max)"} }},
        {"msg_found", { {Language::PL, "Znaleziono na indeksie"}, {Language::EN, "Found at index"} }},
        {"msg_not_found", { {Language::PL, "Nie znaleziono wartosci!"}, {Language::EN, "Value not found!"} }}
    };

    void Localization::setLanguage(Language lang) {
        s_currentLanguage = lang;
    }

    Language Localization::getLanguage() {
        return s_currentLanguage;
    }

    std::string Localization::tr(const std::string& key) {
        auto it = s_dict.find(key);
        if (it != s_dict.end()) {
            return it->second.at(s_currentLanguage);
        }
        return key; // Zwraca klucz, jeśli nie znaleziono tłumaczenia
    }

}