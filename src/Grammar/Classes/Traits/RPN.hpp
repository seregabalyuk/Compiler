#pragma once

#include <type_traits>

#include <Base/Traits/DeclVal.hpp>

namespace sb {
	template<class Table, class Letter>
    struct T_TableRPN;
	// have
		// Rule
		// Type
		// Priority
	//

	template<class Table, class Letter>
	using T_TableRPNR = typename T_TableRPN<Table, Letter>::Rule;
	template<class Table, class Letter>
	using T_TableRPNT = typename T_TableRPN<Table, Letter>::Type;
	template<class Table, class Letter>
	using T_TableRPNP = typename T_TableRPN<Table, Letter>::Priority;
	

	template<class Rule>
    struct T_TableRPNRule;
	// have
		// Type
		// Priority
	// 

	template<class Creator>
	struct T_CreatorRPN;
	// have
		// T
	//

	template<class Creator>
	using T_CreatorRPNT = typename T_CreatorRPN<Creator>::T;
// realization
  // T_TableRPNRule
   // local
	template<class Rule>
	concept lC_T_TableRPNRule = 
	requires(const Rule rule) {
		rule.type();
		rule.priority();
	};

	template<class Rule, bool isRule>
	struct lT_TableRPNRule {
		using Type = void;
		using Priority = void;
	};

	template<class Rule>
	struct lT_TableRPNRule<Rule, 1> {
		using Type = std::remove_cvref_t<
			decltype(DeclLVal<const Rule>().type())
		>;
		using Priority = std::remove_cvref_t<
			decltype(DeclLVal<const Rule>().priority())
		>;
	};
   // global
	template<class Rule>
    class T_TableRPNRule {
		using _Traits = lT_TableRPNRule<
			Rule,
			lC_T_TableRPNRule<Rule>
		>;
	public:
		using Type = typename _Traits::Type;
		using Priority = typename _Traits::Priority;
	};
  // T_TableRPN
   // local
	template<class Table, class Letter>
	concept lC_T_TableRPN = 
	requires(const Table table, const Letter letter) {
		table.get(letter);
	};

	template<class Table, class Letter, bool isTable>
	struct lT_TableRPN {
		using Rule = void;
	};

	template<class Table, class Letter>
	struct lT_TableRPN<Table, Letter, 1> {
		using Rule = std::remove_cvref_t<
			decltype(
				DeclLVal<const Table>().get(
					DeclLVal<const Letter>()
				)
			)
		>;
	};
   // global
	template<class Table, class Letter>
    class T_TableRPN {
		using _Traits = lT_TableRPN<
			Table,
			Letter,
			lC_T_TableRPN<
				Table,
				Letter
			>
		>;
	public:
		using Rule = typename _Traits::Rule;
		using Type = typename T_TableRPNRule<Rule>::Type;
		using Priority = typename T_TableRPNRule<Rule>::Priority;
	};
  // T_CreatorRPN
   // local
	template<class Creator>
	concept lC_T_CreatorRPN = 
	requires(Creator creator) {
		creator.get();
	};

	template<class Creator, bool isCreator>
	struct lT_CreatorRPN {
		using T = void;
	};

	template<class Creator>
	struct lT_CreatorRPN<Creator, 1> {
		using T = std::remove_cvref_t<
			decltype(DeclLVal<Creator>().get())
		>;
	};
   // global
	template<class Creator>
    class T_CreatorRPN {
		using _Traits = lT_CreatorRPN<
			Creator,
			lC_T_CreatorRPN<Creator>
		>;
	public:
		using T = typename _Traits::T;
	};
} // namespace sb