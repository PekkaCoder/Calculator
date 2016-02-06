#include "stdafx.h"
#include "Calculator.h"


Calculator::Action Calculator::getLastInput()
{
	return m_actions.size() <= 0 ? Action{ActionType::None, 0.0} : m_actions.back();
}

void Calculator::reset()
{
	m_leftExpression = 0.0;
	m_actions.clear();
}

bool Calculator::isOperation(ActionType action)
{
	return (action == ActionType::Plus || action == ActionType::Minus ||
		action == ActionType::Multiply || action == ActionType::Divide ||
		action == ActionType::Equals);
}

Calculator::ActionType Calculator::getLastOperation()
{
	for (auto op = m_actions.rbegin(); op != m_actions.rend(); ++op)
	{
		if (isOperation(op->actionType))
			return op->actionType;
	}
	return ActionType::None;
}

bool Calculator::addInput(const Action& input)
{
	const Calculator::Action lastInput = getLastInput();

	if (input.actionType == ActionType::Number)
	{
		// adding a number after a number would be an error -> that entry is ignored
		if (lastInput.actionType != ActionType::Number)
			m_actions.push_back(input);
	}
	else if (isOperation(input.actionType))
	{
		if (lastInput.actionType == ActionType::Number)
		{
			ActionType lastOperation = getLastOperation();
			switch (lastOperation)
			{
			case ActionType::Plus:
				m_leftExpression += lastInput.value;
				break;
			case ActionType::Minus:
				m_leftExpression -= lastInput.value;
				break;
			case ActionType::Multiply:
				m_leftExpression *= lastInput.value;
				break;
			case ActionType::Divide:
				m_leftExpression /= lastInput.value;
				break;
			case ActionType::Equals:
				m_leftExpression = lastInput.value; // "=" is the start of a new beginnning, see (h: *)
				break;
			case ActionType::None:
				m_leftExpression = lastInput.value; // "None" is the start of a new beginnning, see (h: *)
				break;
			}
			m_actions.push_back(input);
			return true;
		}
	}
	return false;
}