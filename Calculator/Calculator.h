#pragma once
#include <vector>

class Calculator
{
public:
	// ActionType: what has been entered from the calculator
	enum class ActionType : char {Number, Plus, Minus, Multiply, Divide, Equals, None};
	struct Action
	{
		ActionType actionType;
		double value;
	};

	void reset();
	bool addInput(const Action& input);
	Action getLastInput();
	double getLeftExpression() { return m_leftExpression; }
	bool isOperation(ActionType action);
	// actions
	int getActionsSize() { return m_actions.size(); }
	const Action& getAction(int i) { return m_actions.at(i);  }
private:
	ActionType getLastOperation();
	std::vector<Action> m_actions;
	// m_leftExpression is always the left hand side of the expression. An example:
	// 5 -> m_leftExpression = 5 (*)
	// 5 + 3 + -> m_leftExpression = 8
	// 5 + 3 + 1 = -> m_leftExpression = 9
	// 5 + 3 + 1 = 9 + -> m_leftExpression = 9 (here "=" the user must add 9
	// before using "+" becouse "=" "resets" the calculations and they must
	// start from the beginning, meaning a number is entered first).
	// So "=" and "None" (see (*)) are the start or the calculations.
	double m_leftExpression = 0.0;
};
