#include <CommunicationParameters.h>
#include <iostream>

void CommunicationParameters::printCurrentParameters()
{
	for (auto &[key, val] : mParameters)
	{
		if (val.type() == typeid(int))
			std::cout << "[" << key <<  " - int type]: " << std::any_cast<int>(val) << "\n";
		else if (val.type() == typeid(std::string))
			std::cout << "[" << key << " - string type]: " << std::any_cast<std::string>(val) << "\n";
		else if (val.type() == typeid(float))
			std::cout << "[" << key << " - float type]: " << std::any_cast<float>(val) << "\n";
		else if (val.type() == typeid(double))
			std::cout << "[" << key << " - double type]: " << std::any_cast<float>(val) << "\n";
		else if (val.type() == typeid(bool))
			std::cout << "[" << key << " - bool type]: " << std::any_cast<float>(val) << "\n";
		else
			std::cout << "[" << key << " - unexpected type]!" << "\n";
	}
}

void CommunicationParameters::updateParameterValue(const std::string& paramName, const std::any& paramValue)
{
	mParameters[paramName] = paramValue;
}

std::optional<std::any> CommunicationParameters::getParameterValue(const std::string& paramName)
{
	std::optional<std::any> parameterValue;

	if (auto itr = mParameters.find(paramName); itr != mParameters.end())
		parameterValue = itr->second;

	return parameterValue;
}
