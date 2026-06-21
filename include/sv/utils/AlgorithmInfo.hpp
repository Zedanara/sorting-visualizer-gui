#pragma once
#include <string>
#include "sv/core/Localization.hpp"

namespace sv::utils {

    struct AlgoDetails {
        std::string description;
        std::string bestCase;
        std::string averageCase;
        std::string worstCase;
        std::string pros;
        std::string cons;
        std::string useCases;
        std::string stepByStepExample;
        std::string cppCode;
    };

    class AlgorithmInfo {
    public:
        static AlgoDetails getDetails(const std::string& algoName, sv::core::Language lang);
    };

}