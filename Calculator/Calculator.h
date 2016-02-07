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
	double getCurrentResult();
	bool hasLeftTermValue() { return m_leftTerm.hasValue(); }
	bool hasLeftExpressionValue() { return m_leftExpression.hasValue(); }
	bool isOperation(ActionType action);
	// actions
	int getActionsSize() { return m_actions.size(); }
	const Action& getAction(int i) { return m_actions.at(i);  }
private:
	bool isTerm(ActionType action);
	bool isExpression(ActionType action);
	class LeftExpression
	{
	public:
		void reset();
		void set(double value, ActionType rightOperation);
		void add(double value, ActionType rightOperation);
		double getValue() { return m_value; }
		bool hasValue() { return m_hasValue; }
	private:
		bool m_hasValue = false;
		double m_value = 0.0;
		ActionType m_rightOperation = ActionType::None;
	};
	class LeftTerm
	{
	public:
		void reset();
		void set(double value, ActionType rightOperation);
		void multiplyBy(double value, ActionType rightOperation);
		double getValue() { return m_value; }
		bool hasValue() { return m_hasValue; }
	private:
		bool m_hasValue = false;
		double m_value;
		ActionType m_rightOperation = ActionType::None;
	};
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
	LeftExpression m_leftExpression;
	LeftTerm m_leftTerm;
};

inline void Calculator::LeftExpression::reset() 
{
	m_hasValue = false;
	m_value = 0.0;
	m_rightOperation = ActionType::None;
}

inline void Calculator::LeftExpression::set(double value, ActionType rightOperation) 
{
	m_value = value;
	m_rightOperation = rightOperation;
	m_hasValue = true;
}

inline void Calculator::LeftExpression::add(double value, ActionType rightOperation)
{
	set(m_value + value, rightOperation);
}

inline void Calculator::LeftTerm::reset() 
{
	m_rightOperation = ActionType::None;
	m_value = 0.0;
	m_hasValue = false;
}

inline void Calculator::LeftTerm::set(double value, ActionType rightOperation) 
{
	m_value = value;
	m_rightOperation = rightOperation;
	m_hasValue = true;
}

inline void Calculator::LeftTerm::multiplyBy(double value, ActionType rightOperation)
{
	set(m_value * value, rightOperation);
}

