#pragma once

#include "HelperFA.hpp"

namespace sb {

    template<C_FA OutFA, C_FA InFA>
    OutFA determineNFA(const InFA& inFA);

/// Realization

    template<C_FA OutFA, C_FA InFA>
    T_FAPtrSt<OutFA> detDFS(
        SetCFA<InFA>&& state,
        Set2StFA<InFA, OutFA>& visits,
        OutFA& outFA
        ) {
        using Type = T_FATy<OutFA>;
        using Letter = T_FALe<OutFA>;
        
        if (visits.count(state)) { 
            return visits.at(state);
        }
        
        Le2SetCFA<InFA> nextStates;
        
        Type type = Type();
        
        for (auto& inState: state) {
            type |= inState->type();
            for (auto& trans: inState->trans()) {
                if (!nextStates.count(trans.first)) {
                    nextStates.emplace(
                        trans.first,
                        SetCFA<InFA>()
                    );
                }
                nextStates.at(trans.first).emplace(
                    trans.second
                );
            }
        }

        auto stateOutFA = outFA.emplace(type);
        visits.emplace(std::move(state), stateOutFA);

        for (auto& [letter, nextState]: nextStates) {
            T_FAPtrSt<OutFA> next = 
            detDFS<OutFA, InFA>(
                std::move(nextState),
                visits,
                outFA
            );
            stateOutFA->emplace(letter, next);
        }
        return stateOutFA;
    }

    template<C_FA OutFA, C_FA InFA>
    OutFA determineNFA(const InFA& inFA) {
        OutFA outFA;

        Set2StFA<InFA, OutFA> visits;
        SetCFA<InFA> startState;

        startState.emplace(inFA.begin());
        detDFS<OutFA, InFA>(
            std::move(startState),
            visits,
            outFA
        );
    
        return outFA;
    };

    
} // namespace sb