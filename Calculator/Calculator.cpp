#include "stdafx.h"
#include "Calculator.h"


Calculator::Action Calculator::getLastInput()
{
	return m_actions.size() <= 0 ? Action{ActionType::None, 0.0} : m_actions.back();
}

void Calculator::reset()
{
	m_leftExpression.reset();
	m_leftTerm.reset();
	m_actions.clear();
}

bool Calculator::isOperation(ActionType action)
{
	return (action == ActionType::Plus || action == ActionType::Minus ||
		action == ActionType::Multiply || action == ActionType::Divide ||
		action == ActionType::Equals);
}

bool Calculator::isTerm(ActionType action)
{
	return (action == ActionType::Multiply || action == ActionType::Divide);
}

bool Calculator::isExpression(ActionType action)
{
	return (action == ActionType::Plus || action == ActionType::Minus);
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

double Calculator::getCurrentResult()
{
	return m_leftExpression.hasValue() ? m_leftExpression.getValue() : m_leftTerm.getValue();
}

// Logic: 
// - If it is a number then just add it to the actions vector (but adding two
// times a number is not allowed as "3 4 6 =" is not a correct syntax. "3 + 6 =" would be correct.)
// - If it is an operation (like "3+4-") then do the operation with the operation before that
// ("3+4" in the example) and add it to "left expression" (m_leftExpression).
// - "=" and "None" as an operation means that a totally new calculation started from there,
// meaning that the first number after them are just assigned to "left expression" (m_leftExpression).
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
				if (isExpression(input.actionType) || input.actionType == ActionType::Equals)
				{
					m_leftExpression.add(lastInput.value, input.actionType);
					m_leftTerm.reset();
				}
				else if (isTerm(input.actionType))
				{
					m_leftTerm.set(lastInput.value, input.actionType);
				}
				break;
			case ActionType::Minus:
				if (isExpression(input.actionType) || input.actionType == ActionType::Equals)
				{
					m_leftExpression.add(-lastInput.value, input.actionType);
					m_leftTerm.reset();
				}
				else if (isTerm(input.actionType))
				{
					m_leftTerm.set(-lastInput.value, input.actionType);
				}

				break;
			case ActionType::Multiply:
				{
					if (isExpression(input.actionType) || input.actionType == ActionType::Equals)
					{
						m_leftExpression.add(m_leftTerm.getValue() * lastInput.value, input.actionType);
						m_leftTerm.reset();
					}
					else if (isTerm(input.actionType))
						m_leftTerm.multiplyBy(lastInput.value, input.actionType);
				}
				break;
			case ActionType::Divide:
			{
				if (isExpression(input.actionType) || input.actionType == ActionType::Equals)
				{
					m_leftExpression.add(m_leftTerm.getValue() / lastInput.value, input.actionType);
					m_leftTerm.reset();
				}
				else if (isTerm(input.actionType))
					m_leftTerm.multiplyBy(1.0 / lastInput.value, input.actionType);
			}
			break;
			case ActionType::Equals: // "=" is the start of a new beginnning, see (h: *)
				{
				if (isTerm(input.actionType))
				{
					m_leftExpression.reset();
					m_leftTerm.set(lastInput.value, input.actionType);
				}
				else if (isExpression(input.actionType))
				{
					m_leftExpression.set(lastInput.value, input.actionType);
					m_leftTerm.reset();
				}
				}
 
				break;
			case ActionType::None: // "None" is the start of a new beginnning, see (h: *)
				{
				if (isTerm(input.actionType))
				{
					m_leftExpression.reset();
					m_leftTerm.set(lastInput.value, input.actionType);
				}
				else if (isExpression(input.actionType))
				{
					m_leftExpression.set(lastInput.value, input.actionType);
					m_leftTerm.reset();
				}
				}
				break;
			}
			m_actions.push_back(input);
			return true;
		}
	}
	return false;
}